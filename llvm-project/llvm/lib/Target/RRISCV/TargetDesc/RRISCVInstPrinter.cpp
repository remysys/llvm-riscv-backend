#include "RRISCVInstPrinter.h"
#include "llvm/MC/MCInst.h"

#define DEBUG_TYPE "rriscv instr printer"
#include <llvm/Support/Debug.h>

using namespace llvm;

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "RRISCVGenAsmWriter.inc"

void RRISCVInstPrinter::printInst(MCInst const *MI, uint64_t Address,
                                  StringRef Annot, MCSubtargetInfo const &STI,
                                  raw_ostream &O) {
  printInstruction(MI, Address, O);
}

void RRISCVInstPrinter::printRegName(raw_ostream &O, unsigned RegNo) const {
  O << getRegisterName(RegNo);
}

// void RRISCVInstPrinter::printOperand(const MCInst *MI, unsigned OpNo, const
// MCSubtargetInfo &STI, raw_ostream &O, const char *Modifier) {}

void RRISCVInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                     raw_ostream &OS) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    printRegName(OS, Op.getReg());
    return;
  }

  if (Op.isImm()) {
    OS << Op.getImm();
    return;
  }
}

void RRISCVInstPrinter::printOperand(const MCInst *MI, uint64_t _Address,
                                     unsigned OpNum, raw_ostream &O) {
  printOperand(MI, OpNum, O);
}

void RRISCVInstPrinter::printMemOperand(const MCInst *MI, int opNum,
                                        raw_ostream &O) {
  printOperand(MI, opNum + 1, O);
  O << "(";
  printOperand(MI, opNum, O);
  O << ")";
}