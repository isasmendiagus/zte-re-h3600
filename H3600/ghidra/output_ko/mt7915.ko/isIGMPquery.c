// module: mt7915.ko
// function: isIGMPquery @ 0x2412ac
// size: 108 bytes
//

undefined4 isIGMPquery(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = isIgmpPkt(param_2,param_3);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(char *)(param_3 + (*(byte *)(param_3 + 2) & 0xf) * 4 + 2) == '\x11') {
    if (DebugLevel < 4) {
      return 1;
    }
    printk("isIGMPquery-> IGMP Type=0x%x IGMP_MEMBERSHIP_QUERY\n");
    return 1;
  }
  return 0;
}

