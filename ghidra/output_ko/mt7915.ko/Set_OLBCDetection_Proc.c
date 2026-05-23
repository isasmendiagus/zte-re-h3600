// module: mt7915.ko
// function: Set_OLBCDetection_Proc @ 0x298b4
// size: 68 bytes
//

undefined4 Set_OLBCDetection_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if ((iVar1 != 0) && (iVar1 != 1)) {
    return 0;
  }
  *(int *)(param_1 + 0x795078) = iVar1;
  return 1;
}

