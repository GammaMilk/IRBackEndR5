//
// Created by gaome on 2023/7/20.
//

#include "R5Yin.h"

namespace R5Emitter
{
string R5Yin::toString() const
{
    return regName;
}
bool R5Yin::isFloat() const
{
    return type == Float;
}
bool R5Yin::isInt() const
{
    return type == Int;
}
bool R5Yin::isPointer() const
{
    return type == Pointer;
}
YinType R5Yin::getType() const
{
    return type;
}

// 注意：不生不灭，不垢不净，不增不减
// 不比较type的原因是，只要名字相同，就是同一个虚拟寄存器。type只是辅助信息
bool R5Yin::operator==(const R5Taichi& rhs) const
{
    return R5Taichi::operator==(rhs) && regName == dynamic_cast<const R5Yin&>(rhs).regName;
}
bool R5Yin::operator!=(const R5Taichi& rhs) const
{
    return R5Taichi::operator!=(rhs) || regName != dynamic_cast<const R5Yin&>(rhs).regName;
}
}   // namespace R5Emitter