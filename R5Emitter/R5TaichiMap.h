//
// Created by gaome on 2023/7/25.
//

#ifndef IRBACKENDR5_R5TAICHIMAP_H
#define IRBACKENDR5_R5TAICHIMAP_H
#include "../R5Def.h"
#include <list>
#include <unordered_map>
#include "stack"
namespace R5Emitter
{


class MemoryBlock
{
public:
    int64_t address;
    int64_t size;
    bool    allocated;

    MemoryBlock(int64_t addr, int64_t sz);
};


// 太极图
// 用于记录alloca和spill中相对于sp的正偏移。
// 也需要对已经释放的内存进行回收。
class R5TaichiMap
{
private:
    std::list<MemoryBlock*>                       memory;        // 内存块链表
    std::unordered_map<std::string, MemoryBlock*> allocations;   // 变量名到内存块的映射

public:
    // 分配新的内存块，并返回变量的地址
    int64_t allocate(const std::string& variableName, int64_t size);

    // 释放内存块
    void release(const std::string& variableName);

    // 查询变量地址
    int64_t query(const std::string& variableName);

    // 获取内存大小
    int64_t getSize() const;

    ~R5TaichiMap();
};




}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5TAICHIMAP_H
