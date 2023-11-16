#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVFRAMELOWERING_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class RRISCVSubtarget;
class RRISCVFrameLowering : public TargetFrameLowering {
private:
  RRISCVSubtarget &STI;

public:
  RRISCVFrameLowering(RRISCVSubtarget &sti);
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  bool hasFP(const MachineFunction &MF) const override;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVFRAMELOWERING_H