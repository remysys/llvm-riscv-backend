#include "RRISCVInstrInfo.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "RRISCVGenInstrInfo.inc"

using namespace llvm;

RRISCVInstrInfo::RRISCVInstrInfo() : RRISCVGenInstrInfo() {}

void RRISCVInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MBBI, Register SrcReg,
                            bool IsKill, int FrameIndex,
                            const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI) const {
  DebugLoc DL;

  unsigned Opc = RRISCV::STORE;
  BuildMI(MBB, MBBI, DL, get(Opc))
      .addReg(SrcReg, getKillRegState(IsKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}