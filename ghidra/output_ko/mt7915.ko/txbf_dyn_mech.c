// module: mt7915.ko
// function: txbf_dyn_mech @ 0x88b9c
// size: 80 bytes
//

void txbf_dyn_mech(int param_1)

{
  if (4 < DebugLevel) {
    printk(&_LC113,"txbf_dyn_mech");
  }
  if ((*(uint *)(param_1 + 0xa789d0) & 1) == 0) {
    return;
  }
  asic_txbf_bfee_adaption(param_1);
  return;
}

