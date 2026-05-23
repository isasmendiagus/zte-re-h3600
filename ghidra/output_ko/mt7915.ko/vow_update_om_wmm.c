// module: mt7915.ko
// function: vow_update_om_wmm @ 0x42a94
// size: 300 bytes
//

void vow_update_om_wmm(int param_1,int param_2,int param_3,char *param_4)

{
  ushort uVar1;
  char *pcVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  byte *pbVar6;
  short *psVar7;
  undefined4 local_24 [2];
  
  local_24[0] = 0x3020001;
  pcVar2 = (char *)wlan_config_get_ht_edca(param_2);
  if ((*(uint *)(param_1 + 0xa7a2e8) & 0xff00ff) != 0) {
    uVar1 = *(ushort *)(param_2 + 0x18);
    if ((uVar1 & 0xb1) == 0) {
      if (*(char *)(param_1 + 0x795070) == '\0') {
        sVar5 = 0x14;
      }
      else {
        sVar5 = 9;
      }
    }
    else {
      sVar5 = 9;
    }
    if (((pcVar2 != (char *)0x0) && (*pcVar2 != '\0' && param_4 != (char *)0x0)) &&
       (iVar3 = 0, *param_4 != '\0')) {
      psVar7 = (short *)(param_1 + param_3 * 8 + 0xa797e2);
      pbVar6 = (byte *)local_24;
      while( true ) {
        iVar3 = iVar3 + 1;
        if ((uVar1 & 0xb1) == 0) {
          sVar4 = 10;
        }
        else {
          sVar4 = 0x10;
        }
        psVar7 = psVar7 + 1;
        *psVar7 = sVar4 + (((byte)pcVar2[*pbVar6 + 7] - 1) + (short)(1 << pcVar2[*pbVar6 + 0xb])) *
                          sVar5;
        if (iVar3 == 4) break;
        uVar1 = *(ushort *)(param_2 + 0x18);
        pbVar6 = pbVar6 + 1;
      }
      vow_set_backoff_time(param_1,param_3);
      return;
    }
  }
  return;
}

