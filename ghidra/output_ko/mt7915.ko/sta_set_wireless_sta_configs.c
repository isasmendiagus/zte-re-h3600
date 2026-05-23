// module: mt7915.ko
// function: sta_set_wireless_sta_configs @ 0xcfc64
// size: 4 bytes
//

void sta_set_wireless_sta_configs(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  uint uVar2;
  byte abStack_11 [5];
  
  abStack_11[0] = 0x21;
  if (param_2 != 0) {
    uVar1 = *(undefined2 *)(param_2 + 0xe0);
    if (*(int *)(param_2 + 8) != 0) {
      uVar2 = wlan_config_get_fixed_mcs(*(int *)(param_2 + 8));
      abStack_11[0] = (byte)uVar2;
      if (2 < DebugLevel) {
        printk("func:%s, arg:%u \n","sta_set_wireless_fixed_mcs_run_time");
        uVar2 = (uint)abStack_11[0];
      }
      if (uVar2 < 0x21) {
        snd_ra_fw_cmd(8,param_1,uVar1,abStack_11);
        return;
      }
    }
  }
  return;
}

