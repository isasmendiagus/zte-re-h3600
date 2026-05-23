// module: mt7915.ko
// function: fill_tx_blk @ 0xc67b0
// size: 32 bytes
//

void fill_tx_blk(undefined4 param_1,int param_2,int param_3)

{
  if ((*(uint *)(param_3 + 0x18) & 0x1000000) == 0) {
                    /* WARNING: Could not recover jumptable at 0x000c67c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)(param_2 + 0x904) + 0x3c))();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000c67cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_2 + 0x904) + 0x38))();
  return;
}

