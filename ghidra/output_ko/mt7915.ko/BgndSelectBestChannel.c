// module: mt7915.ko
// function: BgndSelectBestChannel @ 0x22cfb4
// size: 200 bytes
//

char BgndSelectBestChannel(int param_1,undefined4 param_2)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  
  if (*(char *)(param_1 + 0xa795e4) == '\0') {
    uVar3 = 0xffffffff;
    cVar4 = '\0';
  }
  else {
    cVar4 = '\0';
    pcVar1 = (char *)(param_1 + 0xa79240);
    iVar2 = 0;
    uVar3 = 0xffffffff;
    do {
      if (*pcVar1 == '\0') {
        uVar5 = *(uint *)(pcVar1 + -8);
        if (0 < DebugLevel) {
          printk("Band index=%d, ChIdx=%d control-Channle=%d cen-channel=%d, Percentage=%d\n",
                 param_2,iVar2,pcVar1[-0xc],pcVar1[-0xb],uVar5);
        }
        if (uVar5 <= uVar3) {
          cVar4 = pcVar1[-0xc];
          uVar3 = uVar5;
        }
      }
      iVar2 = iVar2 + 1;
      pcVar1 = pcVar1 + 0x10;
    } while (iVar2 < (int)(uint)*(byte *)(param_1 + 0xa795e4));
  }
  *(uint *)(param_1 + 0xa7961c) = uVar3;
  return cVar4;
}

