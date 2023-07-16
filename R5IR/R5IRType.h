//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_R5IRTYPE_H
#define IRBACKENDR5_R5IRTYPE_H
#include <utility>
#include "../R5Logger.h"
#include "../R5Def.h"
namespace R5BE
{

class R5IRType
{
public:
    enum IRType { INT, FLOAT, VOID, ARRAY, POINTER, FUNCTION, LABEL, ZEROINITIALIZER } type;
    explicit R5IRType(IRType type_)
        : type(type_)
    {
    }
    virtual ~R5IRType() = default;
    virtual bool operator==(const R5IRType& rhs) const
    {
        RUNTIME_ERROR("R5IRType::operator== not implemented");
    }
    [[nodiscard]] inline bool isInt() const { return type == INT; }
    [[nodiscard]] inline bool isFloat() const { return type == FLOAT; }
    [[nodiscard]] inline bool isVoid() const { return type == VOID; }
    [[nodiscard]] inline bool isArray() const { return type == ARRAY; }
    [[nodiscard]] inline bool isPointer() const { return type == POINTER; }
    [[nodiscard]] inline bool isFunction() const { return type == FUNCTION; }
    [[nodiscard]] inline bool isLabel() const { return type == LABEL; }
    [[nodiscard]] inline bool isZeroInitializer() const { return type == ZEROINITIALIZER; }
};
using SPType = std::shared_ptr<R5IRType>;

class IntType : public R5IRType
{
public:
    int bitWidth = 32;

public:
    IntType()
        : R5IRType(INT)
    {
    }
    explicit IntType(int bitWidth_)
        : R5IRType(INT)
        , bitWidth(bitWidth_)
    {
    }
    bool operator==(const R5IRType& rhs) const override
    {
        if (rhs.type == INT) { return bitWidth == dynamic_cast<const IntType&>(rhs).bitWidth; }
        return false;
    }
};

class FloatType : public R5IRType
{
public:
    FloatType()
        : R5IRType(FLOAT)
    {
    }
    bool operator==(const R5IRType& rhs) const override { return rhs.type == FLOAT; }
};

class VoidType : public R5IRType
{
public:
    VoidType()
        : R5IRType(VOID)
    {
    }
    bool operator==(const R5IRType& rhs) const override { return rhs.type == VOID; }
};

class ArrayType : public R5IRType
{
private:
public:
    [[nodiscard]] int           getSize() const { return _size; }
    void                        setSize(int size_) { ArrayType::_size = size_; }
    [[nodiscard]] const SPType& getElementType() const { return _elementType; }
    void setElementType(const SPType& elementType_) { ArrayType::_elementType = elementType_; }

private:
    int    _size;
    SPType _elementType;

public:
    ArrayType(int size_, SPType elementType_)
        : R5IRType(ARRAY)
        , _size(size_)
        , _elementType(std::move(elementType_))
    {
    }
    bool operator==(const R5IRType& rhs) const override
    {
        if (rhs.type == ARRAY) {
            return _size == dynamic_cast<const ArrayType&>(rhs).getSize() &&
                   *_elementType == *dynamic_cast<const ArrayType&>(rhs).getElementType();
        }
        return false;
    }
};

class PointerType : public R5IRType
{
private:
    SPType _elementType;

public:
    explicit PointerType(SPType elementType_)
        : R5IRType(POINTER)
        , _elementType(std::move(elementType_))
    {
    }
    [[nodiscard]] const SPType& getElementType() const { return _elementType; }
    void setElementType(const SPType& elementType_) { PointerType::_elementType = elementType_; }
    bool operator==(const R5IRType& rhs) const override
    {
        if (rhs.type == POINTER) {
            return *_elementType == *dynamic_cast<const PointerType&>(rhs).getElementType();
        }
        return false;
    }
};

class LabelType : public R5IRType
{
public:
    LabelType()
        : R5IRType(LABEL)
    {
    }
    bool operator==(const R5IRType& rhs) const override { return rhs.type == LABEL; }
};

class ZeroInitializerType : public R5IRType
{
public:
    ZeroInitializerType()
        : R5IRType(ZEROINITIALIZER)
    {
    }
    bool operator==(const R5IRType& rhs) const override { return rhs.type == ZEROINITIALIZER; }
};

unique_ptr<R5IRType>        makePointer(const SPType& elementType_);
extern shared_ptr<R5IRType> spVoidType;
extern shared_ptr<R5IRType> spIntType32;
extern shared_ptr<R5IRType> spBoolType;
extern shared_ptr<R5IRType> spFloatType;
extern shared_ptr<R5IRType> spLabelType;
extern shared_ptr<R5IRType> spZeroInitializerType;
}   // namespace R5BE

#endif   // IRBACKENDR5_R5IRTYPE_H
