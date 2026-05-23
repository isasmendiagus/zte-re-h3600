// module: mt7915.ko
// function: enable_greenap @ 0x84960
// size: 108 bytes
//

void enable_greenap(undefined4 param_1,undefined1 *param_2)

{
  if (2 < DebugLevel) {
    printk("band_idx(%d), enable_greenap\n",*param_2);
  }
  HcSetGreenAPActiveByBand(param_1,*param_2,1);
  RTMP_GREENAP_ON_OFF_CTRL(param_1,*param_2,1);
  mt_asic_pcie_aspm_dym_ctrl(param_1,*param_2,1,0);
  return;
}

