//
// Created by gaome on 2023/7/21.
//

#include "R5FakeSeihai.h"
#include "R5Yin.h"
#include "R5Yang.h"
#include "R5Ru.h"
#include "R5Lai.h"
#include "R5Lai64.h"

#define SP std::shared_ptr
namespace R5Emitter
{

/// 从IR的虚拟寄存器生成一个MIR的虚拟寄存器
/// \param v 名字
/// \param yinType 类型（Float/Int/Pointer）
/// \return 太极
static inline shared_ptr<R5Taichi> V(const string& v, YinType yinType)
{
    return make_shared<R5Yin>(v, yinType);
}


/// 生成一个标签
/// \param l 标签名字
/// \return 太极
static inline shared_ptr<R5Taichi> L(const string& l)
{
    return make_shared<R5Ru>(l);
}

/// 生成一个立即数(32位)
/// \param v 数
/// \return 太极
static inline shared_ptr<R5Taichi> N(int v)
{
    return make_shared<R5Lai>(v);
}

/// 生成一个物理寄存器(Float/Long)
/// \param r r0/r1/r2...
/// \return 太极
static inline shared_ptr<R5Taichi> R(YangReg r)
{
    return make_shared<R5Yang>(r);
}


/// 生成一个立即数(64位)
/// \param v 数
/// \return 太极
static inline shared_ptr<R5Taichi> P(uint64_t v)
{
    return make_shared<R5Lai64>(v);
}

/// 生成一个基本块对应的标签名字
/// \param funcName 函数名字
/// \param bbName 基本块名字
/// \return 生成结果
static inline string BN(const string& funcName, const string& bbName)
{
    return ".LBB_" + funcName + "_" + bbName;
}

/// 生成一个新的虚拟寄存器
/// \return 寄存器的名字
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
    this->taichiMap.clear();
    this->taichiSize = 0;
    LOGD("\nFuncName: " << thisFunc->getName());
    for (const auto& bb : thisFunc->getBasicBlocks()) {
        emitBB(bb);   // bbName and bb itself will be added in this func.
        for (auto& t : blockStrangeFake.back()) { LOGD(t.toString()); }
    }
    // 处理返回语句。我的方法是新建立一个.LRET_<funcName> 标签(基本块)，
    // 然后在每个函数的最后一条指令之后插入一条J指令，跳转到。
}
static inline void S(shared_ptr<R5Taichi>& a, shared_ptr<R5Taichi>& b)
{
    swap(a, b);
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
    for (; it1 != instructions.end(); moveNext()) {
        auto inst1 = *it1;
        auto inst2 = inst1;
        if (it2 != instructions.end()) inst2 = *it2;
        if (inst1->isAllocaInst()) handleAllocaInst(inst1);
        // Int Math
        else if (inst1->isMathInst())
            handleIMathInst(sf, inst1);
        // Float Math
        else if (inst1->isFMathInst())
            handleFMathInst(sf, inst1);
        // Load
        else if (inst1->isLoadInst())
            handleLoadInst(sf, inst1);
        // Store
        else if (inst1->isStoreInst())
            handleStoreInst(sf, inst1);
            // ICmp
#pragma region ICMP
        else if (inst1->isICmpInst()) {
            if (inst2->isBrInst()) {
                // 比较且跳转。
                auto cmpInst = std::dynamic_pointer_cast<ICmpInst>(inst1);
                auto brInst  = std::dynamic_pointer_cast<BrInst>(inst2);
                if (brInst->getCond() != cmpInst) {
                    LOGW("他妈的这两个指令不匹配! 回退到《非ICMP+跳转》格式");
                    // TODO 不用goto实现。
                    goto LabelCmpNotJump;
                }
                if (brInst->getIfFalse() == nullptr) {
                    // 直接插入一条跳转指令,不管比较结果如何，都跳转到ifTrue
                    sf.emplace_back(
                        R5AsmStrangeFake(J, {L(BN(thisFunc->getName(), brInst->getIfTrueLabel()))})
                    );
                } else {
                    auto                 cmpOp = cmpInst->getICmpOp();
                    auto                 op1   = cmpInst->getOpVal1();
                    auto                 op2   = cmpInst->getOpVal2();
                    shared_ptr<R5Taichi> taichi1;
                    shared_ptr<R5Taichi> taichi2;
                    // 将0的交换至taichi2. 然后即可解决。
                    if (op1->isConst()) {
                        // 立即数 不能直接比较。需要先装载到寄存器里。
                        int op1Val = std::dynamic_pointer_cast<R5IRValConstInt>(op1)->getValue();
                        if (op1Val == 0)
                            taichi1 = R(zero);
                        else {
                            auto tmp = V(E(), Int);
                            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(op1Val)}));
                            taichi1 = tmp;
                        }
                    } else {
                        // 变量
                        taichi1 = V(op1->getName(), Int);
                    }
                    if (op2->isConst()) {
                        int op2Val = std::dynamic_pointer_cast<R5IRValConstInt>(op2)->getValue();
                        if (op2Val == 0)
                            taichi2 = R(zero);
                        else {
                            auto tmp = V(E(), Int);
                            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(op2Val)}));
                            taichi2 = tmp;
                        }
                    } else {
                        taichi2 = V(op2->getName(), Int);
                    }
                    FakeOPs fop;
                    switch (cmpOp) {
                    case ICmpInst::EQ: fop = BEQ; break;
                    case ICmpInst::NE: fop = BNE; break;
                    case ICmpInst::SGT: fop = BGT; break;
                    case ICmpInst::SGE: fop = BGE; break;
                    case ICmpInst::SLT: fop = BLT; break;
                    case ICmpInst::SLE: fop = BLE; break;
                    case ICmpInst::UGE: fop = BGEU; break;
                    case ICmpInst::UGT: fop = BGTU; break;
                    case ICmpInst::ULE: fop = BLEU; break;
                    case ICmpInst::ULT: fop = BLTU; break;
                    }
                    // 比较完了，接下来是跳转
                    // 跳转的目标是什么？是标签。
                    string ifTrueLabel  = brInst->getIfTrueLabel();
                    ifTrueLabel         = BN(thisFunc->getName(), ifTrueLabel);
                    string ifFalseLabel = brInst->getIfFalseLabel();
                    ifFalseLabel        = BN(thisFunc->getName(), ifFalseLabel);
                    // 并非为了圣杯──也非为其他任何事物，而是为贯彻他们自身的信念。
                    sf.emplace_back(R5AsmStrangeFake(fop, {taichi1, taichi2, L(ifTrueLabel)}));
                    sf.emplace_back(R5AsmStrangeFake(J, {L(ifFalseLabel)}));
                    moveNext();
                }
            } else {
                // 比较 但是没有跳转指令、
            LabelCmpNotJump:
                handleICmpNoBr(sf, inst1);
            }
        }
