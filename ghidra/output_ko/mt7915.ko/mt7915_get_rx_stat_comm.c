// module: mt7915.ko
// function: mt7915_get_rx_stat_comm @ 0x17bc78
// size: 72 bytes
//

undefined4
mt7915_get_rx_stat_comm
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 *param_4)

{
  undefined1 auStack_1c [2];
  undefined2 local_1a;
  undefined4 local_18;
  undefined4 local_14;
  
  os_zero_mem(auStack_1c,0xc);
  mt_cmd_get_rx_stat_comm(param_1,auStack_1c);
  *param_4 = local_1a;
  *(undefined4 *)(param_4 + 2) = local_18;
  *(undefined4 *)(param_4 + 4) = local_14;
  return 0;
}

