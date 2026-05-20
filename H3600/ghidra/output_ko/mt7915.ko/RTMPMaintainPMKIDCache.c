// module: mt7915.ko
// function: RTMPMaintainPMKIDCache @ 0x19c7c
// size: 152 bytes
//

void RTMPMaintainPMKIDCache(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = &DAT_00368858 + param_1;
  iVar2 = 0;
  do {
    if (*pcVar1 != '\0') {
      if ((*(int *)(pcVar1 + -4) - jiffies) +
          *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11DS\n" +
                  (uint)(byte)pcVar1[-0x5c] * 0x5834 + param_1 + 0x28) < 0) {
        RTMPDeletePMKIDCache
                  (&DAT_003687fc + param_1,(uint)(byte)pcVar1[-0x5c],iVar2,
                   *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11DS\n" +
                           (uint)(byte)pcVar1[-0x5c] * 0x5834 + param_1 + 0x28),param_4);
      }
    }
    pcVar1 = pcVar1 + 0x60;
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x80);
  return;
}

