// module: mt7915.ko
// function: HcAcquireUcastWcid @ 0xa9f7c
// size: 112 bytes
//

undefined4 HcAcquireUcastWcid(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","HcAcquireUcastWcid",
             *(undefined1 *)(param_2 + 0xc));
    }
    return 0xffff;
  }
  uVar2 = WtcAcquireUcastWcid(*(undefined4 *)(param_1 + 0xa797a0),uVar2,1);
  return uVar2;
}

