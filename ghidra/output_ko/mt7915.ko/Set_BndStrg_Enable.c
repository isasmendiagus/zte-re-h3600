// module: mt7915.ko
// function: Set_BndStrg_Enable @ 0x9ba00
// size: 200 bytes
//

undefined4 Set_BndStrg_Enable(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = simple_strtol(param_2,0,10);
  uVar3 = HcGetBandByWdev(uVar2);
  if (0 < DebugLevel) {
    printk("%s band %u bndstrg enable %d\n","Set_BndStrg_Enable",uVar3,uVar1);
  }
  if (uVar3 < 2) {
    if (param_1[uVar3 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar3 * 0x425 + 0xdb24f] + 0x1c))
                (param_1 + uVar3 * 0x425 + 0xdae49,uVar1);
      return 1;
    }
  }
  return 1;
}

