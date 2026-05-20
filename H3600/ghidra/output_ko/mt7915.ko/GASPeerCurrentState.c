// module: mt7915.ko
// function: GASPeerCurrentState @ 0x22a99c
// size: 164 bytes
//

undefined4 GASPeerCurrentState(int param_1,byte *param_2)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  
  iVar4 = (uint)*param_2 * 0x5834;
  pcVar3 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar4 + 0x24;
  _raw_spin_lock_bh(pcVar3);
  pcVar2 = *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar4 + 0x1c);
  if ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar4 + 0x1c != pcVar2) {
    do {
      iVar1 = memcmp(pcVar2 + 0xd,param_2 + 1,6);
      if (iVar1 == 0) {
        _raw_spin_unlock_bh(pcVar3);
        return *(undefined4 *)(pcVar2 + 8);
      }
      pcVar2 = *(char **)pcVar2;
    } while ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar4 + 0x1c != pcVar2);
  }
  _raw_spin_unlock_bh(pcVar3);
  return 6;
}

