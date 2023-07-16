//
// Created by gaome on 2023/7/14.
//

#ifndef IRBACKENDR5_R5IRVAL_H
#define IRBACKENDR5_R5IRVAL_H

#include <utility>

#include "R5IRType.h"
namespace R5BE
{

class R5IRVal
{
public:
    R5IRVal()          = default;
    virtual ~R5IRVal() = default;

protected:
    SPType _type;
    string _name;

public:
    explicit R5IRVal(SPType type)
        : _type(std::move(type))
    {
    }
    R5IRVal(SPType type, string name): _type(std::move(type)), _name(std::move(name)) {}
    [[nodiscard]] virtual const SPType& getType() const { return _type; }
    void                                setType(const SPType& type) { _type = type; }
    [[nodiscard]] virtual const string& getName() const { return _name; }
    void                                setName(const string& name) { _name = name; }
};

class R5IRValConst : public R5IRVal
{
public:
    explicit R5IRValConst(SPType type_)
        : R5IRVal(std::move(type_))
    {
    }
};

class R5IRValConstInt : public R5IRValConst
{
public:
    explicit R5IRValConstInt(int value_)
        : R5IRValConst(spIntType32)
        , _value(value_)
    {
    }
    [[nodiscard]] bool needLUI() const { return _value > 0x7fff || _value < -0x8000; }

protected:
    int _value;

public:
    [[nodiscard]] int getValue() const { return _value; }
};
#define IR_INT_CONST(_VAL) std::make_shared<R5IRValConstInt>(_VAL)

class R5IRValConstFloat : public R5IRValConst
{
public:
    explicit R5IRValConstFloat(float value_)
        : R5IRValConst(spFloatType)
        , _value(value_)
    {
    }
    explicit R5IRValConstFloat(uint64_t value_)
        : R5IRValConst(spFloatType)
        , _value((float)*reinterpret_cast<double*>(&value_))
    {
    }
    explicit R5IRValConstFloat(double value_)
        : R5IRValConst(spFloatType)
        , _value((float)value_)
    {
    }

protected:
    float _value;

public:
    [[nodiscard]] float getValue() const { return _value; }
};
#define IR_FLOAT_CONST(_VAL) std::make_shared<R5IRValConstFloat>(_VAL)

class R5IRArray : public R5IRVal
{
public:
    R5IRArray(SPType type_, vector<shared_ptr<R5IRVal>> elements_)
        : R5IRVal(std::move(type_))
        , _elements(std::move(elements_))
    {
        IR_ASSERT(_type->type == R5IRType::ARRAY, "R5IRArray::R5IRArray: type must be ARRAY");
        IR_ASSERT(
            _elements.size() == dynamic_cast<ArrayType*>(_type.get())->getSize(),
            "R5IRArray::R5IRArray: size not match"
        );
    }

protected:
    vector<shared_ptr<R5IRVal>> _elements;
};

class R5IRZeroInitializerVal : public R5IRVal
{
public:
    explicit R5IRZeroInitializerVal()
        : R5IRVal(std::move(spZeroInitializerType))
    {
    }
};

}   // namespace R5BE

#endif   // IRBACKENDR5_R5IRVAL_H
