// module: mt7915.ko
// function: hqa_set_rx_vector_idx @ 0x24bf28
// size: 156 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 hqa_set_rx_vector_idx(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_20 [5];
  
  local_20[0] = param_2 + 0xc;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  FUN_002474f4(1,4,local_20,local_20 + 1);
  FUN_002474f4(1,4,local_20,local_20 + 2);
  FUN_002474f4(1,4,local_20,local_20 + 3);
  *(char *)(param_1 + 0x4cc) = (char)local_20[1];
  uVar1 = mt_serv_set_rx_vector_idx(param_1,local_20[2],local_20[3]);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

