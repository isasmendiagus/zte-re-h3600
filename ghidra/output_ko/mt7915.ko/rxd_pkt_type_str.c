// module: mt7915.ko
// function: rxd_pkt_type_str @ 0x19b198
// size: 24 bytes
//

undefined4 rxd_pkt_type_str(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = rmac_info_type_str._20_4_;
  if (param_1 < 5) {
    uVar1 = *(undefined4 *)(rmac_info_type_str + param_1 * 4);
  }
  return uVar1;
}

