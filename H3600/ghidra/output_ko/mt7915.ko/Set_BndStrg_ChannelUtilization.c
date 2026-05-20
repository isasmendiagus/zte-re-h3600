// module: mt7915.ko
// function: Set_BndStrg_ChannelUtilization @ 0x9c030
// size: 252 bytes
//

undefined4
Set_BndStrg_ChannelUtilization
          (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  
  bVar2 = simple_strtol(param_2,0,10,param_4,param_4);
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar3 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_ChannelUtilization",uVar3);
  }
  if (uVar3 < 2) {
    if (100 < bVar2) {
      return 0;
    }
    if (param_1[uVar3 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar3 * 0x425 + 0xdb24f] + 0x30))
                (param_1 + uVar3 * 0x425 + 0xdae49,bVar2);
    }
    iVar1 = DebugLevel;
    *(byte *)((int)param_1 + uVar3 * 0x1094 + 0x36c949) = bVar2;
    if (0 < iVar1) {
      printk("%s(): ucChanUtilThreshold = %d\n","Set_BndStrg_ChannelUtilization",bVar2);
    }
  }
  return 1;
}

