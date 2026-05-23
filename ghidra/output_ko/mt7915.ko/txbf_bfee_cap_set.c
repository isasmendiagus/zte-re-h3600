// module: mt7915.ko
// function: txbf_bfee_cap_set @ 0x85080
// size: 100 bytes
//

void txbf_bfee_cap_set(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (4 < DebugLevel) {
    printk("[%s] valid=%u, bfer_cap_su=%u, num_snd_dimension=%u\n","txbf_bfee_cap_set",param_1,
           param_2,param_3);
  }
  DAT_005f352c = (char)param_1;
  DAT_005f352d = (char)param_2;
  DAT_005f352e = (char)param_3;
  return;
}

