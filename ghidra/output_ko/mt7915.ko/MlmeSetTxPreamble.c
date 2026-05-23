// module: mt7915.ko
// function: MlmeSetTxPreamble @ 0x12a024
// size: 96 bytes
//

void MlmeSetTxPreamble(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = DebugLevel;
  if (param_2 == 0) {
    *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xffffffef;
    if (iVar1 < 3) {
      return;
    }
    pcVar2 = "LONG";
  }
  else {
    *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) | 0x10;
    if (iVar1 < 3) {
      return;
    }
    pcVar2 = "SHORT";
  }
  printk("MlmeSetTxPreamble = %s PREAMBLE\n",pcVar2);
  return;
}

