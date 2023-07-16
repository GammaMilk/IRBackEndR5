//
// Created by gaome on 2023/7/14.
//

#ifndef IRBACKENDR5_R5IRBASICBLOCK_H
#define IRBACKENDR5_R5IRBASICBLOCK_H

#include "../R5Def.h"
#include "R5IRInst.h"
#include "../R5Logger.h"
#include <list>

namespace R5BE
{
class R5IRBasicBlock
{
private:
    std::string                             _name;
    std::list<std::shared_ptr<R5IRInst>>    _instructions;
    std::vector<shared_ptr<R5IRBasicBlock>> _next;
    std::vector<shared_ptr<R5IRBasicBlock>> _prev;
    std::shared_ptr<R5IRInst>               _terminator;

public:
    explicit R5IRBasicBlock(std::string name_)
        : _name(std::move(name_))
    {
    }
    void addInstruction(std::shared_ptr<R5IRInst> inst)
    {
        _instructions.emplace_back(std::move(inst));
    }
    void addNext(shared_ptr<R5IRBasicBlock> next_) { _next.emplace_back(std::move(next_)); }
    void addPrev(shared_ptr<R5IRBasicBlock> prev_) { _prev.emplace_back(std::move(prev_)); }
    void setTerminator(std::shared_ptr<R5IRInst> terminator_)
    {
        if (_terminator != nullptr)
            LOGW("R5IRBasicBlock::setTerminator: _terminator is not nullptr");
        if (!terminator_->isTerminatorInst())
            RUNTIME_ERROR("R5IRBasicBlock::setTerminator: terminator_ is not a terminator inst");
        _terminator = std::move(terminator_);
    }
    [[nodiscard]] const std::vector<shared_ptr<R5IRBasicBlock>>& getNext() const { return _next; }
    [[nodiscard]] const std::vector<shared_ptr<R5IRBasicBlock>>& getPrev() const { return _prev; }
    [[nodiscard]] std::shared_ptr<R5IRInst> getTerminator() { return _terminator; }
    [[nodiscard]] const std::string&        getName() const { return _name; }
};
}   // namespace R5BE



#endif   // IRBACKENDR5_R5IRBASICBLOCK_H
