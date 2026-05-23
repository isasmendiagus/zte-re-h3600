// module: mt7915.ko
// function: dfs_get_outband_bw @ 0x100bcc
// size: 152 bytes
//

undefined4 dfs_get_outband_bw(undefined4 param_1,int param_2,undefined1 *param_3)

{
  char cVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar2 = *(int *)(param_2 + 0xb10);
  if (iVar2 == 0) {
    return 0;
  }
  if (*(char *)(iVar2 + 0x15) == '\0') {
    *param_3 = 0;
    return 1;
  }
  if (*(char *)(iVar2 + 0x15) == '\x01') {
    cVar1 = *(char *)(iVar2 + 0x5c);
    if (cVar1 == '\0') {
      *param_3 = 1;
      return 1;
    }
    if (cVar1 == '\x01') {
      *param_3 = 2;
      return 1;
    }
    if (cVar1 == '\x02') {
      *param_3 = 3;
      return 1;
    }
    if (cVar1 == '\x03') {
      *param_3 = 6;
    }
    return 1;
  }
  return 1;
}

