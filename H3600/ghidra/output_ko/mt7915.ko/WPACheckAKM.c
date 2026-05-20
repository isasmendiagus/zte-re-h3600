// module: mt7915.ko
// function: WPACheckAKM @ 0x11b704
// size: 760 bytes
//

bool WPACheckAKM(uint *param_1,uint *param_2,char *param_3)

{
  ushort uVar1;
  ushort *puVar2;
  int iVar3;
  char cVar4;
  ushort *__s1;
  uint uVar5;
  ushort *puVar6;
  bool bVar7;
  
  cVar4 = *param_3;
  if (cVar4 == '0') {
    puVar6 = (ushort *)(param_3 + 8);
  }
  else {
    if (cVar4 != -0x23) {
      if (-1 < DebugLevel) {
        printk("%s ==> Unknown WPAIE, WPAIE=%d\n","WPACheckAKM",cVar4);
      }
      return false;
    }
    puVar6 = (ushort *)(param_3 + 0xc);
  }
  puVar6 = puVar6 + (uint)*puVar6 * 2;
  uVar1 = puVar6[1];
  if (uVar1 == 0) {
    uVar5 = *param_2;
  }
  else {
    uVar5 = *param_2;
    puVar2 = puVar6;
    while( true ) {
      __s1 = puVar2 + 2;
      if (cVar4 == -0x23) {
        iVar3 = memcmp(__s1,&OUI_WPA_8021X_AKM,4);
        if (iVar3 == 0) {
          uVar5 = uVar5 | 8;
          *param_2 = uVar5;
        }
        else {
          iVar3 = memcmp(__s1,&OUI_WPA_PSK_AKM,4);
          if (iVar3 == 0) {
            uVar5 = uVar5 | 0x10;
            *param_2 = uVar5;
          }
        }
      }
      else if (cVar4 == '0') {
        iVar3 = memcmp(__s1,&OUI_WPA2_AKM_8021X,4);
        if (iVar3 == 0) {
          uVar5 = uVar5 | 0x40;
          *(undefined1 *)(param_2 + 0xa1) = 0;
          *param_2 = uVar5;
        }
        else {
          iVar3 = memcmp(__s1,&OUI_WPA2_AKM_PSK,4);
          if (iVar3 == 0) {
            uVar5 = uVar5 | 0x80;
            *(undefined1 *)(param_2 + 0xa1) = 0;
            *param_2 = uVar5;
          }
          else {
            iVar3 = memcmp(__s1,&OUI_WPA2_AKM_8021X_SHA256,4);
            if (iVar3 == 0) {
              uVar5 = uVar5 | 0x40;
              *param_2 = uVar5;
              *(undefined1 *)(param_2 + 0xa1) = 1;
            }
            else {
              iVar3 = memcmp(__s1,&OUI_WPA2_AKM_PSK_SHA256,4);
              if (iVar3 == 0) {
                uVar5 = uVar5 | 0x80;
                *param_2 = uVar5;
                *(undefined1 *)(param_2 + 0xa1) = 1;
              }
              else {
                iVar3 = memcmp(__s1,&OUI_WPA2_AKM_TDLS,4);
                if (iVar3 == 0) {
                  uVar5 = uVar5 | 0x1000;
                  *param_2 = uVar5;
                }
                else {
                  iVar3 = memcmp(__s1,&OUI_WPA2_AKM_SAE_SHA256,4);
                  if (iVar3 == 0) {
                    uVar5 = uVar5 | 0x2000;
                    *param_2 = uVar5;
                    *(undefined1 *)(param_2 + 0xa1) = 1;
                  }
                  else {
                    iVar3 = memcmp(__s1,&OUI_WPA2_AKM_FT_SAE_SHA256,4);
                    if (iVar3 == 0) {
                      uVar5 = uVar5 | 0x4000;
                      *param_2 = uVar5;
                      *(undefined1 *)(param_2 + 0xa1) = 1;
                    }
                    else {
                      iVar3 = memcmp(__s1,&OUI_WPA2_AKM_SUITEB_SHA256,4);
                      if (iVar3 == 0) {
                        uVar5 = uVar5 | 0x8000;
                        *param_2 = uVar5;
                        *(undefined1 *)(param_2 + 0xa1) = 1;
                      }
                      else {
                        iVar3 = memcmp(__s1,&OUI_WPA2_AKM_SUITEB_SHA384,4);
                        if (iVar3 == 0) {
                          uVar5 = uVar5 | 0x10000;
                          *param_2 = uVar5;
                          *(undefined1 *)(param_2 + 0xa1) = 2;
                        }
                        else {
                          iVar3 = memcmp(__s1,&OUI_WPA2_AKM_FT_8021X_SHA384,4);
                          if (iVar3 == 0) {
                            uVar5 = uVar5 | 0x20000;
                            *param_2 = uVar5;
                            *(undefined1 *)(param_2 + 0xa1) = 2;
                          }
                          else {
                            iVar3 = memcmp(__s1,&OUI_WPA2_AKM_OWE,4);
                            if (iVar3 == 0) {
                              uVar5 = uVar5 | 0x100000;
                              *param_2 = uVar5;
                              *(undefined1 *)(param_2 + 0xa1) = 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (puVar2 + 4 == puVar6 + 1 + (uint)(ushort)(uVar1 - 1) * 2 + 3) break;
      cVar4 = *param_3;
      puVar2 = __s1;
    }
  }
  bVar7 = (uVar5 & *param_1) == 0;
  if (bVar7) {
    *param_2 = 0;
  }
  return !bVar7;
}

