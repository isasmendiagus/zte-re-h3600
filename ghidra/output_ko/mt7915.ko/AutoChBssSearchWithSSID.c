// module: mt7915.ko
// function: AutoChBssSearchWithSSID @ 0x1f584
// size: 360 bytes
//

uint AutoChBssSearchWithSSID
               (undefined4 param_1,void *param_2,void *param_3,uint param_4,byte param_5,
               undefined4 param_6)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  char *__s2;
  byte bVar6;
  
  uVar3 = HcGetBandByWdev(param_6);
  iVar4 = HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
  pcVar5 = *(char **)(iVar4 + 4);
  if (param_4 < 0x21 && pcVar5 != (char *)0x0) {
    cVar1 = *pcVar5;
    if (cVar1 != '\0') {
      __s2 = pcVar5 + 8;
      bVar6 = 0;
      do {
        while( true ) {
          if ((byte)__s2[0x20] < 0xf) break;
          if (0xe < param_5) {
LAB_0001f600:
            iVar4 = memcmp(__s2 + -7,param_2,6);
            if ((iVar4 == 0) &&
               ((((bVar2 = __s2[-1], bVar2 == param_4 &&
                  (iVar4 = memcmp(param_3,__s2,param_4), iVar4 == 0)) ||
                 (iVar4 = memcmp(param_3,ZeroSsid,param_4), iVar4 == 0)) ||
                (iVar4 = memcmp(__s2,ZeroSsid,(uint)bVar2), iVar4 == 0)))) {
              return (uint)bVar6;
            }
          }
          __s2 = __s2 + 0x2a;
          bVar6 = bVar6 + 1;
          if (__s2 == pcVar5 + (uint)(byte)(cVar1 - 1) * 0x2a + 0x32) {
            return 0xffffffff;
          }
        }
        if (param_5 < 0xf) goto LAB_0001f600;
        __s2 = __s2 + 0x2a;
        bVar6 = bVar6 + 1;
      } while (__s2 != pcVar5 + (uint)(byte)(cVar1 - 1) * 0x2a + 0x32);
    }
  }
  else if (-1 < DebugLevel) {
    printk("pAd->pBssInfoTab equal NULL.\n");
  }
  return 0xffffffff;
}

