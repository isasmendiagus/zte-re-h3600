// module: mt7915.ko
// function: rtmp_ee_bin_write16 @ 0x126728
// size: 92 bytes
//

undefined4 rtmp_ee_bin_write16(int param_1,int param_2,undefined2 param_3)

{
  if (3 < DebugLevel) {
    printk("%s::Write to EEPROM buffer\n","rtmp_ee_bin_write16");
  }
  *(undefined2 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + param_2) = param_3;
  return 0;
}

