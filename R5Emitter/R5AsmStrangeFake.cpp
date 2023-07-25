//
// Created by gaome on 2023/7/20.
//

#include "R5AsmStrangeFake.h"

namespace R5Emitter
{
string R5AsmStrangeFake::FakeOPToString(FakeOPs op)
{

    switch (op) {
    case LUI: return "lui";
    case AUIPC: return "auipc";
    case JAL: return "jal";
    case JALR: return "jalr";
    case BEQ: return "beq";
    case BNE: return "bne";
    case BLT: return "blt";
    case BGE: return "bge";
    case LW: return "lw";
    case SW: return "sw";
    case ADDIW: return "addiw";
    case ADDW: return "addw";
    case SUBW: return "subw";
    case SLT: return "slt";
    case SLTU: return "sltu";
    case MULW: return "mulw";
    case DIVW: return "divw";
    case REMW: return "remw";
    case FLW: return "flw";
    case FSW: return "fsw";
    case FCVT_S_W: return "fcvt.s.w";
    case FCVT_W_S: return "fcvt.w.s";
    case FMV_X_S: return "fmv.x.s";
    case FMV_S_X: return "fmv.s.x";
    case FADD_S: return "fadd.s";
    case FSUB_S: return "fsub.s";
    case FMUL_S: return "fmul.s";
    case FDIV_S: return "fdiv.s";
    case FSGNJ_S: return "fsgnj.s";
    case FSGNJN_S: return "fsgnjn.s";
    case FSGNJX_S: return "fsgnjx.s";
    case FMIN_S: return "fmin.s";
    case FMAX_S: return "fmax.s";
    case FSQRT_S: return "fsqrt.s";
    case FLT: return "flt";
    case FEQ: return "feq";
    case FLE: return "fle";
    case J: return "j";
    case CALL: return "call";
    case BGT: return "bgt";
    case BLE: return "ble";
    case LI: return "li";
    case LA: return "la";

    case FAKEOPS_BEGIN: break;
    case LLA: return "lla";
    case MV: return "mv";
    case RET: return "ret";
    case NOT: return "not";
    case NEGW: return "negw";
    case SEQZ: return "seqz";
    case SNEZ: return "snez";
    case SLTZ: return "sltz";
    case SGTZ: return "sgtz";
    case BEQZ: return "beqz";
    case BNEZ: return "bnez";
    case BLEZ: return "blez";
    case BGEZ: return "bgez";
    case BGTZ: return "bgtz";
    case BLTZ: return "bltz";
    case BGTU: return "bgtu";
    case FAKEOPS_END: break;
    case FMADD_S: return "fmadd.s";
    case FMSUB_S: return "fmsub.s";
    case FNMADD_S: return "fnmadd.s";
    case FNMSUB_S: return "fnmsub.s";
    case NOP: return "nop";
    case LD: return "ld";
    case SD: return "sd";
    case BLTU: return "bltu";
    case BGEU: return "bgeu";
    case BLEU: return "bleu";
    case ADD: return "add";
    case SUB: return "sub";
    case SLL: return "sll";
    case SRL: return "srl";
    case SRA: return "sra";
    case AND: return "and";
    case OR: return "or";
    case XOR: return "xor";
    case SLLI: return "slli";
    case SRLI: return "srli";
    case SRAI: return "srai";
    case ANDI: return "andi";
    case ORI: return "ori";
    case XORI: return "xori";
    case MUL: return "mul";
    case DIV: return "div";
    case REM: return "rem";
    case ADDI: return "addi";
    }
    return "{Unknown FakeOP} " + std::to_string(op);
}
string R5AsmStrangeFake::toString()
{
    stringstream ss;
    ss << FakeOPToString(fakeOP) << "\t";
    if (fakeOP == SW || fakeOP == LW || fakeOP == SD || fakeOP == LD || fakeOP == FLW ||
        fakeOP == FSW) {
        ss << operands[0]->toString() << ", ";
        ss << operands[1]->toString() << "(";
        ss << operands[2]->toString() << ")";
        return ss.str();
    }
    if (defUse[0] != UNUSED) { ss << operands[0]->toString(); }
    for (int i = 1; i < R5_MAX_ARG_NUM; i++) {
        if (defUse[i] == UNUSED)
            break;
        else {
            ss << ", " << operands[i]->toString();
        }
    }
    return ss.str();
}


}   // namespace R5Emitter