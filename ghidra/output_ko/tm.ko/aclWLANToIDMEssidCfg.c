// module: tm.ko
// function: aclWLANToIDMEssidCfg @ 0x587c8
// size: 120 bytes
//

undefined4 aclWLANToIDMEssidCfg(uint param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = param_3 - 0x10U;
  if (param_3 - 0x10U < 0x10) {
    uVar1 = param_1;
  }
  if ((uVar1 < 0x10) && (uVar2 = 0, param_2 - 6U < 2)) {
    (&s_aclWlanToIdmEssidMap)[param_1 * 0x12] = (char)param_2;
    (&DAT_000c1175)[param_1 * 0x12] = (char)param_3;
  }
  else {
    printk("%s %d params is invalid, wlan_index %d, essid %d, idm_port %d\n","aclWLANToIDMEssidCfg",
           0x18e,param_1,param_3,param_2);
    uVar2 = 0xea;
  }
  return uVar2;
}

