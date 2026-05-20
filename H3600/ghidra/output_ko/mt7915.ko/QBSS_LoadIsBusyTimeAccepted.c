// module: mt7915.ko
// function: QBSS_LoadIsBusyTimeAccepted @ 0x26db0
// size: 52 bytes
//

bool QBSS_LoadIsBusyTimeAccepted(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = HcGetQloadCtrl();
  if (*(char *)(iVar1 + 0xc1) == '\0') {
    return true;
  }
  return param_2 < *(uint *)(iVar1 + 0xd4);
}

