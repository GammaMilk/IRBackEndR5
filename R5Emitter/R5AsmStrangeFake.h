//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5ASMSTRANGEFAKE_H
#define IRBACKENDR5_R5ASMSTRANGEFAKE_H
#include "../R5Def.h"
#include "R5Taichi.h"
namespace R5Emitter
{
// clang-format off
enum FakeOPs {
    FAKEOPS_BEGIN, NOP,
    // RV64I
    LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, LW, SW, ADDIW, ADDW, SUBW, SLT, SLTU,
    // RV64M
    MULW, DIVW, REMW,
    // RV64F , convert
    FLW, FSW, FCVT_S_W, FCVT_W_S, FMV_X_S, FMV_S_X,
    // RV64F, Calculate
    FADD_S, FSUB_S, FMUL_S, FDIV_S, FSGNJ_S, FSGNJN_S, FSGNJX_S, FMIN_S, FMAX_S, FSQRT_S,
    FLT, FEQ, FLE,
    // RV64F, R4
    FMADD_S, FMSUB_S, FNMADD_S, FNMSUB_S,
    // Psuedo
    J, CALL, BGT, BLE, LI, LA, LLA, MV, RET, NOT, NEGW, SEQZ, SNEZ, SLTZ, SGTZ,
    BEQZ, BNEZ, BLEZ, BGEZ, BGTZ, BLTZ, BGTU,

    FAKEOPS_END
};
// clang-format on
struct R5AsmStrangeFake {
    // clang-format off
    enum OPType {
        I, R, R4, UJ, S, SB, U
    };
    // clang-format on

    static const int R5_MAX_ARG_NUM = 4;
    FakeOPs          fakeOP         = FAKEOPS_BEGIN;
    R5Taichi*        operands[R5_MAX_ARG_NUM]{};
    enum DefUse { DEF, USE, UNUSED };
    DefUse defUse[4] = {UNUSED, UNUSED, UNUSED, UNUSED};
    R5AsmStrangeFake(FakeOPs oPs, std::initializer_list<R5Taichi*>&& operands_)
        : fakeOP(oPs)
    {
        int i = 0;
        // 一般来讲，第一个都是def, 后面的都是use
        // 特殊情况特殊处理。
        for (auto& operand : operands_) {
            if (i == 0) {
                defUse[i++] = DEF;
            } else {
                defUse[i++] = USE;
            }
            operands[i++] = operand;
        }
        if (fakeOP == CALL || fakeOP == J || fakeOP == RET) {
            for (int j = 0; defUse[j] != UNUSED; ++j) { defUse[j] = USE; }
        }
        if (fakeOP == BEQZ || fakeOP == BNEZ || fakeOP == BLEZ || fakeOP == BGEZ ||
            fakeOP == BGTZ || fakeOP == BLTZ) {
            defUse[0] = USE;
        }
        if (fakeOP == JAL && defUse[1] == UNUSED) { defUse[0] = USE; }
    }
    static string FakeOPToString(FakeOPs op);
    string        toString();
    ~R5AsmStrangeFake()
    {
        for (auto& operand : operands) delete operand;
    }
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5ASMSTRANGEFAKE_H
