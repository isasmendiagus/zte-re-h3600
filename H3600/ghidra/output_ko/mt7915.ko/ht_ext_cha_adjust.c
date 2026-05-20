// module: mt7915.ko
// function: ht_ext_cha_adjust @ 0x141200
// size: 388 bytes
//

void ht_ext_cha_adjust(undefined4 param_1,uint param_2,char *param_3,byte *param_4,
                      undefined4 param_5)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  byte bVar4;
  byte *pbVar5;
  
  iVar1 = wlan_config_get_ch_band(param_5);
  if (iVar1 == 1) {
    pbVar5 = &DAT_00299d4c;
  }
  else {
    if (iVar1 != 2) {
      cVar3 = *param_3;
      if (cVar3 != '\x01') goto LAB_00141238;
      bVar4 = *param_4;
      if ((bVar4 == 0) || (bVar4 == 1)) {
        iVar1 = FUN_00140ed0(param_1,param_2 + 4 & 0xff,param_5);
        if (iVar1 != 0) {
          bVar4 = 1;
          goto LAB_0014137c;
        }
        bVar4 = 3;
        uVar2 = param_2 - 4 & ~((int)(param_2 - 4) >> 0x1f);
      }
      else {
        iVar1 = FUN_00140ed0(param_1,param_2 - 4 & ~((int)(param_2 - 4) >> 0x1f) & 0xff,param_5);
        if (iVar1 != 0) {
LAB_0014137c:
          *param_4 = bVar4;
          goto LAB_0014132c;
        }
        uVar2 = param_2 + 4;
        bVar4 = 1;
      }
      iVar1 = FUN_00140ed0(param_1,uVar2 & 0xff,param_5);
      if (iVar1 == 0) {
        *param_3 = '\0';
      }
      else {
        *param_4 = bVar4;
      }
LAB_0014132c:
      if (param_2 == 0xe) {
        *param_3 = '\0';
      }
      return;
    }
    pbVar5 = &_LANCHOR1;
  }
  cVar3 = *param_3;
  if (cVar3 == '\x01') {
    uVar2 = (uint)*pbVar5;
    if (uVar2 != 0) {
      do {
        if (param_2 == uVar2) {
          uVar2 = param_2 - 4 & ~((int)(param_2 - 4) >> 0x1f);
          if (pbVar5[1] == 1) {
            uVar2 = param_2 + 4;
          }
          iVar1 = FUN_00140ed0(param_1,uVar2 & 0xff,param_5);
          if (iVar1 != 0) {
            *param_4 = pbVar5[1];
            if (*pbVar5 != 0) {
              return;
            }
            break;
          }
        }
        pbVar5 = pbVar5 + 2;
        uVar2 = (uint)*pbVar5;
      } while (uVar2 != 0);
    }
    *param_3 = '\0';
    *param_4 = 0;
    return;
  }
LAB_00141238:
  if (cVar3 == '\0') {
    *param_4 = 0;
  }
  return;
}

