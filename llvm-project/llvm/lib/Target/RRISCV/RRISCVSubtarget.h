#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVSUBTARGET_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVSUBTARGET_H

#include <llvm/ADT/None.h>
#include <llvm/CodeGen/TargetSubtargetInfo.h>
#include <llvm/MC/MCInst.h>
#include "RRISCVISelLowering.h"
#include "RRISCVFrameLowering.h"
#include "RRISCVInstrInfo.h"
#include "RRISCVRegisterInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "RRISCVGenSubtargetInfo.inc"

namespace llvm {
class RRISCVTargetMachine;
class RRISCVSubtarget : public RRISCVGenSubtargetInfo {
private:
  RRISCVTargetLowering TLInfo;
  RRISCVFrameLowering FrameLowering;
  RRISCVInstrInfo InstrInfo;
  RRISCVRegisterInfo RegInfo;
public:
  RRISCVSubtarget(const Triple &TT, StringRef &CPU, StringRef &TuneCPU,
               StringRef &FS, const TargetMachine &TM);

  ~RRISCVSubtarget() override {}

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
  const RRISCVTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }

  const RRISCVFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }

  const RRISCVInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const RRISCVRegisterInfo *getRegisterInfo() const override {
    return &RegInfo;
  }
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVSUBTARGET_H