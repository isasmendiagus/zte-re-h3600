// module: mt7915.ko
// function: Set_RADIUS_Key_Proc @ 0x293cc
// size: 344 bytes
//

undefined4 Set_RADIUS_Key_Proc(int *param_1,undefined4 param_2)

{
  bool bVar1;
  byte bVar2;
  char *__s;
  size_t __n;
  void *pvVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  uVar6 = (uint)*(byte *)(*param_1 + 0x3c);
  if (*(byte *)((int)param_1 + 0x2b7242) <= uVar6) {
    return 0;
  }
  __s = (char *)rstrtok(param_2,&_LC132);
  if (__s != (char *)0x0) {
    iVar5 = 0;
    bVar2 = 0;
    do {
      if (((*__s != '\0') && (__n = strlen(__s), __n < 0x41)) &&
         (iVar5 < (int)(uint)*(byte *)(param_1 + uVar6 * 0x160d + 0xadddb))) {
        iVar4 = iVar5 * 0x49 + uVar6 * 0x5834;
        iVar5 = iVar5 + 1;
        *(char *)((int)param_1 + (int)("%s: ************** Group%d **********\n" + iVar4 + 5)) =
             (char)__n;
        pvVar3 = memmove((char *)((int)param_1 + (int)("Ac2 --> %uus(%u)\n" + iVar4 + 1)),__s,__n);
        if (2 < DebugLevel) {
          printk("IF(ra%d), radius_key(seq-%d)=%s, len=%d\n",uVar6,iVar5,pvVar3,
                 *(char *)((int)param_1 +
                          (int)("%s: ************** Group%d **********\n" + iVar4 + 5)));
        }
      }
      __s = (char *)rstrtok(0,&_LC132);
      bVar1 = (bool)(bVar2 ^ 1);
      bVar2 = 1;
      if (__s == (char *)0x0) {
        bVar1 = false;
      }
    } while (bVar1);
  }
  return 1;
}

