//
// Created by gaome on 2023/7/14.
//

#ifndef IRBACKENDR5_R5IRBRINST_H
#define IRBACKENDR5_R5IRBRINST_H

#include <utility>

#include "R5IRInst.h"
#include "R5IRVal.h"
#include "R5IRBasicBlock.h"
namespace R5BE
{
class BrInst : public R5BE::R5IRInst
{
public:
    enum BrType { UnCondBr, CondBr } _brType;

private:
    std::shared_ptr<R5IRVal> _cond;

private:
    std::shared_ptr<R5IRBasicBlock> _ifTrue;
    std::shared_ptr<R5IRBasicBlock> _ifFalse;

public:
    [[nodiscard]] const string& getIfTrueLabel() const { return _ifTrueLabel; }
    [[nodiscard]] const string& getIfFalseLabel() const { return _ifFalseLabel; }

private:
    string _ifTrueLabel;
    string _ifFalseLabel;

public:
    BrInst(
        BrType                                 brType_,
        std::shared_ptr<R5IRVal>               cond_,
        const std::shared_ptr<R5IRBasicBlock>& ifTrue_,
        const std::shared_ptr<R5IRBasicBlock>& ifFalse_
    )
        : R5IRInst(R5IRInst::InstType::BrInst, spVoidType)
        , _brType(brType_)
        , _cond(std::move(cond_))
        , _ifTrue(ifTrue_)
        , _ifFalse(ifFalse_)
    {
    }
    BrInst(
        BrType brType_, std::shared_ptr<R5IRVal> cond_, string ifTrueLabel_, string ifFalseLabel_
    )
        : R5IRInst(R5IRInst::InstType::BrInst, spVoidType)
        , _brType(brType_)
        , _cond(std::move(cond_))
        , _ifTrueLabel(std::move(ifTrueLabel_))
        , _ifFalseLabel(std::move(ifFalseLabel_))
    {
    }
    [[nodiscard]] const std::shared_ptr<R5IRVal>&        getCond() const { return _cond; }
    [[nodiscard]] const std::shared_ptr<R5IRBasicBlock>& getIfTrue() const { return _ifTrue; }
    [[nodiscard]] const std::shared_ptr<R5IRBasicBlock>& getIfFalse() const { return _ifFalse; }
    void setIfTrue(const shared_ptr<R5IRBasicBlock>& ifTrue) { _ifTrue = ifTrue; }
    void setIfFalse(const shared_ptr<R5IRBasicBlock>& ifFalse) { _ifFalse = ifFalse; }
};
}   // namespace R5BE
#endif   // IRBACKENDR5_R5IRBRINST_H
