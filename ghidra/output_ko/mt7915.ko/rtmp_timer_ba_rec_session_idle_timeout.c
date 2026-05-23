// module: mt7915.ko
// function: rtmp_timer_ba_rec_session_idle_timeout @ 0xa4b88
// size: 152 bytes
//

void rtmp_timer_ba_rec_session_idle_timeout(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = jiffies;
  iVar3 = *(int *)(param_1 + 0x24);
  if ((iVar3 != 0) && (*(int *)(iVar3 + 8) == 4)) {
    if ((*(int *)(iVar3 + 0x18) - jiffies) + 1000 < 0) {
      FUN_000a4598(*(int *)(iVar3 + 0x44),*(int *)(iVar3 + 0x44) + 0x1c0,iVar3);
      iVar1 = DebugLevel;
      *(undefined4 *)(iVar3 + 8) = 3;
      if (0 < iVar1) {
        printk("%ld: REC BA session Timeout\n",iVar2);
      }
    }
  }
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

