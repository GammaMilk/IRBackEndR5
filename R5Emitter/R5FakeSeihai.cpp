//
// Created by gaome on 2023/7/21.
//

#include "R5FakeSeihai.h"
#include "../MiddleIR/MiddleIRBrInst.h"
#include "R5Yin.h"
#include "R5Yang.h"
#include "R5Ru.h"
#include "R5Lai.h"

#define SP std::shared_ptr
namespace R5Emitter
{

// virtual register
static inline R5Taichi* V(const string& v, YinType yinType)
{
    return new R5Yin(v, yinType);
}
// label
static inline R5Taichi* L(const string& l)
{
    return new R5Ru(l);
}
// immediate
static inline R5Taichi* N(int v)
{
    return new R5Lai(v);
}

// Basic Block Name
static inline string BN(const string& funcName, const string& bbName)
{
    return "." + funcName + "_" + bbName;
}

inline string R5FakeSeihai::E()
{
    return "%_t" + std::to_string(extTempVarNum++);
}
R5FakeSeihai::R5FakeSeihai(const shared_ptr<MiddleIRFuncDef>& funcDef)
    : thisFunc(funcDef)
{
}
void R5FakeSeihai::emitFakeSeihai()
{
    this->bbNames.clear();
    this->extTempVarNum = 0;
    this->blockStrangeFake.clear();
    for (const auto& bb : thisFunc->getBasicBlocks()) {
        bbNames.emplace_back(BN(thisFunc->getName(), bb->getName()));
        emitBB(bb);
    }
}
static inline void S(R5Taichi*& a, R5Taichi*& b)
{
    auto tmp = a;
    a        = b;
    b        = tmp;
}
#pragma clang diagnostic push
#pragma ide diagnostic   ignored "modernize-use-emplace"

void R5FakeSeihai::emitBB(const shared_ptr<MiddleIRBasicBlock>& bb)
{
    // 全部装填，包括终结符！
    std::list<SP<MiddleIRInst>> instructions = bb->_instructions;
    instructions.emplace_back(bb->getTerminator());

    vector<R5AsmStrangeFake> sf;
    auto                     it1 = instructions.begin();
    auto                     it2 = instructions.begin();
    it2++;
    auto moveNext = [&]() {
        it1++;
        it2++;
    };
    for (; it2 != instructions.end(); moveNext()) {
        auto inst1 = *it1;
        auto inst2 = *it2;
        if (inst1->isAllocaInst()) {
            continue;
        }
        // Int Math
        else if (inst1->isMathInst()) {
            // only INT, float will be handled later in isFMathInst()
            auto      math    = dynamic_pointer_cast<IMathInst>(inst1);
            auto      iMathOp = math->getIMathOp();
            R5Taichi* taichi1;
            R5Taichi* taichi2;
            R5Taichi* rd;
            auto      op1 = math->getOpVal1();
            if (op1->isConst())
                taichi1 = N(dynamic_pointer_cast<R5IRValConstInt>(op1)->getValue());   // const LAI
            else
                taichi1 = V(op1->getName(), YinType::Int);                             // var YIN
            auto op2 = math->getOpVal2();
            if (op2->isConst())
                taichi2 = N(dynamic_pointer_cast<R5IRValConstInt>(op2)->getValue());
            else
                taichi2 = V(op2->getName(), YinType::Int);
            bool isI = (taichi1->isLai() || taichi2->isLai());
            rd       = V(math->getName(), Int);
            FakeOPs op;
            switch (iMathOp) {

            case IMathInst::IMathOp::ADD: {
                op = isI ? FakeOPs::ADDIW : FakeOPs::ADDW;
                if (taichi1->isLai()) S(taichi1, taichi2);
                sf.emplace_back(R5AsmStrangeFake(op, {rd, taichi1, taichi2}));
            } break;

            case IMathInst::IMathOp::SUB: {
                if (isI) {
                    if (taichi1->isLai()) S(taichi1, taichi2);
                    dynamic_cast<R5Lai*>(taichi2)->negative();
                    op = FakeOPs::ADDIW;
                } else {
                    op = FakeOPs::SUBW;
                }
                sf.emplace_back(R5AsmStrangeFake(op, {rd, taichi1, taichi2}));
            } break;

            case IMathInst::IMathOp::MUL: {
                // 乘法要求两个操作数都是寄存器
                // 不是的话，就要先把立即数装载到寄存器里
                if (taichi1->isLai()) {
                    auto tmp = V(E(), Int);
                    sf.emplace_back(R5AsmStrangeFake(FakeOPs::LI, {tmp, taichi1}));
                    taichi1 = tmp;
                }
                if (taichi2->isLai()) {
                    auto tmp = V(E(), Int);
                    sf.emplace_back(R5AsmStrangeFake(FakeOPs::LI, {tmp, taichi2}));
                    taichi2 = tmp;
                }
                sf.emplace_back(R5AsmStrangeFake(FakeOPs::MULW, {rd, taichi1, taichi2}));
            } break;

            case IMathInst::IMathOp::SDIV: {
                // 除法要求两个操作数都是寄存器
                // 不是的话，就要先把立即数装载到寄存器里
                if (taichi1->isLai()) {
                    auto tmp = V(E(), Int);
                    sf.emplace_back(R5AsmStrangeFake(FakeOPs::LI, {tmp, taichi1}));
                    taichi1 = tmp;
                }
                if (taichi2->isLai()) {
                    auto tmp = V(E(), Int);
                    sf.emplace_back(R5AsmStrangeFake(FakeOPs::LI, {tmp, taichi2}));
                    taichi2 = tmp;
                }
                sf.emplace_back(R5AsmStrangeFake(FakeOPs::DIVW, {rd, taichi1, taichi2}));
            } break;

            case IMathInst::IMathOp::SREM: {
                // 同上。
                if (taichi1->isLai()) {
                    auto tmp = V(E(), Int);
                    sf.emplace_back(R5AsmStrangeFake(FakeOPs::LI, {tmp, taichi1}));
                    taichi1 = tmp;
                }
                if (taichi2->isLai()) {
                    auto tmp = V(E(), Int);
                    sf.emplace_back(R5AsmStrangeFake(FakeOPs::LI, {tmp, taichi2}));
                    taichi2 = tmp;
                }
                sf.emplace_back(R5AsmStrangeFake(FakeOPs::REMW, {rd, taichi1, taichi2}));
            } break;
            case IMathInst::IMathOp::UDIV:
            case IMathInst::IMathOp::UREM: RUNTIME_ERROR("他妈的没有无符号除法和取余");
            }
        }
        // Float Math
        else if (inst1->isFMathInst()) {
            auto fMath = dynamic_pointer_cast<FMathInst>(inst1);
            auto fOp   = fMath->getFMathOp();
            auto op1   = fMath->getOpVal1();
            auto op2   = fMath->getOpVal2();
            auto rd    = V(fMath->getName(), Float);
            // TODO
        }
    }
}

#pragma clang diagnostic pop


}   // namespace R5Emitter
#undef SP