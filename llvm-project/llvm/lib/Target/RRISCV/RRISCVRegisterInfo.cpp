#include "RRISCVRegisterInfo.h"
#include "TargetDesc/RRISCVTargetDesc.h"
#include "RRISCVSubtarget.h"

#define DEBUG_TYPE "rriscv register info"

#define GET_REGINFO_TARGET_DESC
#include "RRISCVGenRegisterInfo.inc"

using namespace llvm;

RRISCVRegisterInfo::RRISCVRegisterInfo(RRISCVSubtarget const &ST, unsigned HwMode)
    : RRISCVGenRegisterInfo(0, 0, 0, 0, HwMode) {}

void RRISCVRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  MachineInstr &MI = *II;
  LLVM_DEBUG(errs() << MI);
  return;
}

MCPhysReg const *
RRISCVRegisterInfo::getCalleeSavedRegs(MachineFunction const *MF) const {
  return CSR_SaveList;
}

BitVector RRISCVRegisterInfo::getReservedRegs(MachineFunction const &MF) const {
  constexpr uint16_t ReservedCPURegs[] = {RRISCV::ZERO};
  BitVector Reserved(getNumRegs());
  for (auto const reg : ReservedCPURegs) {
    Reserved.set(reg);
  }
  return Reserved;
}

Register RRISCVRegisterInfo::getFrameRegister(MachineFunction const &MF) const {
  return RRISCV::SP;
}