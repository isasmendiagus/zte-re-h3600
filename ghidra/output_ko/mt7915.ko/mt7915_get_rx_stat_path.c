// module: mt7915.ko
// function: mt7915_get_rx_stat_path @ 0x17bcc0
// size: 144 bytes
//

undefined4 mt7915_get_rx_stat_path(int param_1,int param_2,uint param_3,undefined2 *param_4)

{
  undefined1 uStack_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  
  os_zero_mem(&uStack_1c,4);
  mt_cmd_get_rx_stat_path(param_1,param_3,&uStack_1c);
  if (param_2 == 1) {
    param_3 = param_3 - 2 & 0xff;
  }
  *(undefined1 *)((int)param_4 + 7) = local_1a;
  *(undefined1 *)(param_4 + 3) = local_1b;
  param_1 = param_1 + ((short)param_2 * 0x5a + param_3) * 4;
  *param_4 = (short)*(undefined4 *)(param_1 + 0xa7bfd4);
  param_4[1] = (short)*(undefined4 *)(param_1 + 0xa7bf84);
  *(char *)(param_4 + 2) = (char)*(undefined4 *)(param_1 + 0xa7bfe4);
  *(char *)((int)param_4 + 5) = (char)*(undefined4 *)(param_1 + 0xa7bff4);
  return 0;
}

