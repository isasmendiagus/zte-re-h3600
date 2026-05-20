// module: mt7915.ko
// function: Set_IgmpSn_TabDisplay_Proc @ 0x241cfc
// size: 420 bytes
//

undefined4 Set_IgmpSn_TabDisplay_Proc(int param_1)

{
  char *pcVar1;
  int *piVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  
  pcVar3 = *(char **)(param_1 + 0xa77bc4);
  if (pcVar3 == (char *)0x0) {
    if (0 < DebugLevel) {
      printk("%s Multicase filter table is not ready.\n","IGMPTableDisplay");
    }
  }
  else {
    if (*pcVar3 != '\0') {
      pcVar5 = pcVar3 + 0xc04;
      iVar4 = 0;
      _raw_spin_lock_bh(pcVar5);
      do {
        if (pcVar3[0x204] == '\x01') {
          if (0 < DebugLevel) {
            pcVar1 = "dynamic";
            if (*(int *)(pcVar3 + 0x208) == 0) {
              pcVar1 = "static";
            }
            printk("IF(%s) entry #%d, type=%s, GrpId=(%02x:%02x:%02x:%02x:%02x:%02x) memberCnt=%d\n"
                   ,*(undefined4 *)(pcVar3 + 0x210),iVar4,pcVar1,pcVar3[0x214],pcVar3[0x215],
                   pcVar3[0x216],pcVar3[0x217],pcVar3[0x218],pcVar3[0x219],pcVar3[0x224]);
          }
          for (piVar2 = *(int **)(pcVar3 + 0x21c); piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
            if (0 < DebugLevel) {
              printk("member mac=(%02x:%02x:%02x:%02x:%02x:%02x)\n",*(undefined1 *)(piVar2 + 1),
                     *(undefined1 *)((int)piVar2 + 5),*(undefined1 *)((int)piVar2 + 6),
                     *(undefined1 *)((int)piVar2 + 7),*(undefined1 *)(piVar2 + 2),
                     *(undefined1 *)((int)piVar2 + 9));
            }
          }
        }
        iVar4 = iVar4 + 1;
        pcVar3 = pcVar3 + 0x28;
      } while (iVar4 != 0x40);
      _raw_spin_unlock_bh(pcVar5);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("Table empty.\n");
    }
  }
  return 1;
}

