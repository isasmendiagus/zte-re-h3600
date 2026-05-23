// module: mt7915.ko
// function: RlmPorCalInfoAlloc @ 0x1c8e58
// size: 84 bytes
//

undefined4 RlmPorCalInfoAlloc(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *local_14 [2];
  
  local_14[0] = (undefined1 *)0x0;
  iVar1 = os_alloc_mem(param_1,local_14,4);
  if (iVar1 == 0) {
    *param_3 = local_14[0];
    os_zero_mem(local_14[0],4);
    uVar2 = 4;
    *local_14[0] = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

