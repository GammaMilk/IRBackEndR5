//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_R5IRINST_H
#define IRBACKENDR5_R5IRINST_H

#include <utility>

#include "R5IRType.h"
#include "R5IRVal.h"
#include "R5IRFuncDecl.h"
namespace R5BE
{

class R5IRInst : public R5IRVal
{
public:
    enum InstType {
        AllocaInst,
        ReturnInst,
        BrInst,
        IMathInst,
        FMathInst,
        ICmpInst,
        FCmpInst,
        LoadInst,
        StoreInst,
        BitCastInst,
        GetElementPtrInst,
        ConvertInst,
        CallInst
    } _instType;
    explicit R5IRInst(InstType instType_, SPType retType_)
        : _instType(instType_)
        , R5IRVal(std::move(retType_))
    {
    }
    inline static bool isAllocaInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::AllocaInst;
    }
    inline static bool isReturnInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::ReturnInst;
    }
    inline static bool isBrInst(const R5IRInst& inst) { return inst._instType == InstType::BrInst; }
    inline static bool isTerminatorInst(const R5IRInst& inst)
    {
        return isReturnInst(inst) || isBrInst(inst);
    }
    inline static bool isIMathInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::IMathInst;
    }
    inline static bool isFMathInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::FMathInst;
    }
    inline static bool isMathInst(const R5IRInst& inst)
    {
        return isIMathInst(inst) || isFMathInst(inst);
    }
    inline static bool isLoadInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::LoadInst;
    }
    inline static bool isStoreInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::StoreInst;
    }
    inline static bool isBitCastInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::BitCastInst;
    }
    inline static bool isGetElementPtrInst(const R5IRInst& inst)
    {
        return inst._instType == InstType::GetElementPtrInst;
    }

    // object method
    [[nodiscard]] inline bool isAllocaInst() const { return _instType == InstType::AllocaInst; }
    [[nodiscard]] inline bool isReturnInst() const { return _instType == InstType::ReturnInst; }
    [[nodiscard]] inline bool isBrInst() const { return _instType == InstType::BrInst; }
    [[nodiscard]] inline bool isTerminatorInst() const { return isReturnInst() || isBrInst(); }
    [[nodiscard]] inline bool isIMathInst() const { return _instType == InstType::IMathInst; }
    [[nodiscard]] inline bool isFMathInst() const { return _instType == InstType::FMathInst; }
    [[nodiscard]] inline bool isMathInst() const { return isIMathInst() || isFMathInst(); }
    [[nodiscard]] inline bool isLoadInst() const { return _instType == InstType::LoadInst; }
    [[nodiscard]] inline bool isStoreInst() const { return _instType == InstType::StoreInst; }
    [[nodiscard]] inline bool isBitCastInst() const { return _instType == InstType::BitCastInst; }
    [[nodiscard]] inline bool isGetElementPtrInst() const
    {
        return _instType == InstType::GetElementPtrInst;
    }
    [[nodiscard]] InstType getInstType() const { return _instType; }

    // virtual destructor
    ~R5IRInst() override = default;
};

class AllocaInst : public R5IRInst
{
private:
public:
    AllocaInst(std::string name_, const SPType& type_)
        : R5IRInst(InstType::AllocaInst, std::move(makePointer(type_)))
    {
        _name = std::move(name_);
    }
};

class ReturnInst : public R5IRInst
{
private:
    SPType                   _opType;
    std::shared_ptr<R5IRVal> _opVal;

public:
    ReturnInst(SPType opType_, std::shared_ptr<R5IRVal> opVal_)
        : R5IRInst(InstType::ReturnInst, opType_)
        , _opType(std::move(opType_))
        , _opVal(std::move(opVal_))
    {
    }
    [[nodiscard]] const SPType&                   getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal() const { return _opVal; }
};

