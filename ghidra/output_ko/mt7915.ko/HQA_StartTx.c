// module: mt7915.ko
// function: HQA_StartTx @ 0x270fbc
// size: 284 bytes
//

undefined4 HQA_StartTx(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  code *pcVar4;
  undefined4 uVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_StartTx");
  }
  uVar1 = *(ushort *)(param_3 + 0x10);
  uVar2 = *(uint *)(param_3 + 0xc);
  iVar3 = net_ad_wrap_service(param_1);
  *(uint *)(iVar3 + 0x1118) =
       uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  iVar3 = net_ad_wrap_service(param_1);
  *(uint *)(iVar3 + 0x6dc) = (uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8);
  *(undefined1 *)(param_1 + 0xa3b8b7) = 1;
  if (*(code **)(iVar6 + 8) == (code *)0x0) {
    pcVar4 = *(code **)(iVar6 + 0x10);
    if (pcVar4 != (code *)0x0) goto LAB_00271068;
    uVar5 = 1;
  }
  else {
    (**(code **)(iVar6 + 8))(param_1);
    pcVar4 = *(code **)(iVar6 + 0x10);
    if (pcVar4 == (code *)0x0) {
      uVar5 = 1;
    }
    else {
LAB_00271068:
      uVar5 = (*pcVar4)(param_1);
    }
    if (*(char *)(param_1 + 0xa3b8b7) != '\x01') goto LAB_00271084;
  }
  *(undefined1 *)(param_1 + 0xa3b8ba) = 1;
LAB_00271084:
  FUN_0026cdd0(param_3,param_2,2,uVar5);
  return uVar5;
}

