#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVINSTRINFO_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVINSTRINFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RRISCVGenInstrInfo.inc"

namespace llvm {
class RRISCVInstrInfo : public RRISCVGenInstrInfo {

public:
  RRISCVInstrInfo();
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVINSTRINFO_H