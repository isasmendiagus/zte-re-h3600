// module: mt7915.ko
// function: mtf_dump_wtbl_info @ 0x19ecd4
// size: 92 bytes
//

void mtf_dump_wtbl_info(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x44) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0019ed08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x44))(param_1,param_2);
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("Not supported\n");
  return;
}

