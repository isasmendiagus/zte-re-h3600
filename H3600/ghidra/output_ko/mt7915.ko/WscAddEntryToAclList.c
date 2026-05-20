// module: mt7915.ko
// function: WscAddEntryToAclList @ 0x201208
// size: 264 bytes
//

void WscAddEntryToAclList(int param_1,int param_2,void *param_3)

{
  bool bVar1;
  int iVar2;
  char *__s1;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = param_2 * 0x5834;
  if ((*(uint *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + param_1 + iVar5 + 0x31) &
      0xfffffffd) == 0) {
    return;
  }
  uVar4 = *(uint *)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" + param_1 + iVar5 + 1);
  if (uVar4 < 0x7f) {
    if (uVar4 != 0) {
      bVar1 = false;
      __s1 = "Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" + param_1 + iVar5 + 5;
      do {
        pcVar3 = __s1 + 8;
        iVar2 = memcmp(__s1,param_3,6);
        if (iVar2 == 0) {
          bVar1 = true;
        }
        __s1 = pcVar3;
      } while (pcVar3 != "Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" +
                         param_1 + iVar5 + uVar4 * 8 + 5);
      if (bVar1) {
        return;
      }
    }
    iVar5 = param_1 + param_2 * 0x5834;
    memmove("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" +
            param_1 + param_2 * 0x5834 + uVar4 * 8 + 5,param_3,6);
    *(int *)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" + iVar5 + 1) =
         *(int *)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" + iVar5 + 1) + 1;
    return;
  }
  if (DebugLevel < 2) {
    return;
  }
  printk("The AccessControlList is full, and no more entry can join the list!\n");
  return;
}

