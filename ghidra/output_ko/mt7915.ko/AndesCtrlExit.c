// module: mt7915.ko
// function: AndesCtrlExit @ 0x1a4c68
// size: 336 bytes
//

void AndesCtrlExit(int param_1)

{
  int iVar1;
  
  iVar1 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar1 != 0) {
    hif_mcu_exit(*(undefined4 *)(param_1 + 0xa797a0));
    AndesBhSchedule(param_1);
    OS_CLEAR_BIT(0,param_1 + 0xa784a0);
    tasklet_kill(param_1 + 0xa784a4);
    AndesCleanupCmdMsg(param_1,param_1 + 0xa784bc);
    AndesCleanupCmdMsg(param_1,param_1 + 0xa784d4);
    AndesCleanupCmdMsg(param_1,param_1 + 0xa784c8);
    AndesCleanupCmdMsg(param_1,param_1 + 0xa784e0);
    AndesCleanupCmdMsg(param_1,param_1 + 0xa784ec);
    AndesCleanupCmdMsg(param_1,param_1 + 0xa784f8);
    if (0 < DebugLevel) {
      printk("tx_kickout_fail_count = %ld\n",*(undefined4 *)(param_1 + 0xa78504));
      if (0 < DebugLevel) {
        printk("tx_timeout_fail_count = %ld\n",*(undefined4 *)(param_1 + 0xa78508));
        if (0 < DebugLevel) {
          printk("rx_receive_fail_count = %ld\n",*(undefined4 *)(param_1 + 0xa7850c));
          if (0 < DebugLevel) {
            printk("alloc_cmd_msg = %ld\n",*(undefined4 *)(param_1 + 0xa78510));
            if (0 < DebugLevel) {
              printk("free_cmd_msg = %ld\n",*(undefined4 *)(param_1 + 0xa78514));
            }
          }
        }
      }
    }
  }
  *(undefined1 *)(param_1 + 0xa78518) = 0;
  *(undefined1 *)(param_1 + 0xa78519) = 0;
  return;
}

