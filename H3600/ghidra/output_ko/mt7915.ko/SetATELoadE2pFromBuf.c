// module: mt7915.ko
// function: SetATELoadE2pFromBuf @ 0x262644
// size: 236 bytes
//

undefined4
SetATELoadE2pFromBuf(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  int extraout_r1;
  int iVar3;
  int extraout_r1_00;
  int iVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  uVar6 = simple_strtol(param_2,0,10,param_4,param_4);
  iVar3 = (int)((ulonglong)uVar6 >> 0x20);
  iVar4 = (int)uVar6;
  if (DebugLevel < 1) {
    if (iVar4 == 0) {
      return 0;
    }
  }
  else {
    printk("===> %s (Value=%d)\n\n","SetATELoadE2pFromBuf",iVar4);
    uVar5 = 0;
    iVar3 = extraout_r1_00;
    if (iVar4 == 0) goto LAB_002626e4;
  }
  if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
    iVar4 = 0;
    do {
      uVar1 = *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + iVar4);
      iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0),iVar3);
      iVar3 = iVar4 << 1;
      iVar4 = iVar4 + 1;
      if (*(code **)(iVar2 + 0xc) != (code *)0x0) {
        (**(code **)(iVar2 + 0xc))(param_1,iVar3,uVar1);
        iVar3 = extraout_r1;
      }
    } while (iVar4 != 0x100);
  }
  uVar5 = 1;
LAB_002626e4:
  if (0 < DebugLevel) {
    printk("<=== %s (Ret=%d)\n","SetATELoadE2pFromBuf",uVar5);
  }
  return uVar5;
}

