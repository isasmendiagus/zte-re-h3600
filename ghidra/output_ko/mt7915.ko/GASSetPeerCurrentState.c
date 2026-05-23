// module: mt7915.ko
// function: GASSetPeerCurrentState @ 0x22aa40
// size: 152 bytes
//

void GASSetPeerCurrentState(int param_1,byte *param_2,undefined4 param_3)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar3 = (uint)*param_2 * 0x5834;
  _raw_spin_lock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar3 + 0x24);
  pcVar2 = *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar3 + 0x1c);
  if ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar3 + 0x1c != pcVar2) {
    do {
      iVar1 = memcmp(pcVar2 + 0xd,param_2 + 1,6);
      if (iVar1 == 0) {
        *(undefined4 *)(pcVar2 + 8) = param_3;
        break;
      }
      pcVar2 = *(char **)pcVar2;
    } while ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar3 + 0x1c != pcVar2);
  }
  _raw_spin_unlock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar3 + 0x24);
  return;
}

