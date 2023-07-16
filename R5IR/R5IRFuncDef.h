//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_R5IRFUNCDEF_H
#define IRBACKENDR5_R5IRFUNCDEF_H

#include "../R5Def.h"
#include "R5IRVal.h"
#include "R5IRBasicBlock.h"
#include "R5IRFuncDecl.h"
#include <unordered_map>
namespace R5BE
{

class R5IRFuncDef : public R5IRFuncDecl
{
private:
    std::vector<std::shared_ptr<R5IRBasicBlock>>                     _basicBlocks;
    std::unordered_map<std::string, std::shared_ptr<R5IRBasicBlock>> _basicBlockMap;
    std::unordered_map<std::string, std::shared_ptr<R5IRVal>>        _valMap;

public:
    R5IRFuncDef(
        SPType                                       type_,
        std::string                                  name_,
        std::vector<SPType>                          params_types_,
        std::vector<std::string>                     params_names_,
        std::vector<std::shared_ptr<R5IRBasicBlock>> basicBlocks_
    )
        : R5IRFuncDecl(
              std::move(type_), std::move(name_), std::move(params_types_), std::move(params_names_)
          )
        , _basicBlocks(std::move(basicBlocks_))
    {
        for(int i=0;i<_params_names.size();i++) {
            addVal(_params_names[i], std::make_shared<R5IRVal>(_params_types[i],_params_names[i]));
        }
    }
    void addBasicBlock(const std::shared_ptr<R5IRBasicBlock>& basicBlock_)
    {
        _basicBlocks.emplace_back(basicBlock_);
        _basicBlockMap[basicBlock_->getName()] = basicBlock_;
    }
    [[nodiscard]] const std::vector<std::shared_ptr<R5IRBasicBlock>>& getBasicBlocks() const
    {
        return _basicBlocks;
    }
    void setBasicBlocks(const std::vector<std::shared_ptr<R5IRBasicBlock>>& basicBlocks_)
    {
        _basicBlocks = basicBlocks_;
    }
    void addVal(const std::string& name_, const std::shared_ptr<R5IRVal>& val_)
    {
        _valMap[name_] = val_;
    }
    [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<R5IRVal>>& getValMap() const
    {
        return _valMap;
    }
    [[nodiscard]] const std::shared_ptr<R5IRBasicBlock>& getBasicBlock(const std::string& name_
    ) const
    {
        return _basicBlockMap.at(name_);
    }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getVal(const std::string& name_) const
    {
        return _valMap.at(name_);
    }
};

}   // namespace R5BE

#endif   // IRBACKENDR5_R5IRFUNCDEF_H
