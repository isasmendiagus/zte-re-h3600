// module: mt7915.ko
// function: HcGetEdca @ 0xa9de0
// size: 124 bytes
//

int HcGetEdca(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *(int *)(param_2 + 0xabc);
  uVar3 = *(undefined4 *)(param_1 + 0xa797a0);
  iVar1 = hdev_obj_state_ready(iVar2);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","HcGetEdca",*(undefined1 *)(param_2 + 0xc),
             DebugLevel,param_4);
      return 0;
    }
  }
  else {
    iVar1 = wmm_ctrl_get_entry_by_idx(uVar3,*(undefined1 *)(iVar2 + 5));
    if (iVar1 != 0) {
      return iVar1 + 4;
    }
  }
  return 0;
}

