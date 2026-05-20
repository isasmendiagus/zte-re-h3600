// module: mt7915.ko
// function: Set_WscExtraTlvTag_Proc @ 0x2ad54
// size: 108 bytes
//

undefined4
Set_WscExtraTlvTag_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  
  iVar3 = *param_1;
  uVar2 = os_str_tol(param_2,0,0x10,param_4,param_4);
  iVar1 = DebugLevel;
  *(undefined2 *)(param_1 + *(int *)(iVar3 + 0x3c) * 0x160d + 0xaec14) = uVar2;
  if (2 < iVar1) {
    printk("Set_WscExtraTlvTag_Proc::(new_tag=0x%04X)\n",uVar2);
  }
  return 1;
}

