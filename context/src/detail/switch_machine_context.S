.global SwitchMachineContext

SwitchMachineContext:

    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12

    pushq %rbx
    pushq %rbp

    movq %rsp, (%rdi) # from_rsp = rsp
    movq (%rsi), %rsp # rsp = to_rsp

    popq %rbp
    popq %rbx

    popq %r12
    popq %r13
    popq %r14
    popq %r15

    retq