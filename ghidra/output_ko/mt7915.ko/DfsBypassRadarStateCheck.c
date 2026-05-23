// module: mt7915.ko
// function: DfsBypassRadarStateCheck @ 0x231c2c
// size: 124 bytes
//

bool DfsBypassRadarStateCheck(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = *(int *)(param_1 + 0x3fe4);
    if (iVar2 != 0) {
      iVar1 = hdev_obj_state_ready(*(undefined4 *)(param_1 + 0xabc));
      if (iVar1 != 0) {
        return *(char *)(iVar2 + 4) == '\0';
      }
      if (-1 < DebugLevel) {
        printk("%s(): wdev=%d, hobj is not ready!\n","DfsBypassRadarStateCheck",
               *(undefined1 *)(param_1 + 0xc));
      }
    }
  }
  return false;
}

