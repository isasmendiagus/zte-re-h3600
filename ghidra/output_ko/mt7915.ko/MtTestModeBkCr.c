// module: mt7915.ko
// function: MtTestModeBkCr @ 0x28119c
// size: 320 bytes
//

undefined4 MtTestModeBkCr(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  
  if (4 < param_3 - 1U) {
    return 2;
  }
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0xa3b8c0);
  do {
    if (piVar2[2] == 0) {
      if (2 < DebugLevel) {
        printk("%s: find emptyp bk entry %d\n","MtTestModeBkCr",iVar1,DebugLevel,param_4);
      }
LAB_00281248:
      if (piVar2 == (int *)0x0) {
        return 3;
      }
      piVar2[2] = param_3;
      *piVar2 = param_2;
      switch(param_3) {
      case 2:
        hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0));
        return 0;
      case 3:
        phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0));
        return 0;
      case 4:
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0));
        return 0;
      case 5:
        mcu_io_read32(*(undefined4 *)(param_1 + 0xa797a0));
        return 0;
      default:
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2,piVar2 + 1);
        return 0;
      }
    }
    if ((param_3 == piVar2[2]) && (*piVar2 == param_2)) {
      if (2 < DebugLevel) {
        printk("%s: update bk entry %d\n","MtTestModeBkCr",iVar1,DebugLevel,param_4);
      }
      goto LAB_00281248;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 3;
    if (iVar1 == 0x1e) {
      return 3;
    }
  } while( true );
}

