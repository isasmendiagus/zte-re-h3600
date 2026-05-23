// module: mt7915.ko
// function: chip_show_amsdu_info @ 0x189b3c
// size: 448 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 chip_show_amsdu_info(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  bool bVar6;
  int aiStack_3c [10];
  
  piVar5 = aiStack_3c;
  iVar3 = *(int *)(param_1 + 0x4328);
  aiStack_3c[1] = 0;
  aiStack_3c[2] = 0;
  aiStack_3c[3] = 0;
  aiStack_3c[4] = 0;
  aiStack_3c[5] = 0;
  aiStack_3c[6] = 0;
  aiStack_3c[7] = 0;
  aiStack_3c[8] = 0;
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10e0,aiStack_3c + 1);
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10e4,aiStack_3c + 2);
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10e8,aiStack_3c + 3);
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10ec,aiStack_3c + 4);
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10f0,aiStack_3c + 5);
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10f4,aiStack_3c + 6);
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10f8,aiStack_3c + 7);
  hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c10fc,aiStack_3c + 8);
  if (0 < DebugLevel) {
    printk("TXD counter status of MSDU:\n");
  }
  piVar2 = aiStack_3c;
  iVar3 = 0;
  do {
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + *piVar2;
  } while (piVar2 != aiStack_3c + 8);
  iVar4 = 1;
  do {
    piVar5 = (int *)((int)piVar5 + 4);
    if (0 < DebugLevel) {
      printk("AMSDU pack count of %d MSDU in TXD: 0x%x ",iVar4,*piVar5);
      if (iVar3 == 0) {
        if (0 < DebugLevel) {
          printk(&_LC12);
        }
      }
      else if (0 < DebugLevel) {
        uVar1 = __aeabi_uidiv(*piVar5 * 100,iVar3);
        printk("(%d%%)\n",uVar1);
      }
    }
    bVar6 = iVar4 != 8;
    iVar4 = iVar4 + 1;
  } while (bVar6);
  return 1;
}

