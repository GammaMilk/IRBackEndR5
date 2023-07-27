//
// Created by gaome on 2023/7/26.
//

#include "R5RegAllocator.h"

#include <utility>

namespace R5Emitter
{
R5RegAllocator::R5RegAllocator(
    const std::list<string>&                        bbNames_,
    const std::list<std::vector<R5AsmStrangeFake>>& bbCodes_,
    R5TaichiMap&                                    taichiMap_,
    fu                                              fu_
)
    : taichiMap(taichiMap_)
    , _fu(std::move(fu_))
{
    bbNames = std::vector<string>(bbNames_.begin(), bbNames_.end());
    bbCodes = std::vector<std::vector<R5AsmStrangeFake>>(bbCodes_.begin(), bbCodes_.end());
    // 初始化分配结果
    allocatedCodes = std::vector<std::vector<R5AsmStrangeFake>>(bbCodes.size());

    // 开始分配
    doAllocate();
}
void R5RegAllocator::doAllocate()
{
    for (int i = 0; i < bbCodes.size(); i++) { doAllocate(i); }
}

using lsPair = std::pair<int, int>;
// 一个寄存器的lifespan，可能有多个生死段。
// 必须倒序扫描基本块，才能构建lifespan。
// 先死而后生，此乃生死循环。凤凰涅槃，浴火重生。
struct Phoenix {
    std::list<lsPair> ls;
    inline void       death(int j)
    {
        if (ls.empty()) {
            // 新建一个生死段
            ls.emplace_back(-1, j);
        } else {
            // 如果最后段的死亡时间是-1，那么就更新它的死亡时间，否则新建一个生死段
            if (ls.back().first == -1) {   // 说明这个段还没活过来
                ;                          // 不必更新
            } else {
                ls.emplace_back(-1, j);
            }
        }
    }
    inline void birth(int j)
    {
        if (ls.empty()) {
            // 新建一个生死段
            ls.emplace_back(j, -1);
        } else {
            // 直接更新最后段的出生时间
            ls.back().first = j;
        }
    }
    inline bool isDead(int j)
    {
        if (ls.empty()) {
            return false;
        } else {
            // 它是个范围，所以要用>=
            if (ls.back().second == -1 || ls.back().first != -1)
                return false;
            else
                return ls.back().second >= j;
        }
    }
    [[maybe_unused]] inline bool isBorn(int j) { return false; }
    inline bool                  isFree(int j)
    {
        if (ls.empty()) {
            return true;
        } else {
            // 范围，是范围！
            return (!isDead(j)) && ls.back().second < j;
        }
    }
    inline bool isComplete()
    {
        if (ls.empty()) {
            return false;
        } else {
            return (ls.back().second != -1) && (ls.back().first != -1);
        }
    }
    // 重载<，用于排序.仅对虚拟寄存器有效。
    inline bool operator<(const Phoenix& rhs) const
    {
        if (ls.empty() || rhs.ls.empty()) {
            return false;
        } else {
            return ls.back().second < rhs.ls.back().second;
        }
    }
};
struct MachineRegPri {
    int    pri;
    string name;
    MachineRegPri(int pri_, string name_)
        : pri(pri_)
        , name(std::move(name_))
    {
    }
    bool operator<(const MachineRegPri& rhs) const { return pri < rhs.pri; }
};

// 优先级顺序，整数：a4-a7, a0-a3, t0-t6, s0-s11, fs0-fs11
// 浮点：fa4-fa7, fa0-fa3, ft0-ft6, fs0-fs11
std::set<MachineRegPri> integerRegAva{
    {0, "a4"}, {0, "a5"}, {0, "a6"}, {0, "a7"}, {1, "a0"},  {1, "a1"},  {1, "a2"},
    {1, "a3"}, {2, "t0"}, {2, "t1"}, {2, "t2"}, {2, "t3"},  {2, "t4"},  {2, "t5"},
    {2, "t6"}, {3, "s0"}, {3, "s1"}, {3, "s2"}, {3, "s3"},  {3, "s4"},  {3, "s5"},
    {3, "s6"}, {3, "s7"}, {3, "s8"}, {3, "s9"}, {3, "s10"}, {3, "s11"},
};
std::set<MachineRegPri> floatRegAva{
    {0, "fa4"}, {0, "fa5"}, {0, "fa6"}, {0, "fa7"}, {1, "fa0"},  {1, "fa1"},  {1, "fa2"},
    {1, "fa3"}, {2, "ft0"}, {2, "ft1"}, {2, "ft2"}, {2, "ft3"},  {2, "ft4"},  {2, "ft5"},
    {2, "ft6"}, {3, "fs0"}, {3, "fs1"}, {3, "fs2"}, {3, "fs3"},  {3, "fs4"},  {3, "fs5"},
    {3, "fs6"}, {3, "fs7"}, {3, "fs8"}, {3, "fs9"}, {3, "fs10"}, {3, "fs11"},
};

void R5RegAllocator::doAllocate(int i)
{
    auto& bb   = bbCodes[i];
    auto& dest = allocatedCodes[i];
    // 构建每个寄存器的lifespan。（unordered_map)
    std::unordered_map<string, Phoenix> lifespan;
    // 倒序扫描基本块，构建lifespan
    for (int j = (int)bb.size() - 1; j >= 0; --j) {
        auto inst = bb[j];
        auto def  = inst.getDefReg();
        auto use  = inst.getUsedRegs();
        // 构建lifespan
        // 一Call而万物死
        if (inst.fakeOP == CALL) {
            // 而如果a0,fa0被用到，那么涅槃重生。
            if (lifespan.find("a0") != lifespan.end()) {
                if (lifespan["a0"].isDead(j)) lifespan["a0"].birth(j);
            }
            if (lifespan.find("fa0") != lifespan.end()) {
                if (lifespan["fa0"].isDead(j)) lifespan["fa0"].birth(j);
            }
            // 死哪些？我们可以知道。
            auto dead = getUsedRegs(inst.operands[0]->toString());
            for (auto t : dead) {
                // 无论如何，都要死
                lifespan[R5Yang::toString(t)].death(j);
            }
        }
        // 死
        for (const auto& r1 : use) {
            string name;
            if (auto ur = dynamic_pointer_cast<R5Yang>(r1)) name = ur->toString();
            if (auto ur2 = dynamic_pointer_cast<R5Yin>(r1)) name = ur2->toString();
            if (!name.empty()) lifespan[name].death(j);
        }
        // 生
        if (def) {
            string name;
            if (auto d = dynamic_pointer_cast<R5Yang>(def)) name = d->toString();
            if (auto d2 = dynamic_pointer_cast<R5Yin>(def)) name = d2->toString();
            if (!name.empty()) lifespan[name].birth(j);
        }
    }
    // 在lifespan 中 去除zero, sp, ra, s0
    lifespan.erase("zero");
    lifespan.erase("sp");
    lifespan.erase("ra");
    lifespan.erase("s0");
    // 修正所有-1开始的lifespan，改为0开始。
    for (auto& [name, ls] : lifespan) {
        for (auto& [birth, death] : ls.ls) {
            if (birth == -1) birth = 0;
        }
    }
    // 修正所有-1结束的lifespan，改为bb.size()-1结束。
    for (auto& [name, ls] : lifespan) {
        for (auto& [birth, death] : ls.ls) {
            if (death == -1) death = (int)bb.size() - 1;
        }
    }

    // 构建结束。开始分配。
    // 优先级顺序，整数：a4-a7, a0-a3, t0-t6, s0-s11, fs0-fs11
    // 浮点：fa4-fa7, fa0-fa3, ft0-ft6, fs0-fs11
}
std::set<YangReg> R5RegAllocator::getUsedRegs(string funcName)
{
    // if starts with "@" , then remove "@"
    if (funcName[0] == '@') { funcName = funcName.substr(1); }
    if (funcName == "memset") return {a0, a1, a2};
    return _fu[funcName];
}

}   // namespace R5Emitter