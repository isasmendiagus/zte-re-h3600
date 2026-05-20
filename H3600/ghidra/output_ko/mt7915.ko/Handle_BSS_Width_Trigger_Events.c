// module: mt7915.ko
// function: Handle_BSS_Width_Trigger_Events @ 0x103374
// size: 224 bytes
//

void Handle_BSS_Width_Trigger_Events(int param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  if (*(char *)(param_1 + 0x79564e) == '\0' || 0xe < param_2) {
    return;
  }
  piVar4 = (int *)(param_1 + 8);
  do {
    while( true ) {
      piVar4 = piVar4 + 1;
      iVar3 = *piVar4;
      if ((((iVar3 != 0) && (*(byte *)(iVar3 + 0x1a) == param_2)) && (*(int *)(iVar3 + 0x14) == 1))
         && (iVar2 = wlan_operate_get_ht_bw(iVar3), iVar2 != 0)) break;
      if (piVar4 == (int *)(param_1 + 0x1a8)) {
        DetectOverlappingPeriodicRound = 0x1f;
        return;
      }
    }
    if (2 < DebugLevel) {
      printk("Rcv BSS Width Trigger Event: 40Mhz --> 20Mhz\n");
    }
    uVar1 = jiffies;
    *(undefined1 *)(param_1 + 0x795949) = 1;
    *(undefined4 *)(param_1 + 0x79594c) = uVar1;
    wlan_operate_set_ht_bw(iVar3,0,0);
  } while (piVar4 != (int *)(param_1 + 0x1a8));
  DetectOverlappingPeriodicRound = 0x1f;
  return;
}

