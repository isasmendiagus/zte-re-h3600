// module: mt7915.ko
// function: mt7915_get_rx_stat_band @ 0x17bd50
// size: 180 bytes
//

undefined4
mt7915_get_rx_stat_band
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 *param_4)

{
  undefined1 auStack_48 [2];
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined4 local_40;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  os_zero_mem(auStack_48,0x20);
  mt_cmd_get_rx_stat_band(param_1,param_2,auStack_48);
  *param_4 = local_46;
  *(undefined4 *)(param_4 + 2) = local_40;
  param_4[4] = local_44;
  param_4[5] = local_42;
  param_4[6] = local_3c;
  param_4[7] = local_3a;
  param_4[8] = local_38;
  param_4[9] = local_36;
  param_4[10] = local_34;
  param_4[0xb] = local_32;
  param_4[0xc] = local_30;
  param_4[0xd] = local_2e;
  param_4[0xe] = local_2c;
  param_4[0xf] = local_2a;
  return 0;
}

