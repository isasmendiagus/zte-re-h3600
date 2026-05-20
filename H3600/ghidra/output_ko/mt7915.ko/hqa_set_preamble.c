// module: mt7915.ko
// function: hqa_set_preamble @ 0x24c270
// size: 116 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 hqa_set_preamble(int param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int local_18 [2];
  
  bVar1 = *(byte *)(param_1 + 0x4cc);
  local_18[0] = param_2 + 0xc;
  local_18[1] = 0;
  FUN_002474f4(1,4,local_18,local_18 + 1);
  *(char *)((uint)bVar1 * 0xd18 + param_1 + 0x1135) = (char)local_18[1];
  uVar2 = mt_serv_set_preamble(param_1);
  FUN_00246b90(param_2,2,uVar2);
  return uVar2;
}

