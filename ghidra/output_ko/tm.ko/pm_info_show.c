// module: tm.ko
// function: pm_info_show @ 0x6e528
// size: 696 bytes
//

int pm_info_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *__s1;
  
  __s1 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = strcmp(__s1,"helppm");
    if (iVar1 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands[HEX]\n");
      printk("============================================================================\n");
      printk(
            " echo [valid][mode 0:in_port;1:out_port][port]                    > spmportrule       - set pm port rule value\n"
            );
      printk(
            " echo [mode 0:in_port;1:out_port][port]                           > gpmportstat       - get pm port statistics by port rule\n"
            );
      printk(
            " echo [valid][dir 0:up;1:dn][port][pri:0-7][vlan]                 > spmg988rule       - set pm g988 rule value\n"
            );
      printk(
            " echo [dir 0:up;1:dn][port][pri:0-7][vlan]                        > gpmg988stat       - get pm g988 statistics by g988 rule\n"
            );
      printk(
            " echo [valid][dir 0:up;1:dn][port][vlan]                          > spmzterule        - set pm zte rule value\n"
            );
      printk(
            " echo [dir 0:up;1:dn][port][vlan]                                 > gpmztestat        - get pm zte statistics by zte rule\n"
            );
      printk(
            " echo [pkt_len_sel][read_clear_en][cnt_mode][fwd_only_en]         > spmflowrule       - set pm flow rule value\n"
            );
      printk(
            " echo [flowen]                                                    > spmflowstaen      - set pm flow statistics enable\n"
            );
      printk(
            " echo [flow_id]                                                   > gpmflowstat       - get pm flow statistics by flow rule\n"
            );
      printk("============================================================================\n");
      printk("Display Commands: cat <file>\n");
      printk("============================================================================\n");
      printk(" cat helppm                    - display pm command help\n");
      printk(" cat gportstat                 - get pm port statistics\n");
      printk(" cat gg988stat                 - get pm g988 statistics\n");
      printk(" cat gztestat                  - get pm zte statistics\n");
      printk(" cat gpmstat                   - get pm all config\n");
      return 0;
    }
    iVar1 = strcmp(__s1,"gportstat");
    if (iVar1 == 0) {
      iVar1 = pm_port_stat_print();
      if (iVar1 != 0) {
        printk("pm_port_stat_print fail, error code %d!\n");
        return iVar1;
      }
      printk("[pm_port_stat_print success!\n ");
      return 0;
    }
    iVar1 = strcmp(__s1,"gg988stat");
    if (iVar1 == 0) {
      iVar1 = pm_g988_stat_print();
      if (iVar1 == 0) {
        printk("pm_g988_stat_print success!\n ");
        iVar1 = 0;
      }
      else {
        printk("pm_g988_stat_print fail, error code %d!\n");
      }
    }
    else {
      iVar1 = strcmp(__s1,"gztestat");
      if (iVar1 == 0) {
        iVar1 = pm_zte_stat_print();
        if (iVar1 == 0) {
          printk("pm_zte_stat_print success!\n ");
          iVar1 = 0;
        }
        else {
          printk("pm_zte_stat_print fail, error code %d!\n");
        }
      }
      else {
        iVar1 = strcmp(__s1,"gpmstat");
        if (iVar1 == 0) {
          iVar1 = pm_port_stat_print();
          iVar2 = pm_g988_stat_print();
          iVar3 = pm_zte_stat_print();
          if ((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) {
            printk("pm_stat_print success!\n ");
            return 0;
          }
          if (6 < g_tm_debug_level) {
            printk("pm_stat_print failed!\n");
          }
          iVar1 = -1;
          printk("pm_stat_print fail, error code %d!\n");
        }
        else {
          printk("%s: illegal operation <%s>\n","pm_info_show",*param_2);
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}

