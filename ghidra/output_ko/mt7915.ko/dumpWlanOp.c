// module: mt7915.ko
// function: dumpWlanOp @ 0x34b4c
// size: 96 bytes
//

void dumpWlanOp(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    return;
  }
  iVar1 = *(int *)(param_1 + 0xb14);
  if (iVar1 == 0) {
    return;
  }
  if (DebugLevel < param_2) {
    return;
  }
  printk("\nfrag_thld=%u\n",*(undefined4 *)(iVar1 + 0x10));
  if (DebugLevel < param_2) {
    return;
  }
  printk("rts_len_thld=%u\n",*(undefined4 *)(iVar1 + 0x18));
  return;
}

