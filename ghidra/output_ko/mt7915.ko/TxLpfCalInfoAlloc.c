// module: mt7915.ko
// function: TxLpfCalInfoAlloc @ 0x1c8c24
// size: 104 bytes
//

undefined4 TxLpfCalInfoAlloc(undefined4 param_1,uint *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  void *local_14 [2];
  
  if ((*param_2 & 1) != 0) {
    iVar1 = os_alloc_mem(param_1,local_14,0xe0);
    if (iVar1 == 0) {
      *param_3 = local_14[0];
      os_zero_mem(local_14[0],0xe0);
      os_move_mem(local_14[0],param_2 + 1,0xe0);
      uVar2 = 0xe0;
    }
    else {
      uVar2 = 0;
    }
    return uVar2;
  }
  return 0;
}

