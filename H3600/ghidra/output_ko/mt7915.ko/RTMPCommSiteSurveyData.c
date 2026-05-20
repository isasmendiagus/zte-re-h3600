// module: mt7915.ko
// function: RTMPCommSiteSurveyData @ 0x15d06c
// size: 1096 bytes
//

void RTMPCommSiteSurveyData(undefined4 *param_1,int param_2)

{
  undefined2 uVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  byte bVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
  iVar4 = strcmp(pcVar3,"WPAPSK");
  if (iVar4 == 0) {
    param_1[0x15] = 0;
    param_1[0x14] = 2;
    param_1[0x23] = 1;
  }
  else {
    pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
    iVar4 = strcmp(pcVar3,"WPA2PSK");
    if (iVar4 == 0) {
      param_1[0x15] = 0;
      param_1[0x14] = 3;
      param_1[0x23] = 1;
    }
    else {
      pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
      iVar4 = strcmp(pcVar3,"WPA3PSK");
      if (iVar4 == 0) {
        uVar8 = 10;
LAB_0015d304:
        param_1[0x14] = uVar8;
        param_1[0x15] = 2;
        param_1[0x23] = 3;
      }
      else {
        pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
        iVar4 = strcmp(pcVar3,"WPAPSKWPA2PSK");
        if (iVar4 == 0) {
          param_1[0x15] = 0;
          param_1[0x14] = 6;
          param_1[0x23] = 1;
        }
        else {
          pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
          iVar4 = strcmp(pcVar3,"WPA2PSKWPA3PSK");
          if (iVar4 == 0) {
            uVar8 = 0xc;
            goto LAB_0015d304;
          }
          pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
          iVar4 = strcmp(pcVar3,"WPA1WPA2");
          if (iVar4 == 0) {
            uVar8 = 6;
          }
          else {
            pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
            iVar4 = strcmp(pcVar3,"WPA3");
            if (iVar4 == 0) {
              uVar8 = 10;
            }
            else {
              pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
              iVar4 = strcmp(pcVar3,"WPA2");
              if (iVar4 != 0) {
                pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
                iVar4 = strcmp(pcVar3,"WPA");
                if (iVar4 == 0) {
                  param_1[0x14] = 2;
                  param_1[0x23] = 2;
                  param_1[0x15] = 1;
                }
                else {
                  pcVar3 = (char *)GetAuthModeStr(*(undefined4 *)(param_2 + 0xc4));
                  iVar4 = strcmp(pcVar3,"OPEN");
                  if (iVar4 == 0) {
                    param_1[0x14] = 0;
                  }
                }
                goto LAB_0015d0a8;
              }
              uVar8 = 3;
            }
          }
          param_1[0x14] = uVar8;
          param_1[0x15] = 1;
          param_1[0x23] = 2;
        }
      }
    }
  }
LAB_0015d0a8:
  pcVar3 = (char *)GetEncryModeStr(*(undefined4 *)(param_2 + 200));
  iVar4 = strcmp(pcVar3,"TKIP");
  if (iVar4 == 0) {
    param_1[0x16] = 0;
  }
  else {
    pcVar3 = (char *)GetEncryModeStr(*(undefined4 *)(param_2 + 200));
    iVar4 = strcmp(pcVar3,"AES");
    if (iVar4 == 0) {
      param_1[0x16] = 1;
    }
    else {
      pcVar3 = (char *)GetEncryModeStr(*(undefined4 *)(param_2 + 200));
      iVar4 = strcmp(pcVar3,"TKIPAES");
      if (iVar4 == 0) {
        param_1[0x16] = 2;
      }
      else {
        pcVar3 = (char *)GetEncryModeStr(*(undefined4 *)(param_2 + 200));
        iVar4 = strcmp(pcVar3,"WEP");
        if (iVar4 == 0) {
          param_1[0x14] = 1;
        }
        else {
          pcVar3 = (char *)GetEncryModeStr(*(undefined4 *)(param_2 + 200));
          iVar4 = strcmp(pcVar3,"NONE");
          if (iVar4 == 0) {
            param_1[0x14] = 0;
          }
        }
      }
    }
  }
  cVar2 = *(char *)(param_2 + 0x71);
  uVar5 = NetworkTypeInUseSanity(param_2);
  if (uVar5 < 2) {
    param_1[0x18] = 2;
    goto LAB_0015d154;
  }
  if (uVar5 == 2) {
    param_1[0x18] = 1;
    goto LAB_0015d154;
  }
  if (uVar5 == 5) {
    param_1[0x18] = 8;
    goto LAB_0015d154;
  }
  if (uVar5 == 7) {
LAB_0015d2d8:
    param_1[0x18] = 9;
  }
  else {
    if (uVar5 == 9) {
      param_1[0x18] = 0xe;
      goto LAB_0015d154;
    }
    if (uVar5 == 3) {
      param_1[0x18] = 3;
      goto LAB_0015d154;
    }
    if (uVar5 != 6) {
      if (uVar5 == 8) {
        param_1[0x18] = 0xd;
        goto LAB_0015d154;
      }
      if (0xd < (uint)param_1[0xf]) goto LAB_0015d2d8;
    }
    param_1[0x18] = 7;
  }
LAB_0015d154:
  bVar7 = *(byte *)(param_2 + 0x50) & 3;
  if (bVar7 == 1) {
    param_1[0x10] = 0;
  }
  else if (bVar7 == 3) {
    param_1[0x10] = 1;
  }
  if (*(char *)(param_2 + 0x14) == '\0') {
    uVar8 = 2;
  }
  else {
    uVar8 = 0;
  }
  param_1[0x19] = uVar8;
  uVar5 = (uint)*(ushort *)(param_2 + 0x18);
  if (uVar5 == 0) {
    uVar5 = 100;
  }
  param_1[0xe] = uVar5;
  uVar5 = (uint)*(ushort *)(param_2 + 0x88);
  if (uVar5 == 0) {
    uVar5 = 1;
  }
  param_1[0x1a] = uVar5;
  if (*(char *)(param_2 + 0x7e) == '\0') {
    uVar5 = *(byte *)(param_2 + 0x35) & 2;
    if ((*(byte *)(param_2 + 0x35) & 2) != 0) {
      uVar5 = 1;
    }
    param_1[0x13] = uVar5;
  }
  else {
    param_1[0x13] = 3;
  }
  *(byte *)((int)param_1 + 0x25) = (byte)(((uint)*(byte *)(param_2 + 0x72) << 0x1a) >> 0x1f);
  if (*(char *)(param_2 + 0x39) == -1) {
    uVar8 = 2;
  }
  else {
    uVar8 = 1;
  }
  if (*(char *)(param_2 + 0x3a) == -1) {
    uVar8 = 3;
  }
  if (*(char *)(param_2 + 0x3b) == -1) {
    uVar8 = 4;
  }
  param_1[10] = uVar8;
  param_1[0xf] = (uint)*(byte *)(param_2 + 0xc);
  uVar9 = *(undefined4 *)(param_2 + 0x99);
  uVar8 = *(undefined4 *)(param_2 + 0x9d);
  uVar6 = *(undefined4 *)(param_2 + 0xa1);
  *param_1 = *(undefined4 *)(param_2 + 0x95);
  param_1[1] = uVar9;
  param_1[2] = uVar8;
  param_1[3] = uVar6;
  uVar9 = *(undefined4 *)(param_2 + 0xa9);
  uVar8 = *(undefined4 *)(param_2 + 0xad);
  uVar6 = *(undefined4 *)(param_2 + 0xb1);
  param_1[4] = *(undefined4 *)(param_2 + 0xa5);
  param_1[5] = uVar9;
  param_1[6] = uVar8;
  param_1[7] = uVar6;
  param_1[0x11] = *(undefined4 *)(param_2 + 6);
  uVar1 = *(undefined2 *)(param_2 + 10);
  param_1[0xb] = (int)cVar2;
  param_1[0xc] = 0xffffffa1;
  *(undefined2 *)(param_1 + 0x12) = uVar1;
  return;
}

