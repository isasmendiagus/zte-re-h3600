// module: mt7915.ko
// function: eFuseGetFreeBlockCount @ 0x1d331c
// size: 588 bytes
//

void eFuseGetFreeBlockCount(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort local_22;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  *param_2 = 0;
  if (*(code **)(iVar1 + 0xdc) != (code *)0x0) {
    iVar1 = (**(code **)(iVar1 + 0xdc))(param_1);
    *param_2 = iVar1;
LAB_001d3364:
    if (2 < DebugLevel) {
      printk("eFuseGetFreeBlockCount is %d\n",*param_2);
    }
    return;
  }
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar4 = (uint)*(ushort *)(iVar1 + 0xe6);
  uVar3 = (uint)*(ushort *)(iVar1 + 0xe8);
  if ((*(ushort *)(iVar1 + 0xe6) & 1) != 0) {
    uVar4 = uVar4 - 1 & 0xffff;
  }
  uVar2 = uVar4;
  if ((*(ushort *)(iVar1 + 0xe8) & 1) != 0) {
    uVar3 = uVar3 - 1 & 0xffff;
  }
  for (; uVar2 <= uVar3; uVar2 = uVar2 + 2 & 0xffff) {
    EfusePhysicalReadRegisters(param_1,uVar2,2,&local_22);
    if (((local_22 & 0xff) == 0) && (uVar2 != *(ushort *)(iVar1 + 0xe6) - 1)) {
      if (2 < DebugLevel) {
        printk("eFuseGetFreeBlockCount, FirstFreeBlock= 0x%x\n",uVar2);
      }
      goto LAB_001d343c;
    }
    if ((local_22 >> 8 == 0) && (*(ushort *)(iVar1 + 0xe8) != uVar2)) {
      uVar2 = uVar2 + 1 & 0xffff;
      if (2 < DebugLevel) {
        printk("eFuseGetFreeBlockCount, FirstFreeBlock= 0x%x\n",uVar2);
      }
      if (uVar2 == 0xffff) goto LAB_001d3418;
      goto LAB_001d343c;
    }
  }
  if (2 < DebugLevel) {
    printk("eFuseGetFreeBlockCount, FirstFreeBlock= 0x%x\n",0xffff);
  }
  goto LAB_001d3418;
  while( true ) {
    if (((local_22 & 0xff) == 0) && (uVar3 != *(ushort *)(iVar1 + 0xe6) - 1)) goto LAB_001d34dc;
    uVar3 = uVar3 - 2 & 0xffff;
    if (uVar3 < uVar4) break;
LAB_001d343c:
    EfusePhysicalReadRegisters(param_1,uVar3,2,&local_22);
    if ((local_22 >> 8 == 0) && (*(ushort *)(iVar1 + 0xe8) != uVar3)) {
      uVar3 = uVar3 + 1 & 0xffff;
LAB_001d34dc:
      if (2 < DebugLevel) goto LAB_001d34a0;
      goto LAB_001d34b0;
    }
  }
  if (2 < DebugLevel) {
    uVar3 = 0xffff;
LAB_001d34a0:
    printk("eFuseGetFreeBlockCount, LastFreeBlock= 0x%x\n",uVar3);
LAB_001d34b0:
    if (uVar3 != 0xffff) {
      if (uVar3 < uVar2) {
        iVar1 = 0;
      }
      else {
        iVar1 = (uVar3 - uVar2) + 1;
      }
      *param_2 = iVar1;
      goto LAB_001d3364;
    }
  }
LAB_001d3418:
  *param_2 = 0;
  return;
}

