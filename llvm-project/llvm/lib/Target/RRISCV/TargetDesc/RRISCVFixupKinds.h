#ifndef LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVFIXUPKINDS_H
#define LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace RRISCV {
enum Fixups {
  // 20-bit fixup corresponding to %hi(foo) for instructions like lui
  fixup_riscv_hi20 = FirstTargetFixupKind,
  // 12-bit fixup corresponding to %lo(foo) for instructions like addi
  fixup_riscv_lo12_i,
  fixup_riscv_jal,
  fixup_riscv_branch,
  fixup_riscv_invalid,
  NumTargetFixupKinds = fixup_riscv_invalid - FirstTargetFixupKind
};
}

} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVFIXUPKINDS_H