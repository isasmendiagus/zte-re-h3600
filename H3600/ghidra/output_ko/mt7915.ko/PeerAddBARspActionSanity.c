// module: mt7915.ko
// function: PeerAddBARspActionSanity @ 0x1109c0
// size: 248 bytes
//

uint PeerAddBARspActionSanity(undefined4 param_1,int param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  
  if (param_3 < 0x21) {
    if (-1 < DebugLevel) {
      printk("%s(): ADDBA Resp frame length incorrect(len=%ld)\n","PeerAddBARspActionSanity");
      return 0;
    }
  }
  else {
    bVar1 = *(byte *)(param_2 + 0x1d);
    uVar2 = (uint)bVar1;
    if ((bVar1 & 2) == 0) {
      if (DebugLevel < 0) {
        return uVar2 & 2;
      }
      printk("%s(): ADDBA Resp Ba Policy[%d] not support\n","PeerAddBARspActionSanity",
             (uVar2 << 0x1e) >> 0x1f);
      return uVar2 & 2;
    }
    uVar2 = (uVar2 << 0x1a) >> 0x1c;
    if (uVar2 < 8) {
      if (*(char *)(param_2 + 0x1e) != '\0' || bVar1 >> 6 != 0) {
        return 1;
      }
      if (DebugLevel < 0) {
        return 0;
      }
      printk("illegal BA buffer size = %d\n");
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("Wrong TID %d!\n",uVar2);
      return 0;
    }
  }
  return 0;
}

