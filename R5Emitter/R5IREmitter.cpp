//
// Created by gaome on 2023/7/20.
//
#include <utility>

#include "R5IREmitter.h"
#include "../MiddleIR/MiddleIRVal.h"
#include "../MiddleIR/ArrayHelper.h"
#include "R5FakeSeihai.h"
namespace R5Emitter
{
#define endl "\n"
#define tab "    "
void R5IREmitter::build(std::ostream& os)
{
    // global variables
    for (auto& globalVar : _middleIRAST->globalVars) {
        // cut first "@"
        string name = globalVar->getName().substr(1);
        if (shared_ptr<MiddleIR::R5IRValConstInt> t =
                dynamic_pointer_cast<MiddleIR::R5IRValConstInt>(globalVar)) {
            if (t->inBss()) {
                os << tab << ".bss" << endl;
                os << name << ":" << endl;
                os << tab << ".zero 4" << endl;
            } else {
                os << tab << ".data" << endl;
                os << name << ":" << endl;
                os << tab << ".word " << t->getWord() << endl;
            }
            os << endl;
        } else if (shared_ptr<MiddleIR::R5IRValConstFloat> tf = dynamic_pointer_cast<MiddleIR::R5IRValConstFloat>(globalVar)) {
            if (tf->inBss()) {
                os << tab << ".bss" << endl;
                os << name << ":" << endl;
                os << tab << ".zero 4" << endl;
            } else {
                os << tab << ".data" << endl;
                os << name << ":" << endl;
                os << tab << ".word " << tf->getWord() << endl;
            }
            os << endl;
        }
        // array
        else if (shared_ptr<MiddleIR::R5IRArray> ta = dynamic_pointer_cast<MiddleIR::R5IRArray>(globalVar)) {
            auto atomType = ta->getArrayType()->getAtomElemType();
            auto idName   = ta->getName().substr(1);
            // 递归吧。现在懒得写。
            if (atomType == MiddleIR::MiddleIRType::INT) {
                auto t1 = MiddleIR::makeArrayChain<int>(ta);
                auto c  = MiddleIR::flattenChain(t1);
                // 先检查是不是全tm是0
                bool allZero = true;
                for (auto& i : c)
                    if (!i.data.empty()) {
                        allZero = false;
                        break;
                    }
                if (allZero) {
                    os << tab << ".bss" << endl;
                } else {
                    os << tab << ".data" << endl;
                }
                os << idName << ":" << endl;
                for (auto& i : c) {
                    if (i.data.empty()) {
                        os << tab << ".zero " << i.zeroBytes << endl;
                    } else {
                        for (auto& j : i.data) {
                            os << tab << ".word ";
                            os << j << " " << endl;
                        }
                    }
                }

            } else {
                auto t1 = MiddleIR::makeArrayChain<float>(ta);
                auto c  = MiddleIR::flattenChain(t1);
                // 同上。
                bool allZero = true;
                for (auto& i : c)
                    if (!i.data.empty()) {
                        allZero = false;
                        break;
                    }
                if (allZero) {
                    os << tab << ".bss" << endl;
                } else {
                    os << tab << ".data" << endl;
                }
                os << idName << ":" << endl;
                for (auto& i : c) {
                    if (i.data.empty()) {
                        os << tab << ".zero " << i.zeroBytes << endl;
                    } else {
                        for (auto j : i.data) {
                            os << tab << ".word ";
                            os << *(uint32_t*)&j << " " << endl;
                        }
                    }
                }
            }
            os << endl;
        }
    }

    // functions
    int blockHash = 0;
    os << tab << ".text" << endl;
    for (auto& function : _middleIRAST->funcDefs) {
        os << function->getName().substr(1) << ":" << endl;
        auto         stackSize = getAllocaSizeOfFunction(function);
        R5FakeSeihai fakeSeihai(function);
        fakeSeihai.emitFakeSeihai();
    }
}
uint64_t R5IREmitter::getAllocaSizeOfFunction(shared_ptr<MiddleIR::MiddleIRFuncDef> func)
{
    uint64_t stackSize = 16;
    for (auto& bb : func->getBasicBlocks()) {
        for (auto& inst : bb->_instructions) {
            if (inst->getInstType() == MiddleIR::MiddleIRInst::AllocaInst) { stackSize += 4; }
        }
    }
    return stackSize;
}
#undef tab
#undef endl
}   // namespace R5Emitter