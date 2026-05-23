// module: mt7915.ko
// function: SupportRate @ 0x146878
// size: 364 bytes
//

void SupportRate(byte *param_1,int *param_2,byte *param_3,byte *param_4)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  uint __n;
  uint __n_00;
  int iVar4;
  
  bVar2 = *param_1;
  __n_00 = (uint)bVar2;
  __n = (uint)param_1[0xd];
  *param_4 = 0;
  if (__n_00 - 1 < 0xc) {
    memmove((void *)*param_2,param_1 + 1,__n_00);
    *param_3 = bVar2;
  }
  else {
    *param_3 = 8;
    *(undefined1 *)*param_2 = 0x82;
    *(undefined1 *)(*param_2 + 1) = 0x84;
    *(undefined1 *)(*param_2 + 2) = 0x8b;
    *(undefined1 *)(*param_2 + 3) = 0x96;
    iVar4 = DebugLevel;
    *(undefined1 *)(*param_2 + 4) = 0x12;
    *(undefined1 *)(*param_2 + 5) = 0x24;
    *(undefined1 *)(*param_2 + 6) = 0x48;
    iVar3 = *param_2;
    *(undefined1 *)(iVar3 + 7) = 0x6c;
    if (3 < iVar4) {
      printk("SUPP_RATES., Len=%d\n",__n_00,0x6c,iVar3,param_4);
    }
    __n_00 = (uint)*param_3;
  }
  if (__n + __n_00 < 0xd) {
    memmove((void *)(*param_2 + __n_00),param_1 + 0xe,__n);
    bVar2 = *param_3;
    *param_3 = (byte)(__n + bVar2);
    if ((__n + bVar2 & 0xff) == 0) {
      return;
    }
  }
  else {
    memmove((void *)(*param_2 + __n_00),param_1 + 0xe,0xc - __n_00);
    *param_3 = 0xc;
  }
  iVar4 = 0;
  do {
    pbVar1 = (byte *)(*param_2 + iVar4);
    iVar4 = iVar4 + 1;
    bVar2 = *pbVar1 & 0x7f;
    if (*param_4 < bVar2) {
      *param_4 = bVar2;
    }
  } while (iVar4 < (int)(uint)*param_3);
  return;
}

