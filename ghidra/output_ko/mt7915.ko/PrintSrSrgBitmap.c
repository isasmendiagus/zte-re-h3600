// module: mt7915.ko
// function: PrintSrSrgBitmap @ 0x16d45c
// size: 308 bytes
//

void PrintSrSrgBitmap(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  undefined *apuStack_20 [3];
  
  apuStack_20[1] = &DAT_002f3af0;
  apuStack_20[0] = &DAT_002f3aec;
  if (-1 < DebugLevel) {
    iVar7 = param_2 + (short)param_1 * 4;
    printk("%s: Color - 31_0:%x, 63_32:%x pBssid - 31_0:%x, 63_32:%x\n","PrintSrSrgBitmap",
           *(undefined4 *)(param_2 + (short)param_1 * 4),*(undefined4 *)(iVar7 + 8),
           *(undefined4 *)(iVar7 + 0x10),*(undefined4 *)(iVar7 + 0x18));
    if (-1 < DebugLevel) {
      printk("BIT  Color  pBssid\n");
    }
  }
  puVar6 = (uint *)(param_2 + param_1 * 4);
  uVar5 = 0;
  do {
    uVar4 = uVar5 - 0x20;
    uVar1 = 1 << (uVar5 & 0xff);
    uVar2 = 1 << (uVar4 & 0xff);
    if (uVar5 < 0x20) {
      uVar3 = (*puVar6 & uVar1) >> (uVar5 & 0xff);
      uVar1 = (puVar6[4] & uVar1) >> (uVar5 & 0xff);
    }
    else {
      uVar3 = (puVar6[2] & uVar2) >> (uVar4 & 0xff);
      uVar1 = (uVar2 & puVar6[6]) >> (uVar4 & 0xff);
    }
    if (-1 < DebugLevel) {
      printk("%2d     %s      %s   \n",uVar5,apuStack_20[uVar3 & 0xff],apuStack_20[uVar1 & 0xff]);
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 0x40);
  return;
}