class ICmpInst : public R5IRInst
{
public:
    enum ICmpOp { EQ, NE, SGT, SGE, SLT, SLE, UGE, UGT, ULE, ULT } iCmpOp;
    ICmpInst(
        ICmpOp                   iMathOp_,
        SPType                   opType_,
        std::shared_ptr<R5IRVal> opVal1_,
        std::shared_ptr<R5IRVal> opVal2_
    )
        : R5IRInst(InstType::ICmpInst, spBoolType)
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , iCmpOp(iMathOp_)
    {
    }
    [[nodiscard]] const SPType&                   getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal1() const { return _opVal1; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal2() const { return _opVal2; }
    static ICmpOp fromString(const string& op_){
        if(op_ == "eq") return ICmpOp::EQ;
        if(op_ == "ne") return ICmpOp::NE;
        if(op_ == "sgt") return ICmpOp::SGT;
        if(op_ == "sge") return ICmpOp::SGE;
        if(op_ == "slt") return ICmpOp::SLT;
        if(op_ == "sle") return ICmpOp::SLE;
        if(op_ == "uge") return ICmpOp::UGE;
        if(op_ == "ugt") return ICmpOp::UGT;
        if(op_ == "ule") return ICmpOp::ULE;
        if(op_ == "ult") return ICmpOp::ULT;
        IR_ASSERT(false, "invalid ICmpOp: "<<op_);
    }

private:
    SPType                   _opType;
    std::shared_ptr<R5IRVal> _opVal1;
    std::shared_ptr<R5IRVal> _opVal2;
};

class FCmpInst : public R5IRInst
{
public:
    enum class FCmpOp {
        FALSE,
        OEQ,
        OGE,
        OGT,
        OLE,
        OLT,
        TRUE,
        UEQ,
        UGE,
        UGT,
        ULE,
        ULT,
        UNE,
        UNO
    } fCmpOp;
    FCmpInst(
        FCmpOp                   fMathOp_,
        SPType                   opType_,
        std::shared_ptr<R5IRVal> opVal1_,
        std::shared_ptr<R5IRVal> opVal2_
    )
        : R5IRInst(InstType::FCmpInst, spBoolType)
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , fCmpOp(fMathOp_)
    {
    }
    [[nodiscard]] FCmpOp getFCmpOp() const { return fCmpOp; }
    static FCmpOp fromString(const string& op_) {
        if(op_ == "false") return FCmpOp::FALSE;
        if(op_ == "oeq") return FCmpOp::OEQ;
        if(op_ == "oge") return FCmpOp::OGE;
        if(op_ == "ogt") return FCmpOp::OGT;
        if(op_ == "ole") return FCmpOp::OLE;
        if(op_ == "olt") return FCmpOp::OLT;
        if(op_ == "true") return FCmpOp::TRUE;
        if(op_ == "ueq") return FCmpOp::UEQ;
        if(op_ == "uge") return FCmpOp::UGE;
        if(op_ == "ugt") return FCmpOp::UGT;
        if(op_ == "ule") return FCmpOp::ULE;
        if(op_ == "ult") return FCmpOp::ULT;
        if(op_ == "une") return FCmpOp::UNE;
        if(op_ == "uno") return FCmpOp::UNO;
        IR_ASSERT(false, "invalid FCmpOp: "<<op_);
    }

private:
    SPType                   _opType;
    std::shared_ptr<R5IRVal> _opVal1;
    std::shared_ptr<R5IRVal> _opVal2;
};

class LoadInst : public R5IRInst
{
public:
    LoadInst(const std::shared_ptr<R5IRVal>& from_, SPType type_)
        : R5IRInst(InstType::LoadInst, std::move(type_))
        , _from(from_)
    {
    }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal() const { return _from; }

protected:
    std::shared_ptr<R5IRVal> _from;
};

class StoreInst : public R5IRInst
{
public:
    StoreInst(shared_ptr<R5IRVal> from_, shared_ptr<R5IRVal> to_)
        : R5IRInst(InstType::StoreInst, spVoidType)
        , _from(std::move(from_))
        , _to(std::move(to_))
    {
    }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal1() const { return _from; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal2() const { return _to; }

protected:
    std::shared_ptr<R5IRVal> _from;
    std::shared_ptr<R5IRVal> _to;
};

class IMathInst : public R5IRInst
{
public:
    enum class IMathOp { ADD, SUB, MUL, SDIV, SREM, UDIV, UREM } iMathOp;
    IMathInst(
        IMathOp                  iMathOp_,
        SPType                   opType_,
        std::shared_ptr<R5IRVal> opVal1_,
        std::shared_ptr<R5IRVal> opVal2_
    )
        : R5IRInst(InstType::IMathInst, std::move(opType_))
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , iMathOp(iMathOp_)
    {
    }
    [[nodiscard]] const SPType&                   getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal1() const { return _opVal1; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal2() const { return _opVal2; }

protected:
    SPType                   _opType;
    std::shared_ptr<R5IRVal> _opVal1;
    std::shared_ptr<R5IRVal> _opVal2;
};
class FMathInst : public R5IRInst
{
public:
    enum FMathOp { FADD, FSUB, FMUL, FDIV, FREM } fMathOp;
    FMathInst(
        FMathOp                  fMathOp_,
        SPType                   opType_,
        std::shared_ptr<R5IRVal> opVal1_,
        std::shared_ptr<R5IRVal> opVal2_
    )
        : R5IRInst(InstType::FMathInst, std::move(opType_))
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , fMathOp(fMathOp_)
    {
    }
    [[nodiscard]] const SPType&                   getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal1() const { return _opVal1; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getOpVal2() const { return _opVal2; }

protected:
    SPType                   _opType;
    std::shared_ptr<R5IRVal> _opVal1;
    std::shared_ptr<R5IRVal> _opVal2;
};

class BitCastInst : public R5IRInst
{
public:
    BitCastInst(SPType fromType_ ,std::shared_ptr<R5IRVal> from_, SPType toType_)
        : R5IRInst(InstType::BitCastInst, std::move(toType_))
        , _fromType(std::move(fromType_))
        , _toType(std::move(toType_))
        , _from(std::move(from_))
    {
    }
    [[nodiscard]] const SPType&                   getFromType() const { return _fromType; }
    [[nodiscard]] const SPType&                   getToType() const { return _toType; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getFrom() const { return _from; }
protected:
    SPType                   _fromType;
    SPType                   _toType;
    std::shared_ptr<R5IRVal> _from;
};

class CallInst : public R5IRInst
{
public:
CallInst(std::shared_ptr<R5IRFuncDecl> func_, std::vector<std::shared_ptr<R5IRVal>> args_, SPType retType_)
    : R5IRInst(InstType::CallInst, std::move(retType_))
    , _func(std::move(func_))
    , _args(std::move(args_))
{
}
[[nodiscard]] const std::shared_ptr<R5IRFuncDecl>& getFunc() const { return _func; }
[[nodiscard]] const std::vector<std::shared_ptr<R5IRVal>>& getArgs() const { return _args; }
protected:
    std::shared_ptr<R5IRFuncDecl> _func;
    std::vector<std::shared_ptr<R5IRVal>> _args;
};

class ConvertInst : public R5IRInst
{
    // 'zext' concreteType value 'to' type;
public:
    enum ConvertOp { ZEXT, SEXT, TRUNC, FPTOUI, FPTOSI, UITOFP, SITOFP } convertOp;
    ConvertInst(ConvertOp op_, SPType fromType_, std::shared_ptr<R5IRVal> from_, SPType toType_)
        : R5IRInst(InstType::ConvertInst, std::move(toType_))
        , _fromType(std::move(fromType_))
        , _toType(std::move(toType_))
        , _from(std::move(from_))
    , convertOp(op_)
    {
    }
    [[nodiscard]] const SPType&                   getFromType() const { return _fromType; }
    [[nodiscard]] const SPType&                   getToType() const { return _toType; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getFrom() const { return _from; }
protected:
    SPType                   _fromType;
    SPType                   _toType;
    std::shared_ptr<R5IRVal> _from;
};

// %v4 = getelementptr [3 x i32], [3 x i32]* %v3, i32 114, i32 1
class GetElementPtrInst : public R5IRInst
{
public:
    GetElementPtrInst(SPType type1, SPType fromType, shared_ptr<R5IRVal> from, vector<int> index)
        : R5IRInst(InstType::GetElementPtrInst, std::move(spVoidType))
        , _fromType(std::move(fromType))
        , _from(std::move(from))
        , _index(std::move(index))
    {
        // from must be a pointer.
        IR_ASSERT(_fromType->isPointer(), "GetElementPtrInst: from must be a pointer.");
        auto fromTypePtr = DPC(PointerType, _fromType);
        // from must be a pointer to type1
        IR_ASSERT(*fromTypePtr->getElementType() == *type1, "GetElementPtrInst: from must be a pointer to type1.");
        //   %v3 = getelementptr [114 x [3 x i32]], [114 x [3 x i32]]* %v1, i32 0, i32 0, i32 0
        //  %v4 = getelementptr [114 x [3 x i32]], [114 x [3 x i32]]* %v1, i32 0, i32 0
        // %v4 = getelementptr [3 x i32], [3 x i32]* %v3, i32 114, i32 1
        // %v5 = getelementptr i32, i32* v7, i32 1
        // in case 1, this instruction returns i32*
        // in case 2, it returns [3 x i32]*
        // in case 3, it returns i32*
        // in case 4, it returns i32*
        auto innerType = fromTypePtr->getElementType();
        for (int i = 1; i < _index.size(); ++i) {
            if(innerType->isArray()) {
                auto arrayType = DPC(ArrayType, innerType);
                innerType = arrayType->getElementType();
            } else if(innerType->isPointer()) {
                auto ptrType = DPC(PointerType, innerType);
                innerType = ptrType->getElementType();
            } else {
                IR_ASSERT(i==_index.size()-1, "GetElementPtrInst: invalid index.");
            }
        }
        _type = makePointer(innerType);

    }
    [[nodiscard]] const SPType&                   getFromType() const { return _fromType; }
    [[nodiscard]] const std::shared_ptr<R5IRVal>& getFrom() const { return _from; }
    [[nodiscard]] const vector<int>&              getIndex() const { return _index; }

protected:
    SPType                   _fromType;
    std::shared_ptr<R5IRVal> _from;
    vector<int>              _index;
};

}   // namespace R5BE

#endif   // IRBACKENDR5_R5IRINST_H
