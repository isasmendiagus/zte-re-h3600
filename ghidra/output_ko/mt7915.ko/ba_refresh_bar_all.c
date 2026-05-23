// module: mt7915.ko
// function: ba_refresh_bar_all @ 0xa8740
// size: 92 bytes
//

void ba_refresh_bar_all(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  while( true ) {
    uVar1 = HcGetMaxStaNum(param_1);
    uVar3 = uVar4 & 0xffff;
    uVar4 = uVar4 + 1;
    iVar2 = uVar3 * 0x14c0;
    if (uVar1 <= uVar3) break;
    if (*(int *)(param_1 + iVar2 + 0xa1d20) != 0) {
      SendRefreshBAR(param_1,param_1 + iVar2 + 0xa1d20);
    }
  }
  return;
}

