// module: mt7915.ko
// function: mtf_get_mib_bcn_tx_cnt @ 0x197328
// size: 64 bytes
//

uint mtf_get_mib_bcn_tx_cnt(int param_1,int param_2)

{
  undefined4 uVar1;
  uint local_c [2];
  
  if (param_2 == 0) {
    uVar1 = 0x820ed010;
  }
  else {
    uVar1 = 0x820fd010;
  }
  local_c[0] = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,local_c);
  return local_c[0] & 0xffff;
}

