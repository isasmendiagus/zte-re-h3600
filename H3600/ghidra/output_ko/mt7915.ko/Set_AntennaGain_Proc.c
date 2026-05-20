// module: mt7915.ko
// function: Set_AntennaGain_Proc @ 0xd82d4
// size: 168 bytes
//

undefined4 Set_AntennaGain_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    printk("%s para error\n","Set_AntennaGain_Proc");
  }
  else {
    uVar3 = HcGetBandByWdev();
    if (uVar3 < 2) {
      uVar1 = simple_strtol(param_2,0,10);
      iVar2 = DebugLevel;
      *(undefined1 *)(param_1 + (int)("MtCmdSetFreqOffset" + uVar3 * 9)) = uVar1;
      if (2 < iVar2) {
        printk("ZteAntennaGain[%d]=%d\n",uVar3,uVar1);
      }
    }
  }
  return 1;
}

