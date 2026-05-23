// module: mt7915.ko
// function: hc_get_pe_ctrl @ 0xa8d1c
// size: 84 bytes
//

undefined4 hc_get_pe_ctrl(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xabc);
  iVar1 = hdev_obj_state_ready(iVar3);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): obj is not ready!!\n","hc_get_pe_ctrl");
    }
    return 0;
  }
  uVar2 = rc_get_pe_ctrl(*(undefined4 *)(iVar3 + 8));
  return uVar2;
}

