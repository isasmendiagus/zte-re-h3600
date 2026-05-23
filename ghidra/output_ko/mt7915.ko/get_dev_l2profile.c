// module: mt7915.ko
// function: get_dev_l2profile @ 0x14f0b4
// size: 180 bytes
//

char * get_dev_l2profile(int param_1)

{
  char *pcVar1;
  int iVar2;
  
  if (1 < *(byte *)(param_1 + 0x286285)) {
    return (char *)0x0;
  }
  iVar2 = *(int *)(param_1 + 0x286280);
  if (iVar2 != 4) {
    if ((iVar2 != 6) && (iVar2 != 2)) {
      if (*(char *)(param_1 + 0x286285) != '\x01') {
        pcVar1 = "/etc/Wireless/RT2860STA/RT2860STA.dat";
        if (*(char *)(param_1 + 0x286285) != '\0') {
          pcVar1 = (char *)0x0;
        }
        return pcVar1;
      }
      return "/etc/Wireless/RT2860AP/RT2860AP.dat";
    }
    if (*(char *)(param_1 + 0x286285) != '\x01') {
      pcVar1 = "/etc/Wireless/RT2870STA/RT2870STA.dat";
      if (*(char *)(param_1 + 0x286285) != '\0') {
        pcVar1 = (char *)0x0;
      }
      return pcVar1;
    }
    return "/etc/Wireless/RT2870AP/RT2870AP.dat";
  }
  pcVar1 = "/etc/Wireless/RT2860/RT2860.dat";
  if (1 < *(byte *)(param_1 + 0x286285)) {
    pcVar1 = (char *)0x0;
  }
  return pcVar1;
}

