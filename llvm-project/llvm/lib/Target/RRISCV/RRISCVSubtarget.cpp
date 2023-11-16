#include "RRISCVSubtarget.h"

#define DEBUG_TYPE "rriscv-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "RRISCVGenSubtargetInfo.inc"

using namespace llvm;

RRISCVSubtarget::RRISCVSubtarget(const Triple &TT, StringRef &CPU,
                                 StringRef &TuneCPU, StringRef &FS,
                                 const TargetMachine &TM)
    : RRISCVGenSubtargetInfo(TT, CPU, TuneCPU, FS), TLInfo(TM, *this),
      RegInfo(*this, getHwMode()), FrameLowering(*this) {}