// module: mt7915.ko
// function: disable_greenap @ 0x849cc
// size: 108 bytes
//

void disable_greenap(undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  if (2 < DebugLevel) {
    printk("band_idx(%d), disable_greenap\n",*param_2);
  }
  HcSetGreenAPActiveByBand(param_1,*param_2,0);
  mt_asic_pcie_aspm_dym_ctrl(param_1,*param_2,0,0);
  RTMP_GREENAP_ON_OFF_CTRL(param_1,*param_2,0,param_4);
  return;
}

