// module: mt7915.ko
// function: hif_io_read32 @ 0x1df438
// size: 52 bytes
//

void hif_io_read32(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)hc_get_io_ops();
  if ((code *)*puVar1 == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001df468. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*puVar1)(param_1,param_2,param_3);
  return;
}

