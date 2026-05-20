// module: mt7915.ko
// function: Set_TxBfAidUpdate @ 0xe91d4
// size: 232 bytes
//

undefined4 Set_TxBfAidUpdate(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Argument is NULL\n","Set_TxBfAidUpdate");
  }
  else {
    uVar1 = os_str_toul(param_2,0,10);
    if (0 < DebugLevel) {
      printk("%s: Aid:%u\n","Set_TxBfAidUpdate",uVar1);
    }
    iVar2 = CmdETxBfAidSetting(param_1,uVar1);
    if (iVar2 == 0) {
      if (DebugLevel < 1) {
        return 1;
      }
      uVar4 = 1;
      pcVar3 = "Success";
      goto LAB_000e9298;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  uVar4 = 0;
  pcVar3 = "Fail";
LAB_000e9298:
  printk("%s: CMD %s\n","Set_TxBfAidUpdate",pcVar3);
  return uVar4;
}

