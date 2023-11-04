#include "RRISCVFrameLowering.h"

using namespace llvm;

RRISCVFrameLowering::RRISCVFrameLowering()
    : TargetFrameLowering(StackGrowsDown, Align(16), 0) {}

void RRISCVFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

void RRISCVFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

bool RRISCVFrameLowering::hasFP(const MachineFunction &MF) const { return false; }