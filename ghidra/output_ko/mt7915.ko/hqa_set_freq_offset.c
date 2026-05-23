// module: mt7915.ko
// function: hqa_set_freq_offset @ 0x24c114
// size: 116 bytes
//

undefined4 hqa_set_freq_offset(int param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int local_18;
  undefined4 local_14;
  
  bVar1 = *(byte *)(param_1 + 0x4cc);
  local_18 = param_2 + 0xc;
  local_14 = 0;
  FUN_002474f4(1,4,&local_18,&local_14);
  *(undefined4 *)((uint)bVar1 * 0xd18 + param_1 + 0x1148) = local_14;
  uVar2 = mt_serv_set_freq_offset(param_1);
  FUN_00246b90(param_2,2,uVar2);
  return uVar2;
}

