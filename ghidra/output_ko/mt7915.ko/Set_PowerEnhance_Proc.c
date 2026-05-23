// module: mt7915.ko
// function: Set_PowerEnhance_Proc @ 0xd8380
// size: 296 bytes
//

undefined4 Set_PowerEnhance_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    printk("%s para error\n","Set_PowerEnhance_Proc");
  }
  else {
    uVar2 = HcGetBandByWdev();
    if (uVar2 < 2) {
      iVar1 = simple_strtol(param_2,0,10);
      param_1[(int)("MtCmdRxFilterPktLen" + uVar2 * 9 + 0x13)] = iVar1;
      if (2 < DebugLevel) {
        printk("PowerEnhance[%d]=%d\n",uVar2);
        iVar1 = param_1[(int)("MtCmdRxFilterPktLen" + uVar2 * 9 + 0x13)];
      }
      if ((iVar1 == 0) && (*(byte *)(param_1 + (int)("MtCmdSetFreqOffset" + uVar2 * 9)) - 1 < 10)) {
        puVar3 = &_LC180;
      }
      else {
        puVar3 = &_LC181;
      }
      _SetSKUCtrl(param_1,uVar2,puVar3);
      _SetBfBackoffCtrl(param_1,uVar2,&_LC181);
      return 1;
    }
  }
  return 1;
}

