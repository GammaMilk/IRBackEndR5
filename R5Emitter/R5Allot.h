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
#include "R5Yang.h"
#include "R5Yin.h"
#include <set>
#include <string>
namespace R5Emitter
{
class R5Allot
{
public:



    std::string ToString(YangReg reg){
        switch (reg) {
        case zero: return "zero";
        case ra: return "ra";
        case sp: return "sp";
        case gp: return "gp";
        case tp: return "tp";
        case t0: return "t0";
        case t1: return "t1";
        case t2: return "t2";
        case t3: return "t3";
        case t4: return "t4";
        case t5: return "t5";
        case t6: return "t6";
        case a0: return "a0";
        case a1: return "a1";
        case a2: return "a2";
        case a3: return "a3";
        case a4: return "a4";
        case a5: return "a5";
        case a6: return "a6";
        case a7: return "a7";
        case s0: return "s0";
        case s1: return "s1";
        case s2: return "s2";
        case s3: return "s3";
        case s4: return "s4";
        case s5: return "s5";
        case s6: return "s6";
        case s7: return "s7";
        case s8: return "s8";
        case s9: return "s9";
        case s10: return "s10";
        case s11: return "s11";
        case ft0: return "ft0";
        case ft1: return "ft1";
        case ft2: return "ft2";
        case ft3: return "ft3";
        case ft4: return "ft4";
        case ft5: return "ft5";
        case ft6: return "ft6";
        case ft7: return "ft7";
        case ft8: return "ft8";
        case ft9: return "ft9";
        case ft10: return "ft10";
        case ft11: return "ft11";
        case fa0: return "fa0";
        case fa1: return "fa1";
        case fa2: return "fa2";
        case fa3: return "fa3";
        case fa4: return "fa4";
        case fa5: return "fa5";
        case fa6: return "fa6";
        case fa7: return "fa7";
        case fs0: return "fs0";
        case fs1: return "fs1";
        case fs2: return "fs2";
        case fs3: return "fs3";
        case fs4: return "fs4";
        case fs5: return "fs5";
        case fs6: return "fs6";
        case fs7: return "fs7";
        case fs8: return "fs8";
        case fs9: return "fs9";
        case fs10: return "fs10";
        case fs11: return "fs11";
        }

    }

    YangReg getRegisterByName(const std::string& regName) {
        if (regName == "zero") return zero;
        if (regName == "ra") return ra;
        if (regName == "sp") return sp;
        if (regName == "gp") return gp;
        if (regName == "tp") return tp;
        if (regName == "t0") return t0;
        if (regName == "t1") return t1;
        if (regName == "t2") return t2;
        if (regName == "t3") return t3;
        if (regName == "t4") return t4;
        if (regName == "t5") return t5;
        if (regName == "t6") return t6;
        if (regName == "a0") return a0;
        if (regName == "a1") return a1;
        if (regName == "a2") return a2;
        if (regName == "a3") return a3;
        if (regName == "a4") return a4;
        if (regName == "a5") return a5;
        if (regName == "a6") return a6;
        if (regName == "a7") return a7;
        if (regName == "s0") return s0;
        if (regName == "s1") return s1;
        if (regName == "s2") return s2;
        if (regName == "s3") return s3;
        if (regName == "s4") return s4;
        if (regName == "s5") return s5;
        if (regName == "s6") return s6;
        if (regName == "s7") return s7;
        if (regName == "s8") return s8;
        if (regName == "s9") return s9;
        if (regName == "s10") return s10;
        if (regName == "s11") return s11;
        if (regName == "ft0") return ft0;
        if (regName == "ft1") return ft1;
        if (regName == "ft2") return ft2;
        if (regName == "ft3") return ft3;
        if (regName == "ft4") return ft4;
        if (regName == "ft5") return ft5;
        if (regName == "ft6") return ft6;
        if (regName == "ft7") return ft7;
        if (regName == "ft8") return ft8;
        if (regName == "ft9") return ft9;
        if (regName == "ft10") return ft10;
        if (regName == "ft11") return ft11;
        if (regName == "fa0") return fa0;
        if (regName == "fa1") return fa1;
        if (regName == "fa2") return fa2;
        if (regName == "fa3") return fa3;
        if (regName == "fa4") return fa4;
        if (regName == "fa5") return fa5;
        if (regName == "fa6") return fa6;
        if (regName == "fa7") return fa7;
        if (regName == "fs0") return fs0;
        if (regName == "fs1") return fs1;
        if (regName == "fs2") return fs2;
        if (regName == "fs3") return fs3;
        if (regName == "fs4") return fs4;
        if (regName == "fs5") return fs5;
        if (regName == "fs6") return fs6;
        if (regName == "fs7") return fs7;
        if (regName == "fs8") return fs8;
        if (regName == "fs9") return fs9;
        if (regName == "fs10") return fs10;
        if (regName == "fs11") return fs11;

        // 如果没有找到匹配的寄存器名字，则返回默认的寄存器
        return zero;
    }

    enum YangType { Float, Int, Pointer } type;





    struct Fakereg {
        int start;
        int end;
        YangType type;
        std::string regName;
        Fakereg() : start(-1), end(-1) {}
    };


    struct Node {
        Fakereg data;
        std::shared_ptr<Node> next;
        Node(const Fakereg& d) : data(d), next(nullptr) {}
    };

