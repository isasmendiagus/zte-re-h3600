// module: mt7915.ko
// function: Set_BasicRate_Proc @ 0x34254
// size: 132 bytes
//

undefined4 Set_BasicRate_Proc(int *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = os_str_tol(param_2,0,10);
  if (0xfff < uVar1) {
    return 0;
  }
  param_1[0x1e5327] = uVar1;
  param_1[0x1e5328] = uVar1;
  MlmeUpdateTxRates(param_1,0,*(undefined1 *)(iVar2 + 0x3c));
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_BasicRate_Proc::(BasicRateBitmap=0x%08lx)\n",param_1[0x1e5327]);
  return 1;
}

