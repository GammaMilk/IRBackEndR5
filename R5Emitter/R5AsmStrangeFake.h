//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5ASMSTRANGEFAKE_H
#define IRBACKENDR5_R5ASMSTRANGEFAKE_H
#include "../R5Def.h"
namespace R5Emitter
{

struct R5AsmStrangeFake {
    string op;
    size_t argNum;
    string args[10];
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5ASMSTRANGEFAKE_H
