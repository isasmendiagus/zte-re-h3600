// module: mt7915.ko
// function: SetMuruCfgDlUlVal @ 0x23f880
// size: 912 bytes
//

undefined4 SetMuruCfgDlUlVal(int *param_1,char *param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  int *piVar6;
  char *local_3c [2];
  undefined4 local_34;
  byte local_30;
  byte local_2f;
  byte local_2e;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_34 = 0x51;
  if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) {
    uVar5 = *(uint *)(*param_1 + 0x3c);
    local_3c[0] = param_2;
    os_zero_mem(&local_30,4);
    pcVar2 = strsep(local_3c,":");
    if (pcVar2 == (char *)0x0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Empty Band Index !!\n","SetMuruCfgDlUlVal");
      uVar1 = 0;
    }
    else {
      local_30 = os_str_toul(pcVar2,0,10);
      uVar1 = 0;
      if (local_30 < 2) {
        pcVar2 = strsep(local_3c,":");
        if (pcVar2 == (char *)0x0) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: Empty ParamUpdList !!\n","SetMuruCfgDlUlVal");
          uVar1 = 0;
        }
        else {
          local_2f = os_str_toul(pcVar2,0,10);
          if (local_2f - 1 < 0xf) {
            pcVar2 = strsep(local_3c,"");
            if (pcVar2 == (char *)0x0) {
              if (DebugLevel < 0) {
                return 0;
              }
              printk("%s: Empty ParamUpdVal !!\n","SetMuruCfgDlUlVal");
              uVar1 = 0;
            }
            else {
              local_2e = os_str_toul(pcVar2,0,10);
              if (local_2e < 0x10) {
                piVar6 = param_1 + (uVar5 & 0xff) * 0x160d + 0xadc92;
                if ((local_2f & 1) != 0) {
                  wlan_config_set_mu_dl_ofdma(piVar6,(local_2e & 1) != 0);
                }
                if ((local_2f & 2) != 0) {
                  bVar4 = local_2e & 2;
                  if ((local_2e & 2) != 0) {
                    bVar4 = 1;
                  }
                  wlan_config_set_mu_ul_ofdma(piVar6,bVar4);
                }
                if ((local_2f & 4) != 0) {
                  bVar4 = local_2e & 4;
                  if ((local_2e & 4) != 0) {
                    bVar4 = 1;
                  }
                  wlan_config_set_mu_dl_mimo(piVar6,bVar4);
                }
                if ((local_2f & 8) != 0) {
                  bVar4 = local_2e & 8;
                  if ((local_2e & 8) != 0) {
                    bVar4 = 1;
                  }
                  wlan_config_set_mu_ul_mimo(piVar6,bVar4);
                }
                iVar3 = AndesAllocCmdMsg(param_1,8);
                if (iVar3 == 0) {
                  uVar1 = 0;
                }
                else {
                  local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
                  local_28 = CONCAT31(local_28._1_3_,10);
                  uVar1 = 1;
                  AndesInitCmdMsg(iVar3,local_2c,local_28,local_24,local_20,local_1c);
                  AndesAppendCmdMsg(iVar3,&local_34,4);
                  AndesAppendCmdMsg(iVar3,&local_30,4);
                  AndesSendCmdMsg(param_1,iVar3);
                  UpdateBeaconHandler(param_1,piVar6,2);
                }
              }
              else {
                if (DebugLevel < 0) {
                  return 0;
                }
                printk("%s: Invalid ParamUpdVal !!\n","SetMuruCfgDlUlVal");
              }
            }
          }
          else {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("%s: Invalid ParamUpdList !!\n","SetMuruCfgDlUlVal");
          }
        }
      }
      else {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: Invalid Band Index !!\n","SetMuruCfgDlUlVal");
      }
    }
    if (0 < DebugLevel) {
      printk("%s:(Ret = %d\n","SetMuruCfgDlUlVal",uVar1);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

