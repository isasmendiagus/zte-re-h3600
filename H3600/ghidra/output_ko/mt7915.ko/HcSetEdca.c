// module: mt7915.ko
// function: HcSetEdca @ 0xa9818
// size: 84 bytes
//

void HcSetEdca(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 != 0) {
    wmm_ctrl_set_edca(uVar2);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s(): wdev=%d, hobj is not ready!\n","HcSetEdca",*(undefined1 *)(param_1 + 0xc),param_4);
  return;
}

