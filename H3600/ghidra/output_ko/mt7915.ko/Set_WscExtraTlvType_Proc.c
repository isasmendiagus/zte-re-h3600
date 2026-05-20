// module: mt7915.ko
// function: Set_WscExtraTlvType_Proc @ 0x2adc0
// size: 108 bytes
//

undefined4
Set_WscExtraTlvType_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = *param_1;
  uVar2 = os_str_tol(param_2,0,10,param_4,param_4);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + *(int *)(iVar3 + 0x3c) * 0x160d + 0xaec16) = uVar2;
  if (2 < iVar1) {
    printk("Set_WscExtraTlvType_Proc::(type=%d)\n",uVar2);
  }
  return 1;
}

