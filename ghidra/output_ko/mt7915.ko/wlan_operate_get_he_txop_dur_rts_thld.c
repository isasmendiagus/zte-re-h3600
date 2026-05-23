// module: mt7915.ko
// function: wlan_operate_get_he_txop_dur_rts_thld @ 0x206238
// size: 76 bytes
//

undefined2 wlan_operate_get_he_txop_dur_rts_thld(int param_1)

{
  undefined2 uVar1;
  
  if (param_1 == 0 || *(int *)(param_1 + 0xb14) == 0) {
    uVar1 = 0x3ff;
  }
  else {
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 0xb14) + 100);
  }
  if (3 < DebugLevel) {
    printk("%s: txop_dur_rts_thld = %d\n","wlan_operate_get_he_txop_dur_rts_thld",uVar1);
  }
  return uVar1;
}

