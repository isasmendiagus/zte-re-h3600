// module: mt7915.ko
// function: HQA_SetTxPath @ 0x26fd04
// size: 176 bytes
//

undefined4 HQA_SetTxPath(int param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  code *pcVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetTxPath");
  }
  pcVar2 = *(code **)(iVar5 + 0x44);
  uVar3 = (*(ushort *)(param_3 + 0xc) & 0xff) << 8;
  bVar1 = (uVar3 & 0x8000) != 0;
  if (bVar1) {
    uVar3 = uVar3 & 0x7fff;
  }
  uVar3 = uVar3 | *(ushort *)(param_3 + 0xc) >> 8;
  if (bVar1) {
    uVar3 = uVar3 | 0x80000000;
  }
  if (pcVar2 == (code *)0x0) {
    uVar4 = 1;
  }
  else {
    uVar4 = (*pcVar2)(param_1,uVar3);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar4);
  return uVar4;
}

