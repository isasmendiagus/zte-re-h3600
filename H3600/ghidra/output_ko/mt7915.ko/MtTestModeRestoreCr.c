// module: mt7915.ko
// function: MtTestModeRestoreCr @ 0x2812f0
// size: 348 bytes
//

undefined4 MtTestModeRestoreCr(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0xa3b8c0);
  while (*piVar2 != param_2) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 3;
    if (iVar1 == 0x1e) {
      return 2;
    }
  }
  if (2 < DebugLevel) {
    printk("%s: find entry %d\n","MtTestModeRestoreCr",iVar1,DebugLevel,param_4);
  }
  if (piVar2 == (int *)0x0) {
    return 2;
  }
  switch(piVar2[2]) {
  case 1:
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2,piVar2[1]);
    return 0;
  case 2:
    hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2,piVar2[1]);
    return 0;
  case 3:
    phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2,piVar2[1]);
    return 0;
  case 4:
    hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2,piVar2[1]);
    return 0;
  case 5:
    mcu_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2,piVar2[1]);
    return 0;
  }
  if (1 < DebugLevel) {
    printk("%s: bk-type not supported\n","MtTestModeRestoreCr");
  }
  piVar2[2] = 0;
  *piVar2 = 0;
  return 0;
}

