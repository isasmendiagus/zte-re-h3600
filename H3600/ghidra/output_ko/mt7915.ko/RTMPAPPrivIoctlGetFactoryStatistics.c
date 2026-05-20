// module: mt7915.ko
// function: RTMPAPPrivIoctlGetFactoryStatistics @ 0x15edf8
// size: 260 bytes
//

int RTMPAPPrivIoctlGetFactoryStatistics(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  if (*(ushort *)(param_2 + 0x14) < 0x10) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("GetFactoryStatistics failed  length=%d \n",*(ushort *)(param_2 + 0x14));
    return 1;
  }
  if (iVar2 < 0) {
    iVar2 = iVar2 + 3;
  }
  uVar3 = *(uint *)(param_2 + 0x10);
  uVar1 = *(uint *)(((uint)&stack0xfffffff8 & 0xffffe000) + 8);
  if (uVar3 < 0xfffffff0 && uVar3 + 0x10 <= uVar1) {
    uVar1 = 0;
  }
  g_stWlanFactoryStatistics._4_4_ = param_1[(iVar2 >> 2) * 3 + 0xdb6ce];
  if (uVar1 == 0) {
    iVar2 = __copy_to_user(uVar3,g_stWlanFactoryStatistics,0x10);
    if (iVar2 == 0) {
      return 0;
    }
  }
  else {
    iVar2 = 0x10;
  }
  if (DebugLevel < 0) {
    return iVar2;
  }
  printk("GetFactoryStatistics failed %d\n",iVar2);
  return iVar2;
}

