// module: mt7915.ko
// function: MlmeScanReqSanity @ 0x110d7c
// size: 140 bytes
//

undefined4
MlmeScanReqSanity(undefined4 param_1,int param_2,undefined4 param_3,byte *param_4,void *param_5,
                 byte *param_6,byte *param_7)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  
  *param_4 = *(byte *)(param_2 + 6);
  bVar1 = *(byte *)(param_2 + 8);
  *param_6 = bVar1;
  memmove(param_5,(void *)(param_2 + 9),(uint)bVar1);
  bVar1 = *(byte *)(param_2 + 7);
  *param_7 = bVar1;
  if (*param_4 < 3) {
    bVar3 = 7 < bVar1;
    bVar2 = bVar1 == 8;
    if (8 < bVar1) {
      bVar3 = 2 < (bVar1 ^ 0x80);
      bVar2 = (bVar1 ^ 0x80) == 3;
    }
    if (!bVar3 || bVar2) {
      return 1;
    }
  }
  if (DebugLevel < 3) {
    return 0;
  }
  printk("MlmeScanReqSanity fail - wrong BssType or ScanType\n");
  return 0;
}

