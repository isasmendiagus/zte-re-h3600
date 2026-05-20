// module: mt7915.ko
// function: HQA_StopRx @ 0x270e4c
// size: 164 bytes
//

undefined4 HQA_StopRx(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  code *pcVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_StopRx",param_3,param_1 + 0xa39000,param_4);
  }
  iVar1 = net_ad_wrap_service(param_1);
  uVar4 = *(uint *)(iVar1 + 0x4e0);
  iVar1 = net_ad_wrap_service(param_1);
  *(uint *)(iVar1 + 0x4e0) = uVar4 & 0xfffffffb;
  *(undefined1 *)(param_1 + 0xa3b8b8) = 0;
  pcVar2 = *(code **)(iVar5 + 0x1c);
  if (pcVar2 == (code *)0x0) {
    uVar3 = 1;
  }
  else {
    uVar3 = (*pcVar2)(param_1);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  return uVar3;
}

