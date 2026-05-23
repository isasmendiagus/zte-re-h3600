// module: tm.ko
// function: adm_info_store @ 0x70c18
// size: 1308 bytes
//

undefined4 adm_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  bool bVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint uVar10;
  undefined *puVar11;
  uint local_48;
  undefined4 local_44;
  uint local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  uint local_30;
  undefined4 local_2c;
  uint local_28;
  undefined4 local_24;
  
  pcVar6 = (char *)*param_2;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  iVar2 = capable(0xc);
  if (iVar2 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    sscanf(param_3,"%d %d %d %d",&local_48,&local_44,&local_40,&local_3c);
    disableIRQinterrupts();
    iVar2 = strcmp(pcVar6,"flowStat");
    if (iVar2 == 0) {
      adm_get_pkt_stastc(local_48,local_44,&local_30);
      printk("PassPkts = %d, PassBytes = %ld\n",local_30,local_2c);
    }
    else {
      iVar2 = strcmp(pcVar6,"protPpsCfg");
      uVar5 = local_48;
      if (iVar2 == 0) {
        printk("|----------------------------------------------|\n");
        printk("|--- adm protocol packet pps ratelimit info ---|\n");
        printk("|----------------------------------------------|\n");
        printk("| %-3s| %-7s| %-6s| %-11s  %-11s|\n",&_LC81,"bktNum","bktEna","ppsRate",&_LC120);
        printk("|----------------------------------------------|\n");
        uVar3 = 0;
        bVar7 = false;
        uVar9 = 0;
        while( true ) {
          adm_get_policing_enable(bVar7,uVar9,&local_38);
          uVar10 = uVar3 - 7;
          adm_get_pass_pktcnt_persec(bVar7,uVar9,&local_34);
          puVar11 = &_LC120;
          printk("| %-3d| %-7d| %-6d| %-11d  %-11s|\n",bVar7,uVar3,local_38,local_34,&_LC120);
          uVar3 = uVar3 + 1;
          if (uVar3 == 0x10) break;
          bVar7 = 7 < uVar3;
          uVar9 = uVar10;
          if (uVar3 < 8) {
            uVar9 = uVar3;
          }
        }
        printk("|-----------------------------------------------------|\n");
        puVar8 = (undefined4 *)(dev_attr_helpBrg + 0xc);
        printk("|------- protocol packet map bucket and cpuid --------|\n");
        printk("|-----------------------------------------------------|\n");
        printk("| %-6s| %-28s| %-6s| %-6s|\n",&_LC125,"protocolTpye","cpuId","bktId",puVar11);
        printk("|-----------------------------------------------------|\n");
        iVar2 = 0;
        do {
          tm_protocol_pkt_limit_map_get(uVar5,iVar2,&local_30,uVar5 == 5);
          puVar8 = puVar8 + 1;
          iVar4 = iVar2 + 1;
          printk("| %-6d| 0x%02x:%-23s| %-6d| %-6d|\n",uVar5,iVar2,*puVar8,local_30,local_30);
          iVar2 = iVar4;
        } while (iVar4 != 0x80);
        printk("|-----------------------------------------------------|\n");
      }
      else {
        iVar2 = strcmp(pcVar6,"spqrtlmten");
        if (iVar2 == 0) {
          uVar5 = local_48 & 0xff;
          uVar3 = tm_flow_rate_limit_ena_set(uVar5);
          if (uVar3 == 0) {
            pcVar6 = "[tmtst]tm_flow_rate_limit_ena_set input: ena = %d\n";
          }
          else {
            pcVar6 = "[tmtst]tm_flow_rate_limit_ena_set fail, error code %d!\n";
            uVar5 = uVar3;
          }
          printk(pcVar6,uVar5);
        }
        else {
          iVar2 = strcmp(pcVar6,"sprotocolpktppsrate");
          local_24 = local_3c;
          uVar5 = local_40;
          local_2c = local_44;
          local_30 = local_48;
          if (iVar2 == 0) {
            __memzero(&local_30,0x10);
            local_28 = CONCAT31(local_28._1_3_,(char)uVar5);
            iVar2 = tm_protocol_pkt_limit_pps_set(local_30,local_2c,uVar5 & 0xff,local_24);
            if (iVar2 == 0) {
              printk("[tmtst]tm_protocol_pkt_limit_pps_set input: direct= %d, pps_unit = %d, pps_ena = 0x%x, pps_num = %d\n"
                     ,local_30,local_2c,local_28 & 0xff,local_24);
            }
            else {
              printk("[tmtst]tm_protocol_pkt_limit_pps_set fail, error code %d!\n");
            }
          }
          else {
            local_30 = strcmp(pcVar6,"gpktlimitpps");
            uVar1 = local_44;
            uVar5 = local_48;
            if (local_30 == 0) {
              local_34 = CONCAT31(local_34._1_3_,0x30);
              iVar2 = tm_protocol_pkt_limit_pps_get(local_48,local_44,&local_34,&local_30);
              if (iVar2 == 0) {
                printk("[tmtst]tm_protocol_pkt_limit_pps_get input: direct= %d, pps_unit = %d, pps_ena = 0x%x, pps_num = %d\n"
                       ,uVar5,uVar1,local_34 & 0xff,local_30);
              }
              else {
                printk("[tmtst]tm_protocol_pkt_limit_pps_get fail, error code %d!\n");
              }
            }
            else {
              iVar2 = strcmp(pcVar6,"sadmppsmap");
              local_28 = local_40;
              local_2c = local_44;
              local_30 = local_48;
              if (iVar2 == 0) {
                __memzero(&local_30,0xc);
                iVar2 = adm_set_protocol_pkt_map(local_30,local_2c,local_28);
                if (iVar2 == 0) {
                  printk("[tmtst]adm_set_protocol_pkt_map input: dir=%d CpuQueId = %d PpsBucketNum = %d\n"
                         ,local_30,local_2c,local_28);
                }
                else {
                  printk("[tmtst]adm_set_protocol_pkt_map fail, error code %d!\n");
                }
              }
              else {
                iVar2 = strcmp(pcVar6,"gadmindramprint");
                if (iVar2 == 0) {
                  iVar2 = adm_indirect_ram_print(local_48);
                  if (iVar2 != 0) {
                    printk("[tmtst]adm_indirect_ram_print fail, error code %d!\n");
                  }
                }
                else {
                  iVar2 = strcmp(pcVar6,"protToqCfg");
                  uVar3 = local_40;
                  uVar5 = local_48;
                  if (iVar2 == 0) {
                    iVar2 = tm_protocol_pkt_limit_map_set(local_3c,local_44,local_40,local_48);
                    if (iVar2 == 0) {
                      iVar2 = tm_protocol_pkt_limit_pps_set(uVar5,uVar3,1,0);
                      if (iVar2 != 0) {
                        printk("[pp_adm_debug]tm_protocol_pkt_limit_pps_set failed!,error code %d\n"
                              );
                      }
                    }
                    else {
                      printk("[pp_adm_debug]tm_protocol_pkt_limit_map_set failed!,error code %d\n");
                    }
                  }
                  else {
                    printk("%s: illegal operation <%s>\n","adm_info_store",*param_2);
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

