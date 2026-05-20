// module: mt7915.ko
// function: HQA_SetFreqOffset @ 0x26f6fc
// size: 160 bytes
//

bool HQA_SetFreqOffset(int param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetFreqOffset");
  }
  pcVar1 = *(code **)(iVar2 + 0x4c);
  bVar3 = pcVar1 == (code *)0x0;
  if (!bVar3) {
    (*pcVar1)(param_1);
  }
  FUN_0026cdd0(param_3,param_2,2,bVar3);
  return bVar3;
}

