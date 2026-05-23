// module: mt7915.ko
// function: Show_VLAN_Info_Proc @ 0x27838
// size: 316 bytes
//

undefined4
Show_VLAN_Info_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *(int *)(*param_1 + 0x38);
  iVar3 = *(int *)(*param_1 + 0x3c);
  if ((iVar1 - 0x100U & 0xfffffeff) == 0) {
    piVar2 = (int *)0x5834;
    param_1 = param_1 + iVar3 * 0x160d + 0xadc92;
  }
  else {
    if (iVar1 != 0x400) {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("Unexpected if_type\n");
      return 0;
    }
    piVar2 = param_1 + iVar3 * 0x84dec;
    param_1 = piVar2 + 0xdb6d6;
  }
  if (param_1 == (int *)0x0) {
    return 0;
  }
  if ((((0 < DebugLevel) &&
       (printk("bVLAN_Tag=%d\n",(char)param_1[0x23e],piVar2,DebugLevel,param_4), 0 < DebugLevel)) &&
      (printk("VLANID=%d\n",*(undefined2 *)((int)param_1 + 0x8fa)), 0 < DebugLevel)) &&
     ((printk("VLANPriority=%d\n",(short)param_1[0x23f]), 0 < DebugLevel &&
      (printk("VLANPolicy(Tx)=%d\n",*(undefined2 *)((int)param_1 + 0x8fe)), 0 < DebugLevel)))) {
    printk("VLANPolicy(Rx)=%d\n",(short)param_1[0x240]);
  }
  return 1;
}

