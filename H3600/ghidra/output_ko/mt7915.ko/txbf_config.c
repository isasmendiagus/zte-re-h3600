// module: mt7915.ko
// function: txbf_config @ 0x88aa4
// size: 244 bytes
//

bool txbf_config(undefined4 param_1,int param_2,char *param_3)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  
  if (1 < DebugLevel) {
    printk("%s: config_type=%d\n","txbf_config",param_2);
  }
  iVar2 = DebugLevel;
  if (param_2 == 0) {
    sVar1 = strlen(param_3);
    iVar3 = 0;
    if (sVar1 < 7) {
      do {
        if (1 < iVar2) {
          printk("%s: config_para[%d]=%d\n","txbf_config",iVar3,param_3[iVar3]);
        }
        iVar3 = iVar3 + 1;
        iVar2 = DebugLevel;
      } while (iVar3 != 6);
      iVar2 = cmd_txbf_config(param_1,0,param_3);
      return iVar2 == 0;
    }
    if (0 < iVar2) {
      printk("%s: Wrong Tx BF Config parameter number (> 6)!\n","txbf_config");
      return false;
    }
  }
  else if (0 < DebugLevel) {
    printk("%s: Wrong Tx BF Config Type: config_type=%d > %d\n","txbf_config",param_2,1);
  }
  return false;
}

