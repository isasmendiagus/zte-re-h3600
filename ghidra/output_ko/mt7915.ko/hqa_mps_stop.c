// module: mt7915.ko
// function: hqa_mps_stop @ 0x24a740
// size: 96 bytes
//

undefined4 hqa_mps_stop(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_18;
  undefined1 local_14 [8];
  
  local_18 = param_2 + 0xc;
  FUN_002474f4(1,4,&local_18,local_14);
  *(undefined1 *)(param_1 + 0x4cc) = local_14[0];
  uVar1 = mt_serv_mps_operation(param_1,1);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

