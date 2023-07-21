//
// Created by gaome on 2023/7/20.
//

#include "R5AsmStrangeFake.h"

namespace R5Emitter
{
string R5AsmStrangeFake::FakeOPToString(FakeOPs op)
{
    /**
     * FAKEOPS_BEGIN,
// RV64I
LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, LW, SW, ADDIW, ADDW, SUBW, SLT, SLTU,
// RV64M
MULW, DIVW, REMW,
// RV64F , convert
FLW, FSW, FCVT_S_W, FCVT_W_S, FMV_X_S, FMV_S_X,
// RV64F, Calculate
FADD_S, FSUB_S, FMUL_S, FDIV_S, FSGNJ_S, FSGNJN_S, FSGNJX_S, FMIN_S, FMAX_S, FSQRT_S,
FLT, FEQ, FLE,
// Psuedo
J, CALL, BGT, BLE, LI, LA, LLA, MV, RET, NOT, NEGW, SEQZ, SNEZ, SLTZ, SGTZ,
BEQZ, BNEZ, BLEZ, BGEZ, BGTZ, BLTZ, BGTU,

FAKEOPS_END
     */
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
    }
    return "{Unknown FakeOP} " + std::to_string(op);
}
string R5AsmStrangeFake::toString()
{
    stringstream ss;
    ss << FakeOPToString(fakeOP) << " ";
    for (int i = 0; i < R5_MAX_ARG_NUM; i++) {
        if (defUse[i] == UNUSED)
            break;
        else {
            ss << operands[i] << " ";
        }
    }
    return ss.str();
}


}   // namespace R5Emitter