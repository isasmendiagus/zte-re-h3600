// module: mt7915.ko
// function: is_ru26_disable_channel @ 0x14266c
// size: 224 bytes
//

undefined4 is_ru26_disable_channel(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  char *pcVar2;
  byte *pbVar3;
  
  if ((param_3 & 0x1c0) == 0) {
    return 0;
  }
  iVar1 = get_reg_table_by_country(param_1 + 0x794c31,param_3);
  if (iVar1 != 0) {
    pcVar2 = (char *)(iVar1 + 0x88);
    do {
      if ((byte)pcVar2[9] != 0) {
        if (param_2 != (byte)pcVar2[9]) {
          pbVar3 = (byte *)(pcVar2 + 9);
          do {
            pbVar3 = pbVar3 + 1;
            if (*pbVar3 == 0) goto LAB_001426e0;
          } while (param_2 != *pbVar3);
        }
        if ((*(uint *)(pcVar2 + 0x84) != 0xffffff) && ((*(uint *)(pcVar2 + 0x84) & 0x10000) != 0)) {
          if (-1 < DebugLevel) {
            printk("%s(): Channel=%d, CountryCode %s, reg_class %d  hit RU26 disable\n",
                   "is_ru26_disable_channel",param_2,param_1 + 0x794c31,*pcVar2);
            return 1;
          }
          return 1;
        }
      }
LAB_001426e0:
      pcVar2 = pcVar2 + 0x88;
    } while (*pcVar2 != '\0');
  }
  return 0;
}

