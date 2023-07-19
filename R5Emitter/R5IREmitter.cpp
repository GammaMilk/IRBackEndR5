//
// Created by gaome on 2023/7/20.
//
#include <utility>

#include "R5IREmitter.h"
#include "../MiddleIR/MiddleIRVal.h"

namespace R5Emitter
{
#define endl "\n"
#define tab "    "
void R5IREmitter::build(std::ostream& os) {
    // global variables
    for (auto& globalVar : _middleIRAST->globalVars) {
        // cut first "@"
        string name = globalVar->getName().substr(1);
        if(shared_ptr<MiddleIR::R5IRValConstInt> t = dynamic_pointer_cast<MiddleIR::R5IRValConstInt>(globalVar)){
            if(t->inBss()) {
                os <<tab<< ".bss" << endl;
                os << name << ":" << endl;
                os <<tab<< ".zero 4" << endl;
            }
            else {
                os <<tab<< ".data" << endl;
                os << name << ":" << endl;
                os <<tab<< ".word " << t->getWord() << endl;
            }
            os<<endl;
        }
        else if(shared_ptr<MiddleIR::R5IRValConstFloat> tf = dynamic_pointer_cast<MiddleIR::R5IRValConstFloat>(globalVar)){
            if(tf->inBss()) {
                os <<tab<< ".bss" << endl;
                os << name << ":" << endl;
                os <<tab<< ".zero 4" << endl;
            }
            else {
                os <<tab<< ".data" << endl;
                os << name << ":" << endl;
                os <<tab<< ".word " << tf->getWord() << endl;
            }
        }
        // array
        else if(shared_ptr<MiddleIR::R5IRArray> ta = dynamic_pointer_cast<MiddleIR::R5IRArray>(globalVar)){
            // 递归吧。现在懒得写。
            // TODO
            os<<endl;
        }
    }

}
#undef tab
#undef endl
}