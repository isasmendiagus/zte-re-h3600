// module: mt7915.ko
// function: RTMPCheckRates @ 0x12f430
// size: 184 bytes
//

void RTMPCheckRates(void *param_1,char *param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  ushort *puVar4;
  uint __n;
  int iVar5;
  byte local_24 [12];
  
  __memzero(local_24,0xc);
  cVar1 = *param_2;
  if (param_3 == 2) {
    iVar5 = 4;
  }
  else {
    iVar5 = 0xc;
  }
  if (cVar1 == '\0') {
    __n = 0;
  }
  else {
    pbVar3 = (byte *)((int)param_1 + -1);
    __n = 0;
    do {
      pbVar3 = pbVar3 + 1;
      bVar2 = *pbVar3;
      puVar4 = (ushort *)(OfdmRateToRxwiMCS + 10);
      do {
        puVar4 = puVar4 + 1;
        if (*puVar4 == (bVar2 & 0x7f)) {
          local_24[__n] = bVar2;
          __n = __n + 1 & 0xff;
        }
      } while (puVar4 != (ushort *)(RateIdTo500Kbps + (iVar5 - 1U & 0xff) * 2));
    } while (pbVar3 != (byte *)((int)param_1 + (uint)(byte)(cVar1 - 1)));
  }
  *param_2 = (char)__n;
  memcpy(param_1,local_24,__n);
  return;
}

