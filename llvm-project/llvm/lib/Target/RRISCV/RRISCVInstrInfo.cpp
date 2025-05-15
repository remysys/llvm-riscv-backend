#include "RRISCVInstrInfo.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "RRISCVGenInstrInfo.inc"

using namespace llvm;

RRISCVInstrInfo::RRISCVInstrInfo() : RRISCVGenInstrInfo() {}

void RRISCVInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                          MachineBasicBlock::iterator MBBI,
                                          Register SrcReg, bool IsKill,
                                          int FrameIndex,
                                          const TargetRegisterClass *RC,
                                          const TargetRegisterInfo *TRI) const {
  DebugLoc DL;

  BuildMI(MBB, MBBI, DL, get(RRISCV::STOREWFI))
      .addReg(SrcReg, getKillRegState(IsKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void RRISCVInstrInfo::loadRegFromStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, Register DestReg,
    int FrameIndex, const TargetRegisterClass *RC,
    const TargetRegisterInfo *TRI) const {
  DebugLoc DL;
  BuildMI(MBB, MBBI, DL, get(RRISCV::LOADWFI), DestReg)
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void RRISCVInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                  MachineBasicBlock::iterator I,
                                  const DebugLoc &DL, MCRegister DestReg,
                                  MCRegister SrcReg, bool KillSrc) const {

  MachineInstrBuilder MIB = BuildMI(MBB, I, DL, get(RRISCV::ADD));

  MIB.addReg(DestReg, RegState::Define);
  MIB.addReg(RRISCV::ZERO);
  MIB.addReg(SrcReg, getKillRegState(KillSrc));
}