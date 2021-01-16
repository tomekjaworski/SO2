#include <assert.h>

int main(void) {
    assert(sizeof(void*) == 8);
    register void* stack_pointer asm("rsp");

    asm(".intel_syntax noprefix");
    asm("mov rax, 0xAAAAAAAAAAAAAAAA");
    asm("push rax"); // - 8
    asm("nop");
    asm("mov eax, 0xBBBBBBBB");
    asm("push eax"); // - 8
    asm("nop");
    asm("mov ax, 0xCCCC");
    asm("push ax"); // - 2
    asm("nop");
    asm("mov al, 0xDD");
    asm("push al"); // - 8
    asm("nop");
    asm("add rsp, 8 + 4 + 2 + 1");
    asm(".att_syntax prefix");

    return 0;
}

