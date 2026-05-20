// module: mt7915.ko
// function: HcReleaseEdca @ 0xa97c0
// size: 84 bytes
//

void HcReleaseEdca(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 != 0) {
    wmm_ctrl_release_entry(uVar2);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s(): wdev=%d, hobj is not ready!\n","HcReleaseEdca",*(undefined1 *)(param_2 + 0xc),
         param_4);
  return;
}

