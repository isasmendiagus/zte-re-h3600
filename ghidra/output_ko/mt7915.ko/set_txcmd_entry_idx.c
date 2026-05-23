// module: mt7915.ko
// function: set_txcmd_entry_idx @ 0x97df8
// size: 152 bytes
//

void set_txcmd_entry_idx(int param_1,char *param_2)

{
  byte bVar1;
  char *pcVar2;
  char *local_c;
  
  local_c = param_2;
  pcVar2 = strsep(&local_c,"-");
  if ((pcVar2 != (char *)0x0) && (*pcVar2 != '\0')) {
    bVar1 = os_str_tol(pcVar2,0,0x10);
    *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0x1f | (bVar1 & 7) << 5;
    if ((bVar1 & 7) < 2) {
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s: invalid txcmd_entry_idx : %d. Set to 0\n","set_txcmd_entry_idx");
    }
  }
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0x1f;
  return;
}

