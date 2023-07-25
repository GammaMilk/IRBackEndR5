//
// Created by 34042 on 2023/7/25.
//

#ifndef IRBACKENDR5_R5ALLOT_H
#define IRBACKENDR5_R5ALLOT_H

#include "../R5Def.h"
#include "R5Taichi.h"
#include "R5AsmStrangeFake.h"
#include <list>
namespace R5Emitter
{
class R5Allot
{
public:
    std::vector<R5Emitter::R5AsmStrangeFake>
    getfake(const std::list<std::vector<R5Emitter::R5AsmStrangeFake>>& blockStrangeFakeList)
    {
        std::vector<R5Emitter::R5AsmStrangeFake> processedList;

        for (const auto& blockStrangeFake : blockStrangeFakeList) {
            for (const auto& asmStrangeFake : blockStrangeFake) {
                // 在这里对asmStrangeFake进行处理，例如将其加入到processedList中
                processedList.push_back(asmStrangeFake);
            }
        }
        return processedList;
    }

    struct Fakereg {
        std::string regName;
        int         start;
        int         end;
    };

    std::vector<Fakereg> linescan(std::vector<R5Emitter::R5AsmStrangeFake>& processedList) {}
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5ALLOT_H
