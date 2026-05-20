// module: mt7915.ko
// function: hc_init_ChCtrl @ 0xaa754
// size: 56 bytes
//

undefined4 hc_init_ChCtrl(int param_1)

{
  os_zero_mem(*(int *)(param_1 + 0xa797a0) + 0x38,0x4e0);
  os_zero_mem(*(int *)(param_1 + 0xa797a0) + 0x518,0x4e0);
  return 0;
}

