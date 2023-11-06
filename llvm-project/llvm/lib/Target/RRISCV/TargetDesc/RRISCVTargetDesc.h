#ifndef LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCTARGETDESC_H
#define LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCTARGETDESC_H

// Defines symbolic names for RISC-V registers.
#define GET_REGINFO_ENUM
#include "RRISCVGenRegisterInfo.inc"

// Defines symbolic names for RISC-V instructions.
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "RRISCVGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "RRISCVGenSubtargetInfo.inc"

#endif