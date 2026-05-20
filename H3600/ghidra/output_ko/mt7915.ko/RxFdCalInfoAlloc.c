// module: mt7915.ko
// function: RxFdCalInfoAlloc @ 0x1c8dd4
// size: 132 bytes
//

undefined4 RxFdCalInfoAlloc(undefined4 param_1,uint *param_2,undefined4 *param_3,int param_4)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  void *local_1c [2];
  
  uVar1 = 1 << (param_4 + 4U & 0xff);
  if ((uVar1 == (*param_2 & uVar1)) && (iVar3 = os_alloc_mem(param_1,local_1c,0x548), iVar3 == 0)) {
    uVar2 = 0x548;
    *param_3 = local_1c[0];
    os_zero_mem();
    *(int *)((int)local_1c[0] + 4) = param_4;
    os_move_mem(local_1c[0],param_2 + param_4 * 0x152 + 0x39c,0x548);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

