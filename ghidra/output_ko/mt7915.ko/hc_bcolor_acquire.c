// module: mt7915.ko
// function: hc_bcolor_acquire @ 0xaa844
// size: 136 bytes
//

undefined4 hc_bcolor_acquire(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = *(int *)(param_1 + 0xabc);
  uVar4 = *(undefined4 *)(iVar3 + 0x24);
  iVar2 = hdev_obj_state_ready(iVar3);
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","hc_bcolor_acquire",
             *(undefined1 *)(param_1 + 0xc));
    }
  }
  else {
    cVar1 = bcolor_acquire_entry(uVar4,iVar3);
    if ((byte)(cVar1 - 1U) < 0x3f) {
      *param_2 = cVar1;
      return 1;
    }
  }
  return 0;
}

