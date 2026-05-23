// module: mt7915.ko
// function: Set_MonitorIndex_Proc @ 0x34840
// size: 168 bytes
//

undefined4 Set_MonitorIndex_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (2 < DebugLevel) {
    printk("--> %s()\n","Set_MonitorIndex_Proc");
  }
  if (iVar2 != 0) {
    uVar3 = HcGetBandByWdev(iVar2);
    uVar1 = simple_strtol(param_2,0,10);
    uVar3 = asic_set_air_mon_idx(param_1,iVar2,uVar1,uVar3);
    return uVar3;
  }
  if (-1 < DebugLevel) {
    printk("wdev is NULL\n");
  }
  return 0;
}

