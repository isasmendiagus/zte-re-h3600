// module: mt7915.ko
// function: ap_set_wireless_fixed_mcs @ 0xce9d8
// size: 152 bytes
//

void ap_set_wireless_fixed_mcs(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  uint uVar2;
  byte local_11 [5];
  
  local_11[0] = 0x21;
  if (param_2 != 0) {
    uVar1 = *(undefined2 *)(param_2 + 0xe0);
    if (*(int *)(param_2 + 8) != 0) {
      uVar2 = wlan_config_get_fixed_mcs(*(int *)(param_2 + 8));
      local_11[0] = (byte)uVar2;
      if (2 < DebugLevel) {
        printk("func:%s, arg:%u \n","ap_set_wireless_fixed_mcs");
        uVar2 = (uint)local_11[0];
      }
      if (uVar2 < 0x21) {
        snd_ra_fw_cmd(8,param_1,uVar1,local_11);
        return;
      }
    }
  }
  return;
}

