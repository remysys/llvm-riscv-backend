add_llvm_component_group(RRISCV)

set(LLVM_TARGET_DEFINITIONS RRISCV.td)
tablegen(LLVM RRISCVGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM RRISCVGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM RRISCVGenAsmWriter.inc -gen-asm-writer)
add_public_tablegen_target(RRISCVCommonTableGen)


add_llvm_target(RRISCVCodeGen
  RRISCVTargetMachine.cpp
  RRISCVISelDAGToDAG.cpp
  RRISCVAsmPrinter.cpp
  RRISCVTargetObjectFile.cpp
  RRISCVSubtarget.cpp
  RRISCVISelLowering.cpp
  RRISCVFrameLowering.cpp
)

add_subdirectory(TargetInfo)
add_subdirectory(TargetDesc)