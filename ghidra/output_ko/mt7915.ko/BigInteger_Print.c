// module: mt7915.ko
// function: BigInteger_Print @ 0x1fafc4
// size: 176 bytes
//

void BigInteger_Print(char *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  if (param_1 == (char *)0x0) {
    return;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    if (*param_1 != '\0') {
      printk("Name=%s\n",param_1);
    }
    iVar1 = *(int *)(param_1 + 0x14);
    uVar3 = 0;
    iVar4 = iVar1 + -1;
    while (-1 < iVar4) {
      iVar4 = iVar4 + -1;
      printk("%08x, ",*(undefined4 *)(*(int *)(param_1 + 0xc) + ((iVar1 + 0x3fffffff) - uVar3) * 4))
      ;
      uVar2 = uVar3 & 0x80000007;
      if ((int)uVar2 < 0) {
        uVar2 = ~(~((uVar2 - 1) * 0x20000000) >> 0x1d) + 1;
      }
      uVar3 = uVar3 + 1;
      if (uVar2 == 7) {
        printk(&_LC3);
      }
    }
    printk(&_LC4);
    return;
  }
  return;
}

