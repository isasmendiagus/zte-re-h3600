// module: mt7915.ko
// function: QBSS_LoadBusyTimeGet @ 0x26d70
// size: 36 bytes
//

void QBSS_LoadBusyTimeGet(void)

{
  int iVar1;
  
  iVar1 = HcGetQloadCtrl();
  if (*(char *)(iVar1 + 0x14) != '\0') {
    __aeabi_uidiv(*(undefined4 *)(iVar1 + 0xc));
    return;
  }
  return;
}

