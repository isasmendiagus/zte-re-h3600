// module: mt7915.ko
// function: WNMNotifyPeerCurrentState @ 0x229c08
// size: 164 bytes
//

undefined4 WNMNotifyPeerCurrentState(int param_1,byte *param_2)

{
  int iVar1;
  char *pcVar2;
  undefined *puVar3;
  int iVar4;
  
  iVar4 = (uint)*param_2 * 0x5834;
  puVar3 = &_LC170 + param_1 + iVar4;
  down_interruptible(puVar3);
  pcVar2 = *(char **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar4 + 4);
  if (pcVar2 != "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar4 + 4) {
    do {
      iVar1 = memcmp(pcVar2 + 0xd,param_2 + 1,6);
      if (iVar1 == 0) {
        up(puVar3);
        return *(undefined4 *)(pcVar2 + 8);
      }
      pcVar2 = *(char **)pcVar2;
    } while (pcVar2 != "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar4 + 4);
  }
  up(puVar3);
  return 2;
}

