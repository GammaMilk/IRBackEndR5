//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_R5IRFUNCDECL_H
#define IRBACKENDR5_R5IRFUNCDECL_H
#include <utility>

#include "R5IRType.h"
#include "../R5Def.h"
#include "R5IRVal.h"
namespace R5BE
{

class R5IRFuncDecl : public R5IRVal
{
protected:
    SPType                   _retType;
    std::vector<SPType>      _params_types;
    std::vector<std::string> _params_names;

public:
    R5IRFuncDecl(
        SPType                   type_,
        std::string              name_,
        std::vector<SPType>      params_types_,
        std::vector<std::string> params_names_
    )
        : R5IRVal(make_shared<R5IRType>(R5IRType::FUNCTION))
        , _retType(std::move(type_))
        , _params_types(std::move(params_types_))
        , _params_names(std::move(params_names_))
    {
        _name = std::move(name_);
        IR_ASSERT(_params_types.size() == _params_names.size(), "params_types.size() != params_names.size()");
    }
    [[nodiscard]] const SPType& getRetType() const { return _retType; }
};

}   // namespace R5BE

#endif   // IRBACKENDR5_R5IRFUNCDECL_H
