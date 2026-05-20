// module: mt7915.ko
// function: build_ht_op_ie @ 0x139a74
// size: 40 bytes
//

undefined1 * build_ht_op_ie(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0x1a);
  param_2[1] = 0;
  param_2[2] = 0;
  *param_2 = uVar1;
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  return param_2 + 0x16;
}

