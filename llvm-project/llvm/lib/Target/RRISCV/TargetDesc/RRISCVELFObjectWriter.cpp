#include "RRISCVELFObjectWriter.h"
using namespace llvm;

unsigned RRISCVELFObjectWriter::getRelocType(MCContext &Ctx,
                                             const MCValue &Target,
                                             const MCFixup &Fixup,
                                             bool IsPCRel) const {
  return ELF::R_RISCV_32;
}