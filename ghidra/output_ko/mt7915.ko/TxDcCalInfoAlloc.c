// module: mt7915.ko
// function: TxDcCalInfoAlloc @ 0x1c8cf4
// size: 108 bytes
//

undefined4 TxDcCalInfoAlloc(undefined4 param_1,uint *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  void *local_14 [2];
  
  if ((*param_2 & 4) != 0) {
    iVar1 = os_alloc_mem(param_1,local_14,0x514);
    if (iVar1 == 0) {
      *param_3 = local_14[0];
      os_zero_mem(local_14[0],0x514);
      os_move_mem(local_14[0],param_2 + 0x17e,0x514);
      uVar2 = 0x514;
    }
    else {
      uVar2 = 0;
    }
    return uVar2;
  }
  return 0;
}

