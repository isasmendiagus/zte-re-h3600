// module: mt7915.ko
// function: mcu_io_read32 @ 0x1df5c0
// size: 52 bytes
//

void mcu_io_read32(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_io_ops();
  if (*(code **)(iVar1 + 0x20) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001df5f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x20))(param_1,param_2,param_3);
  return;
}