#pragma endregion ICMP
        // fptosi/ sitofp. But, Zext/Sext were not implemented.
        else if (inst1->isConvertInst())
            handleCvtInst(sf, inst1);
        else if (inst1->isGetElementPtrInst())
            handleGEPInst(sf, inst1);
        else if (inst1->isBitCastInst())
            handleBitcastInst(sf, inst1);
        else if (inst1->isFCmpInst())
            handleFCmpInst(sf, inst1);
        else if (inst1->isBrInst())
            handleBrInst(sf, inst1, thisFunc->getName());
        else if (inst1->isCallInst())
            handleCallInst(sf, inst1);
        else if (inst1->isReturnInst())
            handleRetInst(sf, inst1);
        else {
            // not implemented
            RUNTIME_ERROR("他妈的不支持的指令类型, 传了什么东西进来❤受不了了");
        }
    }
    // push sf into...
    string bbName = BN(thisFunc->getName(), bb->getName());
    blockStrangeFake.emplace_back(std::move(sf));
    bbNames.emplace_back(bbName);
}
void R5FakeSeihai::handleRetInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    // 整数挪到a0，浮点数挪到fa0,然后跳转到.LRET_<funcname>
    auto retInst = std::dynamic_pointer_cast<ReturnInst>(inst1);
    auto retType = retInst->getAtomRetType();
    if (retType == MiddleIRType::VOID) {
        sf.emplace_back(R5AsmStrangeFake(J, {L(funcRetLabel())}));
    } else if (retType == MiddleIRType::FLOAT) {
        // 先判断是不是立即数。
        auto fVal = retInst->getOpVal();
        if (fVal->isConst()) {
            auto cf   = std::dynamic_pointer_cast<R5IRValConstFloat>(fVal);
            auto c    = L(C(cf->getWord()));
            auto addr = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(LLA, {addr, c}));
            sf.emplace_back(R5AsmStrangeFake(FLW, {R(fa0), P(0), addr}));
        } else {
            sf.emplace_back(R5AsmStrangeFake(MV, {R(fa0), V(fVal->getName(), Float)}));
        }
    } else if (retType == MiddleIRType::INT) {
        auto iVal = retInst->getOpVal();
        if (iVal->isConst()) {
            auto ci = std::dynamic_pointer_cast<R5IRValConstInt>(iVal);
            sf.emplace_back(R5AsmStrangeFake(LI, {R(a0), N(ci->getValue())}));
        } else {
            sf.emplace_back(R5AsmStrangeFake(MV, {R(a0), V(iVal->getName(), Int)}));
        }
    } else {
        RUNTIME_ERROR("他妈的不支持的返回值类型, 传了什么东西进来❤受不了了");
    }
}
void R5FakeSeihai::handleCallInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto callInst = std::dynamic_pointer_cast<CallInst>(inst1);
    bool useReg;
    int  fRegRes = 8, iRegRes = 8;   // fa0-7, a0-7
    for (const auto& arg : callInst->getArgs()) {
        if (arg->getType()->isFloat()) {
            fRegRes -= 1;
        } else if (arg->getType()->isPointer() || arg->getType()->isInt()) {
            iRegRes -= 1;
        }
    }
    useReg = fRegRes >= 0 && iRegRes >= 0;
    // 特判。如果是@llvm.memset.p0.i32(i32*, i8, i32, i1), 那么应该调用的是memset
    if (callInst->getFunc()->getName() == "@llvm.memset.p0.i32") {
        // a0-2: dst, val, len. val肯定是0. dst是指针，len是整数。
        // TODO 一会再写memset.
        auto dstTaichi = V(callInst->getArgs()[0]->getName(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(MV, {R(a0), dstTaichi}));
        sf.emplace_back(R5AsmStrangeFake(MV, {R(a1), R(zero)}));
        int len = std::dynamic_pointer_cast<R5IRValConstInt>(callInst->getArgs()[2])->getValue();
        sf.emplace_back(R5AsmStrangeFake(LI, {R(a2), N(len)}));
        sf.emplace_back(R5AsmStrangeFake(CALL, {L("memset")}));
        return;
    }
    if (useReg) {
        YangReg fReg = fa0;
        YangReg iReg = a0;
        for (const auto& arg : callInst->getArgs()) {
            // TODO: 参数可能是立即数。这里没有处理。
            if (arg->getType()->isFloat()) {
                sf.emplace_back(R5AsmStrangeFake(MV, {R(fReg), V(arg->getName(), Float)}));
                fReg = (YangReg)((int)fReg + 1);
            } else if (arg->getType()->isPointer() || arg->getType()->isInt()) {
                sf.emplace_back(R5AsmStrangeFake(MV, {R(iReg), V(arg->getName(), Int)}));
                iReg = (YangReg)((int)iReg + 1);
            }
        }
        sf.emplace_back(R5AsmStrangeFake(CALL, {L(callInst->getFunc()->getName())}));
        if (callInst->getRetType() == MiddleIR::MiddleIRType::FLOAT) {
            sf.emplace_back(R5AsmStrangeFake(MV, {V(callInst->getName(), Float), R(fa0)}));
        } else if (callInst->getRetType() == MiddleIR::MiddleIRType::INT) {
            sf.emplace_back(R5AsmStrangeFake(MV, {V(callInst->getName(), Int), R(a0)}));
        }
    } else {
        // TODO.使用栈来传参罢。
    }
}
void R5FakeSeihai::handleGEPInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto gep   = std::dynamic_pointer_cast<GetElementPtrInst>(inst1);
    auto type1 = gep->getType1();
    auto from  = gep->getFrom();

    std::shared_ptr<R5Taichi> base;
    auto                      to = V(gep->getName(), Pointer);
    if (from->getName()[0] == '%') {
        if (queryInStackSpace(from->getName())) {
            // on stack
            int64_t o = queryStackSpace(from->getName());
            base      = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(ADDI, {base, R(sp), P(o)}));
        } else {
            base = V(from->getName(), Pointer);
        }
    } else {
        // 是标签
        auto t = L(from->getName());
        base   = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {base, t}));
    }
    // 此时，base存储的是基地址。

    // a GEP instruction like this:
    // %v1 = getelementptr [3 x [4 x i32]], [3 x [4 x i32]]* %v0, i32 0, i32 0, i32 %v0
    // type1 is [3 x [4 x i32]]
    // type1 may be ArrayType or just a Int/Float.❤
    int64_t                   offset   = 0;
    bool                      immSoFar = true;
    std::shared_ptr<R5Taichi> tmp;
    for (const auto& idx : gep->getIndex()) {
        int64_t curShapeSizeBytes = 0;
        if (auto aType1 = std::dynamic_pointer_cast<ArrayType>(type1)) {
            curShapeSizeBytes = (int64_t)aType1->getSizeBytes();
            type1             = aType1->getElementType();
        } else {
            curShapeSizeBytes = 4;
        }
        if (idx->isConst()) {
            if (immSoFar) {
                // 前面的都是立即数，乘以类型大小。
                offset +=
                    std::dynamic_pointer_cast<R5IRValConstInt>(idx)->getValue() * curShapeSizeBytes;
            } else {
                // 前面的不是立即数，那就先乘以类型大小，然后再加上立即数。
                // tmp2=idx*curShapeSizeBytes; tmp1=tmp2+offset;
                uint64_t tmp2 =
                    std::dynamic_pointer_cast<R5IRValConstInt>(idx)->getValue() * curShapeSizeBytes;
                auto tmp3 = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp3, P(tmp2)}));
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp, tmp, tmp3}));
            }
        } else {
            if (immSoFar) {
                immSoFar = false;
                // 把之前的结果先存到寄存器中，然后再加上这个变量*类型大小。
                // tmp1=tmp+offset; tmp2=tmp1+idx*curShapeSizeBytes;
                const std::shared_ptr<R5Taichi>& tmp2 = V(E(), Pointer);
                // li
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp2, P(curShapeSizeBytes)}));
                sf.emplace_back(R5AsmStrangeFake(MUL, {tmp2, V(idx->getName(), Pointer), tmp2}));
                // li offset
                auto tmp4 = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp4, P(offset)}));
                // add
                tmp = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp4, tmp4, tmp2}));
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp, tmp4, base}));
            } else {
                // tmp1=tmp+offset; tmp2=tmp1+idx*curShapeSizeBytes;
                const std::shared_ptr<R5Taichi>& tmp2 = V(E(), Pointer);
                // li
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp2, P(curShapeSizeBytes)}));
                // mul
                const std::shared_ptr<R5Taichi>& tmp3 = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(MUL, {tmp3, V(idx->getName(), Pointer), tmp2}));
                // add
                tmp = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp, tmp, tmp3}));
            }
        }
    }
    if (immSoFar) {
        // 还有待处理的立即数。
        sf.emplace_back(R5AsmStrangeFake(ADDI, {to, base, P(offset)}));
    } else {
        sf.emplace_back(R5AsmStrangeFake(MV, {to, tmp}));
    }
}
void R5FakeSeihai::handleBrInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1, const string& funcName
)
{
    auto brInst = std::dynamic_pointer_cast<BrInst>(inst1);
    if (brInst->getIfFalse() == nullptr) {
        // 直接插入一条跳转指令,不管比较结果如何，都跳转到ifTrue
        string ifTrueLabel = BN(funcName, brInst->getIfTrueLabel());
        sf.emplace_back(R5AsmStrangeFake(J, {L(ifTrueLabel)}));
    } else {
        // 有两个分支，那就是ifTrue和ifFalse
        // 先进行BNE, 然后J
        auto   cond         = brInst->getCond();
        auto   condName     = cond->getName();
        string ifTrueLabel  = BN(funcName, brInst->getIfTrueLabel());
        string ifFalseLabel = BN(funcName, brInst->getIfFalseLabel());
        sf.emplace_back(R5AsmStrangeFake(BNEZ, {V(condName, Int), L(ifTrueLabel)}));
        sf.emplace_back(R5AsmStrangeFake(J, {L(ifFalseLabel)}));
    }
}
void R5FakeSeihai::handleFCmpInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto                 fcmp = std::dynamic_pointer_cast<FCmpInst>(inst1);
    auto                 fOp  = fcmp->getFCmpOp();
    auto                 op1  = fcmp->getOpVal1();
    auto                 op2  = fcmp->getOpVal2();
    shared_ptr<R5Taichi> taichi1;
    shared_ptr<R5Taichi> taichi2;
    taichi1 = V(op1->getName(), Float);
    taichi2 = V(op2->getName(), Float);

    // 特殊情况：两个操作数都是立即数（不可能）
    switch (fOp) {

    case FCmpInst::FCmpOp::FALSE: {
        sf.emplace_back(R5AsmStrangeFake(MV, {V(fcmp->getName(), Int), R(zero)}));
    } break;
    case FCmpInst::FCmpOp::OEQ:
    case FCmpInst::FCmpOp::UEQ: {
        sf.emplace_back(R5AsmStrangeFake(FEQ, {V(fcmp->getName(), Int), taichi1, taichi2}));
    } break;
    case FCmpInst::FCmpOp::OGE:
    case FCmpInst::FCmpOp::UGE: {
        sf.emplace_back(R5AsmStrangeFake(FLE, {V(fcmp->getName(), Int), taichi2, taichi1}));
    } break;
    case FCmpInst::FCmpOp::OGT:
    case FCmpInst::FCmpOp::UGT: {
        sf.emplace_back(R5AsmStrangeFake(FLT, {V(fcmp->getName(), Int), taichi2, taichi1}));
    } break;
    case FCmpInst::FCmpOp::OLE:
    case FCmpInst::FCmpOp::ULE: {
        sf.emplace_back(R5AsmStrangeFake(FLE, {V(fcmp->getName(), Int), taichi1, taichi2}));
    } break;
    case FCmpInst::FCmpOp::OLT:
    case FCmpInst::FCmpOp::ULT: {
        sf.emplace_back(R5AsmStrangeFake(FLT, {V(fcmp->getName(), Int), taichi1, taichi2}));
    } break;
    case FCmpInst::FCmpOp::TRUE: {
        sf.emplace_back(R5AsmStrangeFake(LI, {V(fcmp->getName(), Int), N(1)}));
    } break;
    case FCmpInst::FCmpOp::UNO:
    case FCmpInst::FCmpOp::UNE: {
        auto tmp = V(E(), Int);
        sf.emplace_back(R5AsmStrangeFake(FEQ, {tmp, taichi1, taichi2}));
        sf.emplace_back(R5AsmStrangeFake(NOT, {V(fcmp->getName(), Int), tmp}));
    } break;
    }
}
void R5FakeSeihai::handleBitcastInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto bitCast = std::dynamic_pointer_cast<BitCastInst>(inst1);
    auto from    = bitCast->getFrom()->getName();
    auto to      = bitCast->getName();
    // 直接mv 错误的。需要判断类型。
    if (queryInStackSpace(from)) {
        // on stack
        int64_t o = queryStackSpace(from);
        sf.emplace_back(R5AsmStrangeFake(ADDI, {V(to, Pointer), R(sp), P(o)}));
    } else {
        sf.emplace_back(R5AsmStrangeFake(MV, {V(to, Pointer), V(from, Pointer)}));
    }
}
void R5FakeSeihai::handleCvtInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto convertInst = std::dynamic_pointer_cast<ConvertInst>(inst1);
    auto cvtOp       = convertInst->getConvertOp();
    //  SITOFP, FPTOSI 现在只需要实现这两个。
    if (cvtOp == ConvertInst::SITOFP) {
        // 老样子，还是得单独处理立即数。
        if (convertInst->getFrom()->isConst()) {
            // 整数转浮点数，立即数有点捉急。整数需要先li然后FCVT_S_W
            auto tmp = V(E(), Int);
            int  number =
                std::dynamic_pointer_cast<R5IRValConstInt>(convertInst->getFrom())->getValue();
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(number)}));
            sf.emplace_back(R5AsmStrangeFake(FCVT_S_W, {V(convertInst->getName(), Float), tmp}));
        } else {
            // 变量，直接FCVT_S_W
            sf.emplace_back(R5AsmStrangeFake(
                FCVT_S_W,
                {V(convertInst->getName(), Float), V(convertInst->getFrom()->getName(), Int)}
            ));
        }
    } else if (cvtOp == ConvertInst::FPTOSI) {
        if (convertInst->getFrom()->isConst()) {
            // 浮点他妈直接读出来，然后直接li进去就行了。
            float number =
                std::dynamic_pointer_cast<R5IRValConstFloat>(convertInst->getFrom())->getValue();
            sf.emplace_back(R5AsmStrangeFake(LI, {V(convertInst->getName(), Int), N((int)number)}));
        } else {
            // 变量，直接FCVT_W_S
            sf.emplace_back(R5AsmStrangeFake(
                FCVT_W_S,
                {V(convertInst->getName(), Int), V(convertInst->getFrom()->getName(), Float)}
            ));
        }
    } else {
        // not implemented
        RUNTIME_ERROR("他妈的不支持的Convert类型, 传了什么东西进来❤受不了了");
    }
}
void R5FakeSeihai::handleICmpNoBr(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    // 预期指令: SLT SLTI SLTU SLTIU.
    // 如果带等号的，比较之后取反
    auto cmpInst = std::dynamic_pointer_cast<ICmpInst>(inst1);
    auto cmpOp   = cmpInst->getICmpOp();
    auto op1     = cmpInst->getOpVal1();
    auto op2     = cmpInst->getOpVal2();
    // 特殊情况：两个操作数都是立即数
    if (op1->isConst() && op2->isConst()) {
        int  op1Val = std::dynamic_pointer_cast<R5IRValConstInt>(op1)->getValue();
        int  op2Val = std::dynamic_pointer_cast<R5IRValConstInt>(op2)->getValue();
        bool result;
        switch (cmpOp) {
        case ICmpInst::EQ: result = op1Val == op2Val; break;
        case ICmpInst::NE: result = op1Val != op2Val; break;
        case ICmpInst::SGT: result = op1Val > op2Val; break;
        case ICmpInst::SGE: result = op1Val >= op2Val; break;
        case ICmpInst::SLT: result = op1Val < op2Val; break;
        case ICmpInst::SLE: result = op1Val <= op2Val; break;
        case ICmpInst::UGE: result = op1Val >= op2Val; break;   // Not supported.
        case ICmpInst::UGT: result = op1Val > op2Val; break;    // Not supported.
        case ICmpInst::ULE: result = op1Val <= op2Val; break;   // Not supported.
        case ICmpInst::ULT: result = op1Val < op2Val; break;    // Not supported.
        }
        // 立即数比较结果，直接写入寄存器
        sf.emplace_back(R5AsmStrangeFake(LI, {V(cmpInst->getName(), Int), N((int)result)}));
    }
    // 两个寄存器
    else if (!(op1->isConst()) && (!op2->isConst())) {
        // 两个操作数都是变量
        // 两个操作数都是变量，那就直接比较就行了。
        shared_ptr<R5Taichi> taichi1 = V(op1->getName(), Int);
        shared_ptr<R5Taichi> taichi2 = V(op2->getName(), Int);
        // 小于号，直接使用SLT
        if (cmpOp == ICmpInst::SLT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi1, taichi2}));
        }
        // 大于号，反过来SLT
        else if (cmpOp == ICmpInst::SGT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi2, taichi1}));
        }
        // 大于等于号，先比较，再取反（强制SSA）
        else if (cmpOp == ICmpInst::SGE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 小于等于号，先反过来比较，再取反
        else if (cmpOp == ICmpInst::SLE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi2, taichi1}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 等于号，先减法，再SNEZ
        else if (cmpOp == ICmpInst::EQ) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SUBW, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(SNEZ, {V(cmpInst->getName(), Int), tmp}));
        }
        // 不等于
        else if (cmpOp == ICmpInst::NE) {
            auto tmp  = V(E(), Int);
            auto tmp2 = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SUBW, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(SNEZ, {tmp2, tmp}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp2}));
        } else {
            RUNTIME_ERROR("他妈的不支持的ICMP类型, 传了什么东西进来❤受不了了");
        }
    }
    // 一个寄存器，一个立即数
    else {
        if (op1->isConst()) {
            // 立即数应该在后边
            swap(op1, op2);
        }
        // op1是寄存器，op2是立即数
        shared_ptr<R5Taichi> taichi1   = V(op1->getName(), Int);
        auto                 intValue2 = std::dynamic_pointer_cast<R5IRValConstInt>(op2);
        int                  op2Val    = intValue2->getValue();
        // 总之op2Val需要保存在一个寄存器里。
        shared_ptr<R5Taichi> taichi2;
        if (op2Val == 0) {
            taichi2 = R(zero);
        } else {
            taichi2 = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {taichi2, N(op2Val)}));
        }
        // 小于号，直接使用SLT
        if (cmpOp == ICmpInst::SLT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi1, taichi2}));
        }
        // 大于号，反过来SLT
        else if (cmpOp == ICmpInst::SGT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi2, taichi1}));
        }
        // 大于等于号，先比较，再取反（强制SSA）
        else if (cmpOp == ICmpInst::SGE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 小于等于号，先反过来比较，再取反
        else if (cmpOp == ICmpInst::SLE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi2, taichi1}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 等于号，先减法，再SNEZ
        else if (cmpOp == ICmpInst::EQ) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SUBW, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(SNEZ, {V(cmpInst->getName(), Int), tmp}));
        } else {
            RUNTIME_ERROR("他妈的不支持的ICMP类型, 传了什么东西进来❤受不了了");
        }
    }
}
void R5FakeSeihai::handleStoreInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto    storeInst = std::dynamic_pointer_cast<StoreInst>(inst1);
    auto    from      = storeInst->getFrom();
    auto    to        = storeInst->getTo();
    bool    isFloat   = from->getType()->isFloat();
    FakeOPs op        = isFloat ? FSW : SW;
    // 草，好像有bug。要是存储的是个指针，就不能用FSW/SW，就得用SD
    if (from->getType()->isPointer()) { op = SD; }
    shared_ptr<R5Taichi> rs;
    shared_ptr<R5Taichi> rt;
    // 先检查rt是全局还是栈
    auto name     = to->getName();
    bool onStack  = queryInStackSpace(name);
    bool isGlobal = name[0] == '@';
    if (onStack) {
        // 栈
        uint64_t offset = queryStackSpace(to->getName());
        rt              = P(offset);
        onStack         = true;
    } else if (isGlobal) {
        // 全局
        rt      = L(to->getName());
        onStack = false;
    } else {
        // GetElementPtrInst的结果
        rt = V(to->getName(), Pointer);
    }
    // 是不是立即数
    if (from->isConst()) {
        // 立即数有点捉急。因为他妈的，立即数不能直接存到内存里。
        if (isFloat) {
            string newCLabel = C(std::dynamic_pointer_cast<R5IRValConstFloat>(from)->getWord());
            auto   tmp       = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(newCLabel)}));
            rs = V(E(), Float);
            sf.emplace_back(R5AsmStrangeFake(FLW, {rs, P(0), tmp}));
        } else {
            auto tmp = V(E(), Int);
            // li
            sf.emplace_back(R5AsmStrangeFake(
                LI, {tmp, N(std::dynamic_pointer_cast<R5IRValConstInt>(from)->getValue())}
            ));
            rs = tmp;
        }
        // 此时立即数已经在rs里了。
    } else {
        // 变量
        rs = V(from->getName(), isFloat ? Float : Int);
    }
    if (onStack) {
        // TODO 检查rt是不是超出范围了
        int64_t of = (dynamic_pointer_cast<R5Lai64>(rt))->value;
        if (of >= -2048 && of <= 2047) {
            // 可以用SW
            sf.emplace_back(R5AsmStrangeFake(op, {rs, rt, R(sp)}));
        } else {
            // 先LI，再SW
            auto tmp0 = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp0, rt}));
            sf.emplace_back(R5AsmStrangeFake(op, {rs, P(0), tmp0}));
        }
    } else if (isGlobal) {
        // lla+fsw/sw
        auto tmp = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, rt}));
        sf.emplace_back(R5AsmStrangeFake(op, {rs, P(0), tmp}));
    } else {
        // GetElementPtrInst的结果
        sf.emplace_back(R5AsmStrangeFake(op, {rs, P(0), rt}));
    }
}
void R5FakeSeihai::handleLoadInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto                 loadInst = std::dynamic_pointer_cast<LoadInst>(inst1);
    bool                 isFloat  = loadInst->getType()->isFloat();
    FakeOPs              op       = isFloat ? FLW : LW;
    shared_ptr<R5Taichi> rd       = V(loadInst->getName(), isFloat ? Float : Int);
    // 等会，如果需要加载的是个指针，那就不能用FLW/LW，得用LD
    if (loadInst->getType()->isPointer()) { op = LD; }
    // 我草，load可能从栈里读，也可能从全局变量里读。这该如何是好？
    string rsName = loadInst->getOpVal()->getName();
    // 他妈的，如果是全局变量，那就是@开头的，如果是栈变量，那就是%开头的
    // 草，应该没别的情况了吧？
    // 有！ 还可能是GetElementPtrInst的结果！
    bool isGlobal = rsName[0] == '@';
    bool onStack  = queryInStackSpace(rsName);
    if (isGlobal) {
        // 全局变量 草，这个时候，rsName是一个label
        auto tmp = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(rsName)}));
        sf.emplace_back(R5AsmStrangeFake(op, {rd, P(0), tmp}));
    } else if (onStack) {
        // 栈变量
        uint64_t offset = queryStackSpace(rsName);
        sf.emplace_back(R5AsmStrangeFake(op, {rd, P(offset), R(sp)}));
    } else {
        // GetElementPtrInst的结果
        sf.emplace_back(R5AsmStrangeFake(op, {rd, P(0), V(rsName, Pointer)}));
    }
}
void R5FakeSeihai::handleAllocaInst(const shared_ptr<MiddleIRInst>& inst1)
{
    // 更新太极图，把虚拟寄存器和栈地址绑定
    auto     allocaInst = std::dynamic_pointer_cast<AllocaInst>(inst1);
    auto     name       = allocaInst->getName();
    uint64_t size;
    if (allocaInst->getType()->isFloat() || allocaInst->getType()->isInt())
        size = 4;
    else if (allocaInst->getType()->isPointer())
        size = 8;
    else if (allocaInst->getType()->isArray()) {
        auto arrayTypeI = allocaInst->getType();
        auto arrayType  = std::dynamic_pointer_cast<ArrayType>(arrayTypeI);
        size            = arrayType->getSizeBytes();
    } else
        RUNTIME_ERROR("他妈的不支持的alloca类型, 传了什么东西进来❤受不了了");
    allocateStackSpace(name, size);
}
void R5FakeSeihai::handleFMathInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto                 fMath = std::dynamic_pointer_cast<FMathInst>(inst1);
    auto                 fOp   = fMath->getFMathOp();
    auto                 op1   = fMath->getOpVal1();
    auto                 op2   = fMath->getOpVal2();
    auto                 rd    = V(fMath->getName(), Float);
    shared_ptr<R5Taichi> taichi1;
    shared_ptr<R5Taichi> taichi2;
    // check if op1 or op2 is const. if const, we need to LI it first and move it to a float
    // register
    if (op1->isConst()) {
        // 先需要把立即数装载到整数寄存器里。之后再转换成浮点数寄存器
        // 太蠢了。gcc的做法是把立即数装载到内存里，然后再从内存里装载到浮点数寄存器里
        string newCLabel = C(std::dynamic_pointer_cast<R5IRValConstFloat>(op1)->getWord());
        // LLA and FLW
        auto tmp = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(newCLabel)}));
        taichi1 = V(E(), Float);
        sf.emplace_back(R5AsmStrangeFake(FLW, {taichi1, P(0), tmp}));
    } else {
        taichi1 = V(op1->getName(), Float);
    }
    if (op2->isConst()) {
        string newCLabel = C(std::dynamic_pointer_cast<R5IRValConstFloat>(op2)->getWord());
        auto   tmp       = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(newCLabel)}));
        taichi2 = V(E(), Float);
        sf.emplace_back(R5AsmStrangeFake(FLW, {taichi2, P(0), tmp}));
    } else {
        taichi2 = V(op2->getName(), Float);
    }
    // 现在可以保证两个太极都是浮点寄存器
    switch (fOp) {
    case FMathInst::FADD: {
        sf.emplace_back(R5AsmStrangeFake(FADD_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FSUB: {
        sf.emplace_back(R5AsmStrangeFake(FSUB_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FMUL: {
        sf.emplace_back(R5AsmStrangeFake(FMUL_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FDIV: {
        sf.emplace_back(R5AsmStrangeFake(FDIV_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FREM: RUNTIME_ERROR("他妈的没有浮点数取余");
    }
}
void R5FakeSeihai::handleIMathInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    // only INT, float will be handled later in isFMathInst()
    auto                 math    = std::dynamic_pointer_cast<IMathInst>(inst1);
    auto                 iMathOp = math->getIMathOp();
    shared_ptr<R5Taichi> taichi1;
    shared_ptr<R5Taichi> taichi2;
    shared_ptr<R5Taichi> rd;
    auto                 op1 = math->getOpVal1();
    if (op1->isConst())
        taichi1 = N(std::dynamic_pointer_cast<R5IRValConstInt>(op1)->getValue());   // const LAI
    else
        taichi1 = V(op1->getName(), Int);                                           // var YIN
    auto op2 = math->getOpVal2();
    if (op2->isConst())
        taichi2 = N(std::dynamic_pointer_cast<R5IRValConstInt>(op2)->getValue());
    else
        taichi2 = V(op2->getName(), Int);
    bool isI =
        (taichi1->isLai() || taichi2->isLai()
        );   // 这里从前端中就已经确定不可能是两个立即数相运算。
    rd = V(math->getName(), Int);
    FakeOPs op;
    switch (iMathOp) {
        // todo
        // 如果他妈的是立即数，并且还是需要LUI那种，就不能直接使用ADDI等指令了。交给@ZZZCOLA处理。
        // 留言：注意使用严格的SSA，不要出现同一个寄存器被多次写入的情况。

    case IMathInst::IMathOp::ADD: {
        op = isI ? ADDIW : ADDW;   // 这里假设了没有两个立即数相加的情况。（实际上也不会有）
        if (taichi1->isLai()) S(taichi1, taichi2);
        sf.emplace_back(R5AsmStrangeFake(op, {rd, taichi1, taichi2}));
    } break;

    case IMathInst::IMathOp::SUB: {
        if (isI) {
            if (taichi1->isLai()) S(taichi1, taichi2);
            dynamic_pointer_cast<R5Lai>(taichi2)->negative();
            op = ADDIW;
        } else {
            op = SUBW;
        }
        sf.emplace_back(R5AsmStrangeFake(op, {rd, taichi1, taichi2}));
    } break;

    case IMathInst::IMathOp::MUL: {
        // 乘法要求两个操作数都是寄存器
        // 不是的话，就要先把立即数装载到寄存器里
        if (taichi1->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi1}));
            taichi1 = tmp;
        }
        if (taichi2->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi2}));
            taichi2 = tmp;
        }
        sf.emplace_back(R5AsmStrangeFake(MULW, {rd, taichi1, taichi2}));
    } break;

    case IMathInst::IMathOp::SDIV: {
        // 除法要求两个操作数都是寄存器
        // 不是的话，就要先把立即数装载到寄存器里
        if (taichi1->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi1}));
            taichi1 = tmp;
        }
        if (taichi2->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi2}));
            taichi2 = tmp;
        }
        sf.emplace_back(R5AsmStrangeFake(DIVW, {rd, taichi1, taichi2}));
    } break;

    case IMathInst::IMathOp::SREM: {
        // 同上。
        if (taichi1->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi1}));
            taichi1 = tmp;
        }
        if (taichi2->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi2}));
            taichi2 = tmp;
        }
        sf.emplace_back(R5AsmStrangeFake(REMW, {rd, taichi1, taichi2}));
    } break;
    case IMathInst::IMathOp::UDIV:
    case IMathInst::IMathOp::UREM: RUNTIME_ERROR("他妈的没有无符号除法和取余");
    }
}

/// 在栈上为name分配size字节大小的空间
/// \param name
/// \param size
void R5FakeSeihai::allocateStackSpace(const string& name, uint64_t size)
{
    // TODO 实现4/8字节对齐
    taichiMap[name] = taichiSize;
    taichiSize += size;
}
int64_t R5FakeSeihai::queryStackSpace(const string& name)
{
    return taichiMap.at(name);
}

/// 生成函数的返回标签名字
/// \return 如你所愿
string R5FakeSeihai::funcRetLabel()
{
    return ".LRET_" + thisFunc->getName();
}
bool R5FakeSeihai::queryInStackSpace(const string& name)
{
    return taichiMap.find(name) != taichiMap.end();
}

/// 生成一个内存中常亮的标签，存储常量值，并且返回这个标签的名字
/// \tparam T Int/Float
/// \param v 数
/// \return 标签名字
template<class T>
string R5FakeSeihai::C(T v)
{
    uint32_t word       = *(uint32_t*)&v;
    string   labelName  = ".LC_" + thisFunc->getName() + "_" + std::to_string(extTempMemVarNum++);
    constMem[labelName] = word;
    return labelName;
}

#pragma clang diagnostic pop


}   // namespace R5Emitter
#undef SP