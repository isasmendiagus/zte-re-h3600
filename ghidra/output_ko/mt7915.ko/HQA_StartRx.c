// module: mt7915.ko
// function: HQA_StartRx @ 0x26e0cc
// size: 132 bytes
//

undefined4 HQA_StartRx(int param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_StartRx");
  }
  uVar2 = 1;
  *(undefined1 *)(param_1 + 0xa3b8b8) = 1;
  pcVar1 = *(code **)(iVar3 + 0x14);
  if (pcVar1 != (code *)0x0) {
    uVar2 = (*pcVar1)(param_1);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}

