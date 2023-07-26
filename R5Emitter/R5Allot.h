//
// Created by 34042 on 2023/7/25.
//

#ifndef IRBACKENDR5_R5ALLOT_H
#define IRBACKENDR5_R5ALLOT_H

#include "../R5Def.h"
#include "R5Taichi.h"
#include "R5AsmStrangeFake.h"
#include <list>
#include <unordered_map>
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
        size_t      start;
        size_t      end;
    };
    // 用一个图来存储虚拟寄存器的起止位置
    std::unordered_map<std::string, Fakereg> handleinst(R5AsmStrangeFake& instruction, int index)
    {
        std::unordered_map<std::string, Fakereg> virtualReg;

        for (int i = 0; i < 4; i++) {
            if (instruction.defUse[i] != R5AsmStrangeFake::UNUSED) {
                if (std::dynamic_pointer_cast<R5Taichi>(instruction.operands[i])) {
                    std::string virtualRegName = instruction.operands[i]->toString();
                    if (virtualReg.find(virtualRegName) == virtualReg.end()) {
                        virtualReg[virtualRegName].start = index;
                    }
                    virtualReg[virtualRegName].end = index;
                } else {
                    // UNUSED,直接退
                    break;
                }
            }
        }

        return virtualReg;
    }


    void fenkuai(std::list<std::vector<R5Emitter::R5AsmStrangeFake>> blockStrangeFake)
    {
        // 遍历一共多少个基本块
        for (auto bbIt = blockStrangeFake.begin(); bbIt != blockStrangeFake.end(); ++bbIt) {
            int                                       index           = 0;
            std::vector<R5Emitter::R5AsmStrangeFake>& instructionList = *bbIt;
            // 遍历基本块内的指令
            for (auto instIt = instructionList.begin(); instIt != instructionList.end(); ++instIt) {
                R5Emitter::R5AsmStrangeFake& instruction = *instIt;
                // 记录起止
                std::unordered_map<std::string, Fakereg> virtualRegGraph =
                    handleinst(instruction, index);
                index++;
            }
        }
    }
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5ALLOT_H
