#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVSUBTARGET_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVSUBTARGET_H

#include <llvm/ADT/None.h>
#include <llvm/CodeGen/TargetSubtargetInfo.h>
#include <llvm/MC/MCInst.h>

#define GET_SUBTARGETINFO_HEADER
#include "RRISCVGenSubtargetInfo.inc"

namespace llvm {
class RRISCVTargetMachine;
class RRISCVSubtarget : public RRISCVGenSubtargetInfo {
public:
  RRISCVSubtarget(const Triple &TT, StringRef &CPU, StringRef &TuneCPU,
               StringRef &FS, const RRISCVTargetMachine &TTM);

  ~RRISCVSubtarget() override {}

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVSUBTARGET_H