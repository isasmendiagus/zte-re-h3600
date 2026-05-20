// module: mt7915.ko
// function: BTMStartWaitBTMReqTimer @ 0x227110
// size: 192 bytes
//

void BTMStartWaitBTMReqTimer(int param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  
  bVar1 = *param_2;
  down_interruptible("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" +
                     param_1 + (uint)bVar1 * 0x5834 + 0x20);
  iVar3 = param_1 + (uint)bVar1 * 0x5834;
  pcVar4 = *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar3 + 0x28);
  if (pcVar4 != "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar3 + 0x28) {
    do {
      iVar2 = memcmp(pcVar4 + 0xd,param_2 + 1,6);
      if (iVar2 == 0) {
        RTMPInitTimer(param_1,pcVar4 + 0x4c,rtmp_timer_WaitPeerBTMReqTimeout,pcVar4,0);
        RTMPSetTimer(pcVar4 + 0x4c,30000);
        break;
      }
      pcVar4 = *(char **)pcVar4;
    } while (pcVar4 != "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar3 + 0x28);
  }
  up("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + (uint)bVar1 * 0x5834 + 0x20);
  return;
}

