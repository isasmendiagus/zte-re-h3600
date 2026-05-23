// module: mt7915.ko
// function: show_fw_info @ 0x1c170c
// size: 124 bytes
//

void show_fw_info(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  
  iVar2 = param_1 + 0xa78548;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = 0;
  uVar4 = *(uint *)(iVar1 + 0x100);
  do {
    if ((uVar4 >> iVar3 & 1) != 0) {
      if (-1 < DebugLevel) {
        printk("CPU %d fw info\n",iVar3);
      }
      FUN_001bf6f4(iVar2);
    }
    bVar5 = iVar3 != 1;
    iVar2 = iVar2 + 0x3c;
    iVar3 = 1;
  } while (bVar5);
  return;
}

