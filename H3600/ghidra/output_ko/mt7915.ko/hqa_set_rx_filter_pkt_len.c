// module: mt7915.ko
// function: hqa_set_rx_filter_pkt_len @ 0x24b610
// size: 176 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 hqa_set_rx_filter_pkt_len(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_20;
  int local_1c [4];
  
  local_20 = param_2 + 0xc;
  local_1c[0] = 0;
  local_1c[1] = 0;
  local_1c[2] = 0;
  FUN_002474f4(1,4,&local_20,local_1c);
  FUN_002474f4(1,4,&local_20,local_1c + 1);
  FUN_002474f4(1,4,&local_20,local_1c + 2);
  iVar2 = local_1c[0] * 0xd18 + param_1;
  *(char *)(param_1 + 0x4cc) = (char)local_1c[0];
  *(int *)(iVar2 + 0x110c) = local_1c[2];
  *(char *)(iVar2 + 0x110b) = (char)local_1c[1];
  uVar1 = mt_serv_set_rx_filter_pkt_len(param_1);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

