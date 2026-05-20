// module: mt7915.ko
// function: RandomByte2 @ 0x12f394
// size: 152 bytes
//

byte RandomByte2(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar4 + 0x30) != 2) {
    AsicGetCCACnt(param_1,0);
    bVar1 = AsicGetCrcErrCnt(param_1);
    bVar2 = get_random_seed_by_phy(param_1);
    bVar3 = RandomByte(param_1);
    return bVar3 ^ bVar2 ^ bVar1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("%s(%d): Not support for HIF_MT yet!\n","RandomByte2",0x1864);
  return 0;
}

