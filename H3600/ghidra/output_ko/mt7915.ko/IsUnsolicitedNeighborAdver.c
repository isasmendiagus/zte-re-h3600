// module: mt7915.ko
// function: IsUnsolicitedNeighborAdver @ 0x225304
// size: 180 bytes
//

undefined4 IsUnsolicitedNeighborAdver(undefined4 param_1,ushort *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  local_20 = 0x2ff;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0x1000000;
  if (((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x86dd) &&
     (iVar2 = memcmp(param_2 + 0xd,&local_20,0x10), iVar2 == 0)) {
    uVar1 = 0;
    if (((char)param_2[0x15] == -0x78) && ((param_2[0x17] & 0x40) == 0)) {
      if (DebugLevel < 1) {
        uVar1 = 1;
      }
      else {
        printk("The Packet is UnsolicitedNeighborAdver\n");
        uVar1 = 1;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

