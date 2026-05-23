// module: switch.ko
// function: sw_init_wlan_ssid @ 0x17434
// size: 116 bytes
//

void sw_init_wlan_ssid(void)

{
  undefined4 in_r3;
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  
  aclWlanToIdmReset();
  uVar2 = 0;
  puVar1 = &DAT_0002c20d;
  uVar4 = 0x10;
  uVar3 = 6;
  do {
    if (puVar1[-1] != '\0') {
      if (puVar1[0x24] == '\0') {
        uVar4 = puVar1[0x26];
        uVar3 = 6;
      }
      else if (puVar1[0x24] == '\x01') {
        uVar4 = puVar1[0x26];
        uVar3 = 7;
      }
      aclWLANToIDMEssidCfg2(uVar2 & 0xff,uVar3,uVar4,puVar1,in_r3);
    }
    uVar2 = uVar2 + 1;
    puVar1 = puVar1 + 0x29;
  } while (uVar2 != 0x10);
  return;
}

