// module: mt7915.ko
// function: MtPwrLimitLoadParamHandle @ 0x152058
// size: 388 bytes
//

undefined4 MtPwrLimitLoadParamHandle(int param_1,int param_2)

{
  int iVar1;
  int local_18;
  int local_14;
  
  local_14 = 0;
  MtPwrGetPwrLimitInstance();
  if (local_14 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: null pointer for link list!!\n","MtPwrLimitLoadParamHandle");
  }
  else {
    *(int *)local_14 = local_14;
    *(int *)(local_14 + 4) = local_14;
    os_alloc_mem(param_1,&local_18,42000);
    if (local_18 == 0) {
      return 1;
    }
    iVar1 = MtReadPwrLimitTable(param_1,local_18,param_2);
    if (iVar1 == 0) {
      iVar1 = MtParsePwrLimitTable(param_1,local_18,param_2);
      if (iVar1 == 0) {
        *(undefined1 *)(param_1 + param_2 + 0xa7863c) = 1;
        iVar1 = MtShowPwrLimitTable(param_1,param_2,4);
        if (iVar1 == 0) {
          os_free_mem(local_18);
          return 0;
        }
        if (-1 < DebugLevel) {
          printk("%s: Show Power Table Error!!\n","MtPwrLimitLoadParamHandle");
        }
      }
      else if (-1 < DebugLevel) {
        printk("%s: Parse Power Table Error!!\n","MtPwrLimitLoadParamHandle");
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: Read Power Table Error!!\n","MtPwrLimitLoadParamHandle");
    }
    os_free_mem(local_18);
  }
  return 1;
}

