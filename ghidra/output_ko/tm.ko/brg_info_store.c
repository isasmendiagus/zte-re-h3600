// module: tm.ko
// function: brg_info_store @ 0x71e98
// size: 2516 bytes
//

undefined4 brg_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  char *__s1;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint *puVar7;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  undefined1 local_44;
  undefined1 local_43;
  uint local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  __s1 = (char *)*param_2;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    puVar7 = &local_5c;
    sscanf(param_3,"%u %u %u %u",&local_64,&local_60,puVar7,&local_58);
    disableIRQinterrupts();
    iVar1 = strcmp(__s1,"svlancfg");
    if (iVar1 == 0) {
      uVar4 = local_64 & 0xff;
      uVar3 = local_60 & 0xffff;
      uVar2 = local_5c & 0xffff;
      puVar6 = (uint *)(local_58 & 0xff);
      iVar1 = zte_api_sw_vlan_set_port_vlancfg(uVar4,uVar3,uVar2,puVar6);
      if (iVar1 == 0) {
        printk("s_api_port_vlancfg input:port = 0x%x,minvlan = 0x%x,maxvlan = 0x%x,mode = 0x%x\n",
               uVar4,uVar3,uVar2,puVar6);
        puVar7 = puVar6;
      }
      else {
        printk("s_api_port_vlancfg failed\n");
      }
    }
    iVar1 = strcmp(__s1,"gvlancfg");
    uVar2 = local_64;
    if (iVar1 == 0) {
      iVar1 = zte_api_sw_vlan_get_port_vlancfg(local_64 & 0xffff,&local_48,&local_40);
      if (iVar1 == 0) {
        printk("g_api_port_vlancfg input:vlan = 0x%x, output:mbmask = 0x%x untagmask = 0x%x\n",uVar2
               ,local_48,local_40,puVar7);
      }
      else {
        printk("g_api_port_vlancfg failed\n");
      }
    }
    else {
      uVar2 = strcmp(__s1,"sportisolate");
      if (uVar2 == 0) {
        local_48 = uVar2;
        local_40 = uVar2;
        sscanf(param_3,"%u %x",&local_48,&local_40);
        iVar1 = zte_api_sw_port_set_port_isolatemask(local_48 & 0xff,local_40);
        if (iVar1 == 0) {
          printk("s_api_port_isolate input:port = 0x%x,portMask = 0x%x\n",local_48,local_40);
        }
        else {
          printk("s_api_port_isolate error!\n");
        }
      }
      else {
        iVar1 = strcmp(__s1,"gportisolate");
        if (iVar1 == 0) {
          local_40 = local_64;
          iVar1 = tm_port_isolate_get(local_64,&local_3c);
          if (iVar1 == 0) {
            printk("g_api_port_isolate input:p_isolateReg = %d output:p_portMsk = 0x%x\n",local_40,
                   local_3c);
          }
          else {
            printk("g_api_port_isolate fail, error code %d!\n");
          }
        }
        else {
          iVar1 = strcmp(__s1,"sportlinkmode");
          if (iVar1 == 0) {
            uVar2 = local_64 & 0xff;
            uVar3 = local_60 & 0xff;
            uVar4 = local_5c & 0xff;
            uVar5 = local_58 & 0xff;
            iVar1 = zte_api_sw_port_set_port_linkmode(uVar2,uVar3,uVar4,uVar5);
          }
          else {
            iVar1 = strcmp(__s1,"sportmirror");
            if (iVar1 != 0) {
              iVar1 = strcmp(__s1,"gportmirror");
              if (iVar1 == 0) {
                local_4c = local_4c & 0xffffff00;
                local_48 = local_48 & 0xffffff00;
                uVar2 = local_64 & 0xff;
                local_40 = local_40 & 0xffffff00;
                iVar1 = zte_api_sw_port_get_port_mirror(uVar2,&local_4c,&local_48,&local_40);
                if (iVar1 == 0) {
                  printk("g_api_port_mirror input:sport = 0x%x,output:enable = 0x%x,direct = 0x%x, dport = 0x%x\n"
                         ,uVar2,local_4c & 0xff,local_48 & 0xff,local_40 & 0xff);
                  return param_4;
                }
                printk("g_api_port_mirror error!\n");
                return param_4;
              }
              iVar1 = strcmp(__s1,"sportloopback");
              uVar4 = local_5c;
              uVar3 = local_60;
              uVar2 = local_64;
              if (iVar1 == 0) {
                iVar1 = zte_api_sw_port_set_port_loopback
                                  (local_64 & 0xff,local_60 & 0xff,local_5c & 0xff);
                if (iVar1 == 0) {
                  printk("g_api_port_lookback input:port = 0x%x,direct = 0x%x,enable = 0x%x\n",uVar2
                         ,uVar3,uVar4);
                  return param_4;
                }
              }
              else {
                iVar1 = strcmp(__s1,"gportloopback");
                uVar2 = local_64;
                if (iVar1 != 0) {
                  iVar1 = strcmp(__s1,"smacagingtime");
                  uVar2 = local_64;
                  if (iVar1 == 0) {
                    iVar1 = zte_api_sw_mac_set_onu_agingtime(local_64);
                    if (iVar1 == 0) {
                      printk("s_api_mac_agingtime input:agingtime = %d\n",uVar2);
                      return param_4;
                    }
                    printk("s_api_mac_agingtime failed\n");
                    return param_4;
                  }
                  iVar1 = strcmp(__s1,"smaclearnlimit");
                  uVar4 = local_5c;
                  uVar3 = local_60;
                  uVar2 = local_64;
                  if (iVar1 == 0) {
                    iVar1 = zte_api_sw_mac_set_port_learnlimit
                                      (local_64 & 0xff,local_60 & 0xff,local_5c);
                    if (iVar1 == 0) {
                      printk("s_api_mac_learnlimit input:port = %d,enable = %d,limit = %d\n",uVar2,
                             uVar3,uVar4);
                      return param_4;
                    }
                    printk("s_api_mac_learnlimit failed\n");
                    return param_4;
                  }
                  uVar3 = strcmp(__s1,"gmaclearnlimit");
                  uVar2 = local_64;
                  if (uVar3 == 0) {
                    local_48 = local_48 & 0xffffff00;
                    local_40 = uVar3;
                    iVar1 = zte_api_sw_mac_get_port_learnlimit(local_64 & 0xff,&local_48,&local_40);
                    if (iVar1 == 0) {
                      printk("g_api_mac_learnlimit input:port = %d,output:enable = %d,limit = %d\n",
                             uVar2,local_48 & 0xff,local_40);
                      return param_4;
                    }
                    printk("g_api_mac_learnlimit failed\n");
                    return param_4;
                  }
                  local_54 = strcmp(__s1,"macaddradd");
                  if (local_54 == 0) {
                    local_50 = local_54;
                    local_4c = local_54;
                    sscanf(param_3,"%u %x:%x:%x:%x:%x:%x %u %x",&local_54,&local_40,&local_3c,
                           &local_38,&local_34,&local_30,local_2c,&local_50,&local_4c);
                    local_48 = CONCAT13((char)local_34,
                                        CONCAT12((char)local_38,
                                                 CONCAT11((char)local_3c,(char)local_40)));
                    local_44 = (undefined1)local_30;
                    local_43 = (undefined1)local_2c[0];
                    iVar1 = zte_api_sw_mac_add_port_macaddress
                                      (local_54 & 0xff,&local_48,local_50 & 0xffff,local_4c & 0xff);
                    if (iVar1 != 0) {
                      printk("macaddr_add fail, error code %d!\n");
                      return param_4;
                    }
                    printk("macaddr_add input:   macaddr = %-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n",local_40
                           ,local_3c,local_38,local_34,local_30,local_2c[0]);
                    printk("macaddr_add input: port = %d,vlanid=%d,mode = 0x%x\n",local_54,local_50,
                           local_4c);
                    return param_4;
                  }
                  local_54 = strcmp(__s1,"macaddrdelete");
                  if (local_54 == 0) {
                    local_50 = local_54;
                    local_4c = local_54;
                    sscanf(param_3,"%u %x %x %x %x %x %x %u %x",&local_54,&local_40,&local_3c,
                           &local_38,&local_34,&local_30,local_2c,&local_50,&local_4c);
                    local_48 = CONCAT13((char)local_34,
                                        CONCAT12((char)local_38,
                                                 CONCAT11((char)local_3c,(char)local_40)));
                    local_44 = (undefined1)local_30;
                    local_43 = (undefined1)local_2c[0];
                    iVar1 = zte_api_sw_mac_del_port_macaddress
                                      (local_54 & 0xff,&local_48,local_50 & 0xffff,local_4c & 0xff);
                    if (iVar1 != 0) {
                      printk("macaddr_delete fail, error code %d!\n");
                      return param_4;
                    }
                    printk("macaddr_delete input:macaddr = %-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n",local_40
                           ,local_3c,local_38,local_34,local_30,local_2c[0]);
                    printk("macaddr_add input: port = %d,vlanid=%d,mode = %d\n",local_54,local_50,
                           local_4c);
                    return param_4;
                  }
                  iVar1 = strcmp(__s1,"smacfiltermode");
                  uVar3 = local_60;
                  uVar2 = local_64;
                  if (iVar1 == 0) {
                    iVar1 = zte_api_sw_mac_set_port_macfiltermode(local_64 & 0xff,local_60 & 0xff);
                    if (iVar1 == 0) {
                      printk("macfilter_mode input: port = %d,mode = %d\n",uVar2,uVar3);
                      return param_4;
                    }
                    printk("macfilter_mode fail, error code %d!\n");
                    return param_4;
                  }
                  local_54 = strcmp(__s1,"macfilteradd");
                  if (local_54 == 0) {
                    local_50 = local_54;
                    local_4c = local_54;
                    sscanf(param_3,"%u %x:%x:%x:%x:%x:%x %u %u",&local_54,&local_40,&local_3c,
                           &local_38,&local_34,&local_30,local_2c,&local_50,&local_4c);
                    local_48 = CONCAT13((char)local_34,
                                        CONCAT12((char)local_38,
                                                 CONCAT11((char)local_3c,(char)local_40)));
                    local_44 = (undefined1)local_30;
                    local_43 = (undefined1)local_2c[0];
                    iVar1 = zte_api_sw_mac_add_port_macfilterentry
                                      (local_54 & 0xff,&local_48,local_50 & 0xffff,local_4c & 0xff);
                    if (iVar1 != 0) {
                      printk("macfilter_add fail, error code %d!\n");
                      return param_4;
                    }
                    printk("macfilter_add input: macaddr = %-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n",local_40
                           ,local_3c,local_38,local_34,local_30,local_2c[0]);
                    printk("macfilter_add input: port = %d,vlanid=%d,mode = %d\n",local_54,local_50,
                           local_4c);
                    return param_4;
                  }
                  local_54 = strcmp(__s1,"macfilterdel");
                  if (local_54 != 0) {
                    iVar1 = strcmp(__s1,"desc");
                    if (iVar1 != 0) {
                      return param_4;
                    }
                    PrintBrgDesc(local_64 & 0xff);
                    return param_4;
                  }
                  local_50 = local_54;
                  local_4c = local_54;
                  sscanf(param_3,"%u %x:%x:%x:%x:%x:%x %u %u",&local_54,&local_40,&local_3c,
                         &local_38,&local_34,&local_30,local_2c,&local_50,&local_4c);
                  local_48 = CONCAT13((char)local_34,
                                      CONCAT12((char)local_38,
                                               CONCAT11((char)local_3c,(char)local_40)));
                  local_44 = (undefined1)local_30;
                  local_43 = (undefined1)local_2c[0];
                  iVar1 = zte_api_sw_mac_del_port_macfilterentry
                                    (local_54 & 0xff,&local_48,local_50 & 0xffff,local_4c & 0xff);
                  if (iVar1 != 0) {
                    printk("macfilter_del fail, error code %d!\n");
                    return param_4;
                  }
                  printk("macfilter_del input: macaddr = %-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n",local_40,
                         local_3c,local_38,local_34,local_30,local_2c[0]);
                  printk("macfilter_del input: port = %d,vlanid=%d,mode = %d\n",local_54,local_50,
                         local_4c);
                  return param_4;
                }
                local_48 = local_48 & 0xffffff00;
                local_40 = local_40 & 0xffffff00;
                iVar1 = zte_api_sw_port_get_port_loopback(local_64 & 0xff,&local_48,&local_40);
                if (iVar1 == 0) {
                  printk("g_api_port_lookback input:port = %d,direct = %d,enable = %d\n",uVar2,
                         local_48 & 0xff,local_40 & 0xff);
                  return param_4;
                }
              }
              printk("g_api_port_lookback error!\n");
              return param_4;
            }
            uVar2 = local_64 & 0xff;
            uVar3 = local_60 & 0xff;
            uVar4 = local_5c & 0xff;
            uVar5 = local_58 & 0xff;
            iVar1 = zte_api_sw_port_set_port_mirror(uVar2,uVar3,uVar4,uVar5);
          }
          if (iVar1 == 0) {
            printk("s_api_port_vlancfg input:port = 0x%x,minvlan = 0x%x,maxvlan = 0x%x,mode = 0x%x\n"
                   ,uVar2,uVar3,uVar4,uVar5);
          }
          else {
            printk("s_api_port_vlancfg failed\n");
          }
        }
      }
    }
  }
  return param_4;
}

