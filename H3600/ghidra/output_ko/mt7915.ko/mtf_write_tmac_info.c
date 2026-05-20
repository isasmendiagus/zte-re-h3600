// module: mt7915.ko
// function: mtf_write_tmac_info @ 0x19e698
// size: 20 bytes
//

void mtf_write_tmac_info(undefined4 param_1,undefined4 param_2,int param_3)

{
  if ((*(uint *)(param_3 + 0x18) & 0x1000000) == 0) {
    mtf_write_tmac_info_by_host();
    return;
  }
  mtf_write_tmac_info_by_wa();
  return;
}

