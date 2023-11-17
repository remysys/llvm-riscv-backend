#include "RRISCVFrameLowering.h"
#include "RRISCVSubtarget.h"
#include "TargetDesc/RRISCVTargetDesc.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include <llvm/CodeGen/MachineFrameInfo.h>
#include <llvm/CodeGen/MachineFunction.h>
#include <llvm/MC/MCInstrInfo.h>

using namespace llvm;

RRISCVFrameLowering::RRISCVFrameLowering(RRISCVSubtarget &sti)
    : TargetFrameLowering(StackGrowsDown, Align(16), 0), STI(sti) {}

void RRISCVFrameLowering::emitPrologue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {

  MachineBasicBlock::iterator MBBI = MBB.begin();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  const RRISCVInstrInfo &TII =
      *static_cast<const RRISCVInstrInfo *>(STI.getInstrInfo());

  DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();
  uint64_t StackSize = MFI.getStackSize();

  if (StackSize == 0 && !MFI.adjustsStack())
    return;
  BuildMI(MBB, MBBI, DL, TII.get(RRISCV::ADDI), RRISCV::SP)
      .addReg(RRISCV::SP)
      .addImm(-StackSize);
}

void RRISCVFrameLowering::emitEpilogue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator MBBI = MBB.getFirstTerminator();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  const RRISCVInstrInfo &TII =
      *static_cast<const RRISCVInstrInfo *>(STI.getInstrInfo());
  DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();
  uint64_t StackSize = MFI.getStackSize();

  if (StackSize == 0 && !MFI.adjustsStack())
    return;
  BuildMI(MBB, MBBI, DL, TII.get(RRISCV::ADDI), RRISCV::SP)
      .addReg(RRISCV::SP)
      .addImm(StackSize);
}

bool RRISCVFrameLowering::hasFP(const MachineFunction &MF) const {
  return false;
}

void RRISCVFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                               BitVector &SavedRegs,
                                               RegScavenger *RS) const {
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
  if (MF.getFrameInfo().hasCalls()) {
    SavedRegs.set(RRISCV::RA);
  }
}