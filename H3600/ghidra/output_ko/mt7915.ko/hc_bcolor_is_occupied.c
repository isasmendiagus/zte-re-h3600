// module: mt7915.ko
// function: hc_bcolor_is_occupied @ 0xaa9b8
// size: 120 bytes
//

undefined4 hc_bcolor_is_occupied(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *(int *)(param_1 + 0xabc);
  uVar3 = *(undefined4 *)(iVar2 + 0x24);
  iVar1 = hdev_obj_state_ready(iVar2);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","hc_bcolor_is_occupied",
             *(undefined1 *)(param_1 + 0xc));
    }
  }
  else if (param_2 - 1U < 0x3f) {
    uVar3 = bcolor_entry_is_occupied(uVar3,iVar2,param_2,param_4);
    return uVar3;
  }
  return 0;
}

