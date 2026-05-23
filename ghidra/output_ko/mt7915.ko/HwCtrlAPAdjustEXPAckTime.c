// module: mt7915.ko
// function: HwCtrlAPAdjustEXPAckTime @ 0xaf844
// size: 108 bytes
//

undefined4 HwCtrlAPAdjustEXPAckTime(int param_1)

{
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    return 0;
  }
  if (2 < DebugLevel) {
    printk("CmdThread::CMDTHREAD_AP_ADJUST_EXP_ACK_TIME\n");
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1380,&DAT_005400ca);
  return 0;
}

