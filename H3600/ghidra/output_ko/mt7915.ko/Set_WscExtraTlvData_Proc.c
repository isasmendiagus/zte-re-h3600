// module: mt7915.ko
// function: Set_WscExtraTlvData_Proc @ 0x2c5a0
// size: 476 bytes
//

undefined4 Set_WscExtraTlvData_Proc(int *param_1,byte *param_2)

{
  size_t __n;
  void *__dest;
  byte *pbVar1;
  int iVar2;
  
  __n = strlen((char *)param_2);
  iVar2 = *(int *)(*param_1 + 0x3c);
  if (2 < DebugLevel) {
    printk("Set_WscExtraTlvData_Proc::(DataLen = %d)\n",__n);
  }
  if (__n == 0) {
    if (param_1[iVar2 * 0x160d + 0xaec15] != 0) {
      os_free_mem();
      param_1[iVar2 * 0x160d + 0xaec15] = 0;
    }
  }
  else {
    if ((char)param_1[iVar2 * 0x160d + 0xaec16] == '\x01') {
      if (((&_ctype)[*param_2] & 0x44) != 0) {
        pbVar1 = param_2;
        do {
          pbVar1 = pbVar1 + 1;
          if (pbVar1 == param_2 + __n) goto LAB_0002c600;
        } while (((&_ctype)[*pbVar1] & 0x44) != 0);
      }
      return 0;
    }
LAB_0002c600:
    if (param_1[iVar2 * 0x160d + 0xaec15] != 0) {
      os_free_mem();
      param_1[iVar2 * 0x160d + 0xaec15] = 0;
    }
    *(undefined2 *)((int)param_1 + iVar2 * 0x5834 + 0x2bb052) = 0;
    os_alloc_mem(0,param_1 + iVar2 * 0x160d + 0xaec15,__n);
    __dest = (void *)param_1[iVar2 * 0x160d + 0xaec15];
    if (__dest == (void *)0x0) {
      if (2 < DebugLevel) {
        printk("Set_WscExtraTlvData_Proc::os_alloc_mem fail\n");
        return 0;
      }
      return 0;
    }
    if ((char)param_1[iVar2 * 0x160d + 0xaec16] == '\0') {
      memmove(__dest,param_2,__n);
      *(short *)((int)param_1 + iVar2 * 0x5834 + 0x2bb052) = (short)__n;
      return 1;
    }
    *(short *)((int)param_1 + iVar2 * 0x5834 + 0x2bb052) = (short)(__n >> 1);
    AtoH(param_2,__dest,__n >> 1 & 0xffff);
  }
  return 1;
}

