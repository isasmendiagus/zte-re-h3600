// module: mt7915.ko
// function: phy_io_write32 @ 0x1df58c
// size: 52 bytes
//

void phy_io_write32(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_io_ops();
  if (*(code **)(iVar1 + 0x2c) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001df5bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x2c))(param_1,param_2,param_3);
  return;
}

