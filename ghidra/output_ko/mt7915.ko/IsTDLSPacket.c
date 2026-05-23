// module: mt7915.ko
// function: IsTDLSPacket @ 0x225c7c
// size: 100 bytes
//

undefined4 IsTDLSPacket(undefined4 param_1,ushort *param_2)

{
  undefined4 uVar1;
  
  if ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x890d) {
    if (DebugLevel < 3) {
      uVar1 = 1;
    }
    else {
      printk("THe Packet is TDLS\n");
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

