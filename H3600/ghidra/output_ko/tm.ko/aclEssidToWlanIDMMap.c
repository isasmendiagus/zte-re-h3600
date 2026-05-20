// module: tm.ko
// function: aclEssidToWlanIDMMap @ 0x588c4
// size: 168 bytes
//

undefined4
aclEssidToWlanIDMMap(uint param_1,undefined1 *param_2,undefined1 *param_3,undefined4 param_4)

{
  byte *pbVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (0xf < param_1 - 0x10) {
    printk("%s %d  Essid invalid\n","aclEssidToWlanIDMMap",0x1b8,param_1 - 0x10,param_4);
    return 0xea;
  }
  if (param_3 == (undefined1 *)0x0 || param_2 == (undefined1 *)0x0) {
    printk("%s %d params is NULL\n","aclEssidToWlanIDMMap",0x1be,1,param_4);
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
      return 0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x10);
  return 0xff;
}

