// module: mt7915.ko
// function: MultiCastFilterTableReset @ 0x240458
// size: 96 bytes
//

void MultiCastFilterTableReset(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r2;
  
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar1 & 0x400) != 0) {
    return;
  }
  if (*param_2 != 0) {
    os_free_mem();
    *param_2 = 0;
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s Multicase filter table is not ready.\n","MultiCastFilterTableReset",extraout_r2,param_4
        );
  return;
}

