//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5TAICHI_H
#define IRBACKENDR5_R5TAICHI_H
#include "../R5Def.h"
namespace R5Emitter
{

// 太极生两仪，两仪生四象，四象生八卦，八卦定吉凶
// 故太极者，抽象寄存器也。两仪谓之阴阳：阴者，柔也；阳者，刚也。
// 是故虚拟寄存器之阴，柔也；物理寄存器之阳，刚也。
class R5Taichi
{
public:
    // 太极生两仪
    enum Phase { Yin, Yang, Ru, Lai } phase;
    [[nodiscard]] inline bool isYang() const { return phase == Yang; }
    [[nodiscard]] inline bool isYin() const { return phase == Yin; }
    [[nodiscard]] inline bool isRu() const { return phase == Ru; }
    [[nodiscard]] inline bool isLai() const { return phase == Lai; }
    virtual bool              operator==(const R5Taichi& rhs) const { return phase == rhs.phase; }
    virtual bool              operator!=(const R5Taichi& rhs) const { return !(rhs == *this); }
    explicit R5Taichi(Phase p)
        : phase(p)
    {
    }
    virtual ~R5Taichi()                           = default;
    [[nodiscard]] virtual string toString() const = 0;
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5TAICHI_H
