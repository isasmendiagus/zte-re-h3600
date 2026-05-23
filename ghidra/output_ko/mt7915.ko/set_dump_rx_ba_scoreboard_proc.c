// module: mt7915.ko
// function: set_dump_rx_ba_scoreboard_proc @ 0x27bd8
// size: 112 bytes
//

undefined4 set_dump_rx_ba_scoreboard_proc(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 8);
  do {
    piVar2 = piVar2 + 1;
    iVar1 = *piVar2;
    if ((((iVar1 != 0) && (*(int *)(iVar1 + 0x14) == 2)) && (*(char *)(iVar1 + 0xac4) != -1)) &&
       (-1 < DebugLevel)) {
      printk("wdev idx:%d, wdev_type:%x ,TriggerNum = %d\n",*(undefined1 *)(iVar1 + 0xc),2,
             *(undefined4 *)(iVar1 + 0xad8));
    }
  } while (piVar2 != (int *)(param_1 + 0x1a8));
  return 1;
}

