// module: mt7915.ko
// function: store_time_log_by_tag @ 0x1478d8
// size: 92 bytes
//

int store_time_log_by_tag(int param_1,void *param_2)

{
  void *__dest;
  uint uVar1;
  uint uVar2;
  
  if (param_1 != 1) {
    return param_1;
  }
  uVar2 = (uint)DAT_005f39cc;
  __dest = (void *)(uVar2 * 0x8c + 0x5f39d0);
  if (__dest == (void *)0x0) {
    return 0;
  }
  memcpy(__dest,param_2,0x8c);
  uVar2 = uVar2 + 1;
  uVar1 = uVar2 & 0xff;
  DAT_005f39cc = (char)uVar2 + (char)(uVar1 / 6) * -6;
  return uVar1 * -0x55555555;
}

