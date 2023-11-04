add_llvm_component_group(RRISCV)

set(LLVM_TARGET_DEFINITIONS RRISCV.td)
tablegen(LLVM RRISCVGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(RRISCVCommonTableGen)


add_llvm_target(RRISCVCodeGen
  RRISCVTargetMachine.cpp
)

add_subdirectory(TargetInfo)
add_subdirectory(TargetDesc)