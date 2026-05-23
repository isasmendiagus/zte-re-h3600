// module: tm.ko
// function: brg_info_show @ 0x728a0
// size: 4184 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int brg_info_show(undefined4 param_1,undefined4 *param_2,char *param_3)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  char *__s1;
  int iVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  int *piVar15;
  int *piVar16;
  uint uVar17;
  uint uVar18;
  byte local_4c;
  byte local_4b;
  byte local_4a;
  byte local_49;
  undefined4 local_48;
  char *apcStack_44 [4];
  char *local_34;
  char *pcStack_30;
  char *pcStack_2c;
  
  local_48 = 0;
  __s1 = (char *)*param_2;
  sscanf(param_3,"%u",&local_48);
  iVar2 = capable(0xc);
  if (iVar2 == 0) {
    iVar2 = -1;
  }
  else {
    iVar2 = strcmp(__s1,"helpBrg");
    if (iVar2 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands[HEX]\n");
      printk("============================================================================\n");
      printk(
            " echo [port][autoneg][speed 0:10M;1:100M;2:1000M][duplex]         > sportlinkmode     - set port linkmode\n"
            );
      printk(
            " echo [port][minvlan][maxvlan][mode 0:tag;1:untag;2:notm;3:nochg] > svlancfg          - set port vlancfg\n"
            );
      printk(
            " echo [vlan]                                                      > gvlancfg          - set port vlancfg\n"
            );
      printk(
            " echo [sport][enable][dir 0:up;1:dn][dport]                       > sportmirror       - set port mirror\n"
            );
      printk(
            " echo [port]                                                      > gportmirror       - get port mirror\n"
            );
      printk(
            " echo [port][dir 0:up;1:dn][enable]                               > sportlookback     - set port lookback\n"
            );
      printk(
            " echo [port]                                                      > sportlookback     - get port lookback\n"
            );
      printk(
            " echo [port][portmask bit0=1:uni0 isolate;...]                    > sportisolate      - set port isolate\n"
            );
      printk(
            " echo [port]                                                      > gportisolate      - get port isolate\n"
            );
      printk(
            " echo [time]                                                      > smacagingtime     - set mac agingtime\n"
            );
      printk(
            " echo [port][enable][limit]                                       > smaclearnlimit    - set mac learn limit\n"
            );
      printk(
            " echo [port]                                                      > gmaclearnlimit    - get mac learn limit\n"
            );
      printk(
            " echo [port][mac0:mac1:mac2:mac3:mac4:mac5][vid][mode]            > macaddradd        - add port mac address\n"
            );
      printk(
            " echo [port][mac0:mac1:mac2:mac3:mac4:mac5][vid][mode]            > macaddrdelete     - del port mac address\n"
            );
      printk(
            " echo [port][mode]                                                > smacfiltermode    - set port mac filtermode\n"
            );
      printk(
            " echo [port][mac0:mac1:mac2:mac3:mac4:mac5][vid][mode]            > macfilteradd      - add port mac filterentry\n"
            );
      printk(
            " echo [port][mac0:mac1:mac2:mac3:mac4:mac5][vid][mode]            > macfilterdel      - del port mac filterentry\n"
            );
      printk(
            "echo  [en]                                                        > brgdesc           - 0 print ingress desc 1 print egress desc"
            );
      printk("============================================================================\n");
      printk("Display Commands: cat <file>\n");
      printk("============================================================================\n");
      printk(" cat helpBrg                                       - display brg command help\n");
      printk(" cat statics                                       - dump printing options\n");
      printk(" cat PortInfo                                      - dump printing options\n");
      printk(" cat macTable                                      - dump printing options\n");
      printk(" cat macTableClear                                 - clear mac table\n");
      printk(" cat v4Table                                       - dump printing options\n");
      printk(" cat v6Table                                       - dump printing options\n");
      printk(" cat vlanTable                                     - dump printing options\n");
      printk(" cat multTransTable                                - dump printing options\n");
      printk(" cat brdTransTable                                 - dump printing options\n");
      printk(" cat gmacagingtime                                 - dump printing options\n");
      printk(" cat portStatus                                    - dump printing options\n");
      printk(" cat portStat                                      - dump printing options\n");
      return 0;
    }
    iVar2 = strcmp(__s1,"statics");
    if (iVar2 == 0) {
      iVar2 = brgDebugStatics();
      return iVar2;
    }
    iVar2 = strcmp(__s1,"PortInfo");
    if (iVar2 == 0) {
      printk("bit0:UNI0;bit1:UNI1;bit2:UNI2;......\n");
      printk("-------------------------------------\n");
      printk("VLAN CHECK INFO:\n");
      uVar3 = fpga_read_reg(0xe2002);
      printk("addr 0x6/e2002 : 0x%08x\n",uVar3);
      printk("inport vlan check value(0-7)   :0x%x\n",uVar3 & 0xff);
      printk("outport vlan check value(8-15) :0x%x\n",(uVar3 << 0x10) >> 0x18);
      printk("-------------------------------------\n");
      printk("SMAC LEARN INFO:\n");
      uVar3 = fpga_read_reg(0xe2070);
      printk("addr 0x6/e2070: 0x%08x\n",uVar3);
      printk("sa look fail ctrl(0:pass;1:drop): 0x%x\n",(uVar3 << 0x10) >> 0x18);
      printk("sa look enable                  : 0x%x\n",uVar3 & 0xff);
      uVar6 = fpga_read_reg(0xe2071);
      printk("addr 0x6/e2071: 0x%08x\n",uVar6);
      printk("sa learn mode 0x%08x:00-not learn;01-hd learn;10-trap;11-copy\n",uVar6);
      iVar2 = 0xe2075;
      iVar12 = 0xe2080;
      do {
        uVar3 = fpga_read_reg(iVar2);
        iVar11 = iVar2 + 1;
        printk("addr 0x%x: 0x%08x --- port %d mac limit count %d\n",iVar2,uVar3,iVar2 + -0xe2075,
               uVar3 & 0xfff);
        uVar3 = fpga_read_reg(iVar12);
        printk("addr 0x%x: 0x%08x --- port %d curt mac learn count %d\n",iVar12,uVar3,
               iVar2 + -0xe2075,uVar3 & 0xfff);
        iVar2 = iVar11;
        iVar12 = iVar12 + 1;
      } while (iVar11 != 0xe207d);
      printk("-------------------------------------\n");
      printk("DMAC LOOK INFO:\n");
      uVar3 = fpga_read_reg(0xe20b0);
      printk("addr 0xe20b0: 0x%08x\n",uVar3);
      printk("port dmac look enable(0-7) 0x%x\n",uVar3 & 0xff);
      printk("-------------------------------------\n");
      printk("PKT FLOOD CTRL INFO:\n");
      uVar3 = fpga_read_reg(0xe20d1);
      printk("addr 0x6/e20d1: 0x%08x\n",uVar3);
      printk("unknown unicast pkt form pon enabled flood to port: 0x%x\n",uVar3 & 0xff);
      uVar3 = fpga_read_reg(0xe20d0);
      printk("addr 0x6/e20d0: 0x%08x\n",uVar3);
      printk("unicast pkt from port 0x%x ctrl(1:enable look da;0:drop)\n",uVar3 & 0xff);
      printk("unknown unicast pkt from port action: 0x%x(00:drop;01:flood;10:cpy&flodd;11:trap))\n",
             (uVar3 << 8) >> 0x10);
      printk("unknown unicast pkt enabled forward to port: 0x%x\n",uVar3 >> 0x18);
      uVar3 = fpga_read_reg(0xe20c0);
      printk("addr 0x6/e20c0: 0x%08x\n",uVar3);
      printk("brd pkt form port 0x%x enabled flood\n",uVar3 & 0xff);
      printk("brd pkt enabled forward to port: 0x%x\n",(uVar3 << 0x10) >> 0x18);
      uVar3 = fpga_read_reg(0xe20c1);
      printk("addr 0x6/e20c1: 0x%08x\n",uVar3);
      printk("brd pkt form PON enabled flood to port: 0x%x\n",uVar3 & 0xff);
      uVar3 = fpga_read_reg(0xe20b5);
      printk("addr 0x6/e20b5: 0x%08x\n",uVar3);
      printk("multicast pkt from port 0x%x ctrl(1:enable look multitable;0:drop)\n",uVar3 & 0xff);
      printk("unknown multicast pkt from port 0x%x enable flood\n",(uVar3 << 0x10) >> 0x18);
      printk("unknown multicast pkt enabled forward to port 0x%x\n",(uVar3 << 8) >> 0x18);
      iVar2 = 0;
      do {
        uVar1 = fpga_read_reg(iVar2 + 0xe20b6);
        iVar12 = iVar2 + 1;
        printk("unknown mutli pkt from port %d enabled flood to port 0x%x\n",iVar2,uVar1);
        iVar2 = iVar12;
      } while (iVar12 != 8);
      printk("-------------------------------------\n");
      printk("VLAN TRANSLATE CONFIG INFO:\n");
      uVar3 = fpga_read_reg(0xe218e);
      printk("addr 0x6/e218e: 0x%08x\n",uVar3);
      printk("multi vlan trans table look fail ctrl(0:fwd;1:drop): 0x%x\n",uVar3 & 0xff);
      uVar3 = fpga_read_reg(0xe218f);
      printk("addr 0x6/e218f: 0x%08x\n",uVar3);
      printk("brdcast vlan trans table look fail ctrl(00:drop;01:do engress vlan check;10:fwd): 0x%x\n"
             ,uVar3 & 0xffff);
      printk("unicast vlan trans table look fail ctrl(00:drop;01:do engress vlan check;10:fwd): 0x%x\n"
             ,uVar3 >> 0x10);
      printk("-------------------------------------\n");
      printk("PKT CONFIG INFO:\n");
      uVar3 = fpga_read_reg(0xe20e0);
      printk("addr 0x6/e20e0: 0x%08x\n",uVar3);
      printk("transparent port 0x%x\n",uVar3 & 0xff);
      iVar2 = 0xe20f0;
      do {
        uVar3 = fpga_read_reg(iVar2);
        iVar12 = iVar2 + 1;
        printk("addr 0x%x: 0x%08x --- port %d isolate port %d\n",iVar2,uVar3,iVar2 + -0xe20f0,
               uVar3 & 0xff);
        iVar2 = iVar12;
      } while (iVar12 != 0xe20f8);
      printk("-------------------------------------\n");
      iVar2 = 0;
    }
    else {
      iVar2 = strcmp(__s1,"macTable");
      uVar6 = g_tm_debug_level;
      if (iVar2 == 0) {
        iVar2 = 1;
        g_tm_debug_level = 7;
        sbrg_print_mactable();
        g_tm_debug_level = uVar6;
      }
      else {
        iVar2 = strcmp(__s1,"macTableClear");
        if (iVar2 == 0) {
          zte_api_sw_mac_clear_macaddress();
          iVar2 = 1;
        }
        else {
          iVar2 = strcmp(__s1,"v4Table");
          uVar6 = g_tm_debug_level;
          if (iVar2 == 0) {
            iVar2 = 1;
            g_tm_debug_level = 7;
            sbrg_print_ipv4table();
            g_tm_debug_level = uVar6;
          }
          else {
            iVar2 = strcmp(__s1,"v6Table");
            uVar6 = g_tm_debug_level;
            if (iVar2 == 0) {
              iVar2 = 1;
              g_tm_debug_level = 7;
              sbrg_print_ipv6table();
              g_tm_debug_level = uVar6;
            }
            else {
              iVar2 = strcmp(__s1,"vlanTable");
              uVar6 = g_tm_debug_level;
              if (iVar2 == 0) {
                iVar2 = 1;
                g_tm_debug_level = 7;
                sbrg_print_vltbl();
                g_tm_debug_level = uVar6;
              }
              else {
                iVar2 = strcmp(__s1,"multTransTable");
                if (iVar2 == 0) {
                  iVar2 = tm_multicst_vltrans_table_print_get();
                  if (iVar2 != 0) {
                    printk("multicast_vlantrans_table_print fail, error code %d!\n");
                    return 1;
                  }
                }
                else {
                  iVar2 = strcmp(__s1,"brdTransTable");
                  if (iVar2 == 0) {
                    iVar2 = tm_broadcst_vltrans_table_print_get();
                    if (iVar2 != 0) {
                      printk("broadcast_vlantrans_table_print fail, error code %d!\n");
                      return 1;
                    }
                  }
                  else {
                    iVar2 = strcmp(__s1,"portStatus");
                    if (iVar2 != 0) {
                      iVar2 = strcmp(__s1,"portStat");
                      if (iVar2 == 0) {
                        piVar4 = (int *)kmem_cache_alloc(_DAT_000df0f8,0xd0);
                        if (piVar4 == (int *)0x0) {
                          printk("SW BRG err: brgShowPortStatics alloc mem failed\n");
                          return -1;
                        }
                        piVar5 = (int *)kmem_cache_alloc(_DAT_000df0f8,0xd0);
                        if (piVar5 == (int *)0x0) {
                          printk("SW BRG err: brgShowPortStatics alloc mem failed\n");
                          kfree(piVar4);
                          return -1;
                        }
                        __memzero(piVar4,0x208);
                        __memzero(piVar5,600);
                        iVar2 = 0;
                        piVar15 = piVar5;
                        piVar16 = piVar4;
                        do {
                          *piVar16 = iVar2;
                          *piVar15 = iVar2;
                          iVar2 = iVar2 + 1;
                          tm_smac_statistics3(piVar16);
                          tm_smac_statistics1(piVar15);
                          piVar16 = piVar16 + 0x1a;
                          piVar15 = piVar15 + 0x1e;
                        } while (iVar2 != 5);
                        printk("PortNum       %10lu %10lu %10lu %10lu %10lu\n",0,1,2,3,4);
                        printk(
                              "-----------------------------------------------------------------------------------------------\n"
                              );
                        printk("inbytes       %10lu %10lu %10lu %10lu %10lu\n",piVar5[2],
                               piVar5[0x20],piVar5[0x3e],piVar5[0x5c],piVar5[0x7a]);
                        printk("inpkts        %10lu %10lu %10lu %10lu %10lu\n",piVar5[4],
                               piVar5[0x22],piVar5[0x40],piVar5[0x5e],piVar5[0x7c]);
                        printk("inunicast     %10lu %10lu %10lu %10lu %10lu\n",piVar5[6],
                               piVar5[0x24],piVar5[0x42],piVar5[0x60],piVar5[0x7e]);
                        printk("inbroadcast   %10lu %10lu %10lu %10lu %10lu\n",piVar5[10],
                               piVar5[0x28],piVar5[0x46],piVar5[100],piVar5[0x82]);
                        printk("inmulticast   %10lu %10lu %10lu %10lu %10lu\n",piVar5[8],
                               piVar5[0x26],piVar5[0x44],piVar5[0x62],piVar5[0x80]);
                        printk("inerror       %10lu %10lu %10lu %10lu %10lu\n",piVar5[0xc],
                               piVar5[0x2a],piVar5[0x48],piVar5[0x66],piVar5[0x84]);
                        printk("indiscard     %10lu %10lu %10lu %10lu %10lu\n",piVar5[0xe],
                               piVar5[0x2c],piVar5[0x4a],piVar5[0x68],piVar5[0x86]);
                        printk("in64          %10lu %10lu %10lu %10lu %10lu\n",piVar4[2],
                               piVar4[0x1c],piVar4[0x36],piVar4[0x50],piVar4[0x6a]);
                        printk("in65to127     %10lu %10lu %10lu %10lu %10lu\n",piVar4[4],
                               piVar4[0x1e],piVar4[0x38],piVar4[0x52],piVar4[0x6c]);
                        printk("in128to255    %10lu %10lu %10lu %10lu %10lu\n",piVar4[6],
                               piVar4[0x20],piVar4[0x3a],piVar4[0x54],piVar4[0x6e]);
                        printk("in256to511    %10lu %10lu %10lu %10lu %10lu\n",piVar4[8],
                               piVar4[0x22],piVar4[0x3c],piVar4[0x56],piVar4[0x70]);
                        printk("in512to1023   %10lu %10lu %10lu %10lu %10lu\n",piVar4[10],
                               piVar4[0x24],piVar4[0x3e],piVar4[0x58],piVar4[0x72]);
                        printk("in1024tomax   %10lu %10lu %10lu %10lu %10lu\n",piVar4[0xc],
                               piVar4[0x26],piVar4[0x40],piVar4[0x5a],piVar4[0x74]);
                        uVar6 = fpga_read_reg(
                                             "TM][cla_set_def_qos_info_cfg]input invalid parameter!\n"
                                             );
                        uVar7 = fpga_read_reg("m_get_cmd_ram_info]indirect access time out\n");
                        uVar8 = fpga_read_reg("il\n");
                        uVar9 = fpga_read_reg("                      0x%x\n");
                        uVar10 = fpga_read_reg(0xc01f5);
                        printk("inoverflow    %10lu %10lu %10lu %10lu %10lu\n",uVar6,uVar7,uVar8,
                               uVar9,uVar10);
                        uVar6 = fpga_read_reg(
                                             "][cla_set_def_qos_info_cfg]input invalid parameter!\n"
                                             );
                        uVar7 = fpga_read_reg("get_cmd_ram_info]indirect access time out\n");
                        uVar8 = fpga_read_reg("\n");
                        uVar9 = fpga_read_reg("                    0x%x\n");
                        uVar10 = fpga_read_reg(0xc01f7);
                        printk("inwderror     %10lu %10lu %10lu %10lu %10lu\n",uVar6,uVar7,uVar8,
                               uVar9,uVar10);
                        printk("outbytes      %10lu %10lu %10lu %10lu %10lu\n",piVar5[0x10],
                               piVar5[0x2e],piVar5[0x4c],piVar5[0x6a],piVar5[0x88]);
                        printk("outpkts       %10lu %10lu %10lu %10lu %10lu\n",piVar5[0x12],
                               piVar5[0x30],piVar5[0x4e],piVar5[0x6c],piVar5[0x8a]);
                        printk("outunicast    %10lu %10lu %10lu %10lu %10lu\n",piVar5[0x14],
                               piVar5[0x32],piVar5[0x50],piVar5[0x6e],piVar5[0x8c]);
                        printk("outmulticast  %10lu %10lu %10lu %10lu %10lu\n",piVar5[0x16],
                               piVar5[0x34],piVar5[0x52],piVar5[0x70],piVar5[0x8e]);
                        printk("outbroadcast  %10lu %10lu %10lu %10lu %10lu\n",piVar5[0x18],
                               piVar5[0x36],piVar5[0x54],piVar5[0x72],piVar5[0x90]);
                        printk("outdiscard    %10lu %10lu %10lu %10lu %10lu\n",piVar5[0x1c],
                               piVar5[0x3a],piVar5[0x58],piVar5[0x76],piVar5[0x94]);
                        printk("outerror      %10lu %10lu %10lu %10lu %10lu\n",piVar5[0x1a],
                               piVar5[0x38],piVar5[0x56],piVar5[0x74],piVar5[0x92]);
                        printk("out64         %10lu %10lu %10lu %10lu %10lu\n",piVar4[0xe],
                               piVar4[0x28],piVar4[0x42],piVar4[0x5c],piVar4[0x76]);
                        printk("out65to127    %10lu %10lu %10lu %10lu %10lu\n",piVar4[0x10],
                               piVar4[0x2a],piVar4[0x44],piVar4[0x5e],piVar4[0x78]);
                        printk("out128to255   %10lu %10lu %10lu %10lu %10lu\n",piVar4[0x12],
                               piVar4[0x2c],piVar4[0x46],piVar4[0x60],piVar4[0x7a]);
                        printk("out256to511   %10lu %10lu %10lu %10lu %10lu\n",piVar4[0x14],
                               piVar4[0x2e],piVar4[0x48],piVar4[0x62],piVar4[0x7c]);
                        printk("out512to1024  %10lu %10lu %10lu %10lu %10lu\n",piVar4[0x16],
                               piVar4[0x30],piVar4[0x4a],piVar4[100],piVar4[0x7e]);
                        printk("out1024tomax  %10lu %10lu %10lu %10lu %10lu\n",piVar4[0x18],
                               piVar4[0x32],piVar4[0x4c],piVar4[0x66],piVar4[0x80]);
                        uVar6 = fpga_read_reg("s_vld = %d, qos_id = %d\n");
                        uVar7 = fpga_read_reg("id parameter!\n");
                        uVar8 = fpga_read_reg(&DAT_000a01db);
                        uVar9 = fpga_read_reg("0x%x\n");
                        uVar10 = fpga_read_reg(0xc01db);
                        printk("outexceerror  %10lu %10lu %10lu %10lu %10lu\n",uVar6,uVar7,uVar8,
                               uVar9,uVar10);
                        zte_api_sw_port_clear_port_count();
                        kfree(piVar4);
                        kfree(piVar5);
                        return 1;
                      }
                      iVar2 = strcmp(__s1,"gmacagingtime");
                      if (iVar2 != 0) {
                        printk("%s: illegal operation <%s>\n","brg_info_show",*param_2);
                        return 0;
                      }
                      iVar2 = zte_api_sw_mac_get_onu_agingtime(apcStack_44 + 4);
                      if (iVar2 == 0) {
                        printk("g_api_mac_agingtime output:agingtime = %d\n",local_34);
                        return 0;
                      }
                      printk("g_api_mac_agingtime failed\n");
                      return iVar2;
                    }
                    local_49 = 0;
                    pcStack_2c = "1000M";
                    pcStack_30 = "100M ";
                    local_34 = "10M  ";
                    apcStack_44[0] = "HALF";
                    apcStack_44[1] = "FULL";
                    apcStack_44[2] = "DOWN";
                    apcStack_44[3] = "up  ";
                    uVar3 = 0;
                    do {
                      zte_api_sw_port_get_port_linkmode(uVar3 & 0xff,&local_4c,&local_4b,&local_4a);
                      zte_api_sw_port_get_port_linkstate(uVar3 & 0xff,&local_49,&local_4b,&local_4a)
                      ;
                      uVar14 = (uint)local_49;
                      uVar18 = (uint)local_4b;
                      uVar17 = (uint)local_4a;
                      if ((((1 < uVar14) || (2 < uVar18)) || (1 < uVar17)) || (1 < local_4c)) {
                        printk("error port link state port %d, autoEn %d, speed %d, link %d, duplex %d\n"
                               ,uVar3,local_4c,uVar18,uVar14,uVar17);
                        return 0;
                      }
                      uVar13 = uVar3 + 1;
                      printk("port %d: link %s, autoEn %d, speed %s, duplex %s\n",uVar3,
                             apcStack_44[uVar14 + 2],local_4c,apcStack_44[uVar18 + 4],
                             apcStack_44[uVar17]);
                      uVar3 = uVar13;
                    } while (uVar13 != 5);
                  }
                }
                iVar2 = 1;
              }
            }
          }
        }
      }
    }
  }
  return iVar2;
}

