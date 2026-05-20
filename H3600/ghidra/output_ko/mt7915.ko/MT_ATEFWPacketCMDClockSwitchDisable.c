// module: mt7915.ko
// function: MT_ATEFWPacketCMDClockSwitchDisable @ 0x27d470
// size: 72 bytes
//

void MT_ATEFWPacketCMDClockSwitchDisable(undefined4 param_1,undefined4 param_2)

{
  if (2 < DebugLevel) {
    printk("%s: isDsiable=%d\n","MT_ATEFWPacketCMDClockSwitchDisable",param_2);
  }
  MtCmdClockSwitchDisable(param_1,param_2);
  return;
}

