// module: mt7915.ko
// function: HQA_SetRxPath @ 0x26fc58
// size: 168 bytes
//

undefined4 HQA_SetRxPath(int param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetRxPath");
  }
  pcVar1 = *(code **)(iVar3 + 0x48);
  if (pcVar1 == (code *)0x0) {
    uVar2 = 1;
  }
  else {
    uVar2 = (*pcVar1)(param_1,(int)(char)((ushort)*(undefined2 *)(param_3 + 0xc) >> 8));
  }
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}

