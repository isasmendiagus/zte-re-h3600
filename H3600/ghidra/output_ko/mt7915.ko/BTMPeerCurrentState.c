// module: mt7915.ko
// function: BTMPeerCurrentState @ 0x22847c
// size: 336 bytes
//

undefined4 BTMPeerCurrentState(int param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  
  bVar1 = *param_2;
  uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (bVar1 < uVar2) {
    bVar1 = *param_2;
    pcVar6 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + (uint)bVar1 * 0x5834 + 0x20
    ;
    down_interruptible(pcVar6);
    iVar4 = param_1 + (uint)bVar1 * 0x5834;
    pcVar5 = *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar4 + 0x28);
    if (pcVar5 != "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar4 + 0x28) {
      do {
        iVar3 = memcmp(pcVar5 + 0xd,param_2 + 1,6);
        if (iVar3 == 0) goto LAB_00228520;
        pcVar5 = *(char **)pcVar5;
      } while (pcVar5 != "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar4 + 0x28);
    }
    up(pcVar6);
    if (*param_2 < 2) {
      iVar4 = (uint)*param_2 * 0x2137b0;
      pcVar6 = &DAT_00580dec + param_1 + iVar4;
      down_interruptible(pcVar6);
      pcVar5 = *(char **)(&DAT_00580e28 + param_1 + iVar4);
      if (pcVar5 != &DAT_00580e28 + param_1 + iVar4) {
        do {
          iVar3 = memcmp(pcVar5 + 0xd,param_2 + 1,6);
          if (iVar3 == 0) {
LAB_00228520:
            up(pcVar6);
            return *(undefined4 *)(pcVar5 + 8);
          }
          pcVar5 = *(char **)pcVar5;
        } while (pcVar5 != &DAT_00580e28 + param_1 + iVar4);
      }
      up(pcVar6);
    }
  }
  return 6;
}

