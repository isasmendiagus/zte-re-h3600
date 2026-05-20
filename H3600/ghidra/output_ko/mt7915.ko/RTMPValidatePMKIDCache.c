// module: mt7915.ko
// function: RTMPValidatePMKIDCache @ 0x19bd0
// size: 72 bytes
//

int RTMPValidatePMKIDCache(int param_1,undefined4 param_2,undefined4 param_3,void *param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RTMPSearchPMKIDCache();
  if (iVar1 != -1) {
    iVar2 = memcmp(param_4,(void *)(param_1 + iVar1 * 0x60 + 7),0x10);
    if (iVar2 != 0) {
      iVar1 = -1;
    }
    return iVar1;
  }
  return -1;
}

