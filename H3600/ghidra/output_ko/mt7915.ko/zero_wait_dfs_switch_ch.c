// module: mt7915.ko
// function: zero_wait_dfs_switch_ch @ 0x22fc4c
// size: 444 bytes
//

undefined4 zero_wait_dfs_switch_ch(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (0 < DebugLevel) {
    printk("%s(): outband ch %d, ch_stat %d\n","zero_wait_dfs_switch_ch",
           *(undefined1 *)(param_1 + 0x7953fb),*(undefined4 *)(param_1 + 0x79540c));
  }
  if ((*(ushort *)(param_2 + 0x18) & 0xb1) != 0) {
    if (*(char *)(param_1 + 0x795404) == '\0') {
      if (2 < DebugLevel) {
        printk("%s(): bDedicatedZeroWaitDefault != 0\n","zero_wait_dfs_switch_ch");
        return 0;
      }
    }
    else {
      iVar2 = *(int *)(param_1 + 0x79540c);
      switch(iVar2) {
      case 0:
      case 5:
        if (*(char *)(param_1 + 0x7953fb) != '\0') {
          if (0 < DebugLevel) {
            printk("%s(): OutBandCh %d, OutBandBw %d\n","zero_wait_dfs_switch_ch",
                   *(char *)(param_1 + 0x7953fb),*(undefined1 *)(param_1 + 0x7953fc));
            iVar2 = *(int *)(param_1 + 0x79540c);
          }
          if (iVar2 == 5) {
            if (DebugLevel < 1) {
              uVar1 = 1000;
            }
            else {
              printk("%s(): Do not switch to DFS ch immediately\n","zero_wait_dfs_switch_ch");
              uVar1 = 1000;
            }
          }
          else {
            uVar1 = 6000;
          }
          RTMPSetTimer(param_1 + 0xa791c4,uVar1);
          return 1;
        }
        return 1;
      case 1:
      case 2:
        if (0 < DebugLevel) {
          printk("%s(): OUTBAND_SWITCH, ch_stat %d\n","zero_wait_dfs_switch_ch");
        }
        *(undefined4 *)(param_1 + 0xa79184) = 2;
        MlmeEnqueue(param_1,0x2b,8,0,0,0);
        RtmpOsMlmeUp(param_1 + 0x286298);
        return 1;
      default:
        if (2 < DebugLevel) {
          printk("%s(): ch_stat %d\n","zero_wait_dfs_switch_ch");
        }
      }
    }
  }
  return 0;
}

