// module: mt7915.ko
// function: owe_calculate_secret @ 0x21bdf8
// size: 180 bytes
//

undefined4 owe_calculate_secret(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *local_1c [2];
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  local_1c[0] = (undefined4 *)0x0;
  ecc_point_mul_windowed
            (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x14),uVar1,local_1c);
  if (local_1c[0] == (undefined4 *)0x0) {
    uVar1 = 0;
    if (-1 < DebugLevel) {
      printk("==> %s(), can\'t output the common secret point\n","owe_calculate_secret");
    }
  }
  else {
    ecc_point_3d_to_2d(uVar1,local_1c[0]);
    Bignum_Copy(*local_1c[0],param_2);
    if (local_1c[0] == (undefined4 *)0x0) {
      uVar1 = 1;
    }
    else {
      ecc_point_free(local_1c);
      uVar1 = 1;
    }
  }
  return uVar1;
}

