#include "RRISCVRegisterInfo.h"
#include "RRISCVSubtarget.h"
#include "TargetDesc/RRISCVTargetDesc.h"
#include <llvm/CodeGen/MachineFrameInfo.h>

#define DEBUG_TYPE "rriscv register info"

#define GET_REGINFO_TARGET_DESC
#include "RRISCVGenRegisterInfo.inc"

using namespace llvm;

RRISCVRegisterInfo::RRISCVRegisterInfo(RRISCVSubtarget const &ST,
                                       unsigned HwMode)
    : RRISCVGenRegisterInfo(0, 0, 0, 0, HwMode) {}

void RRISCVRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                             int SPAdj, unsigned FIOperandNum,
                                             RegScavenger *RS) const {
  MachineInstr &MI = *II;
  LLVM_DEBUG(errs() << MI);
  int i = 0;
  while (!MI.getOperand(i).isFI()) {
    ++i;
    assert(i < MI.getNumOperands());
  }
  int FI = MI.getOperand(i).getIndex();
  MachineFunction &MF = *MI.getParent()->getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  int64_t offset = MFI.getObjectOffset(FI);
  uint64_t stack_size = MFI.getStackSize();
  offset += (int64_t)stack_size;

  MI.getOperand(i).ChangeToRegister(RRISCV::SP, false);
  MI.getOperand(i + 1).ChangeToImmediate(offset);

  return;
}

MCPhysReg const *
RRISCVRegisterInfo::getCalleeSavedRegs(MachineFunction const *MF) const {
  return CSR_SaveList;
}

BitVector RRISCVRegisterInfo::getReservedRegs(MachineFunction const &MF) const {
  constexpr uint16_t ReservedCPURegs[] = {RRISCV::ZERO, RRISCV::RA, RRISCV::SP};
  BitVector Reserved(getNumRegs());
  for (auto const reg : ReservedCPURegs) {
    Reserved.set(reg);
  }
  return Reserved;
}

Register RRISCVRegisterInfo::getFrameRegister(MachineFunction const &MF) const {
  return RRISCV::SP;
}