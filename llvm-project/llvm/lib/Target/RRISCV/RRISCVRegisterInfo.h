#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVREGISTERINFO_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "RRISCVGenRegisterInfo.inc"

namespace llvm {
class RRISCVSubtarget;
class RRISCVRegisterInfo : public RRISCVGenRegisterInfo {
public:
  RRISCVRegisterInfo(RRISCVSubtarget const &ST, unsigned HwMode);
  MCPhysReg const *getCalleeSavedRegs(MachineFunction const *MF) const override;

  BitVector getReservedRegs(MachineFunction const &MF) const override;
  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;
  Register getFrameRegister(MachineFunction const &MF) const override;
  uint32_t const *getCallPreservedMask(MachineFunction const &MF,
                                       CallingConv::ID) const override;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVREGISTERINFO_H