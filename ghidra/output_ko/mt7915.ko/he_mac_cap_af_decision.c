// module: mt7915.ko
// function: he_mac_cap_af_decision @ 0x206038
// size: 112 bytes
//

void he_mac_cap_af_decision(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar3 = (uint)(param_2 << 3) >> 0x1e;
  uVar1 = wlan_operate_get_he_af();
  if (uVar3 <= uVar1) {
    uVar1 = uVar3;
  }
  if (2 < DebugLevel) {
    uVar2 = wlan_operate_get_he_af(param_1);
    printk("%s:he_af(%d,%d,%d)\n","he_mac_cap_af_decision",uVar1 & 0xff,uVar2,uVar3);
  }
  wlan_operate_set_he_af(param_1,uVar1 & 0xff);
  return;
}

