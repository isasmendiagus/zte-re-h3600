// module: mt7915.ko
// function: SetPSMBitHdlr @ 0xc493c
// size: 48 bytes
//

undefined4 SetPSMBitHdlr(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  if (*(char *)(param_1 + 0x286285) == '\0') {
    puVar1 = *(undefined4 **)(param_2 + 4);
    MlmeSetPsmBit(param_1,*puVar1,*(undefined2 *)(puVar1 + 1),puVar1,param_4);
  }
  return 0;
}

