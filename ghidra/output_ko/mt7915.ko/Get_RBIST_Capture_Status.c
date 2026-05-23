// module: mt7915.ko
// function: Get_RBIST_Capture_Status @ 0xeb094
// size: 200 bytes
//

undefined4 Get_RBIST_Capture_Status(int param_1,undefined4 param_2)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = simple_strtol(param_2,0,10);
  if (iVar1 == 0) {
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    pcVar2 = *(code **)(iVar1 + 0x18c);
  }
  else {
    if (iVar1 != 1) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Not support for %d this selection !!\n","Get_RBIST_Capture_Status");
      return 1;
    }
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    pcVar2 = *(code **)(iVar1 + 0x1a4);
  }
  if (pcVar2 == (code *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s : The function is not hooked !!\n","Get_RBIST_Capture_Status");
    }
    return 1;
  }
  (*pcVar2)(param_1);
  return 1;
}

