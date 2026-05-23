// module: mt7915.ko
// function: RepeaterCliReset @ 0x810cc
// size: 256 bytes
//

void RepeaterCliReset(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  cVar1 = *(char *)(iVar2 + 0x14a);
  if ((&DAT_0036790d)[param_1] == '\x01') {
    _raw_spin_lock_bh(&DAT_00367914 + param_1);
    if (cVar1 != '\0') {
      iVar2 = 0;
      do {
        *(undefined1 *)(*(int *)(&DAT_003687a8 + param_1) + iVar2) = 0;
        iVar2 = iVar2 + 0x42f4;
      } while (iVar2 != ((byte)(cVar1 - 1) + 1) * 0x42f4);
    }
    (&DAT_00367912)[param_1] = 0;
    (&DAT_00367913)[param_1] = 0;
    os_zero_mem(&DAT_00368120 + param_1,0x584);
    os_zero_mem(&DAT_00367918 + param_1,0x400);
    os_zero_mem(&DAT_00367d18 + param_1,0x400);
    if (2 < DebugLevel) {
      printk("%s() is done\n","RepeaterCliReset");
    }
    _raw_spin_unlock_bh(&DAT_00367914 + param_1);
    return;
  }
  return;
}

