// module: mt7915.ko
// function: chip_get_lpon_frcr @ 0x189044
// size: 48 bytes
//

undefined4 chip_get_lpon_frcr(int param_1)

{
  undefined4 local_c [2];
  
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820eb314,local_c);
  return local_c[0];
}

