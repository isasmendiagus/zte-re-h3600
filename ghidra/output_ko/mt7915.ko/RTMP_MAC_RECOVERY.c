// module: mt7915.ko
// function: RTMP_MAC_RECOVERY @ 0xb1314
// size: 292 bytes
//

void RTMP_MAC_RECOVERY(int param_1,uint param_2)

{
  uint uVar1;
  uint unaff_r6;
  
  uVar1 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar1 == 0x7915 ||
      (uVar1 == 0x7626 || (uVar1 == 0x6867 || (uVar1 == 0x6632 || uVar1 == 0x7663)))) {
    unaff_r6 = param_2 & 0x3c;
  }
  if (uVar1 != 0x7915 &&
      (uVar1 != 0x7626 && (uVar1 != 0x6867 && (uVar1 != 0x6632 && uVar1 != 0x7663)))) {
    unaff_r6 = 0;
  }
  if (*(int *)(param_1 + 0x285d2c) != 2) {
    if (-1 < DebugLevel) {
      printk("%s::ERR! SER func not ready(%d)\n","RTMP_MAC_RECOVERY");
      return;
    }
    return;
  }
  if (*(uint *)(param_1 + 0x285d30) != unaff_r6) {
    if (-1 < DebugLevel) {
      printk("%s::Status(0x%x)\n","RTMP_MAC_RECOVERY",param_2);
    }
    *(uint *)(param_1 + 0x285d30) = unaff_r6;
    RtmpOsCmdUp(param_1 + 0x285cfc);
    return;
  }
  if (-1 < DebugLevel) {
    printk("%s::ERR! prev state=%x, new stat=%x\n","RTMP_MAC_RECOVERY",unaff_r6,unaff_r6);
    return;
  }
  return;
}

