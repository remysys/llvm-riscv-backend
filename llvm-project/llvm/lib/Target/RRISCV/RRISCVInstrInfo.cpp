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

  BuildMI(MBB, MBBI, DL, get(RRISCV::STOREFI))
      .addReg(SrcReg, getKillRegState(IsKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void RRISCVInstrInfo::loadRegFromStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, Register DestReg,
    int FrameIndex, const TargetRegisterClass *RC,
    const TargetRegisterInfo *TRI) const {
  DebugLoc DL;
  BuildMI(MBB, MBBI, DL, get(RRISCV::LOADFI), DestReg)
      .addFrameIndex(FrameIndex)
      .addImm(0);
}