// module: mt7915.ko
// function: ZTE_Temperature_Protection_Work @ 0x15ff40
// size: 124 bytes
//

void ZTE_Temperature_Protection_Work(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined4 local_1c;
  
  iVar2 = g_pAd;
  iVar3 = 0;
  local_1c = 0;
  if (g_pAd != 0) {
    cVar4 = '\0';
    do {
      pcVar1 = &_LANCHOR0 + iVar3;
      iVar3 = iVar3 + 10;
      if (*pcVar1 != '\0') {
        RTMP_GET_TEMPERATURE(iVar2,cVar4,&local_1c);
        ZTE_WLAN_Temperature_Protection_Check(iVar2,cVar4,local_1c);
      }
      cVar4 = cVar4 + '\x01';
    } while (iVar3 != 0x14);
  }
  return;
}

