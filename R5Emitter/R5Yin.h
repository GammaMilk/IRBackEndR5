//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5YIN_H
#define IRBACKENDR5_R5YIN_H

#include <utility>

#include "R5Taichi.h"
namespace R5Emitter
{
enum YinType { Float, Int, Pointer };
// 阴，虚也
// 故此处作为虚拟寄存器
class R5Yin : public R5Taichi
{
public:
    explicit R5Yin(string name, YinType type_)
        : R5Taichi(Yin)
        , regName(std::move(name))
        , type(type_)
    {
    }
    string               regName;
    YinType              type;
    [[nodiscard]] string toString() const override;
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5YIN_H
