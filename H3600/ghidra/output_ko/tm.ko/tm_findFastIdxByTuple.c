// module: tm.ko
// function: tm_findFastIdxByTuple @ 0x65438
// size: 340 bytes
//

undefined4 tm_findFastIdxByTuple(uint param_1,int *param_2,int *param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == (int *)0x0 || 0x1ff < param_1) {
    printk("[%s] params is NULL or invalid\n","zte_sw_api.c",param_3,param_4,param_4);
    return 0xffffffff;
  }
  iVar1 = *(int *)(g_FastList + param_1 * 4);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  do {
    while (((param_2[1] != 0 || (param_2[2] != 0)) || (param_2[3] != 0))) {
      if (((((*param_2 == *(int *)(iVar1 + 8)) && (param_2[1] == *(int *)(iVar1 + 0xc))) &&
           ((param_2[2] == *(int *)(iVar1 + 0x10) &&
            ((param_2[3] == *(int *)(iVar1 + 0x14) && (param_2[4] == *(int *)(iVar1 + 0x18))))))) &&
          (param_2[5] == *(int *)(iVar1 + 0x1c))) &&
         ((param_2[6] == *(int *)(iVar1 + 0x20) && (param_2[7] == *(int *)(iVar1 + 0x24))))) {
LAB_00065520:
        if ((param_2[8] == *(int *)(iVar1 + 0x28)) && ((char)param_2[9] == *(char *)(iVar1 + 0x2c)))
        {
          *param_3 = iVar1;
          return 0;
        }
      }
LAB_00065490:
      iVar1 = *(int *)(iVar1 + 0x48);
      if (iVar1 == 0) {
        return 0xffffffff;
      }
    }
    if (*param_2 != *(int *)(iVar1 + 8)) goto LAB_00065490;
    if (param_2[4] == *(int *)(iVar1 + 0x18)) goto LAB_00065520;
    iVar1 = *(int *)(iVar1 + 0x48);
    if (iVar1 == 0) {
      return 0xffffffff;
    }
  } while( true );
}

