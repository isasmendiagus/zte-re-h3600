// module: mt7915.ko
// function: MlmeAddBAReqSanity @ 0x110600
// size: 184 bytes
//

undefined4 MlmeAddBAReqSanity(undefined4 param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  
  if (param_3 == 0x12) {
    uVar1 = *param_2;
    uVar2 = HcGetMaxStaNum();
    if (uVar1 < uVar2) {
      if ((param_2[1] & 1) == 0) {
        return 1;
      }
      if (2 < DebugLevel) {
        printk("MlmeAddBAReqSanity fail - multicast address not support BA\n");
        return 0;
      }
    }
    else if (2 < DebugLevel) {
      printk("MlmeAddBAReqSanity fail - The peer Mac is not associated yet.\n");
      return 0;
    }
  }
  else if (2 < DebugLevel) {
    printk("MlmeAddBAReqSanity fail - message lenght not correct.\n");
  }
  return 0;
}

