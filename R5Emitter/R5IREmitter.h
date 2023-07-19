//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5IREMITTER_H
#define IRBACKENDR5_R5IREMITTER_H
#include <utility>

#include "../R5Def.h"
#include "../MiddleIR/MiddleIRAST.h"
namespace R5Emitter
{
class R5IREmitter
{
public:
    ~R5IREmitter() = default;
    explicit R5IREmitter(shared_ptr<MiddleIR::MiddleIRAST> ast_): _middleIRAST(std::move(ast_)) {}
    void build(std::ostream& os);

protected:
    shared_ptr<MiddleIR::MiddleIRAST> _middleIRAST;
};
}
#endif   // IRBACKENDR5_R5IREMITTER_H
