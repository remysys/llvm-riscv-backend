#include "RRISCVInstPrinter.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "RRISCVGenAsmWriter.inc"

void RRISCVInstPrinter::printInst(MCInst const *MI, uint64_t Address, StringRef Annot, MCSubtargetInfo const &STI, raw_ostream &O) {}

void RRISCVInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {}

void RRISCVInstPrinter::printOperand(const MCInst *MI, unsigned OpNo, const MCSubtargetInfo &STI, raw_ostream &O, const char *Modifier) {}