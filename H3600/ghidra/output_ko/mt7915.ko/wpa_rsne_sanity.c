// module: mt7915.ko
// function: wpa_rsne_sanity @ 0x11ba34
// size: 1168 bytes
//

undefined4 wpa_rsne_sanity(char *param_1,int param_2,undefined1 *param_3)

{
  char cVar1;
  ushort *puVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  uVar6 = (uint)(byte)param_1[1];
  if (uVar6 + 2 == param_2) {
    if (uVar6 < 2) {
      if (-1 < DebugLevel) {
        printk("[ERROR]%s : len is too short(len = %d) !!!\n","wpa_rsne_sanity",uVar6);
        return 0;
      }
    }
    else {
      cVar1 = *param_1;
      if (cVar1 == '0') {
        psVar3 = (short *)(param_1 + 2);
        uVar7 = 2;
        iVar5 = 0;
      }
      else {
        if (cVar1 != -0x23) {
          if (cVar1 == 'D') {
            return 1;
          }
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[ERROR]%s : invalid IE=%d\n","wpa_rsne_sanity");
          return 0;
        }
        if (uVar6 < 6) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[ERROR]%s : no version(len = %d)\n","wpa_rsne_sanity",uVar6);
          return 0;
        }
        psVar3 = (short *)(param_1 + 6);
        uVar7 = 6;
        iVar5 = 4;
      }
      if (*psVar3 == 1) {
        if (uVar6 == uVar7) {
          *param_3 = 0;
          return 1;
        }
        if (uVar6 < iVar5 + 6U) {
          if (-1 < DebugLevel) {
            printk("[ERROR]%s : group cipher is truncated(len = %d)\n","wpa_rsne_sanity",uVar6);
            return 0;
          }
        }
        else {
          if (uVar6 == iVar5 + 6U) {
            *param_3 = 1;
            return 1;
          }
          if (uVar6 < iVar5 + 8U) {
            if (-1 < DebugLevel) {
              printk("[ERROR]%s :  pairwise cipher suite cnt is truncated(%d)\n","wpa_rsne_sanity",
                     uVar6);
              return 0;
            }
          }
          else {
            puVar2 = (ushort *)(psVar3 + 3);
            uVar7 = iVar5 + 8U + (uint)*puVar2 * 4 & 0xff;
            if (uVar6 < uVar7) {
              if (-1 < DebugLevel) {
                printk("[ERROR]%s : Pairwise Cipher Suite is truncated(len %d)\n","wpa_rsne_sanity",
                       uVar6);
                return 0;
              }
            }
            else {
              if (uVar6 == uVar7) {
                *param_3 = 2;
                return 1;
              }
              uVar7 = uVar7 + 2 & 0xff;
              if (uVar6 < uVar7) {
                if (-1 < DebugLevel) {
                  printk("[ERROR]%s :  akm suite cnt is truncated(%d)\n","wpa_rsne_sanity",uVar6);
                  return 0;
                }
              }
              else {
                uVar4 = (uint)puVar2[(uint)*puVar2 * 2 + 1];
                uVar7 = uVar7 + uVar4 * 4 & 0xff;
                if (uVar6 < uVar7) {
                  if (-1 < DebugLevel) {
                    printk("[ERROR]%s : Akm Suite is truncated(len %d)\n","wpa_rsne_sanity",uVar6);
                    return 0;
                  }
                }
                else {
                  if (uVar6 == uVar7) {
                    *param_3 = 3;
                    return 1;
                  }
                  uVar8 = uVar7 + 2 & 0xff;
                  if (uVar6 < uVar8) {
                    if (-1 < DebugLevel) {
                      printk("[ERROR]%s : RSN capabilities is truncated(len %d)\n","wpa_rsne_sanity"
                             ,uVar6);
                      return 0;
                    }
                  }
                  else {
                    if (uVar6 == uVar8) {
                      *param_3 = 4;
                      return 1;
                    }
                    uVar7 = uVar7 + 4 & 0xff;
                    if (uVar6 < uVar7) {
                      if (-1 < DebugLevel) {
                        printk("[ERROR]%s :  pmkid cnt is truncated(%d)\n","wpa_rsne_sanity",uVar6);
                        return 0;
                      }
                    }
                    else {
                      uVar7 = uVar7 + (uint)(puVar2 + (uint)*puVar2 * 2 + 1)[uVar4 * 2 + 2] * 0x10 &
                              0xff;
                      if (uVar6 < uVar7) {
                        if (-1 < DebugLevel) {
                          printk("[ERROR]%s : PMKID is truncated(len %d)\n","wpa_rsne_sanity",uVar6)
                          ;
                          return 0;
                        }
                      }
                      else {
                        if (uVar6 == uVar7) {
                          *param_3 = 5;
                          return 1;
                        }
                        uVar7 = uVar7 + 4 & 0xff;
                        if (uVar7 <= uVar6) {
                          if (uVar6 == uVar7) {
                            *param_3 = 6;
                            return 1;
                          }
                          if (2 < DebugLevel) {
                            printk("%s : extensible element len %d\n","wpa_rsne_sanity",
                                   uVar6 - uVar7);
                          }
                          *param_3 = 7;
                          return 1;
                        }
                        if (-1 < DebugLevel) {
                          printk("[ERROR]%s : Group Management Cipher Suite is truncated(len %d)\n",
                                 "wpa_rsne_sanity",uVar6);
                          return 0;
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
      else if (-1 < DebugLevel) {
        printk("[ERROR]%s : unknown version(%d)\n","wpa_rsne_sanity",*psVar3);
        return 0;
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("[ERROR]%s : the len is invalid !!!\n","wpa_rsne_sanity");
  }
  return 0;
}

