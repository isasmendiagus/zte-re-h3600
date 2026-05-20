// module: mt7915.ko
// function: Set_BndStrg_Loading_INFO @ 0x9e4e4
// size: 192 bytes
//

undefined4 Set_BndStrg_Loading_INFO(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = simple_strtol(param_2,0,10);
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar2 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_Loading_INFO",uVar2);
  }
  if (uVar2 < 2) {
    if (param_1[uVar2 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar2 * 0x425 + 0xdb24f] + 0x48))
                (param_1,param_1 + uVar2 * 0x425 + 0xdae49,uVar1,4);
      return 1;
    }
  }
  return 1;
}

