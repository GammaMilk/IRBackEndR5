//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_R5IRAST_H
#define IRBACKENDR5_R5IRAST_H
#include "../R5Def.h"
#include "R5IRFuncDef.h"
#include "R5IRGlobalVar.h"
#include "R5IRGlobalConst.h"
namespace R5BE
{

struct R5IRAST {
    virtual ~R5IRAST() = default;
    std::vector<std::shared_ptr<R5IRFuncDef>>     funcDefs;
    std::vector<std::shared_ptr<R5IRFuncDecl>>    funcDecls;
    std::vector<std::shared_ptr<R5IRGlobalVar>>   globalVars;
    std::vector<std::shared_ptr<R5IRGlobalConst>> globalConsts;
    [[nodiscard]] shared_ptr<R5IRVal> findVal(const std::string& name) const {
        for (const auto& funcDef : funcDefs) {
            if (funcDef->getName() == name) {
                return funcDef;
            }
        }
        for (const auto& funcDecl : funcDecls) {
            if (funcDecl->getName() == name) {
                return funcDecl;
            }
        }
        for (const auto& globalVar : globalVars) {
            if (globalVar->getName() == name) {
                return globalVar;
            }
        }
        for (const auto& globalConst : globalConsts) {
            if (globalConst->getName() == name) {
                return globalConst;
            }
        }
        return nullptr;
    }
};

}   // namespace R5BE

#endif   // IRBACKENDR5_R5IRAST_H
