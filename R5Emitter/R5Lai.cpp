//
// Created by gaome on 2023/7/21.
//

#include "R5Lai.h"

namespace R5Emitter
{
string R5Lai::toString() const
{
    return std::to_string(value);
}
void R5Lai::negative()
{
    value = -value;
}
}   // namespace R5Emitter