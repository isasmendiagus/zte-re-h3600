// module: mt7915.ko
// function: chip_check_txv @ 0x18df40
// size: 356 bytes
//

undefined4 chip_check_txv(undefined4 param_1,char *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  char *__s1;
  uint uVar3;
  uint local_24;
  
  local_24 = 0;
  if (*param_2 == '\0') {
    if (-1 < DebugLevel) {
      printk("%s: Unknown parameter name!\n","chip_check_txv");
    }
  }
  else {
    __s1 = "ant id";
    uVar3 = 0;
    do {
      iVar1 = strcmp(__s1,param_2);
      uVar2 = uVar3 + 1 & 0xff;
      if (iVar1 == 0) {
        mac_io_read32(param_1,(&DAT_0029c59c)[uVar3 * 4],&local_24);
        local_24 = (local_24 & (&DAT_0029c5a0)[uVar3 * 4]) >> ((&DAT_0029c5a4)[uVar3 * 4] & 0xff);
        if (local_24 == param_3) {
          if (DebugLevel < 1) {
            return 0;
          }
          printk("%s: [Matched] %s = %d\n","chip_check_txv",__s1,param_3);
          return 0;
        }
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s: [Mis-matched] %s = (%d:%d)\n","chip_check_txv",__s1,local_24,param_3);
        return 0;
      }
      __s1 = *(char **)(&UNK_0029c598 + uVar2 * 0x10);
      uVar3 = uVar2;
    } while (__s1 != (char *)0x0);
    if (0 < DebugLevel) {
      printk("%s: %s not found!\n","chip_check_txv",0);
    }
  }
  return 0;
}

