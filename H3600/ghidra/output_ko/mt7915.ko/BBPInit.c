// module: mt7915.ko
// function: BBPInit @ 0x17d604
// size: 312 bytes
//

void BBPInit(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  undefined1 local_52 [2];
  undefined4 local_50 [13];
  
  local_52[0] = 1;
  local_50[0] = 1;
  local_50[2] = 1;
  local_50[4] = 1;
  local_50[1] = 0;
  local_50[3] = 0;
  local_50[5] = 0;
  local_50[6] = 0;
  local_50[7] = 0;
  local_50[9] = 0;
  local_50[0xb] = 0;
  local_50[8] = 2;
  local_50[10] = 2;
  local_50[6] = vht_prim_ch_idx(1,1,1);
  local_52[1] = 0;
  if (0 < DebugLevel) {
    printk("%s():BBP Initialization.....\n","BBPInit");
  }
  iVar2 = 0;
  iVar1 = DebugLevel;
  do {
    if (0 < iVar1) {
      printk("\tBand %d: valid=%d, isDBDC=%d, Band=%d, CBW=%d, CentCh/PrimCh=%d/%d, prim_ch_idx=%d, txStream=%d\n"
             ,iVar2,local_52[iVar2],0,local_50[iVar2 + 8],local_50[iVar2],local_50[iVar2 + 2],
             local_50[iVar2 + 4],local_50[iVar2 + 6],local_50[iVar2 + 10]);
      iVar1 = DebugLevel;
    }
    bVar3 = iVar2 != 1;
    iVar2 = 1;
  } while (bVar3);
  if (iVar1 < 0) {
    return;
  }
  printk("%s() todo\n","BBPInit");
  return;
}

