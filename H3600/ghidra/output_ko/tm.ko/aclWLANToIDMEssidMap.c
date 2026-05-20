// module: tm.ko
// function: aclWLANToIDMEssidMap @ 0x58840
// size: 128 bytes
//

undefined4
aclWLANToIDMEssidMap(uint param_1,undefined1 *param_2,undefined1 *param_3,undefined4 param_4)

{
  if (0xf < param_1) {
    printk("%s %d params is invalid, wlan_index %d\n","aclWLANToIDMEssidMap",0x19f,param_1,param_4);
    return 0xea;
  }
  if (param_3 != (undefined1 *)0x0 && param_2 != (undefined1 *)0x0) {
    *param_2 = (&s_aclWlanToIdmEssidMap)[param_1 * 0x12];
    *param_3 = (&DAT_000c1175)[param_1 * 0x12];
    return 0;
  }
  printk("%s %d params is NULL\n","aclWLANToIDMEssidMap",0x1a5,param_1,param_4);
  return 0xea;
}

