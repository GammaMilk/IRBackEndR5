
// Generated from LLVMIR.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "LLVMIRListener.h"


/**
 * This class provides an empty implementation of LLVMIRListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LLVMIRBaseListener : public LLVMIRListener {
public:

  virtual void enterCompilationUnit(LLVMIRParser::CompilationUnitContext * /*ctx*/) override { }
  virtual void exitCompilationUnit(LLVMIRParser::CompilationUnitContext * /*ctx*/) override { }

  virtual void enterTopLevelEntity(LLVMIRParser::TopLevelEntityContext * /*ctx*/) override { }
  virtual void exitTopLevelEntity(LLVMIRParser::TopLevelEntityContext * /*ctx*/) override { }

  virtual void enterGlobalDecl(LLVMIRParser::GlobalDeclContext * /*ctx*/) override { }
  virtual void exitGlobalDecl(LLVMIRParser::GlobalDeclContext * /*ctx*/) override { }

  virtual void enterGlobalDef(LLVMIRParser::GlobalDefContext * /*ctx*/) override { }
  virtual void exitGlobalDef(LLVMIRParser::GlobalDefContext * /*ctx*/) override { }

  virtual void enterImmutable(LLVMIRParser::ImmutableContext * /*ctx*/) override { }
  virtual void exitImmutable(LLVMIRParser::ImmutableContext * /*ctx*/) override { }

  virtual void enterFuncDecl(LLVMIRParser::FuncDeclContext * /*ctx*/) override { }
  virtual void exitFuncDecl(LLVMIRParser::FuncDeclContext * /*ctx*/) override { }

  virtual void enterFuncDef(LLVMIRParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(LLVMIRParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterFuncHeader(LLVMIRParser::FuncHeaderContext * /*ctx*/) override { }
  virtual void exitFuncHeader(LLVMIRParser::FuncHeaderContext * /*ctx*/) override { }

  virtual void enterFuncBody(LLVMIRParser::FuncBodyContext * /*ctx*/) override { }
  virtual void exitFuncBody(LLVMIRParser::FuncBodyContext * /*ctx*/) override { }

  virtual void enterBasicBlock(LLVMIRParser::BasicBlockContext * /*ctx*/) override { }
  virtual void exitBasicBlock(LLVMIRParser::BasicBlockContext * /*ctx*/) override { }

  virtual void enterInstruction(LLVMIRParser::InstructionContext * /*ctx*/) override { }
  virtual void exitInstruction(LLVMIRParser::InstructionContext * /*ctx*/) override { }

  virtual void enterTerminator(LLVMIRParser::TerminatorContext * /*ctx*/) override { }
  virtual void exitTerminator(LLVMIRParser::TerminatorContext * /*ctx*/) override { }

  virtual void enterLocalDefInst(LLVMIRParser::LocalDefInstContext * /*ctx*/) override { }
  virtual void exitLocalDefInst(LLVMIRParser::LocalDefInstContext * /*ctx*/) override { }

  virtual void enterAddInst(LLVMIRParser::AddInstContext * /*ctx*/) override { }
  virtual void exitAddInst(LLVMIRParser::AddInstContext * /*ctx*/) override { }

  virtual void enterFaddInst(LLVMIRParser::FaddInstContext * /*ctx*/) override { }
  virtual void exitFaddInst(LLVMIRParser::FaddInstContext * /*ctx*/) override { }

  virtual void enterSubInst(LLVMIRParser::SubInstContext * /*ctx*/) override { }
  virtual void exitSubInst(LLVMIRParser::SubInstContext * /*ctx*/) override { }

  virtual void enterFsubInst(LLVMIRParser::FsubInstContext * /*ctx*/) override { }
  virtual void exitFsubInst(LLVMIRParser::FsubInstContext * /*ctx*/) override { }

  virtual void enterMulInst(LLVMIRParser::MulInstContext * /*ctx*/) override { }
  virtual void exitMulInst(LLVMIRParser::MulInstContext * /*ctx*/) override { }

  virtual void enterFmulInst(LLVMIRParser::FmulInstContext * /*ctx*/) override { }
  virtual void exitFmulInst(LLVMIRParser::FmulInstContext * /*ctx*/) override { }

  virtual void enterUdivInst(LLVMIRParser::UdivInstContext * /*ctx*/) override { }
  virtual void exitUdivInst(LLVMIRParser::UdivInstContext * /*ctx*/) override { }

  virtual void enterSdivInst(LLVMIRParser::SdivInstContext * /*ctx*/) override { }
  virtual void exitSdivInst(LLVMIRParser::SdivInstContext * /*ctx*/) override { }

  virtual void enterFdivInst(LLVMIRParser::FdivInstContext * /*ctx*/) override { }
  virtual void exitFdivInst(LLVMIRParser::FdivInstContext * /*ctx*/) override { }

  virtual void enterUremInst(LLVMIRParser::UremInstContext * /*ctx*/) override { }
  virtual void exitUremInst(LLVMIRParser::UremInstContext * /*ctx*/) override { }

  virtual void enterSremInst(LLVMIRParser::SremInstContext * /*ctx*/) override { }
  virtual void exitSremInst(LLVMIRParser::SremInstContext * /*ctx*/) override { }

  virtual void enterFremInst(LLVMIRParser::FremInstContext * /*ctx*/) override { }
  virtual void exitFremInst(LLVMIRParser::FremInstContext * /*ctx*/) override { }

  virtual void enterMathInstruction_(LLVMIRParser::MathInstruction_Context * /*ctx*/) override { }
  virtual void exitMathInstruction_(LLVMIRParser::MathInstruction_Context * /*ctx*/) override { }

  virtual void enterAllocaInst_(LLVMIRParser::AllocaInst_Context * /*ctx*/) override { }
  virtual void exitAllocaInst_(LLVMIRParser::AllocaInst_Context * /*ctx*/) override { }

  virtual void enterLoadInst_(LLVMIRParser::LoadInst_Context * /*ctx*/) override { }
  virtual void exitLoadInst_(LLVMIRParser::LoadInst_Context * /*ctx*/) override { }

  virtual void enterGEPInst_(LLVMIRParser::GEPInst_Context * /*ctx*/) override { }
  virtual void exitGEPInst_(LLVMIRParser::GEPInst_Context * /*ctx*/) override { }

  virtual void enterZExtInst_(LLVMIRParser::ZExtInst_Context * /*ctx*/) override { }
  virtual void exitZExtInst_(LLVMIRParser::ZExtInst_Context * /*ctx*/) override { }

  virtual void enterSExtInst_(LLVMIRParser::SExtInst_Context * /*ctx*/) override { }
  virtual void exitSExtInst_(LLVMIRParser::SExtInst_Context * /*ctx*/) override { }

  virtual void enterSiToFpInst_(LLVMIRParser::SiToFpInst_Context * /*ctx*/) override { }
  virtual void exitSiToFpInst_(LLVMIRParser::SiToFpInst_Context * /*ctx*/) override { }

  virtual void enterFpToSiInst_(LLVMIRParser::FpToSiInst_Context * /*ctx*/) override { }
  virtual void exitFpToSiInst_(LLVMIRParser::FpToSiInst_Context * /*ctx*/) override { }

  virtual void enterBitCastInst_(LLVMIRParser::BitCastInst_Context * /*ctx*/) override { }
  virtual void exitBitCastInst_(LLVMIRParser::BitCastInst_Context * /*ctx*/) override { }

  virtual void enterICmpInst_(LLVMIRParser::ICmpInst_Context * /*ctx*/) override { }
  virtual void exitICmpInst_(LLVMIRParser::ICmpInst_Context * /*ctx*/) override { }

  virtual void enterFCmpInst_(LLVMIRParser::FCmpInst_Context * /*ctx*/) override { }
  virtual void exitFCmpInst_(LLVMIRParser::FCmpInst_Context * /*ctx*/) override { }

  virtual void enterCallInst_(LLVMIRParser::CallInst_Context * /*ctx*/) override { }
  virtual void exitCallInst_(LLVMIRParser::CallInst_Context * /*ctx*/) override { }

  virtual void enterStoreInst(LLVMIRParser::StoreInstContext * /*ctx*/) override { }
  virtual void exitStoreInst(LLVMIRParser::StoreInstContext * /*ctx*/) override { }

  virtual void enterAllocaInst(LLVMIRParser::AllocaInstContext * /*ctx*/) override { }
  virtual void exitAllocaInst(LLVMIRParser::AllocaInstContext * /*ctx*/) override { }

  virtual void enterLoadInst(LLVMIRParser::LoadInstContext * /*ctx*/) override { }
  virtual void exitLoadInst(LLVMIRParser::LoadInstContext * /*ctx*/) override { }

  virtual void enterGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext * /*ctx*/) override { }
  virtual void exitGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext * /*ctx*/) override { }

  virtual void enterBitCastInst(LLVMIRParser::BitCastInstContext * /*ctx*/) override { }
  virtual void exitBitCastInst(LLVMIRParser::BitCastInstContext * /*ctx*/) override { }

  virtual void enterZExtInst(LLVMIRParser::ZExtInstContext * /*ctx*/) override { }
  virtual void exitZExtInst(LLVMIRParser::ZExtInstContext * /*ctx*/) override { }

  virtual void enterSExtInst(LLVMIRParser::SExtInstContext * /*ctx*/) override { }
  virtual void exitSExtInst(LLVMIRParser::SExtInstContext * /*ctx*/) override { }

  virtual void enterSiToFpInst(LLVMIRParser::SiToFpInstContext * /*ctx*/) override { }
  virtual void exitSiToFpInst(LLVMIRParser::SiToFpInstContext * /*ctx*/) override { }

  virtual void enterFpToSiInst(LLVMIRParser::FpToSiInstContext * /*ctx*/) override { }
  virtual void exitFpToSiInst(LLVMIRParser::FpToSiInstContext * /*ctx*/) override { }

  virtual void enterICmpInst(LLVMIRParser::ICmpInstContext * /*ctx*/) override { }
  virtual void exitICmpInst(LLVMIRParser::ICmpInstContext * /*ctx*/) override { }

  virtual void enterFCmpInst(LLVMIRParser::FCmpInstContext * /*ctx*/) override { }
  virtual void exitFCmpInst(LLVMIRParser::FCmpInstContext * /*ctx*/) override { }

  virtual void enterCallInst(LLVMIRParser::CallInstContext * /*ctx*/) override { }
  virtual void exitCallInst(LLVMIRParser::CallInstContext * /*ctx*/) override { }

  virtual void enterRetTerm(LLVMIRParser::RetTermContext * /*ctx*/) override { }
  virtual void exitRetTerm(LLVMIRParser::RetTermContext * /*ctx*/) override { }

  virtual void enterBrTerm(LLVMIRParser::BrTermContext * /*ctx*/) override { }
  virtual void exitBrTerm(LLVMIRParser::BrTermContext * /*ctx*/) override { }

  virtual void enterCondBrTerm(LLVMIRParser::CondBrTermContext * /*ctx*/) override { }
  virtual void exitCondBrTerm(LLVMIRParser::CondBrTermContext * /*ctx*/) override { }

  virtual void enterFloatType(LLVMIRParser::FloatTypeContext * /*ctx*/) override { }
  virtual void exitFloatType(LLVMIRParser::FloatTypeContext * /*ctx*/) override { }

  virtual void enterConcreteType(LLVMIRParser::ConcreteTypeContext * /*ctx*/) override { }
  virtual void exitConcreteType(LLVMIRParser::ConcreteTypeContext * /*ctx*/) override { }

  virtual void enterValue(LLVMIRParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(LLVMIRParser::ValueContext * /*ctx*/) override { }

  virtual void enterConstant(LLVMIRParser::ConstantContext * /*ctx*/) override { }
  virtual void exitConstant(LLVMIRParser::ConstantContext * /*ctx*/) override { }

  virtual void enterBoolConst(LLVMIRParser::BoolConstContext * /*ctx*/) override { }
  virtual void exitBoolConst(LLVMIRParser::BoolConstContext * /*ctx*/) override { }

  virtual void enterIntConst(LLVMIRParser::IntConstContext * /*ctx*/) override { }
  virtual void exitIntConst(LLVMIRParser::IntConstContext * /*ctx*/) override { }

  virtual void enterFloatConst(LLVMIRParser::FloatConstContext * /*ctx*/) override { }
  virtual void exitFloatConst(LLVMIRParser::FloatConstContext * /*ctx*/) override { }

  virtual void enterArrayConst(LLVMIRParser::ArrayConstContext * /*ctx*/) override { }
  virtual void exitArrayConst(LLVMIRParser::ArrayConstContext * /*ctx*/) override { }

  virtual void enterType(LLVMIRParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(LLVMIRParser::TypeContext * /*ctx*/) override { }

  virtual void enterIntType(LLVMIRParser::IntTypeContext * /*ctx*/) override { }
  virtual void exitIntType(LLVMIRParser::IntTypeContext * /*ctx*/) override { }

  virtual void enterPointerType(LLVMIRParser::PointerTypeContext * /*ctx*/) override { }
  virtual void exitPointerType(LLVMIRParser::PointerTypeContext * /*ctx*/) override { }

  virtual void enterLabelType(LLVMIRParser::LabelTypeContext * /*ctx*/) override { }
  virtual void exitLabelType(LLVMIRParser::LabelTypeContext * /*ctx*/) override { }

  virtual void enterArrayType(LLVMIRParser::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(LLVMIRParser::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterNamedType(LLVMIRParser::NamedTypeContext * /*ctx*/) override { }
  virtual void exitNamedType(LLVMIRParser::NamedTypeContext * /*ctx*/) override { }

  virtual void enterParams(LLVMIRParser::ParamsContext * /*ctx*/) override { }
  virtual void exitParams(LLVMIRParser::ParamsContext * /*ctx*/) override { }

  virtual void enterParam(LLVMIRParser::ParamContext * /*ctx*/) override { }
  virtual void exitParam(LLVMIRParser::ParamContext * /*ctx*/) override { }

  virtual void enterLabel(LLVMIRParser::LabelContext * /*ctx*/) override { }
  virtual void exitLabel(LLVMIRParser::LabelContext * /*ctx*/) override { }

  virtual void enterIPred(LLVMIRParser::IPredContext * /*ctx*/) override { }
  virtual void exitIPred(LLVMIRParser::IPredContext * /*ctx*/) override { }

  virtual void enterArgs(LLVMIRParser::ArgsContext * /*ctx*/) override { }
  virtual void exitArgs(LLVMIRParser::ArgsContext * /*ctx*/) override { }

  virtual void enterArg(LLVMIRParser::ArgContext * /*ctx*/) override { }
  virtual void exitArg(LLVMIRParser::ArgContext * /*ctx*/) override { }

  virtual void enterZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext * /*ctx*/) override { }
  virtual void exitZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext * /*ctx*/) override { }

  virtual void enterFPred(LLVMIRParser::FPredContext * /*ctx*/) override { }
  virtual void exitFPred(LLVMIRParser::FPredContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

