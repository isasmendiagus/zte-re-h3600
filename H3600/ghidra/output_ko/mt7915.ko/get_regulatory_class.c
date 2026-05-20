// module: mt7915.ko
// function: get_regulatory_class @ 0x141c58
// size: 908 bytes
//

char get_regulatory_class(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  byte *pbVar6;
  char *pcVar7;
  uint uVar8;
  
  iVar2 = wlan_config_get_ht_bw(param_4);
  uVar3 = wlan_config_get_vht_bw(param_4);
  uVar4 = wlan_config_get_he_bw(param_4);
  uVar8 = (uint)((param_3 & 0x18) != 0);
  cVar1 = *(char *)(param_1 + 0xa7cc26);
  if (iVar2 == 0) {
    uVar8 = 0;
  }
  if ((param_3 & 0x20) != 0) {
    switch(uVar3) {
    case 0:
      uVar8 = (uint)(iVar2 == 1);
      break;
    case 1:
      uVar8 = 2;
      break;
    case 2:
      uVar8 = 3;
      break;
    case 3:
      uVar8 = 6;
    }
  }
  if ((param_3 & 0x1c0) == 0) {
    if (3 < DebugLevel) {
      printk("%s(): Channel=%d,HT_BW=%d bw=%d\n","get_regulatory_class",param_2,iVar2,uVar8);
    }
    if ((param_3 & 0x20) == 0) {
      iVar2 = get_reg_table_by_country(param_1 + 0x794c31,param_3);
      if (iVar2 != 0) {
        pcVar7 = (char *)(iVar2 + 0x20);
        do {
          if ((*(uint *)(BW_VALUE + uVar8 * 4) <= *(uint *)(BW_VALUE + (uint)(byte)pcVar7[8] * 4))
             && ((byte)pcVar7[9] != 0)) {
            if (param_2 == (byte)pcVar7[9]) {
LAB_00141f74:
              if (cVar1 == '\0') {
                return *pcVar7;
              }
              return pcVar7[1];
            }
            pbVar6 = (byte *)(pcVar7 + 9);
            while( true ) {
              pbVar6 = pbVar6 + 1;
              if (*pbVar6 == 0) break;
              if (param_2 == *pbVar6) goto LAB_00141f74;
            }
          }
          pcVar7 = pcVar7 + 0x20;
        } while (*pcVar7 != '\0');
      }
    }
    else {
      iVar2 = get_reg_table_by_country(param_1 + 0x794c31,param_3);
      if (iVar2 != 0) {
        uVar4 = wlan_config_get_ch_band(param_4);
        pcVar7 = (char *)(iVar2 + 0x30);
        do {
          if (*(uint *)(BW_VALUE + uVar8 * 4) <= *(uint *)(BW_VALUE + (uint)(byte)pcVar7[8] * 4)) {
            if ((byte)pcVar7[9] != 0) {
              if (param_2 == (byte)pcVar7[9]) goto LAB_00141f60;
              pbVar6 = (byte *)(pcVar7 + 9);
              while( true ) {
                pbVar6 = pbVar6 + 1;
                if (*pbVar6 == 0) break;
                if (param_2 == *pbVar6) goto LAB_00141f60;
              }
            }
            uVar5 = vht_cent_ch_freq(param_2,uVar3,uVar4);
            if ((byte)pcVar7[0x19] != 0) {
              if (uVar5 == (byte)pcVar7[0x19]) goto LAB_00141f60;
              pbVar6 = (byte *)(pcVar7 + 0x19);
              while( true ) {
                pbVar6 = pbVar6 + 1;
                if (*pbVar6 == 0) break;
                if (uVar5 == *pbVar6) goto LAB_00141f60;
              }
            }
          }
          pcVar7 = pcVar7 + 0x30;
        } while (*pcVar7 != '\0');
      }
    }
  }
  else {
    switch(uVar4) {
    case 1:
      uVar8 = (uint)(iVar2 == 1);
      break;
    case 2:
      uVar8 = 2;
      break;
    case 3:
      uVar8 = 3;
      break;
    case 4:
      uVar8 = 6;
    }
    if (3 < DebugLevel) {
      printk("%s(): Channel=%d,HT_BW=%d bw=%d\n","get_regulatory_class",param_2,iVar2,uVar8);
    }
    iVar2 = get_reg_table_by_country(param_1 + 0x794c31,param_3);
    if (iVar2 != 0) {
      uVar4 = wlan_config_get_ch_band(param_4);
      pcVar7 = (char *)(iVar2 + 0x88);
      do {
        if (*(uint *)(BW_VALUE + uVar8 * 4) <= *(uint *)(BW_VALUE + (uint)(byte)pcVar7[8] * 4)) {
          if ((byte)pcVar7[9] != 0) {
            if (param_2 == (byte)pcVar7[9]) {
LAB_00141f60:
              if (cVar1 == '\0') {
                cVar1 = *pcVar7;
              }
              else {
                cVar1 = pcVar7[1];
              }
              return cVar1;
            }
            pbVar6 = (byte *)(pcVar7 + 9);
            while( true ) {
              pbVar6 = pbVar6 + 1;
              if (*pbVar6 == 0) break;
              if (param_2 == *pbVar6) goto LAB_00141f60;
            }
          }
          uVar5 = vht_cent_ch_freq(param_2,uVar3,uVar4);
          if ((byte)pcVar7[0x45] != 0) {
            if (uVar5 == (byte)pcVar7[0x45]) goto LAB_00141f60;
            pbVar6 = (byte *)(pcVar7 + 0x45);
            while( true ) {
              pbVar6 = pbVar6 + 1;
              if (*pbVar6 == 0) break;
              if (uVar5 == *pbVar6) goto LAB_00141f60;
            }
          }
        }
        pcVar7 = pcVar7 + 0x88;
      } while (*pcVar7 != '\0');
    }
  }
  return '\0';
}

