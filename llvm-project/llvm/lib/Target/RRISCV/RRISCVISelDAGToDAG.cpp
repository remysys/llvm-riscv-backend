#include "RRISCVISelDAGToDAG.h"

using namespace llvm;

void RRISCVDAGToDAGISel::Select(SDNode *N) { SelectCode(N); }