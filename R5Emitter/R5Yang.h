//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5YANG_H
#define IRBACKENDR5_R5YANG_H

#include "R5Taichi.h"
namespace R5Emitter
{

// ☰, ☱, ☲, ☳
// ䷗䷚䷂䷩䷲䷔䷐䷘䷣䷕䷾䷤䷶䷝䷰䷌䷒䷨䷻䷼䷵䷥䷹䷉䷊䷙䷄䷈䷡䷍䷪䷀
class R5Yang : public R5Taichi
{
    // 阳，乾，天，刚，健，父，君，君子，圣人，圣贤，圣人之道，
    // 于编译器后端，于刚，于健，于父，于君，于物理寄存器
    /**
     *
     */
public:
    // 乾 ☰
    enum {
        zero,
        ra,
        sp,
        gp,
        tp,
        t0,
        t1,
        t2,
        t3,
        t4,
        t5,
        t6,
        a0,
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        s0,
        s1,
        s2,
        s3,
        s4,
        s5,
        s6,
        s7,
        s8,
        s9,
        s10,
        s11
    };
    inline bool isCallerSave(size_t reg) { return reg >= t0 && reg <= t6; }
    inline bool isCalleeSave(size_t reg) { return reg >= s0 && reg <= s11; }
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5YANG_H
