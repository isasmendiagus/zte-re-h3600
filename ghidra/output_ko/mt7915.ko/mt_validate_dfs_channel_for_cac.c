// module: mt7915.ko
// function: mt_validate_dfs_channel_for_cac @ 0xd8e50
// size: 120 bytes
//

undefined4 mt_validate_dfs_channel_for_cac(undefined4 param_1,int param_2)

{
  char cVar1;
  uint *puVar2;
  uint uVar3;
  
  if (*(int *)(param_2 + 0x14) == 0x100 || *(int *)(param_2 + 0x14) == 2) {
    uVar3 = 0;
    puVar2 = (uint *)get_scan_tab_by_wdev();
    if (*puVar2 != 0) {
      cVar1 = (char)puVar2[5];
      while( true ) {
        if (cVar1 == *(char *)(param_2 + 0x1a)) {
          return 0;
        }
        uVar3 = uVar3 + 1 & 0xff;
        if (*puVar2 <= uVar3) break;
        cVar1 = (char)puVar2[uVar3 * 0x2bd + 5];
      }
    }
  }
  return 1;
}

