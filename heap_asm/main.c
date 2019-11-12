
int main(void) {
  
    asm(".intel_syntax noprefix");
    asm("mov rax, 0xAAAAAAAAAAAAAAAA");
    asm("push rax");
    asm("nop");
    asm("mov rax, 0xBBBBBBBBBBBBBBBB");
    asm("push rax");
    asm("nop");
    asm("mov rax, 0xCCCCCCCCCCCCCCCC");
    asm("push ax");
    asm("nop");
    asm("mov rax, 0xDDDDDDDDDDDDDDDD");
    asm("push rax");
    asm("nop");
    asm(".att_syntax prefix");
    
  return 0;
}