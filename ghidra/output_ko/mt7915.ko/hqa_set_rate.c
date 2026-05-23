// module: mt7915.ko
// function: hqa_set_rate @ 0x247700
// size: 104 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 hqa_set_rate(int param_1,int param_2)

{
  byte bVar1;
  int local_20 [3];
  
  bVar1 = *(byte *)(param_1 + 0x4cc);
  local_20[0] = param_2 + 0xc;
  local_20[1] = 0;
  FUN_002474f4(1,4,local_20,local_20 + 1);
  *(char *)((uint)bVar1 * 0xd18 + param_1 + 0x1138) = (char)local_20[1];
  FUN_00246b90(param_2,2,0);
  return 0;
}

