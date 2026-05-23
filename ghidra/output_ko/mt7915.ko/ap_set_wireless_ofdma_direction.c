// module: mt7915.ko
// function: ap_set_wireless_ofdma_direction @ 0xceb74
// size: 124 bytes
//

void ap_set_wireless_ofdma_direction(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    return;
  }
  iVar1 = wlan_config_get_ofdma_direction(param_2);
  if (2 < DebugLevel) {
    printk("func:%s, arg:%u \n","ap_set_wireless_ofdma_direction",iVar1);
  }
  if (iVar1 == 0) {
    return;
  }
  SetMuruProtFrameThr(param_1,&_LC9);
  if (iVar1 != 3) {
    return;
  }
  SetMuru20MDynAlgo(param_1,&_LC10);
  return;
}

