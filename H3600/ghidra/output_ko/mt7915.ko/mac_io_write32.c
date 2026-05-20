// module: mt7915.ko
// function: mac_io_write32 @ 0x1df524
// size: 52 bytes
//

void mac_io_write32(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_io_ops();
  if (*(code **)(iVar1 + 0x14) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001df554. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x14))(param_1,param_2,param_3);
  return;
}

