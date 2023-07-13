
// Generated from LLVMIR.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "LLVMIRVisitor.h"


/**
 * This class provides an empty implementation of LLVMIRVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LLVMIRBaseVisitor : public LLVMIRVisitor {
public:

  virtual std::any visitCompilationUnit(LLVMIRParser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTopLevelEntity(LLVMIRParser::TopLevelEntityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalDecl(LLVMIRParser::GlobalDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalDef(LLVMIRParser::GlobalDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImmutable(LLVMIRParser::ImmutableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDecl(LLVMIRParser::FuncDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(LLVMIRParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncHeader(LLVMIRParser::FuncHeaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncBody(LLVMIRParser::FuncBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicBlock(LLVMIRParser::BasicBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstruction(LLVMIRParser::InstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerminator(LLVMIRParser::TerminatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLocalDefInst(LLVMIRParser::LocalDefInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddInst(LLVMIRParser::AddInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFaddInst(LLVMIRParser::FaddInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubInst(LLVMIRParser::SubInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFsubInst(LLVMIRParser::FsubInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulInst(LLVMIRParser::MulInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFmulInst(LLVMIRParser::FmulInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUdivInst(LLVMIRParser::UdivInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSdivInst(LLVMIRParser::SdivInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFdivInst(LLVMIRParser::FdivInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUremInst(LLVMIRParser::UremInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSremInst(LLVMIRParser::SremInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFremInst(LLVMIRParser::FremInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMathInstruction_(LLVMIRParser::MathInstruction_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllocaInst_(LLVMIRParser::AllocaInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoadInst_(LLVMIRParser::LoadInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGEPInst_(LLVMIRParser::GEPInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitZExtInst_(LLVMIRParser::ZExtInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSExtInst_(LLVMIRParser::SExtInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSiToFpInst_(LLVMIRParser::SiToFpInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFpToSiInst_(LLVMIRParser::FpToSiInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitCastInst_(LLVMIRParser::BitCastInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitICmpInst_(LLVMIRParser::ICmpInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFCmpInst_(LLVMIRParser::FCmpInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallInst_(LLVMIRParser::CallInst_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStoreInst(LLVMIRParser::StoreInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllocaInst(LLVMIRParser::AllocaInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoadInst(LLVMIRParser::LoadInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitCastInst(LLVMIRParser::BitCastInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitZExtInst(LLVMIRParser::ZExtInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSExtInst(LLVMIRParser::SExtInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSiToFpInst(LLVMIRParser::SiToFpInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFpToSiInst(LLVMIRParser::FpToSiInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitICmpInst(LLVMIRParser::ICmpInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFCmpInst(LLVMIRParser::FCmpInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallInst(LLVMIRParser::CallInstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRetTerm(LLVMIRParser::RetTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBrTerm(LLVMIRParser::BrTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondBrTerm(LLVMIRParser::CondBrTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatType(LLVMIRParser::FloatTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConcreteType(LLVMIRParser::ConcreteTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue(LLVMIRParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstant(LLVMIRParser::ConstantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolConst(LLVMIRParser::BoolConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntConst(LLVMIRParser::IntConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatConst(LLVMIRParser::FloatConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayConst(LLVMIRParser::ArrayConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(LLVMIRParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntType(LLVMIRParser::IntTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointerType(LLVMIRParser::PointerTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabelType(LLVMIRParser::LabelTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(LLVMIRParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamedType(LLVMIRParser::NamedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParams(LLVMIRParser::ParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(LLVMIRParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabel(LLVMIRParser::LabelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIPred(LLVMIRParser::IPredContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgs(LLVMIRParser::ArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArg(LLVMIRParser::ArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFPred(LLVMIRParser::FPredContext *ctx) override {
    return visitChildren(ctx);
  }


};

