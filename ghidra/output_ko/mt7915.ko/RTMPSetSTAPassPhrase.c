// module: mt7915.ko
// function: RTMPSetSTAPassPhrase @ 0xef2f8
// size: 372 bytes
//

void RTMPSetSTAPassPhrase(undefined4 param_1,int param_2,char *param_3)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 != 0) {
    sVar2 = strlen(param_3);
    param_3[sVar2] = '\0';
    if (((*(uint *)(param_2 + 0x2c) & 0x12cf8) != 0) &&
       (iVar3 = SetWPAPSKKey(param_1,param_3,sVar2,iVar1 + 0x212406,
                             *(undefined1 *)(iVar1 + 0x212426),iVar1 + 0x212520), iVar3 == 1)) {
      RTMPZeroMemory(iVar1 + 0x2124da,0x40);
      sVar2 = strlen(param_3);
      RTMPMoveMemory(iVar1 + 0x2124da,param_3,sVar2);
      sVar2 = strlen(param_3);
      *(size_t *)(iVar1 + 0x21251c) = sVar2;
      if ((*(uint *)(param_2 + 0x2c) & 0x90) == 0) {
        if ((*(uint *)(param_2 + 0x2c) & 0x20) != 0) {
          *(undefined1 *)(iVar1 + 0x2127b9) = 0;
        }
      }
      else {
        *(undefined1 *)(iVar1 + 0x2127b9) = 1;
      }
      __memzero((void *)(iVar1 + 0x3c81),0x40);
      *(undefined4 *)(iVar1 + 0x3cc4) = 0;
      sVar2 = strlen(param_3);
      if (sVar2 - 8 < 0x39) {
        memmove((void *)(iVar1 + 0x3c81),param_3,sVar2);
        sVar2 = strlen(param_3);
        *(size_t *)(iVar1 + 0x3cc4) = sVar2;
      }
      if (3 < DebugLevel) {
        printk("%s::(WPAPSK=%s)\n","RTMPSetSTAPassPhrase",param_3);
        return;
      }
    }
  }
  return;
}

