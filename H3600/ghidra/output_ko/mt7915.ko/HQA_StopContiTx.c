// module: mt7915.ko
// function: HQA_StopContiTx @ 0x26e048
// size: 128 bytes
//

bool HQA_StopContiTx(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_StopContiTx",param_3,param_1 + 0xa39000,param_4);
  }
  pcVar1 = *(code **)(iVar2 + 0xa0);
  bVar3 = pcVar1 == (code *)0x0;
  if (!bVar3) {
    (*pcVar1)(param_1,1);
  }
  FUN_0026cdd0(param_3,param_2,2,bVar3);
  return bVar3;
}

