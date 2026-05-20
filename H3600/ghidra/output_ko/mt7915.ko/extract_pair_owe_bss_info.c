// module: mt7915.ko
// function: extract_pair_owe_bss_info @ 0x21c9d0
// size: 168 bytes
//

undefined4
extract_pair_owe_bss_info
          (void *param_1,uint param_2,void *param_3,void *param_4,byte *param_5,undefined1 *param_6)

{
  byte bVar1;
  uint __n;
  
  bVar1 = *(byte *)((int)param_1 + 6);
  __n = (uint)bVar1;
  if ((int)param_2 < (int)(__n + 6)) {
    return 0;
  }
  if ((__n + 7 & 0xff) < param_2) {
    memmove(param_3,param_1,6);
    memmove(param_4,(void *)((int)param_1 + 7),__n);
    *param_5 = bVar1;
    *param_6 = *(undefined1 *)((int)param_1 + 7 + __n + 1);
    return 1;
  }
  memmove(param_3,param_1,6);
  memmove(param_4,(void *)((int)param_1 + 7),__n);
  *param_5 = bVar1;
  return 1;
}

