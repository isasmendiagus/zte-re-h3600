// module: mt7915.ko
// function: Set_BndStrg_2G_InSilenceNum @ 0x9bec8
// size: 160 bytes
//

undefined4 Set_BndStrg_2G_InSilenceNum(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar1 = simple_strtol(param_2,0,10);
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar2 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_2G_InSilenceNum",uVar2);
  }
  if ((uVar2 < 2) && (*(char *)((int)param_1 + uVar2 * 0x1094 + 0x36c992) != '\x01')) {
    *(undefined1 *)((int)param_1 + uVar2 * 0x1094 + 0x36c9b2) = uVar1;
  }
  return 1;
}

