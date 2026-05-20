// module: mt7915.ko
// function: dfs_get_band_by_ch @ 0x231dc4
// size: 124 bytes
//

int dfs_get_band_by_ch(int param_1,uint param_2)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = 0;
  while( true ) {
    iVar2 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar5);
    if (*(char *)(iVar2 + 0x49c) != '\0') {
      iVar3 = 0;
      do {
        pbVar1 = (byte *)(iVar2 + iVar3);
        iVar3 = iVar3 + 0x14;
        if (*pbVar1 == param_2) {
          iVar4 = iVar5;
        }
      } while (iVar3 != ((byte)(*(char *)(iVar2 + 0x49c) - 1) + 1) * 0x14);
    }
    if (iVar5 == 1) break;
    iVar5 = 1;
  }
  return iVar4;
}

