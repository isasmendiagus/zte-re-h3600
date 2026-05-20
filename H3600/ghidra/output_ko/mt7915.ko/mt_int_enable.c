// module: mt7915.ko
// function: mt_int_enable @ 0x1ca040
// size: 84 bytes
//

void mt_int_enable(int param_1,uint *param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = *param_2 & ~(param_2[2] & ~param_3);
  param_2[2] = param_2[2] & ~param_3;
  hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2[1],uVar1,param_2,param_4);
  if (uVar1 != 0) {
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x2000;
  }
  return;
}

