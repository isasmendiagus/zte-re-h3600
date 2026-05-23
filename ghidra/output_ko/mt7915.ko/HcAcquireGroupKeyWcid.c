// module: mt7915.ko
// function: HcAcquireGroupKeyWcid @ 0xa9ed0
// size: 116 bytes
//

undefined4 HcAcquireGroupKeyWcid(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 != 0) {
    uVar2 = WtcAcquireGroupKeyWcid(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
    *(short *)(param_2 + 0x10) = (short)uVar2;
    return uVar2;
  }
  if (DebugLevel < 0) {
    return 0xffff;
  }
  printk("%s(): wdev=%d, hobj is not ready!\n","HcAcquireGroupKeyWcid",
         *(undefined1 *)(param_2 + 0xc));
  return 0xffff;
}

