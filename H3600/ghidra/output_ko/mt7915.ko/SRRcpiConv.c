// module: mt7915.ko
// function: SRRcpiConv @ 0x1715c4
// size: 84 bytes
//

int SRRcpiConv(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if ((param_1 + 0x6eU & 0xff) < 0x31) {
    return (param_1 + 0x6eU & 0x7f) << 1;
  }
  if (DebugLevel < 0) {
    return 0xc2;
  }
  printk("%s Return default value\n","SRRcpiConv",param_3,DebugLevel,param_4);
  return 0xc2;
}