    //将活跃区间排序
    void insertact(std::shared_ptr<Node>& active, const Fakereg& data)
    {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(data);
        if (!active || active->data.start > data.start) {
            newNode->next = active;
            active        = newNode;
        } else {
            std::shared_ptr<Node> curr = active;
            while (curr->next && curr->next->data.start <= data.start) { curr = curr->next; }
            newNode->next = curr->next;
            curr->next    = newNode;
        }
    }


    // 用一个图来存储虚拟寄存器的起止位置
    std::unordered_map<std::string, Fakereg> handleinst(R5AsmStrangeFake& instruction, int index)
    {
        std::unordered_map<std::string, Fakereg> virtualReg;

        for (int i = 0; i < 4; i++) {
            if (instruction.defUse[i] != R5AsmStrangeFake::UNUSED) {
                if (std::dynamic_pointer_cast<R5Yin>(instruction.operands[i])) {
                    std::string virtualRegName = instruction.operands[i]->toString();
                    virtualReg[virtualRegName].type = instruction.operands[i] ;
                    if (virtualReg.find(virtualRegName) == virtualReg.end()) {
                        virtualReg[virtualRegName].start = index;
                        virtualReg[virtualRegName].regName = virtualRegName; // 存储寄存器名字
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

    YangReg getUnusedRegister(const std::set<YangReg>& usedRegs , R5Yin& opprands) {
        // todo 用于获取一个未使用的寄存器
        YangReg availableRegs[] = { t0, t1, t2, t3, t4, t5, t6, a0, a1, a2, a3, a4, a5, a6, a7, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, ft0, ft1, ft2, ft3, ft4, ft5, ft6, ft7, ft8, ft9, ft10, ft11, fa0, fa1, fa2, fa3, fa4, fa5, fa6, fa7, fs0, fs1, fs2, fs3, fs4, fs5, fs6, fs7, fs8, fs9, fs10, fs11 };

        // 遍历所有可用的物理寄存器，找到一个未被使用的寄存器
        for (YangReg reg : availableRegs) {
            if (usedRegs.find(reg) == usedRegs.end()) {
                YinType virtualRegType = opprands.getType();
                if (reg == getRegisterByName(virtualRegType)) {
                    return reg; // 匹配则返回当前物理寄存器
                }
            }
        }

        // 如果所有的物理寄存器都已经被使用，返回默认寄存器 zero
        return zero;// 返回默认寄存器
    }

    struct SpillSlot {
        std::string name; // 栈上空间的名称
        // 可以添加其他字段，比如大小、偏移量等
    };




    void fenkuai(std::list<std::vector<R5Emitter::R5AsmStrangeFake>> blockStrangeFake)
    {
        // 遍历一共多少个基本块
        for (auto bbIt = blockStrangeFake.begin(); bbIt != blockStrangeFake.end(); ++bbIt) {
            int index = 0;
            std::vector<R5Emitter::R5AsmStrangeFake>& instructionList = *bbIt;
            std::unordered_map<std::string, Fakereg> virtualRegGraph;
            // 遍历基本块内的指令
            for (auto instIt = instructionList.begin(); instIt != instructionList.end(); ++instIt) {
                R5Emitter::R5AsmStrangeFake& instruction = *instIt;
                // 记录起止
                 virtualRegGraph = handleinst(instruction, index);
                index++;
            }
            std::shared_ptr<Node> active = nullptr;
            //将活跃区间排序
            for (const auto& entry : virtualRegGraph) {
                insertact(active, entry.second);
            }
            std::set<YangReg> usedRegs; // 已经使用的寄存器 ?
            std::shared_ptr<Node> curr = active;
            while (curr) {
                const Fakereg& regInfo = curr->data;
                if (usedRegs.size() < 16) {
                    // 有空余寄存器，直接分配
                    R5Emitter::YangReg allocatedReg = getUnusedRegister(usedRegs);
                    usedRegs.insert(allocatedReg);
                    virtualRegGraph[regInfo.regName].regName = ToString(allocatedReg);
                } else {
                    // 没有空余寄存器，需要释放老活跃区间的寄存器
                    std::shared_ptr<Node> prev = nullptr;
                    std::shared_ptr<Node> oldCurr = active;
                    while (oldCurr != curr) {
                        if (oldCurr->data.end <= regInfo.start) {
                            // 老活跃区间的结束位置小于等于新活跃区间的起点，释放寄存器
                            YangReg oldReg = getRegisterByName(oldCurr->data.regName);
                            usedRegs.erase(oldReg);
                            if (prev) {
                                prev->next = oldCurr->next;
                            } else {
                                active = oldCurr->next;
                            }
                            oldCurr = oldCurr->next;
                        } else {
                            //spill
                        }
                    }
                    YangReg allocatedReg = getUnusedRegister(usedRegs); // 获取一个未使用的寄存器
                    usedRegs.insert(allocatedReg);
                    virtualRegGraph[regInfo.regName].regName = ToString(allocatedReg); // 更新虚拟寄存器对应的物理寄存器名字
                }
                curr = curr->next;
            }
            for(auto& instruction : instructionList){
                for (int i = 0; i < 4; i++) {
                    if (instruction.defUse[i] != R5AsmStrangeFake::UNUSED){
                        if (std::dynamic_pointer_cast<R5Yin>(instruction.operands[i])){

                            std::string virtualRegName = instruction.operands[i]->toString();
                            instruction.operands[i] = std::make_shared<R5Yang>(getRegisterByName(virtualRegGraph[virtualRegName].regName));
                        }
                    }
                }
            }


        }
    }




};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5ALLOT_H
