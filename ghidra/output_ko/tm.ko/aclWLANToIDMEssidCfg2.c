// module: tm.ko
// function: aclWLANToIDMEssidCfg2 @ 0x58a38
// size: 108 bytes
//

undefined4 aclWLANToIDMEssidCfg2(uint param_1,undefined1 param_2,undefined1 param_3,char *param_4)

{
  int iVar1;
  
  if (param_1 < 0x10) {
    iVar1 = param_1 * 0x12;
    (&s_aclWlanToIdmEssidMap)[iVar1] = param_2;
    (&DAT_000c1175)[iVar1] = param_3;
    strncpy(&DAT_000c1176 + iVar1,param_4,0xf);
    return 0;
  }
  printk("%s %d params is invalid, wlan_index %d\n","aclWLANToIDMEssidCfg2",0x158,param_1,param_4);
  return 0xea;
}

