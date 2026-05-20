// module: mt7915.ko
// function: WscApCliLinkDownById @ 0x1e9cc0
// size: 268 bytes
//

void WscApCliLinkDownById(int param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  
  if (1 < param_2) {
    return;
  }
  cVar1 = (&DAT_00580e8d)[param_1 + param_2 * 0x2137b0];
  if (2 < DebugLevel) {
    printk("-----> WscApCliLinkDownById, apidx=%u, apcliEn=%d\n",param_2,cVar1);
  }
  iVar2 = param_1 + param_2 * 0x2137b0;
  memmove((void *)(iVar2 + 0x36eebe),&DAT_0036db73 + iVar2,6);
  if (cVar1 == '\x01') {
    (&DAT_00580e8d)[param_1 + param_2 * 0x2137b0] = 0;
    ApCliIfDown(param_1);
  }
  param_1 = param_1 + param_2 * 0x2137b0;
  (&DAT_00580e8d)[param_1] = cVar1;
  *(undefined4 *)(&DAT_0036ee48 + param_1) = 3;
  (&DAT_00371820)[param_1] = 1;
  return;
}

