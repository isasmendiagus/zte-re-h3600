// module: mt7915.ko
// function: Set_WscConfMode_Proc @ 0x59f90
// size: 236 bytes
//

undefined4 Set_WscConfMode_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,10);
  iVar2 = 0;
  if ((iVar1 == 0) || (iVar1 = os_str_tol(param_2,0,10), iVar2 = 1, iVar1 == 1)) {
    param_1[iVar3 * 0x84dec + 0xdbb8f] = iVar2;
  }
  else {
    iVar2 = os_str_tol(param_2,0,10);
    if (iVar2 == 2) {
      iVar2 = 4;
    }
    else {
      iVar2 = 0;
    }
    param_1[iVar3 * 0x84dec + 0xdbb8f] = iVar2;
  }
  if (2 < DebugLevel) {
    printk("IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n",
           param_1[iVar3 * 0x84dec + 0xdbb8f]);
  }
  return 1;
}

