//
// Created by gaome on 2023/7/13.
//

#include "R5IRType.h"

namespace R5BE
{
VoidType             voidType;
IntType              intType32(32);
IntType              boolType(1);
FloatType            floatType;
LabelType            labelType;
shared_ptr<R5IRType> spVoidType            = std::make_shared<VoidType>(voidType);
shared_ptr<R5IRType> spIntType32           = std::make_shared<IntType>(intType32);
shared_ptr<R5IRType> spBoolType            = std::make_shared<IntType>(boolType);
shared_ptr<R5IRType> spFloatType           = std::make_shared<FloatType>(floatType);
shared_ptr<R5IRType> spLabelType           = std::make_shared<LabelType>(labelType);
shared_ptr<R5IRType> spZeroInitializerType = std::make_shared<ZeroInitializerType>();
unique_ptr<R5IRType> makePointer(const SPType& elementType_)
{
    return std::make_unique<PointerType>(elementType_);
}
}   // namespace R5BE