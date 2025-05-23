#include "RRISCVAsmBackend.h"
#include "RRISCVELFObjectWriter.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCELFObjectWriter.h"

using namespace llvm;

const MCFixupKindInfo &
RRISCVAsmBackend::getFixupKindInfo(MCFixupKind Kind) const {
  return MCAsmBackend::getFixupKindInfo(Kind);
}

static std::unique_ptr<MCObjectTargetWriter>
createRRISCVELFObjectWriter(const Triple &TT) {
  uint8_t OSABI = MCELFObjectTargetWriter::getOSABI(TT.getOS());
  bool IsN64 = false;
  bool HasRelocationAddend = false;
  return std::make_unique<RRISCVELFObjectWriter>(OSABI, HasRelocationAddend,
                                                 IsN64);
}

std::unique_ptr<MCObjectTargetWriter>
RRISCVAsmBackend::createObjectTargetWriter() const {
  return createRRISCVELFObjectWriter(TheTriple);
}