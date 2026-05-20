// module: mt7915.ko
// function: driver_own @ 0x1781a0
// size: 148 bytes
//

int driver_own(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_r2;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(iVar1 + 0xa4);
  if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
    iVar2 = FUN_00177ffc(param_1,0);
    if (iVar2 != 0) {
      return iVar2;
    }
    if (iVar1 != 0) {
      iVar1 = FUN_00177ffc(param_1,1,extraout_r2,param_4);
      return iVar1;
    }
    if (0 < DebugLevel) {
      printk("%s: port=1 is not enabled\n","driver_own");
      return 0;
    }
  }
  return 0;
}

