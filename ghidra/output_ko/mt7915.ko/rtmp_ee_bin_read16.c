// module: mt7915.ko
// function: rtmp_ee_bin_read16 @ 0x1266b0
// size: 120 bytes
//

bool rtmp_ee_bin_read16(int param_1,int param_2,short *param_3)

{
  if (3 < DebugLevel) {
    printk("%s::Read from EEPROM buffer\n","rtmp_ee_bin_read16");
  }
  memmove(param_3,(void *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + param_2),2);
  return 0xfffd < (ushort)(*param_3 - 1U);
}

