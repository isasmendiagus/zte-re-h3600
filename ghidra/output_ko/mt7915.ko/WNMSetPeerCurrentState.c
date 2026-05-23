// module: mt7915.ko
// function: WNMSetPeerCurrentState @ 0x229850
// size: 152 bytes
//

void WNMSetPeerCurrentState(int param_1,byte *param_2,undefined4 param_3)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar3 = (uint)*param_2 * 0x5834;
  down_interruptible(&_LC170 + param_1 + iVar3);
  pcVar2 = *(char **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar3 + 4);
  if (pcVar2 != "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar3 + 4) {
    do {
      iVar1 = memcmp(pcVar2 + 0xd,param_2 + 1,6);
      if (iVar1 == 0) {
        *(undefined4 *)(pcVar2 + 8) = param_3;
        break;
      }
      pcVar2 = *(char **)pcVar2;
    } while (pcVar2 != "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar3 + 4);
  }
  up(&_LC170 + param_1 + iVar3);
  return;
}

