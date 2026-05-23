// module: mt7915.ko
// function: MulticastFilterTableLookup @ 0x24071c
// size: 548 bytes
//

char * MulticastFilterTableLookup(char *param_1,byte *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  uint uVar6;
  
  if (param_1 == (char *)0x0) {
    pcVar4 = (char *)0x0;
    if (2 < DebugLevel) {
      printk("%s Multicase filter table is not ready.\n","MulticastFilterTableLookup");
    }
  }
  else {
    _raw_spin_lock_bh(param_1 + 0xc04);
    uVar6 = (byte)(param_2[1] ^ *param_2 ^ param_2[2] ^ param_2[3] ^ param_2[4] ^ param_2[5]) & 0x7f
    ;
    pcVar5 = *(char **)(param_1 + uVar6 * 4 + 4);
    if (pcVar5 == (char *)0x0) {
LAB_002408a4:
      pcVar4 = (char *)0x0;
    }
    else {
      cVar1 = *pcVar5;
      pcVar4 = pcVar5;
      while (cVar1 != '\0') {
        if ((param_3 == *(int *)(pcVar4 + 0xc)) &&
           (iVar2 = memcmp(pcVar4 + 0x10,param_2,6), iVar2 == 0)) {
          *(int *)(pcVar4 + 8) = jiffies;
          break;
        }
        if (((cVar1 == '\x01') && (*(int *)(pcVar4 + 4) == 1)) &&
           ((*(int *)(pcVar4 + 8) + 12000) - jiffies < 0)) {
          if (pcVar4 == *(char **)(param_1 + uVar6 * 4 + 4)) {
            pcVar3 = *(char **)(pcVar4 + 0x24);
            *(char **)(param_1 + uVar6 * 4 + 4) = pcVar3;
            FUN_0023ff78(param_1,pcVar4 + 0x18);
            __memzero(pcVar4,0x28);
            *param_1 = *param_1 + -1;
            pcVar5 = pcVar3;
            if (2 < DebugLevel) {
              printk("MCastFilterTableDeleteEntry 2 - Total= %d\n");
            }
          }
          else {
            *(undefined4 *)(pcVar5 + 0x24) = *(undefined4 *)(pcVar4 + 0x24);
            FUN_0023ff78(param_1,pcVar4 + 0x18);
            __memzero(pcVar4,0x28);
            *param_1 = *param_1 + -1;
            pcVar3 = *(char **)(pcVar5 + 0x24);
            if (2 < DebugLevel) {
              printk("MCastFilterTableDeleteEntry 2 - Total= %d\n");
            }
          }
        }
        else {
          pcVar3 = *(char **)(pcVar4 + 0x24);
          pcVar5 = pcVar4;
        }
        if (pcVar3 == (char *)0x0) goto LAB_002408a4;
        pcVar4 = pcVar3;
        cVar1 = *pcVar3;
      }
    }
    _raw_spin_unlock_bh(param_1 + 0xc04);
  }
  return pcVar4;
}

