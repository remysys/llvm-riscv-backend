#ifndef LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVELFOBJECTWRITER_H
#define LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVELFOBJECTWRITER_H
#include "llvm/MC/MCELFObjectWriter.h"

namespace llvm {
class RRISCVELFObjectWriter : public MCELFObjectTargetWriter {
public:
  RRISCVELFObjectWriter(uint8_t OSABI, bool HasRelocationAddend, bool Is64)
      : MCELFObjectTargetWriter(
            /*Is64Bit_=false*/ false, OSABI, ELF::EM_RISCV,
            /*HasRelocationAddend_ = false*/ false) {}

  ~RRISCVELFObjectWriter() = default;

  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
  bool needsRelocateWithSymbol(const MCSymbol &Sym,
                               unsigned Type) const override {
    return true;
  }
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVELFOBJECTWRITER_H