// module: mt7915.ko
// function: Set_WscFragmentSize_Proc @ 0x2ac68
// size: 120 bytes
//

undefined4 Set_WscFragmentSize_Proc(int *param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = os_str_tol(param_2,0,10);
  if (2 < DebugLevel) {
    printk("Set_WscFragmentSize_Proc::(WscFragSize=%d)\n",(uint)uVar1);
  }
  if (uVar1 - 0x80 < 0xad) {
    *(ushort *)(param_1 + *(int *)(iVar2 + 0x3c) * 0x160d + 0xaec46) = uVar1;
  }
  return 1;
}

