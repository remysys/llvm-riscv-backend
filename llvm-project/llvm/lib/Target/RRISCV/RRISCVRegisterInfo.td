def ZERO : Register<"zero">,  DwarfRegNum<[0]> {
    let Namespace="RRISCV";
}

def GPR:RegisterClass<"RRISCV", [i32], 32, (add ZERO)> {}
