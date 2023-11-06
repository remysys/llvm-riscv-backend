def ZERO : Register<"zero">,  DwarfRegNum<[0]> {
    let Namespace="RRISCV";
}

def RA : Register<"ra">,  DwarfRegNum<[1]> {
    let Namespace="RRISCV";
}
def SP : Register<"sp">,  DwarfRegNum<[2]> {
    let Namespace="RRISCV";
}

def GPR : RegisterClass<"RRISCV", [i32], 32, (add ZERO, RA, SP)> {}