#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVINSTRINFO_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVINSTRINFO_H

#include "TargetDesc/RRISCVTargetDesc.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RRISCVGenInstrInfo.inc"

namespace llvm {
class RRISCVInstrInfo : public RRISCVGenInstrInfo {

public:
  RRISCVInstrInfo();

  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MBBI, Register SrcReg,
                           bool IsKill, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI) const override;

  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MBBI, Register DstReg,
                            int FrameIndex, const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI) const override;

  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                   const DebugLoc &DL, MCRegister DestReg, MCRegister SrcReg,
                   bool KillSrc) const override;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVINSTRINFO_H