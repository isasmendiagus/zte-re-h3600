// module: mt7915.ko
// function: MlmeQueueDestroy @ 0x12db14
// size: 48 bytes
//

void MlmeQueueDestroy(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  _raw_spin_lock_bh(param_1 + 3);
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  _raw_spin_unlock_bh(param_1 + 3,extraout_r1,extraout_r2,param_4);
  return;
}

