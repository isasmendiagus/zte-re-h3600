// module: mt7915.ko
// function: sys_ad_alloc_mem @ 0x25ea88
// size: 40 bytes
//

undefined4 sys_ad_alloc_mem(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = __kmalloc(param_2,0x20);
  *param_1 = iVar1;
  if (iVar1 == 0) {
    uVar2 = 0x700;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

