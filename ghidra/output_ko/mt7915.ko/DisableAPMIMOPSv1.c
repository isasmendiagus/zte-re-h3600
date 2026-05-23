// module: mt7915.ko
// function: DisableAPMIMOPSv1 @ 0x84cc0
// size: 256 bytes
//

void DisableAPMIMOPSv1(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  
  iVar1 = get_default_wdev();
  uVar2 = wlan_operate_get_ext_cha();
  iVar3 = wlan_config_get_ht_bw(iVar1);
  HcSetGreenAPActiveByBand(param_1,0,0);
  if ((iVar3 == 1) && (cVar4 = *(char *)(iVar1 + 0x1a), cVar4 != '\x0e')) {
    if (3 < DebugLevel) {
      printk("Run with BW_40\n");
      cVar4 = *(char *)(iVar1 + 0x1a);
    }
    wlan_operate_set_prim_ch(iVar1,cVar4);
    wlan_operate_set_ht_bw(iVar1,1,uVar2);
  }
  if (((*(ushort *)(iVar1 + 0x18) & 0x18) == 0) ||
     (("SetPartProfileParameters"[param_1 + 0x18] & 0xf0U) != 0x20)) {
    bbp_set_txdac(param_1,0);
  }
  else {
    bbp_set_txdac(param_1,2);
  }
  bbp_set_rxpath(param_1,"SetPartProfileParameters"[param_1 + 0x18] & 0xf);
  if (3 < DebugLevel) {
    printk("DisableAPMIMOPS, 305x/28xx reserve only one antenna\n");
    return;
  }
  return;
}

