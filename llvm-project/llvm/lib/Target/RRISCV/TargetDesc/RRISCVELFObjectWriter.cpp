#include "RRISCVELFObjectWriter.h"
using namespace llvm;
#include "RRISCVFixupKinds.h"
#include "llvm/MC/MCContext.h"

unsigned RRISCVELFObjectWriter::getRelocType(MCContext &Ctx,
                                             const MCValue &Target,
                                             const MCFixup &Fixup,
                                             bool IsPCRel) const {
  unsigned Kind = Fixup.getTargetKind();
  switch (Kind) {
  default:
    Ctx.reportError(Fixup.getLoc(), "unsupported relocation type");
    return ELF::R_RISCV_NONE;
  case RRISCV::fixup_riscv_hi20:
    return ELF::R_RISCV_HI20;
  case RRISCV::fixup_riscv_lo12_i:
    return ELF::R_RISCV_LO12_I;
  }
  return ELF::R_RISCV_NONE;
}