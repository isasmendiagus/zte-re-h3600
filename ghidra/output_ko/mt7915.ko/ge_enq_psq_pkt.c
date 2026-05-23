// module: mt7915.ko
// function: ge_enq_psq_pkt @ 0xcfe44
// size: 80 bytes
//

undefined4 ge_enq_psq_pkt(undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  _raw_spin_lock_bh(param_3 + 0xa4);
  *param_4 = 0;
  if (*(undefined4 **)(param_3 + 0x68) == (undefined4 *)0x0) {
    *(undefined4 **)(param_3 + 100) = param_4;
  }
  else {
    **(undefined4 **)(param_3 + 0x68) = param_4;
  }
  *(undefined4 **)(param_3 + 0x68) = param_4;
  *(int *)(param_3 + 0x6c) = *(int *)(param_3 + 0x6c) + 1;
  _raw_spin_unlock_bh(param_3 + 0xa4);
  return 0;
}

