// module: mt7915.ko
// function: PeerAddBAReqActionSanity @ 0x1108b4
// size: 268 bytes
//

uint PeerAddBAReqActionSanity(undefined4 param_1,int param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_3 < 0x21) {
    if (-1 < DebugLevel) {
      printk("PeerAddBAReqActionSanity: ADDBA Request frame length size = %ld incorrect\n",param_3);
      return 0;
    }
  }
  else {
    bVar1 = *(byte *)(param_2 + 0x1b);
    uVar2 = (uint)bVar1;
    if ((bVar1 & 2) == 0) {
      if (DebugLevel < 0) {
        return uVar2 & 2;
      }
      printk("PeerAddBAReqActionSanity: ADDBA Request Ba Policy[%d] not support\n",
             (uVar2 << 0x1e) >> 0x1f);
      return uVar2 & 2;
    }
    uVar3 = (uVar2 << 0x1a) >> 0x1c;
    if (uVar3 < 8) {
      if (2 < DebugLevel) {
        printk("ADDBA Request: Start Seq = %08x, wsize = %d, TID = %d, AMSDU = %x\n",
               (uint)*(byte *)(param_2 + 0x20) << 4 | (uint)(*(byte *)(param_2 + 0x1f) >> 4),
               (uint)*(byte *)(param_2 + 0x1c) << 2 | (uint)(bVar1 >> 6),uVar3,uVar2 & 1);
        return 1;
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("Wrong TID %d!\n",uVar3);
      return 0;
    }
  }
  return 0;
}

