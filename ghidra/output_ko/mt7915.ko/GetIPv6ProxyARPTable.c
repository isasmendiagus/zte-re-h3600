// module: mt7915.ko
// function: GetIPv6ProxyARPTable @ 0x225e54
// size: 164 bytes
//

undefined4
GetIPv6ProxyARPTable(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  int *piVar1;
  void *__dest;
  
  __dest = (void *)*param_3;
  if (0 < DebugLevel) {
    printk(&_LC4,"GetIPv6ProxyARPTable",param_3,DebugLevel,param_4);
  }
  _raw_spin_lock_bh(param_2 + 0x4ca4);
  for (piVar1 = *(int **)(param_2 + 0x4cb0); piVar1 != (int *)(param_2 + 0x4cb0);
      piVar1 = (int *)*piVar1) {
    memmove(__dest,piVar1 + 2,6);
    *(undefined1 *)((int)__dest + 6) = *(undefined1 *)((int)piVar1 + 0xe);
    memmove((void *)((int)__dest + 7),(void *)((int)piVar1 + 0xf),0x10);
    __dest = (void *)((int)__dest + 0x17);
  }
  _raw_spin_unlock_bh(param_2 + 0x4ca4);
  return 1;
}

