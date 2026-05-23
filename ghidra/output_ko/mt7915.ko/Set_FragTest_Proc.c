// module: mt7915.ko
// function: Set_FragTest_Proc @ 0x57e08
// size: 124 bytes
//

undefined4 Set_FragTest_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
  if (iVar1 != 0) {
    *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0x16036b) = 1;
    return 1;
  }
  *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0x16036b) = 0;
  return 1;
}

