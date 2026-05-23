// module: mt7915.ko
// function: ecc_point_set_z_to_one @ 0x2183a8
// size: 52 bytes
//

void ecc_point_set_z_to_one(int param_1)

{
  undefined1 local_11 [5];
  
  local_11[0] = 1;
  Bignum_Bin2BI(local_11,1,param_1 + 8);
  *(undefined1 *)(param_1 + 0xc) = 1;
  return;
}

