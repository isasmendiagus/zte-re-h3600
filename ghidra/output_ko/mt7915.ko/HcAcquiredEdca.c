// module: mt7915.ko
// function: HcAcquiredEdca @ 0xa974c
// size: 112 bytes
//

bool HcAcquiredEdca(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","HcAcquiredEdca",*(undefined1 *)(param_2 + 0xc),
             DebugLevel,param_4);
    }
    return false;
  }
  iVar1 = wmm_ctrl_acquire_entry(uVar2,param_3);
  return iVar1 != 0;
}

