// module: mt7915.ko
// function: hqa_set_fagc_rssi_path @ 0x24be98
// size: 144 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 hqa_set_fagc_rssi_path(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c;
  int local_18 [3];
  
  local_1c = param_2 + 0xc;
  local_18[0] = 0;
  local_18[1] = 0;
  FUN_002474f4(1,4,&local_1c,local_18);
  FUN_002474f4(1,4,&local_1c,local_18 + 1);
  *(char *)(param_1 + 0x4cc) = (char)local_18[0];
  *(char *)(local_18[0] * 0xd18 + param_1 + 0x113e) = (char)local_18[1];
  uVar1 = mt_serv_set_fagc_rssi_path(param_1);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

