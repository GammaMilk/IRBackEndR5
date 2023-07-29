//
// Created by gaome on 2023/7/28.
//

#include "R5RegDispatcher.h"
#include <set>
#include <map>
namespace R5Emitter
{

// 优先级顺序，整数：a4-a7, a0-a3, t0-t6, s0-s11, fs0-fs11
// 浮点：fa4-fa7, fa0-fa3, ft0-ft6, fs0-fs11
std::map<YangReg, int> regPri{
    {a4, 0},   {a5, 1},   {a6, 2},   {a7, 3},   {a2, 4},   {a3, 5},   {a0, 6},   {a1, 7},   {t0, 8},   {t1, 9},   {t2, 10},  {t3, 11},  {t4, 12},  {t5, 13},
    {t6, 14},  {s1, 16},  {s2, 17},  {s3, 18},  {s4, 19},  {s5, 20},  {s6, 21},  {s7, 22},  {s8, 23},
    {s9, 24},  {fa4, 25}, {fa5, 26}, {fa6, 27}, {fa7, 28}, {fa2, 29}, {fa3, 30}, {fa0, 31},
    {fa1, 32}, {ft0, 33}, {ft1, 34}, {ft2, 35}, {ft3, 36}, {ft4, 37}, {ft5, 38}, {ft6, 39},
    {fs0, 40}, {fs1, 41}, {fs2, 42}, {fs3, 43}, {fs4, 44}, {fs5, 45}, {fs6, 46}, {fs7, 47},
    {fs8, 48}, {fs9, 49},
};

void R5RegDispatcher::insertReg(std::set<RPri>& regs, YangReg r)
{
    regs.insert({r, regPri[r]});
}
R5RegDispatcher::R5RegDispatcher(R5TaichiMap& taichiMap_)
    : taichiMap(taichiMap_)
{
    for (auto [k, _] : regPri) {
        if (isFloat(k))
            insertReg(freeFRegs, k);
        else
            insertReg(freeIRegs, k);
    }
}
void R5RegDispatcher::releaseIV(const string& vName)
{
    YangReg r = queryReg(vName);
    if (r != InvalidReg) {
        nowUsedRegs.erase(r);
        freeIRegs.insert({r, regPri[r]});
        var2Reg.erase(vName);
        reg2Var.erase(r);
    }
}
void R5RegDispatcher::releaseFV(const string& vName)
{
    YangReg r = queryReg((vName));
    if (r != InvalidReg) {
        nowUsedRegs.erase(r);
        freeFRegs.insert({r, regPri[r]});
        var2Reg.erase((vName));
        reg2Var.erase(r);
    }
}
void R5RegDispatcher::releaseV(const string& vName)
{
    YangReg r = queryReg((vName));
    if (r != InvalidReg) {
        nowUsedRegs.erase(r);
        if (isFloat(r))
            freeFRegs.insert({r, regPri[r]});
        else
            freeIRegs.insert({r, regPri[r]});
        var2Reg.erase((vName));
        reg2Var.erase(r);
    }
}
void R5RegDispatcher::releaseIR(YangReg r)
{
    if (r == InvalidReg) return;
    nowUsedRegs.erase(r);
    freeIRegs.insert({r, regPri[r]});
    var2Reg.erase(reg2Var[r]);
    reg2Var.erase(r);
}
void R5RegDispatcher::releaseFR(YangReg r)
{
    if (r == InvalidReg) return;
    nowUsedRegs.erase(r);
    freeFRegs.insert({r, regPri[r]});
    var2Reg.erase(reg2Var[r]);
    reg2Var.erase(r);
}
void R5RegDispatcher::releaseR(YangReg r)
{
    if (isFloat(r))
        releaseFR(r);
    else
        releaseIR(r);
}
YangReg R5RegDispatcher::allocateIV(const string& vName)
{
    YangReg r = queryReg(vName);
    if (r != InvalidReg) return r;
    if (freeIRegs.empty()) {
        // allocate stack here.
        allocateStack(vName, 8);
        return InvalidReg;
    }
    auto reg = (*freeIRegs.begin()).reg;
    freeIRegs.erase(freeIRegs.begin());
    nowUsedRegs.insert(reg);
    totalUsedRegs.insert(reg);
    reg2Var[reg]   = vName;
    var2Reg[vName] = reg;
    return reg;
}
YangReg R5RegDispatcher::allocateFV(const string& vName)
{
    YangReg r = queryReg(vName);
    if (r != InvalidReg) return r;
    if (freeFRegs.empty()) {
        // allocate stack here.
        allocateStack(vName, 4);
        return InvalidReg;
    }
    auto reg = (*freeFRegs.begin()).reg;
    freeFRegs.erase(freeFRegs.begin());
    nowUsedRegs.insert(reg);
    totalUsedRegs.insert(reg);
    reg2Var[reg]   = vName;
    var2Reg[vName] = reg;
    return reg;
}
YangReg R5RegDispatcher::allocateIR(YangReg r)
{
    if (r == InvalidReg) return r;
    if (freeIRegs.empty()) {
        // allocate stack here.
        return InvalidReg;
    }
    // freeIRegs.erase(freeIRegs.begin()); not works.
    freeIRegs.erase({r, regPri[r]});
    nowUsedRegs.insert(r);
    totalUsedRegs.insert(r);
    return r;
}
YangReg R5RegDispatcher::allocateFR(YangReg r)
{
    if (r == InvalidReg) return r;
    if (freeFRegs.empty()) {
        // allocate stack here.
        return InvalidReg;
    }
    // freeFRegs.erase(freeFRegs.begin()); not works.
    freeFRegs.erase({r, regPri[r]});
    nowUsedRegs.insert(r);
    totalUsedRegs.insert(r);
    return r;
}
YangReg R5RegDispatcher::allocateR(YangReg r)
{
    if (isFloat(r))
        return allocateFR(r);
    else
        return allocateIR(r);
}
int64_t R5RegDispatcher::queryStackOffset(const string& vName)
{
    return taichiMap.query(preTaichi(vName));
}
int64_t R5RegDispatcher::allocateStack(const string& vName, int64_t sz)
{
    return taichiMap.allocate(preTaichi(vName), sz);
}
YangReg R5RegDispatcher::queryReg(const string& vName)
{
    if (var2Reg.find(vName) != var2Reg.end())
        return var2Reg[vName];
    else
        return InvalidReg;
}
std::set<YangReg> R5RegDispatcher::getNowUsedRegs()
{
    return nowUsedRegs;
}
YangReg R5RegDispatcher::getReservedIReg1()
{
    return s10;
}
YangReg R5RegDispatcher::getReservedIReg2()
{
    return s11;
}
YangReg R5RegDispatcher::getReservedFReg1()
{
    return fs10;
}
YangReg R5RegDispatcher::getReservedFReg2()
{
    return fs11;
}
bool R5RegDispatcher::isFloat(YangReg r)
{
    return R5Yang::isFloatReg(r);
}
bool R5RegDispatcher::isInt(YangReg r)
{
    return R5Yang::isIntReg(r);
}
string R5RegDispatcher::preTaichi(const string& vName)
{
    return "!" + vName;
}
const std::set<YangReg>& R5RegDispatcher::getTotalUsedRegs() const
{
    return totalUsedRegs;
}
}   // namespace R5Emitter