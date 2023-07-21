//
// Created by gaome on 2023/7/21.
//

#ifndef IRBACKENDR5_R5FAKESEIHAI_H
#define IRBACKENDR5_R5FAKESEIHAI_H

#include <list>
#include "../MiddleIR/MiddleIRInst.h"
#include "R5AsmStrangeFake.h"
#include "../MiddleIR/MiddleIRFuncDef.h"
using namespace MiddleIR;

namespace R5Emitter
{
class R5FakeSeihai
{
public:
    explicit R5FakeSeihai(const std::shared_ptr<MiddleIRFuncDef>& funcDef);
    void emitFakeSeihai();

    vector<string>                   bbNames;
    vector<vector<R5AsmStrangeFake>> blockStrangeFake;

private:
    int                                     extTempVarNum = 0;
    inline string                           E();
    const std::shared_ptr<MiddleIRFuncDef>& thisFunc;
    void                                    emitBB(const std::shared_ptr<MiddleIRBasicBlock>& bb);
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5FAKESEIHAI_H
