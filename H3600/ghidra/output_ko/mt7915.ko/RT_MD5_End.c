// module: mt7915.ko
// function: RT_MD5_End @ 0x12560c
// size: 124 bytes
//

void RT_MD5_End(void *param_1,void *param_2)

{
  uint uVar1;
  undefined1 auStack_10 [4];
  
  *(undefined1 *)((int)param_1 + *(int *)((int)param_1 + 0x58) + 0x18) = 0x80;
  if (0x37 < *(uint *)((int)param_1 + 0x58)) {
    RT_MD5_Hash();
  }
  uVar1 = *(int *)((int)param_1 + 0x14) << 3 | *(uint *)((int)param_1 + 0x10) >> 0x1d;
  *(uint *)((int)param_1 + 0x50) = *(uint *)((int)param_1 + 0x10) << 3;
  *(uint *)((int)param_1 + 0x54) = uVar1;
  RT_MD5_Hash(param_1,uVar1,auStack_10);
  memmove(param_2,param_1,0x10);
  return;
}

