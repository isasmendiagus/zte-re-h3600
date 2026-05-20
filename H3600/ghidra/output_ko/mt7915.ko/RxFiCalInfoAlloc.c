// module: mt7915.ko
// function: RxFiCalInfoAlloc @ 0x1c8d60
// size: 116 bytes
//

undefined4 RxFiCalInfoAlloc(undefined4 param_1,uint *param_2,undefined4 *param_3)

{
  int iVar1;
  void *local_14 [2];
  
  local_14[0] = (void *)0x0;
  if (((*param_2 & 8) != 0) && (iVar1 = os_alloc_mem(param_1,local_14,0x364), iVar1 == 0)) {
    *param_3 = local_14[0];
    os_zero_mem(local_14[0],0x364);
    os_move_mem(local_14[0],param_2 + 0x2c3,0x364);
    return 0x364;
  }
  return 0;
}

