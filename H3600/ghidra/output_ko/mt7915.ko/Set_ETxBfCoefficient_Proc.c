// module: mt7915.ko
// function: Set_ETxBfCoefficient_Proc @ 0xe5368
// size: 160 bytes
//

undefined4
Set_ETxBfCoefficient_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 == 2) {
    if (0 < DebugLevel) {
      printk("%s(): Not support for HIF_MT yet!\n","Set_ETxBfCoefficient_Proc");
      return 0;
    }
  }
  else {
    if (uVar1 < 4) {
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("Set_ETxBfCoefficient_Proc: value > 3!\n");
      return 0;
    }
  }
  return 0;
}

