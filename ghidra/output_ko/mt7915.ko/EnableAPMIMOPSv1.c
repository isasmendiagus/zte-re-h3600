// module: mt7915.ko
// function: EnableAPMIMOPSv1 @ 0x84c14
// size: 172 bytes
//

void EnableAPMIMOPSv1(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = get_default_wdev();
  HcSetGreenAPActiveByBand(param_1,0,1);
  if (3 < DebugLevel) {
    printk("Run with BW_20\n");
  }
  wlan_operate_set_ht_bw(uVar1,0,0);
  if ((1 < ("SetPartProfileParameters"[param_1 + 0x18] & 0xfU)) ||
     (0x1f < (byte)"SetPartProfileParameters"[param_1 + 0x18])) {
    bbp_set_txdac(param_1,0);
    bbp_set_rxpath(param_1,1);
  }
  if (3 < DebugLevel) {
    printk("EnableAPMIMOPS, 305x/28xx changes the # of antenna to 1\n");
    return;
  }
  return;
}

