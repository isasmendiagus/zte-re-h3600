// module: mt7915.ko
// function: vht40_channel_group @ 0x20371c
// size: 240 bytes
//

undefined4 vht40_channel_group(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  byte *pbVar4;
  bool bVar5;
  bool bVar6;
  undefined8 uVar7;
  
  uVar7 = wlan_config_get_ch_band(param_3);
  iVar1 = (int)uVar7;
  if (iVar1 == 1) {
    iVar1 = GetCountryRegionFromCountryCode(param_1 + 0x794c31,(int)((ulonglong)uVar7 >> 0x20),1);
    for (pbVar4 = &DAT_002a15d4; pbVar4[1] != 0; pbVar4 = pbVar4 + 3) {
      if (param_2 <= pbVar4[1] && *pbVar4 <= param_2) {
        if (iVar1 != 0) {
          return 1;
        }
        if (pbVar4[2] != 0x8e) {
          return 1;
        }
      }
    }
  }
  else {
    if (iVar1 == 2) {
      if (4 < param_2 - 1) {
        puVar3 = &UNK_002a1578;
        do {
          uVar2 = (uint)(byte)puVar3[4];
          if (uVar2 == 0) {
            return 0;
          }
          bVar6 = param_2 <= (byte)puVar3[3];
          bVar5 = (byte)puVar3[3] == param_2;
          if (!bVar6 || bVar5) {
            bVar6 = uVar2 <= param_2;
            bVar5 = param_2 == uVar2;
          }
          puVar3 = puVar3 + 3;
        } while (bVar6 && !bVar5);
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s() invalid ch_band %d\n","vht40_channel_group",iVar1,DebugLevel,param_4);
    }
  }
  return 0;
}

