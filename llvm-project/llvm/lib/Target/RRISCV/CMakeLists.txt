add_llvm_component_group(RRISCV)

add_llvm_target(RRISCVCodeGen
  RRISCVTargetMachine.cpp
)

add_subdirectory(TargetInfo)
add_subdirectory(TargetDesc)