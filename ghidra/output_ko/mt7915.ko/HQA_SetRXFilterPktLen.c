// module: mt7915.ko
// function: HQA_SetRXFilterPktLen @ 0x26ec98
// size: 216 bytes
//

bool HQA_SetRXFilterPktLen(int param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetRXFilterPktLen");
  }
  *(char *)(param_1 + 0xa3ae36) = (char)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  pcVar1 = *(code **)(iVar2 + 0xec);
  bVar3 = pcVar1 == (code *)0x0;
  if (!bVar3) {
    (*pcVar1)(param_1);
  }
  FUN_0026cdd0(param_3,param_2,2,bVar3);
  return bVar3;
}

