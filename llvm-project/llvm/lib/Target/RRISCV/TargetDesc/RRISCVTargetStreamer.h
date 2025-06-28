#ifndef LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVTARGETSTREAMER_H
#define LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {
class RRISCVTargetStreamer : public MCTargetStreamer {
public:
  RRISCVTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI)
      : MCTargetStreamer(S) {}

  void finish() override;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVTARGETSTREAMER_H