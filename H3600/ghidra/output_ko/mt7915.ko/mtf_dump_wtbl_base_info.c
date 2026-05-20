// module: mt7915.ko
// function: mtf_dump_wtbl_base_info @ 0x19ec80
// size: 84 bytes
//

void mtf_dump_wtbl_base_info(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x4c) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0019ecac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x4c))(param_1);
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("Not supported\n");
  return;
}

