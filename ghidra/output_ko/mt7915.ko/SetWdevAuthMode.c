// module: mt7915.ko
// function: SetWdevAuthMode @ 0x112a54
// size: 796 bytes
//

void SetWdevAuthMode(undefined4 *param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  
  iVar1 = rtstrcasecmp(param_2,&_LC0);
  if ((iVar1 == 1) || (iVar1 = rtstrcasecmp(param_2,&_LC1), iVar1 == 1)) {
    uVar3 = 1;
  }
  else {
    iVar1 = rtstrcasecmp(param_2,"SHARED");
    if (iVar1 == 1) {
      uVar3 = 2;
    }
    else {
      iVar1 = rtstrcasecmp(param_2,"WEPAUTO");
      if (iVar1 == 1) {
        uVar3 = 5;
      }
      else {
        iVar1 = rtstrcasecmp(param_2,&_LC4);
        if (iVar1 == 1) {
          uVar3 = 8;
        }
        else {
          iVar1 = rtstrcasecmp(param_2,"WPAPSK");
          if (iVar1 == 1) {
            uVar3 = 0x10;
          }
          else {
            iVar1 = rtstrcasecmp(param_2,"WPANONE");
            if (iVar1 == 1) {
              uVar3 = 0x20;
            }
            else {
              iVar1 = rtstrcasecmp(param_2,&_LC7);
              if (iVar1 == 1) {
                uVar3 = 0x40;
              }
              else {
                iVar1 = rtstrcasecmp(param_2,"WPA2PSK");
                if (iVar1 == 1) {
                  uVar3 = 0x80;
                }
                else {
                  iVar1 = rtstrcasecmp(param_2,&_LC9);
                  if (iVar1 == 1) {
                    uVar3 = 0x800040;
                  }
                  else {
                    iVar1 = rtstrcasecmp(param_2,"WPA3-192");
                    if (iVar1 == 1) {
                      uVar3 = 0x10000;
                    }
                    else {
                      iVar1 = rtstrcasecmp(param_2,"WPA3PSK");
                      if (iVar1 == 1) {
                        uVar3 = 0x2000;
                      }
                      else {
                        iVar1 = rtstrcasecmp(param_2,"WPA2PSKWPA3PSK");
                        if (iVar1 == 1) {
                          uVar3 = 0x2080;
                        }
                        else {
                          iVar1 = rtstrcasecmp(param_2,"WPA1WPA2");
                          if (iVar1 == 1) {
                            uVar3 = 0x48;
                          }
                          else {
                            iVar1 = rtstrcasecmp(param_2,"WPAPSKWPA2PSK");
                            if (((((iVar1 == 1) ||
                                  (iVar1 = rtstrcasecmp(param_2,"WPA_AES_WPA2_TKIPAES"), iVar1 == 1)
                                  ) || (iVar1 = rtstrcasecmp(param_2,"WPA_AES_WPA2_TKIP"),
                                       iVar1 == 1)) ||
                                ((iVar1 = rtstrcasecmp(param_2,"WPA_TKIP_WPA2_AES"), iVar1 == 1 ||
                                 (iVar1 = rtstrcasecmp(param_2,"WPA_TKIP_WPA2_TKIPAES"), iVar1 == 1)
                                 ))) || ((iVar1 = rtstrcasecmp(param_2,"WPA_TKIPAES_WPA2_AES"),
                                         iVar1 == 1 ||
                                         ((iVar1 = rtstrcasecmp(param_2,"WPA_TKIPAES_WPA2_TKIPAES"),
                                          iVar1 == 1 ||
                                          (iVar1 = rtstrcasecmp(param_2,"WPA_TKIPAES_WPA2_TKIP"),
                                          iVar1 == 1)))))) {
                              uVar3 = 0x90;
                            }
                            else {
                              iVar1 = rtstrcasecmp(param_2,&_LC22);
                              if (iVar1 != 1) {
                                if (-1 < DebugLevel) {
                                  sVar2 = strlen(param_2);
                                  printk("%s:: Not support (AuthMode=%s, len=%d)\n",
                                         "SetWdevAuthMode",param_2,sVar2);
                                }
                                goto LAB_00112bb0;
                              }
                              uVar3 = 0x100000;
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
    }
  }
  *param_1 = uVar3;
LAB_00112bb0:
  if (DebugLevel < 3) {
    return;
  }
  printk("%s::AuthMode=0x%x\n","SetWdevAuthMode",*param_1);
  return;
}

