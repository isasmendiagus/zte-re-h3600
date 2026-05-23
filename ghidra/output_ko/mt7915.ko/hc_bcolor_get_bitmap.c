// module: mt7915.ko
// function: hc_bcolor_get_bitmap @ 0xaaa9c
// size: 100 bytes
//

void hc_bcolor_get_bitmap(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *(int *)(param_1 + 0xabc);
  uVar3 = *(undefined4 *)(iVar2 + 0x24);
  iVar1 = hdev_obj_state_ready(iVar2);
  if (iVar1 != 0) {
    bcolor_get_bitmap(uVar3,iVar2,param_2,param_4);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s(): wdev=%d, hobj is not ready!\n","hc_bcolor_get_bitmap",*(undefined1 *)(param_1 + 0xc)
         ,param_4);
  return;
}

