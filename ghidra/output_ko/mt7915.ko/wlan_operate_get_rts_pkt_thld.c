// module: mt7915.ko
// function: wlan_operate_get_rts_pkt_thld @ 0x107f44
// size: 24 bytes
//

undefined1 wlan_operate_get_rts_pkt_thld(int param_1)

{
  undefined1 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0xb14) != 0) {
    uVar1 = *(undefined1 *)(*(int *)(param_1 + 0xb14) + 0x14);
  }
  return uVar1;
}

