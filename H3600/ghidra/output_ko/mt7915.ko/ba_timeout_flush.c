// module: mt7915.ko
// function: ba_timeout_flush @ 0xa59f8
// size: 188 bytes
//

void ba_timeout_flush(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  
  uVar1 = jiffies;
  puVar5 = (uint *)(param_1 + 0x2f5ec);
  iVar6 = 0;
  do {
    puVar5 = puVar5 + 1;
    uVar7 = *puVar5;
    if (uVar7 != 0) {
      iVar4 = 0;
      iVar3 = param_1 + iVar6 * 0xc00 + 0x1c0;
      do {
        iVar4 = iVar4 + 1;
        if ((uVar7 & 1) != 0) {
          iVar2 = *(int *)(iVar3 + 0x50);
          if (*(int *)(iVar3 + 0x54) == iVar2) {
            ba_flush_reordering_timeout_mpdus(param_1,param_1 + 0x1c0,iVar3,uVar1);
            iVar2 = *(int *)(iVar3 + 0x50);
          }
          *(int *)(iVar3 + 0x54) = iVar2;
          uVar7 = *puVar5;
        }
        uVar7 = uVar7 >> 1;
        iVar3 = iVar3 + 0x60;
        *puVar5 = uVar7;
      } while (uVar7 != 0 && iVar4 != 0x20);
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 != 0x24);
  *(undefined1 *)(param_1 + 0x2f5ec) = 0;
  return;
}

