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

    std::list<string>                   bbNames;
    std::list<vector<R5AsmStrangeFake>> blockStrangeFake;

private:
    int extTempVarNum    = 0;   // 额外的虚拟寄存器
    int extTempMemVarNum = 0;   // 额外的内存常量区

    // 新建虚拟寄存器
    inline string E();

    // 新建内存常量区
    template<class T>
    inline string C(T v);

    // 内存常量区表
    std::unordered_map<string, uint32_t> constMem;

    // 太极图 表示alloca和spill中相对于sp的正偏移。
    std::unordered_map<string, int64_t> taichiMap;
    // 表示太极图部分（alloca和spill）的大小。
    uint64_t taichiSize = 0;
    // 分配一个栈空间。单位字节。按4字节对齐。
    void allocateStackSpace(const string& name, uint64_t size);
    // 查询太极图中的偏移量。是sp的正偏移。
    int64_t queryStackSpace(const string& name);
    // 太极图中真的有吗？如有！
    bool queryInStackSpace(const string& name);

    // 函数返回标签
    string funcRetLabel();

    const std::shared_ptr<MiddleIRFuncDef>& thisFunc;

    void emitBB(const std::shared_ptr<MiddleIRBasicBlock>& bb);

    // Inst Handler
    void handleIMathInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleFMathInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleAllocaInst(const shared_ptr<MiddleIRInst>& inst1);
    void handleLoadInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleStoreInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleICmpNoBr(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleCvtInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    static void
         handleBitcastInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleFCmpInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    static void handleBrInst(
        vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1, const string& funcName
    );
    void handleGEPInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleCallInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleRetInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5FAKESEIHAI_H
