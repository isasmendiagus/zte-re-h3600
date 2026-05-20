// module: tm.ko
// function: aclEssidToWlanIDMMap2 @ 0x58aa8
// size: 260 bytes
//

undefined4 aclEssidToWlanIDMMap2(uint param_1,undefined1 *param_2,char *param_3,char *param_4)

{
  byte *pbVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (0xf < param_1 - 0x10) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_28000,"aclEssidToWlanIDMMap2"), iVar2 != 0)) {
      printk("%s %d  Essid %d invalid\n","aclEssidToWlanIDMMap2",0x16c,param_1,param_4);
    }
    return 0xea;
  }
  if (param_2 == (undefined1 *)0x0 || (param_3 == (char *)0x0 || param_3 == param_4)) {
    printk("%s %d params is NULL\n","aclEssidToWlanIDMMap2",0x172,param_4,param_4);
    return 0xea;
  }
  puVar3 = &s_aclWlanToIdmEssidMap;
  iVar2 = 0;
  do {
    pbVar1 = puVar3 + 1;
    puVar3 = puVar3 + 0x12;
    if (*pbVar1 == param_1) {
      *param_2 = (char)iVar2;
      *param_3 = (&s_aclWlanToIdmEssidMap)[iVar2 * 0x12];
      strncpy(param_4,&DAT_000c1176 + iVar2 * 0x12,0xf);
      return 0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x10);
  return 0xff;
}

