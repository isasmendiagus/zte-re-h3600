// module: mt7915.ko
// function: hif_io_force_write32 @ 0x1df404
// size: 52 bytes
//

void hif_io_force_write32(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_io_ops();
  if (*(code **)(iVar1 + 0xc) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001df434. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0xc))(param_1,param_2,param_3);
  return;
}

