// module: mt7915.ko
// function: RT_CfgSetShortSlot @ 0xb881c
// size: 72 bytes
//

undefined4 RT_CfgSetShortSlot(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if ((iVar1 != 1) && (iVar1 != 0)) {
    return 0;
  }
  *(char *)(param_1 + 0x795070) = (char)iVar1;
  return 1;
}

