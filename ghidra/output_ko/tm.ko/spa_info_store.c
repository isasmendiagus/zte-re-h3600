// module: tm.ko
// function: spa_info_store @ 0x6ecd8
// size: 1788 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 spa_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  char *__s1;
  uint uVar3;
  uint uVar4;
  undefined1 local_51;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  undefined4 local_40;
  undefined2 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  uint local_28 [4];
  
  __s1 = (char *)*param_2;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    sscanf(param_3,"%d %d %d",&local_50,&local_4c,&local_48);
    disableIRQinterrupts();
    iVar1 = strcmp(__s1,"svlaninframemode");
    if (iVar1 == 0) {
      uVar3 = local_50 & 0xff;
      uVar2 = local_4c & 0xff;
      iVar1 = zte_api_sw_vlan_set_port_inframemode(uVar3,uVar2);
      if (iVar1 == 0) {
        printk("s_api_vlan_inframemode input:p_port =0x%x,p_mode =0x%x\n",uVar3,uVar2);
      }
      else {
        printk("s_api_vlan_inframemode fail\n");
      }
    }
    else {
      iVar1 = strcmp(__s1,"gvlaninframemode");
      if (iVar1 == 0) {
        local_44 = local_44 & 0xffffff00;
        uVar2 = local_50 & 0xff;
        iVar1 = zte_api_sw_vlan_get_port_inframemode(uVar2);
        if (iVar1 == 0) {
          printk("g_api_vlan_inframemode input:p_port = 0x%x,output:p_mode = 0x%x\n",uVar2,
                 local_44 & 0xff);
        }
        else {
          printk("g_api_vlan_inframemode fail\n");
        }
      }
      else {
        iVar1 = strcmp(__s1,"sportpvid");
        if (iVar1 == 0) {
          uVar4 = local_50 & 0xff;
          uVar3 = local_4c & 0xffff;
          uVar2 = local_48 & 0xff;
          iVar1 = zte_api_sw_vlan_set_port_pvid(uVar4,uVar3,uVar2);
          if (iVar1 == 0) {
            printk("s_api_port_pvid input:p_port = 0x%x,p_pvid = 0x%x,p_pri = 0x%x\n",uVar4,uVar3,
                   uVar2);
          }
          else {
            printk("s_api_port_pvid fail, error code %d!\n");
          }
        }
        else {
          iVar1 = strcmp(__s1,"gportpvid");
          if (iVar1 == 0) {
            local_44 = local_44 & 0xffff0000;
            local_51 = 0;
            uVar2 = local_50 & 0xff;
            iVar1 = zte_api_sw_vlan_get_port_pvid(uVar2,&local_44,&local_51);
            if (iVar1 == 0) {
              printk("g_api_port_pvid input:p_port = 0x%x output:p_pvid = 0x%x,p_pri = 0x%x\n",uVar2
                     ,local_44 & 0xffff,local_51);
            }
            else {
              printk("g_api_port_pvid fail, error code %d!\n");
            }
          }
          else {
            uVar2 = strcmp(__s1,"sstpaction");
            if (uVar2 == 0) {
              local_40 = local_40 & 0xffff0000;
              uVar3 = local_50 & 0xff;
              local_44 = uVar2;
              iVar1 = zte_api_sw_mac_set_onu_stpaction(0,&local_44,uVar3);
              if (iVar1 == 0) {
                printk("s_api_stp_action,input:action = %d\n",uVar3);
              }
              else {
                printk("s_api_stp_action failed\n");
              }
            }
            else {
              iVar1 = strcmp(__s1,"sproaction");
              if (iVar1 == 0) {
                uVar3 = local_50 & 0xff;
                uVar2 = local_4c & 0xff;
                iVar1 = zte_api_sw_mac_set_onu_proaction(uVar3,uVar2);
                if (iVar1 == 0) {
                  printk("s_api_pro_action,input:protocol_type = %d,action =%d\n",uVar3,uVar2);
                }
                else {
                  printk("s_api_pro_action failed\n");
                }
              }
              else {
                iVar1 = strcmp(__s1,"sportvlanfilter");
                uVar3 = local_4c;
                uVar2 = local_50;
                if (iVar1 == 0) {
                  iVar1 = tm_port_vlan_filter_set(local_50,local_4c);
                  if (iVar1 == 0) {
                    printk("s_api_port_vlan_filter input:p_port = 0x%x,p_vlTagMsk = 0x%x\n",uVar2,
                           uVar3);
                  }
                  else {
                    printk("s_api_port_vlan_filter fail, error code %d!\n");
                  }
                }
                else {
                  iVar1 = strcmp(__s1,"gportvlanfilter");
                  if (iVar1 == 0) {
                    local_44 = local_50;
                    iVar1 = tm_port_vlan_filter_get(local_50,&local_40);
                    if (iVar1 == 0) {
                      printk("g_api_port_vlan_filter input:p_port = %d output:p_vlTagMsk = 0x%x\n",
                             local_44,local_40);
                    }
                    else {
                      printk("g_api_port_vlan_filter fail, error code %d!\n");
                    }
                  }
                  else {
                    iVar1 = strcmp(__s1,"sportpktfilter");
                    uVar3 = local_4c;
                    uVar2 = local_50;
                    if (iVar1 == 0) {
                      iVar1 = tm_port_pkt_filter_set(local_50,local_4c);
                      if (iVar1 == 0) {
                        printk("s_api_port_pkt_filter input:p_port = 0x%x,pkttype = 0x%x\n",uVar2,
                               uVar3);
                      }
                      else {
                        printk("s_api_port_pkt_filter fail, error code %d!\n");
                      }
                    }
                    else {
                      iVar1 = strcmp(__s1,"gportpktfilter");
                      if (iVar1 == 0) {
                        local_44 = local_50;
                        iVar1 = tm_port_pkt_filter_get(local_50,&local_40);
                        if (iVar1 == 0) {
                          printk("g_api_port_pkt_filter input:p_port =0x%x output:p_pkttype = %d\n",
                                 local_44,local_40);
                        }
                        else {
                          printk("g_api_port_pkt_filter fail, error code %d!\n");
                        }
                      }
                      else {
                        iVar1 = strcmp(__s1,"sbpdupass802x");
                        uVar2 = local_50;
                        if (iVar1 == 0) {
                          uVar3 = local_4c & 0xff;
                          iVar1 = tm_port_bpdu_pass802x_set(local_50,uVar3);
                          if (iVar1 == 0) {
                            printk("s_api_bpdu_pass802x input :port = %d,en = %d\n",uVar2,uVar3);
                            return param_4;
                          }
                        }
                        else {
                          iVar1 = strcmp(__s1,"gbpdupass802x");
                          if (iVar1 != 0) {
                            iVar1 = strcmp(__s1,"s802xtrap");
                            uVar2 = local_50;
                            if (iVar1 == 0) {
                              uVar3 = local_4c & 0xff;
                              iVar1 = tm_port_802x_trap_set(local_50,uVar3);
                              if (iVar1 == 0) {
                                printk("s_api_802x_trap input :port = %d,en = %d\n",uVar2,uVar3);
                                return param_4;
                              }
                              printk("s_api_802x_trap fail, error code %d!\n");
                              return param_4;
                            }
                            iVar1 = strcmp(__s1,"g802xtrap");
                            if (iVar1 == 0) {
                              local_44 = local_50;
                              iVar1 = tm_port_802x_trap_get(local_50,&local_40);
                              if (iVar1 == 0) {
                                printk("g_api_802x_trap input :port = %d output :en = %d\n",local_44
                                       ,local_40 & 0xff);
                                return param_4;
                              }
                              printk("g_api_802x_trap fail, error code %d!\n");
                              return param_4;
                            }
                            iVar1 = strcmp(__s1,"sonerule");
                            if (iVar1 == 0) {
                              sscanf(param_3,"%x %x %x %x %x %x %x %x",&local_38,&local_34,&local_30
                                     ,&local_2c,local_28,local_28 + 1,local_28 + 2,local_28 + 3);
                              local_44 = CONCAT13((char)local_2c,
                                                  CONCAT12((char)local_30,
                                                           CONCAT11((char)local_34,(char)local_38)))
                              ;
                              local_40 = CONCAT22((short)local_28[2],
                                                  CONCAT11((char)local_28[1],(char)local_28[0]));
                              local_3c = (undefined2)local_28[3];
                              spa_set_matchram(&local_44);
                              return param_4;
                            }
                            iVar1 = strcmp(__s1,"sonehashramentry");
                            if (iVar1 != 0) {
                              return param_4;
                            }
                            sscanf(param_3,"%x %x %x %x %x",&local_38,&local_34,&local_30,&local_2c,
                                   local_28);
                            local_44._0_2_ = (ushort)((byte)local_34 & 3);
                            uVar2 = local_40 >> 8;
                            local_44 = (uint)(ushort)((ushort)local_44 |
                                                     (ushort)((local_30 & 0x7f) << 2));
                            local_44 = local_44 | local_2c << 9;
                            local_40._0_2_ =
                                 CONCAT11((byte)uVar2 & 0xfc | (byte)(local_2c >> 0x1f) |
                                          (byte)((local_28[0] & 1) << 1),(char)(local_2c >> 0x17));
                            spa_set_hashram(local_38,&local_44);
                            return param_4;
                          }
                          local_44 = local_50;
                          iVar1 = tm_port_bpdu_pass802x_get(local_50,&local_40);
                          if (iVar1 == 0) {
                            printk("g_api_bpdu_pass802x input :port = %d output :en = %d\n",local_44
                                   ,local_40 & 0xff);
                            return param_4;
                          }
                        }
                        printk("s_api_bpdu_pass802x fail, error code %d!\n");
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
  return param_4;
}

