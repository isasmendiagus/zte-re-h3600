// module: mt7915.ko
// function: AsicUpdateTxOP @ 0x133e90
// size: 244 bytes
//

undefined1 AsicUpdateTxOP(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 != 2) {
    AsicNotSupportFunc(param_1,"AsicUpdateTxOP");
    return 0;
  }
  if (*(char *)(param_1 + 0x795b0e) == '\0') {
    if (*(code **)(iVar1 + 0x9c) == (code *)0x0) {
      if (param_3 == 0) {
        return 1;
      }
    }
    else {
      iVar1 = (**(code **)(iVar1 + 0x9c))(param_1,param_2,0);
      if (iVar1 == param_3) {
        return 1;
      }
      if (iVar1 == -0x21524111) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: Error CR value for TxOP = 0x%08x\n","AsicUpdateTxOP",0xdeadbeef);
        return 0;
      }
    }
    MtAsicSetWmmParam(param_1,0,param_2,0,param_3);
  }
  return 1;
}

