#include <assert.h>

int main(void) {
    assert(sizeof(void*) == 8);
    register void* stack_pointer asm("rsp");

    asm(".intel_syntax noprefix");
    asm("mov rax, 0xAAAAAAAAAAAAAAAA");
    asm("push rax"); // - 8
    asm("nop");
    asm("mov ax, 0xBBBB");
    asm("push ax"); // - 8
    asm("nop");
    asm("mov rax, 0xCCCCCCCCCCCCCCCC");
    asm("push rax"); // - 2
    asm("nop");
    asm("mov ax, 0xDDDD");
    asm("push ax"); // - 8
    asm("nop");
    asm("add rsp, 8 + 2 + 8 + 2");
    asm(".att_syntax prefix");

    return 0;
}

