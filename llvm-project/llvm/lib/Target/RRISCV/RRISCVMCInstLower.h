#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVMCINSTLOWER_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVMCINSTLOWER_H

namespace llvm {
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class RRISCVMCInstLower {
public:
  RRISCVMCInstLower(){};
  void Lower(const MachineInstr *MI, MCInst &OutMI) const;
  MCOperand LowerOperand(const MachineOperand &MO) const;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVMCINSTLOWER_H