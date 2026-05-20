// module: mt7915.ko
// function: HwCtrlAPRecoverEXPAckTime @ 0xaf7d8
// size: 108 bytes
//

undefined4 HwCtrlAPRecoverEXPAckTime(int param_1)

{
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    return 0;
  }
  if (2 < DebugLevel) {
    printk("CmdThread::CMDTHREAD_AP_RECOVER_EXP_ACK_TIME\n");
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1380,0x2400ca);
  return 0;
}

