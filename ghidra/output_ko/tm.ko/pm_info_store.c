// module: tm.ko
// function: pm_info_store @ 0x6d4cc
// size: 1576 bytes
//

undefined4 pm_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r1;
  char *__s1;
  undefined4 *puVar2;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  uint local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  __s1 = (char *)*param_2;
  local_bc = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    puVar2 = &local_b0;
    sscanf(param_3,"%d %d %d %d %d",&local_bc,&local_b8,&local_b4,puVar2,&local_ac);
    disableIRQinterrupts();
    iVar1 = strcmp(__s1,"spmportrule");
    if (iVar1 == 0) {
      __memzero(&local_90,0xc);
      local_8c = local_bc;
      local_90 = local_b8;
      local_88 = local_b4;
      iVar1 = tm_pm_port_rule_set(&local_90);
      if (iVar1 == 0) {
        printk("tm_pm_port_rule_set input:valid = %d, direction = %d, port = %d\n",local_bc,local_b8
               ,local_b4);
      }
      else {
        printk("tm_pm_port_rule_set fail!\n");
      }
    }
    else {
      iVar1 = strcmp(__s1,"gpmportstat");
      if (iVar1 == 0) {
        __memzero(&local_a8,0xc);
        __memzero(&local_90,0x30);
        local_a8 = local_bc;
        local_a0 = local_b8;
        iVar1 = tm_pm_port_statistics_get(&local_a8,&local_90);
        if (iVar1 == 0) {
          printk("tm_pm_port_statistics_get input:direction = %d, port = %d\n",local_bc,local_b8);
          printk("tm_pm_port_statistics_get Output:\nrx_uni_octets          = %lld,\nrx_uni_packets         = %d,\nrx_multi_octets        = %lld,\nrx_multi_packets       = %d,\nrx_broad_octets        = %lld,\nrx_broad_packets       = %d\n"
                 ,local_68,local_90,local_8c,local_88,puVar2,local_80,local_7c,local_78);
        }
        else {
          printk("tm_pm_port_statistics_get fail!\n");
        }
      }
      else {
        iVar1 = strcmp(__s1,"spmg988rule");
        if (iVar1 == 0) {
          __memzero(&local_90,0x18);
          local_8c = local_8c & 0xffffff00;
          local_90 = local_bc;
          local_88 = local_b8;
          local_84 = local_b4;
          local_80 = local_b0;
          local_7c = local_ac;
          iVar1 = tm_pm_g988_rule_set(&local_90);
          if (iVar1 == 0) {
            printk("tm_pm_g988_rule_set input:valid = %d, direction = %d, in_port = %d, pri = %d, vlan_id = %d\n"
                   ,local_bc,local_b8,local_b4,local_b0,local_ac);
          }
          else {
            printk("tm_pm_g988_rule_set fail!\n");
          }
        }
        else {
          iVar1 = strcmp(__s1,"gpmg988stat");
          if (iVar1 == 0) {
            __memzero(&local_a8,0x18);
            __memzero(&local_90,0x68);
            local_a0 = local_bc;
            local_9c = local_b8;
            local_98 = local_b4;
            local_94 = local_b0;
            local_a4 = CONCAT31(local_a4._1_3_,(char)local_ac);
            iVar1 = tm_pm_g988_statistics_get(&local_a8,&local_90);
            if (iVar1 == 0) {
              printk("tm_pm_g988_statistics_get input:direction = %d, in_port = %d, pri = %d, vlan_id = %d\n"
                     ,local_bc,local_b8,local_b4,local_b0);
              printk("tm_pm_g988_statistics_get Output:\nrx_drop        = %d,\nrx_octets      = %lld,\nrx_packets     = %d,\nrx_broadcast   = %d,\nrx_multicast   = %d,\nrx_undersize   = %d,\nrx_64          = %d,\nrx_65to127     = %d,\nrx_128to255    = %d,\nrx_256to511    = %d,\nrx_512to1023   = %d,\nrx_1024to1518  = %d,\nrx_oversize    = %d\n"
                     ,extraout_r1,local_90,local_8c,local_88,local_84,local_80,local_7c,local_78,
                     local_74,local_70,local_6c,local_68,local_64,local_60,uStack_5c,local_58,
                     uStack_54,local_50,uStack_4c,local_48,uStack_44,local_40,uStack_3c,local_38,
                     uStack_34,local_30,uStack_2c);
            }
            else {
              printk("[tmtst]tm_pm_g988_statistics_get fail!\n");
            }
          }
          else {
            iVar1 = strcmp(__s1,"spmzterule");
            if (iVar1 == 0) {
              __memzero(&local_90,0x10);
              local_90 = local_bc;
              local_8c = local_b8;
              local_84 = local_b4;
              local_88 = local_b0;
              iVar1 = tm_pm_zte_rule_set(&local_90);
              if (iVar1 == 0) {
                printk("tm_pm_zte_rule_set input:valid = %d, direction = %d, port = %d, vlan_id = %d\n"
                       ,local_bc,local_b8,local_b4,local_b0);
              }
              else {
                printk("tm_pm_zte_rule_set fail!\n");
              }
            }
            else {
              iVar1 = strcmp(__s1,"gpmztestat");
              if (iVar1 == 0) {
                __memzero(&local_a8,0x10);
                __memzero(&local_90,0x38);
                local_a4 = local_bc;
                local_9c = local_b8;
                local_a0 = local_b4;
                iVar1 = tm_pm_zte_statistics_get(&local_a8,&local_90);
                if (iVar1 == 0) {
                  printk("tm_pm_zte_statistics_get input:direction = %d, port = %d, vlan_id = %d\n",
                         local_bc,local_b8,local_b4);
                  printk("tm_pm_zte_statistics_get Output:\nrx_packets        = %d,\nrx_octets         = %lld,\nrx_drop           = %d,\nrx_adm_drop       = %d,\nrx_bp_drop        = %d,\nrx_pppoe_drop     = %d,\nrx_brg_drop       = %d,\nrx_age_drop       = %d,\nrx_cla_drop       = %d,\nrx_spa_drop       = %d,\nrx_total_forward  = %d\n"
                         ,local_90,local_88,local_84,local_80,local_7c,local_78,local_74,local_70,
                         local_6c,local_68,local_64,local_60);
                }
                else {
                  printk("tm_pm_zte_statistics_get fail!\n");
                }
              }
              else {
                iVar1 = strcmp(__s1,"spmflowrule");
                if (iVar1 == 0) {
                  __memzero(&local_90,0x10);
                  local_90 = local_bc;
                  local_8c = local_b8;
                  local_88 = local_b4;
                  local_84 = local_b0;
                  iVar1 = tm_pm_flow_rule_set(&local_90);
                  if (iVar1 == 0) {
                    printk("tm_pm_flow_rule_set input:pkt_len_sel = %d, read_clear_en = %d, cnt_mode = %d, fwd_only_en = %d\n"
                           ,local_bc,local_b8,local_b4,local_b0);
                  }
                  else {
                    printk("tm_pm_flow_rule_set fail!\n");
                  }
                }
                else {
                  iVar1 = strcmp(__s1,"spmflowstaen");
                  if (iVar1 == 0) {
                    iVar1 = tm_pm_flow_sta_en_set(local_bc);
                    if (iVar1 == 0) {
                      printk("tm_pm_flow_sta_en_set input:flow_sta_en = %d\n",local_bc);
                    }
                    else {
                      printk("tm_pm_flow_sta_en_set fail!\n");
                    }
                  }
                  else {
                    iVar1 = strcmp(__s1,"gpmflowstat");
                    if (iVar1 == 0) {
                      __memzero(&local_90,0x10);
                      iVar1 = tm_pm_flow_statistics_get(local_bc,&local_90);
                      if (iVar1 == 0) {
                        printk("tm_pm_flow_statistics_get input:flow_id = %d\n",local_bc);
                        printk("tm_pm_flow_statistics_get Output:\nrx_packets        = %d,\nrx_octets         = %lld\n"
                               ,local_90,local_88,local_84);
                      }
                      else {
                        printk("[tmtst]tm_pm_flow_statistics_get fail!\n");
                      }
                    }
                    else {
                      printk("%s: illegal operation <%s>\n","pm_info_store",*param_2);
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

