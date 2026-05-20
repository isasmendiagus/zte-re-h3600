// module: mt7915.ko
// function: mt7915_rxv_stat_reset @ 0x17b32c
// size: 88 bytes
//

undefined4 mt7915_rxv_stat_reset(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  os_zero_mem(*(undefined4 *)(param_1 + 0xa7c214),*(undefined2 *)(param_1 + 0xa7c210),param_3,
              param_4,param_4);
  os_free_mem(*(undefined4 *)(param_1 + 0xa7c214));
  *(undefined4 *)(param_1 + 0xa7c214) = 0;
  *(undefined2 *)(param_1 + 0xa7c210) = 0;
  *(undefined4 *)(param_1 + param_2 * 0x168 + 0xa7bf40) = 0;
  return 0;
}

