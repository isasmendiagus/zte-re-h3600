/* ============= FUNCTION: ethdrv_port_dev_open @ 00010000 ============= */

undefined4 ethdrv_port_dev_open(void)

{
  return 0;
}


/* ============= FUNCTION: ethdrv_port_dev_init @ 00010008 ============= */

undefined4 ethdrv_port_dev_init(void)

{
  return 0;
}


/* ============= FUNCTION: ethdrv_port_dev_destruct @ 00010010 ============= */

void ethdrv_port_dev_destruct(void)

{
  return;
}


/* ============= FUNCTION: ethdrv_port_dev_stop @ 00010014 ============= */

undefined4 ethdrv_port_dev_stop(void)

{
  return 0;
}


/* ============= FUNCTION: ethdrv_port_dev_ioctl @ 0001001c ============= */

undefined4 ethdrv_port_dev_ioctl(void)

{
  return 0;
}


/* ============= FUNCTION: ethdrv_port_dev_change_mtu @ 00010024 ============= */

uint ethdrv_port_dev_change_mtu(int param_1,uint param_2)

{
  if (*(uint *)(*(int *)(param_1 + 0x4c4) + 0x14c) < param_2) {
    param_2 = 0xffffffde;
  }
  else {
    *(uint *)(param_1 + 0x14c) = param_2;
  }
  return param_2;
}


/* ============= FUNCTION: ethdrv_port_dev_get_stats @ 00010040 ============= */

int ethdrv_port_dev_get_stats(int param_1)

{
  return param_1 + 0x4c8;
}


/* ============= FUNCTION: ethdrv_test_show @ 0001004c ============= */

undefined4 ethdrv_test_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  pcVar3 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = strcmp(pcVar3,"help");
    if (iVar1 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands\n");
      printk("============================================================================\n");
      printk(" echo dbg recv|mac|send|close|all >dbg set the debug mode\n");
      printk(" echo mac xx:xx:xx:xx:xx:xx       >mac set the debug mac \n");
      printk("============================================================================\n");
      printk("Display Commands: cat <file>\n");
      printk("============================================================================\n");
      printk(" cat help\n");
      printk(" cat dbgmode                           show debug mode\n");
      printk(" cat dbgmac                            show debug mac\n");
      return 0;
    }
    iVar1 = strcmp(pcVar3,"dbgmode");
    if (iVar1 == 0) {
      if (g_debug_mode < 5) {
        pcVar3 = (&CSWTCH_19)[g_debug_mode];
      }
      else {
        pcVar3 = "UNKOWN";
      }
      printk("debug mode %s \n",pcVar3);
      uVar2 = 0;
    }
    else {
      iVar1 = strcmp(pcVar3,"dbgmac");
      if (iVar1 == 0) {
        printk("debug mac is %02x:%02x:%02x:%02x:%02x:%02x\n",(undefined1)g_eth_debug_mac,
               g_eth_debug_mac._1_1_,g_eth_debug_mac._2_1_,g_eth_debug_mac._3_1_,
               g_eth_debug_mac._4_1_,g_eth_debug_mac._5_1_);
        return 0;
      }
      uVar2 = 0;
      printk("illegal operation <%s>\n",*param_2);
    }
  }
  return uVar2;
}


/* ============= FUNCTION: ethdrv_test_store @ 000101e0 ============= */

/* WARNING: Type propagation algorithm not settling */

undefined4
ethdrv_test_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  char *__s1;
  char local_44 [20];
  undefined4 local_30 [6];
  
  __s1 = (char *)*param_2;
  local_44[0] = '\0';
  local_44[1] = '\0';
  local_44[2] = '\0';
  local_44[3] = '\0';
  local_44[4] = '\0';
  local_44[5] = '\0';
  local_44[6] = '\0';
  local_44[7] = '\0';
  local_44[8] = '\0';
  local_44[9] = '\0';
  local_44[10] = '\0';
  local_44[0xb] = '\0';
  local_44[0xc] = '\0';
  local_44[0xd] = '\0';
  local_44[0xe] = '\0';
  local_44[0xf] = '\0';
  local_44[0x10] = '\0';
  local_44[0x11] = '\0';
  local_44[0x12] = '\0';
  local_44[0x13] = '\0';
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  local_30[4] = 0;
  local_30[5] = 0;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    disableIRQinterrupts();
    iVar1 = strcmp(__s1,"dbg");
    if (iVar1 == 0) {
      iVar1 = sscanf(param_3,"dbg %s",local_44);
      if (iVar1 == 1) {
        iVar1 = strncmp(local_44,"mac",3);
        if (iVar1 == 0) {
          g_debug_mode = 4;
        }
        else {
          iVar1 = strncmp(local_44,"recv",4);
          if (iVar1 == 0) {
            g_debug_mode = 2;
          }
          else {
            iVar1 = strncmp(local_44,"send",4);
            if (iVar1 == 0) {
              g_debug_mode = 3;
            }
            else {
              iVar1 = strncmp(local_44,"all",3);
              g_debug_mode = iVar1 == 0;
            }
          }
        }
      }
    }
    else {
      iVar1 = strcmp(__s1,"mac");
      if (iVar1 == 0) {
        iVar1 = sscanf(param_3,"mac %s",local_44);
        if (iVar1 == 1) {
          sscanf(param_3,"mac %x:%x:%x:%x:%x:%x",local_30,local_30 + 1,local_30 + 2,local_30 + 3,
                 local_30 + 4,local_30 + 5);
          puVar2 = DAT_000103c0 + 6;
          puVar3 = local_30;
          puVar4 = DAT_000103c0;
          do {
            puVar5 = puVar4 + 1;
            *puVar4 = (char)*puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar5;
          } while (puVar5 != puVar2);
        }
      }
      else {
        printk("llegal operation <%s>\n",*param_2);
      }
    }
  }
  return param_4;
}


/* ============= FUNCTION: ethdrv_port_dev_set_mac_addr @ 000103c4 ============= */

undefined4 ethdrv_port_dev_set_mac_addr(int param_1,int param_2)

{
  if (param_1 != 0 && param_2 != 0) {
    memcpy(*(void **)(param_1 + 0x1dc),(void *)(param_2 + 2),(uint)*(byte *)(param_1 + 0x179));
    return 0;
  }
  return 0xffffffde;
}


/* ============= FUNCTION: set_mii_dev_name_type.part.0 @ 00010400 ============= */

void set_mii_dev_name_type_part_0(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char *__dest;
  
  __dest = (char *)(DAT_00010434 + param_1 * 0x10);
  strncpy(__dest,param_2,0xf);
  printk("g_mii_dev_name[%d]  %s \n",param_1,__dest,param_4);
  return;
}


/* ============= FUNCTION: ethdrv_del_br_device @ 00010438 ============= */

undefined4 ethdrv_del_br_device(void)

{
  undefined4 uVar1;
  
  uVar1 = g_sw_netInfo._4_4_;
  if (g_sw_netInfo._4_4_ != 0) {
    unregister_netdev(g_sw_netInfo._4_4_);
    free_netdev(uVar1);
    g_sw_netInfo._4_4_ = 0;
    g_sw_netInfo[0] = g_sw_netInfo[0] + -1;
    return 0;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: set_mii_dev_name_type @ 00010480 ============= */

void set_mii_dev_name_type(uint param_1)

{
  if (2 < param_1) {
    printk("invalid dev_type %d \n",param_1);
    return;
  }
  set_mii_dev_name_type_part_0();
  return;
}


/* ============= FUNCTION: ethdrv_set_wanportid @ 000104a0 ============= */

void ethdrv_set_wanportid(undefined1 param_1)

{
  g_sw_netInfo[0x2c] = param_1;
  return;
}


/* ============= FUNCTION: pdt_ethdriver_init @ 000104b0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
pdt_ethdriver_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  code *pcVar9;
  int *piVar10;
  int iVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  
  set_mii_dev_name_type_part_0(0,&_LC26,param_3,param_4,param_4);
  set_mii_dev_name_type_part_0(1,&_LC27);
  if (_tm_port_unknwn_multicast_floodport_set != 0) {
    uVar7 = 0;
    pcVar9 = zte_api_sw_mac_set_port_macfiltermode;
    iVar11 = 0;
    uVar8 = 1;
    piVar10 = DAT_00010718;
    do {
      uVar2 = (undefined1)uVar7;
      if (uVar7 < 8) {
        if ((byte)*pcVar9 == _tm_vlan_check_ena_set) {
          iVar11 = dev_get_by_name(&init_net,DAT_00010720 + 0x10);
          printk("port id %d, name %s\n",_tm_vlan_check_ena_set,DAT_0001072c);
        }
        else {
          iVar11 = dev_get_by_name(&init_net,DAT_00010720);
        }
      }
      if (iVar11 == 0) {
        printk("mii_dev = NULL!@func %s %d\n",DAT_00010728,0xfe);
        break;
      }
      if ((*(uint *)(iVar11 + 0x138) & 1) == 0) {
        rtnl_lock();
        dev_change_flags(iVar11,*(uint *)(iVar11 + 0x138) | 1);
        rtnl_unlock();
        msleep(1000);
      }
      disableIRQinterrupts();
      iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar4 + *(int *)(iVar11 + 0x280)) = *(int *)(iVar4 + *(int *)(iVar11 + 0x280)) + -1;
      uVar7 = uVar7 + 1;
      iVar4 = alloc_etherdev_mqs(100,1,1);
      pcVar9 = pcVar9 + 1;
      if (iVar4 == 0) {
        printk("kmalloc error!\n");
        break;
      }
      *(uint *)(iVar4 + 0x138) = *(uint *)(iVar11 + 0x138) & 0xfffffffe;
      *(undefined4 *)(iVar4 + 0x14c) = *(undefined4 *)(iVar11 + 0x14c);
      memcpy((void *)(iVar4 + 0x200),(void *)(iVar11 + 0x200),(uint)*(byte *)(iVar11 + 0x179));
      memcpy(*(void **)(iVar4 + 0x1dc),*(void **)(iVar11 + 0x1dc),(uint)*(byte *)(iVar11 + 0x179));
      uVar3 = DAT_0001071c;
      uVar1 = *(undefined1 *)(iVar11 + 0x179);
      *(code **)(iVar4 + 0x298) = ethdrv_port_dev_destruct;
      *(undefined1 *)(iVar4 + 0x179) = uVar1;
      *(undefined4 *)(iVar4 + 300) = uVar3;
      __memzero(iVar4 + 0x4c0,100);
      *(undefined1 *)(iVar4 + 0x4c0) = uVar2;
      *(int *)(iVar4 + 0x4c4) = iVar11;
      iVar5 = register_netdev(iVar4);
      if (iVar5 != 0) {
        printk("Register_netdev %s failed..\n",iVar4);
        free_netdev(iVar4);
        break;
      }
      netif_carrier_off(iVar4);
      uVar6 = _tm_port_unknwn_multicast_floodport_set;
      bVar14 = 9 < (uVar8 & 0xff);
      bVar12 = (uVar8 & 0xff) == 10;
      if (!bVar12) {
        bVar14 = uVar8 <= _tm_port_unknwn_multicast_floodport_set;
      }
      bVar13 = _tm_port_unknwn_multicast_floodport_set == uVar8;
      piVar10 = piVar10 + 1;
      *piVar10 = iVar4;
      uVar8 = uVar8 + 1;
      if (!bVar14 || (bVar12 || bVar13)) {
        uVar6 = 1;
      }
      if (bVar14 && (!bVar12 && !bVar13)) {
        uVar6 = 0;
      }
      g_sw_netInfo[0] = g_sw_netInfo[0] + '\x01';
    } while (uVar6 == 0);
  }
  switch_skb_recv = pdt_ethdrv_recv;
  iVar11 = sysfs_create_group(DAT_00010724,&ethdrv_test_group);
  if (iVar11 != 0) {
    printk("sysfs group failed %d\n");
  }
  return 0;
}


/* ============= FUNCTION: pdt_ethdrv_rate_limit_1s @ 00010730 ============= */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 pdt_ethdrv_rate_limit_1s(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = jiffies;
  if (g_timestamp_1 == 0) {
    g_timestamp_1 = jiffies;
  }
  g_rev_packet_100ms = g_rev_packet_100ms + 1;
  if (param_1 < g_rev_packet_100ms) {
    g_timestamp_2 = jiffies;
    iVar2 = msecs_to_jiffies(1000);
    if ((iVar1 - g_timestamp_1) - iVar2 < 0) {
      return 0xffffffff;
    }
    g_timestamp_1 = jiffies;
    g_rev_packet_100ms = 0;
    return 0;
  }
  return 0;
}


/* ============= FUNCTION: swport_dev_get_stats @ 000107c0 ============= */

int swport_dev_get_stats(int param_1)

{
  return param_1 + 0x4c8;
}


/* ============= FUNCTION: swport_dev_xmit_fin @ 000107cc ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 swport_dev_xmit_fin(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_2 + 0x4c4);
  if (iVar3 == 0) {
    *(int *)(param_2 + 0x4e4) = *(int *)(param_2 + 0x4e4) + 1;
    __dev_kfree_skb_any();
    return 0xffffffff;
  }
  if ((g_pon_work_mode & 0x10) != 0) {
    if (wanLogicPort == 0xff) {
      if (wan_to_lan != 0) {
        uVar1 = (uint)*(byte *)(param_1 + 0xb4);
LAB_0001083c:
        if (_tm_vlan_check_ena_set == uVar1) {
          iVar3 = dev_get_by_name(&init_net,&_LC1,iVar3,_tm_vlan_check_ena_set,param_4);
          goto joined_r0x000108fc;
        }
      }
    }
    else if (wan_to_lan != 0) {
      uVar1 = (uint)*(byte *)(param_1 + 0xb4);
      if ((byte)zte_api_sw_mac_set_port_macfiltermode[wanLogicPort] != uVar1) goto LAB_0001083c;
      iVar3 = dev_get_by_name(&init_net,&_LC0,iVar3,
                              (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[wanLogicPort],
                              param_4);
joined_r0x000108fc:
      if (iVar3 == 0) {
        __dev_kfree_skb_any(param_1,1);
        return 0xffffffff;
      }
      *(int *)(param_1 + 0x18) = iVar3;
      disableIRQinterrupts();
      iVar2 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar2 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar2 + *(int *)(iVar3 + 0x280)) + -1;
      goto LAB_0001084c;
    }
  }
  *(int *)(param_1 + 0x18) = iVar3;
LAB_0001084c:
  *(int *)(param_2 + 0x4cc) = *(int *)(param_2 + 0x4cc) + 1;
  *(int *)(param_2 + 0x4d4) = *(int *)(param_2 + 0x4d4) + *(int *)(param_1 + 100);
  dev_queue_xmit_sk(*(undefined4 *)(param_1 + 0x14),param_1);
  return 0;
}


/* ============= FUNCTION: ethdrv_recv_fin @ 00010930 ============= */

undefined4 ethdrv_recv_fin(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int *piVar3;
  
  if (param_2 == 0) {
    __dev_kfree_skb_any(param_1,1);
    return 0xffffffff;
  }
  piVar3 = (int *)ethdrv_port_dev_get_stats(param_2);
  *piVar3 = *piVar3 + 1;
  piVar3[2] = piVar3[2] + *(int *)(param_1 + 100);
  uVar2 = eth_type_trans(param_1,param_2);
  *(int *)(param_1 + 0x18) = param_2;
  uVar1 = jiffies;
  *(undefined2 *)(param_1 + 0xa4) = uVar2;
  *(undefined4 *)(param_2 + 0x1d8) = uVar1;
  if ((*(byte *)(param_1 + 0x74) & 7) == 2) {
    piVar3[8] = piVar3[8] + 1;
  }
  netif_receive_skb_sk(*(undefined4 *)(param_1 + 0x14),param_1);
  return 0;
}


/* ============= FUNCTION: pdt_ethdrv_recv @ 000109c8 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 pdt_ethdrv_recv(int param_1)

{
  uint uVar1;
  undefined2 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  void *__s1;
  int extraout_r1;
  uint uVar6;
  uint uVar7;
  char *__s1_00;
  int iVar8;
  ushort uVar9;
  bool bVar10;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 auStack_38 [20];
  
  local_3a = 0;
  local_39 = 0;
  if (param_1 == 0) {
    if (g_eth_err_print != '\x01') {
      return 0xffffffff;
    }
    iVar3 = __printk_ratelimit("pdt_ethdrv_recv");
    if (iVar3 == 0) {
      return 0xffffffff;
    }
    printk("Error! skb == NULL @func %s %d\n","pdt_ethdrv_recv",0x1b0);
    return 0xffffffff;
  }
  uVar6 = (uint)g_debug_mode;
  if (uVar6 == 7) {
    if (*(short *)(*(int *)(param_1 + 0xcc) + 0xc) == 0x81) {
      uVar9 = *(ushort *)(*(int *)(param_1 + 0xcc) + 0xe);
      uVar6 = (uint)(uVar9 >> 8);
      uVar1 = (uVar9 & 0xff) << 8;
      uVar7 = uVar1 & 0xfff | uVar6;
      g_eth_vlan = (ushort)(((uVar1 | uVar6) << 0x14) >> 0x14);
    }
    else {
      uVar7 = 0xfff;
      g_eth_vlan = 0xfff;
    }
    if (g_eth_debug_vlan != uVar7) goto LAB_00010a1c;
LAB_00010b18:
    printk("debbug skb @:====  %s   ===\n","pdt_ethdrv_recv");
    uVar6 = 0;
    printk("skb->dev->name = %s,skb->len = %d \n",*(undefined4 *)(param_1 + 0x18),
           *(undefined4 *)(param_1 + 100));
    printk("skbinfo: port %d\n",*(undefined1 *)(param_1 + 0xb4));
    while (uVar6 < *(uint *)(param_1 + 100)) {
      printk("%02x ",*(undefined1 *)(*(int *)(param_1 + 0xcc) + uVar6));
      __aeabi_idivmod(uVar6,0xc);
      bVar10 = uVar6 != 0;
      uVar6 = uVar6 + 1;
      if (bVar10 && extraout_r1 == 0xb) {
        printk(&_LC6);
      }
    }
    printk(&_LC6);
  }
  else {
    if (uVar6 - 1 < 2) goto LAB_00010b18;
    if (uVar6 == 4) {
      __s1 = *(void **)(param_1 + 0xcc);
      iVar3 = memcmp((void *)((int)__s1 + 6),&g_eth_debug_mac,6);
      if (iVar3 != 0) {
LAB_00010d44:
        iVar3 = memcmp(__s1,&g_eth_debug_mac,6);
        if (iVar3 != 0) goto LAB_00010a1c;
      }
      goto LAB_00010b18;
    }
    if (uVar6 == 6) {
      iVar3 = memcmp((void *)(*(int *)(param_1 + 0xcc) + 6),&g_eth_debug_mac,6);
      if (iVar3 == 0) goto LAB_00010b18;
    }
    else if (uVar6 == 5) {
      __s1 = *(void **)(param_1 + 0xcc);
      goto LAB_00010d44;
    }
  }
LAB_00010a1c:
  __s1_00 = *(char **)(param_1 + 0x18);
  if (*__s1_00 != 'p') {
    uVar6 = (uint)*(byte *)(param_1 + 0xb4);
    if ((_zte_api_sw_mac_set_port_learnlimit & 1 << uVar6) != 0) {
      iVar8 = *(int *)(g_sw_netInfo +
                      (uint)(byte)zte_api_sw_port_set_port_isolatemask[uVar6] * 4 + 4);
      *(int *)(param_1 + 0x18) = iVar8;
      iVar3 = ffe_receive_skb(param_1,3);
      if (iVar3 == 0) {
        return 0;
      }
      if (iVar8 != 0) {
        piVar4 = (int *)ethdrv_port_dev_get_stats(iVar8);
        *piVar4 = *piVar4 + 1;
        piVar4[2] = piVar4[2] + *(int *)(param_1 + 100);
        uVar2 = eth_type_trans(param_1,iVar8);
        *(int *)(param_1 + 0x18) = iVar8;
        iVar3 = jiffies;
        *(undefined2 *)(param_1 + 0xa4) = uVar2;
        *(int *)(iVar8 + 0x1d8) = iVar3;
        if ((*(byte *)(param_1 + 0x74) & 7) == 2) {
          piVar4[8] = piVar4[8] + 1;
        }
        netif_receive_skb_sk(*(undefined4 *)(param_1 + 0x14),param_1);
        return 0;
      }
      __dev_kfree_skb_any(param_1,1);
      return 0;
    }
    iVar3 = aclEssidToWlanIDMMap2(uVar6 + 1 & 0xff,&local_3a,&local_39,auStack_38);
    if (iVar3 == 0) {
      iVar3 = dev_get_by_name(&init_net,auStack_38);
      if ((iVar3 != 0) && (*(char *)(iVar3 + 0x294) != '\0')) {
        *(int *)(param_1 + 0x18) = iVar3;
        iVar8 = ffe_receive_skb(param_1,3);
        if (iVar8 != 0) {
          uVar2 = eth_type_trans(param_1,iVar3);
          iVar8 = jiffies;
          *(undefined2 *)(param_1 + 0xa4) = uVar2;
          *(int *)(*(int *)(param_1 + 0x18) + 0x1d8) = iVar8;
          netif_rx(param_1);
          disableIRQinterrupts();
          iVar8 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) + -1
          ;
          return 0;
        }
        disableIRQinterrupts();
        iVar8 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
        *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) + -1;
        return 0;
      }
      __dev_kfree_skb_any(param_1,1);
      if (g_eth_err_print != '\x01') {
        return 0xffffffff;
      }
      iVar3 = __printk_ratelimit("pdt_ethdrv_recv");
      if (iVar3 != 0) {
        printk("pdt_ethdrv_recv meet error pdev==NULL || pdev->reg_state== 0,when dev_name = %s\n",
               auStack_38);
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    if ((g_eth_err_print == '\x01') && (iVar3 = __printk_ratelimit("pdt_ethdrv_recv"), iVar3 != 0))
    {
      printk("Error! skb->port = %d @func %s %d\n",*(undefined1 *)(param_1 + 0xb4),"pdt_ethdrv_recv"
             ,0x2af);
    }
    goto LAB_00011008;
  }
  if ((g_pon_work_mode & 0x10) == 0) {
    if (g_debug_ratelimit_action != '\0') {
      uVar9 = 0;
      bVar10 = false;
      goto LAB_00010c28;
    }
    uVar9 = 0;
    bVar10 = false;
LAB_00010f54:
    iVar3 = ffe_receive_skb(param_1,3);
    if (iVar3 == 0) {
      return 0;
    }
  }
  else {
    uVar9 = *(ushort *)(*(int *)(param_1 + 0xcc) + 0xc);
    uVar9 = uVar9 << 8 | uVar9 >> 8;
    if (uVar9 == 0x884c || uVar9 == 0x8899) {
      bVar10 = uVar9 == 0x8899 || uVar9 == 0x884c;
      if (g_debug_ratelimit_action == '\0') goto LAB_00010c94;
    }
    else {
      iVar3 = dev_get_by_name(&init_net,&_LC8);
      if (iVar3 == 0) {
        bVar10 = false;
      }
      else if ((*(uint *)(iVar3 + 0x138) & 1) == 0) {
        disableIRQinterrupts();
        iVar8 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
        *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) + -1;
        bVar10 = false;
      }
      else {
        *(int *)(param_1 + 0x18) = iVar3;
        disableIRQinterrupts();
        iVar8 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
        *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) + -1;
        bVar10 = true;
      }
      if (g_debug_ratelimit_action == '\0') goto LAB_00010f54;
    }
LAB_00010c28:
    iVar3 = jiffies;
    if (g_timestamp_1 == 0) {
      g_timestamp_1 = jiffies;
    }
    g_rev_packet_100ms = g_rev_packet_100ms + 1;
    if (g_debug_ratelimit_maxinum < g_rev_packet_100ms) {
      g_timestamp_2 = jiffies;
      iVar8 = msecs_to_jiffies(1000);
      if ((iVar3 - g_timestamp_1) - iVar8 < 0) {
LAB_00011008:
        __dev_kfree_skb_any(param_1,1);
        return 0xffffffff;
      }
      g_timestamp_1 = jiffies;
      g_rev_packet_100ms = 0;
    }
    if (uVar9 != 0x884c && uVar9 != 0x8899) goto LAB_00010f54;
  }
  if ((g_pon_work_mode & 0x10) == 0) {
    return 0;
  }
LAB_00010c94:
  if ((bVar10) && (iVar3 = strcmp(__s1_00,"pon"), iVar3 == 0)) {
    if (uVar9 == 0x884c) {
      iVar3 = dev_get_by_name(&init_net,&_LC1);
      *(int *)(param_1 + 0x18) = iVar3;
      disableIRQinterrupts();
      iVar8 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar8 + *(int *)(iVar3 + 0x280)) + -1;
    }
    uVar2 = eth_type_trans(param_1,*(undefined4 *)(param_1 + 0x18));
    *(undefined2 *)(param_1 + 0xa4) = uVar2;
    uVar5 = netif_receive_skb_sk(*(undefined4 *)(param_1 + 0x14),param_1);
    return uVar5;
  }
  *(undefined4 *)(param_1 + 0x18) =
       *(undefined4 *)
        (g_sw_netInfo +
        (uint)(byte)zte_api_sw_port_set_port_isolatemask[_tm_vlan_check_ena_set] * 4 + 4);
  piVar4 = (int *)ethdrv_port_dev_get_stats();
  *piVar4 = *piVar4 + 1;
  piVar4[2] = piVar4[2] + *(int *)(param_1 + 100);
  uVar2 = eth_type_trans(param_1,*(undefined4 *)(param_1 + 0x18));
  iVar3 = jiffies;
  *(undefined2 *)(param_1 + 0xa4) = uVar2;
  *(int *)(*(int *)(param_1 + 0x18) + 0x1d8) = iVar3;
  if ((*(byte *)(param_1 + 0x74) & 7) == 2) {
    piVar4[8] = piVar4[8] + 1;
  }
  uVar5 = netif_receive_skb_sk(*(undefined4 *)(param_1 + 0x14),param_1);
  return uVar5;
}


/* ============= FUNCTION: pdt_ethdrv_send @ 00011130 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 pdt_ethdrv_send(int param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  void *__s1;
  int iVar5;
  int extraout_r1;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  
  if (param_1 == 0) {
    if (g_eth_err_print != '\x01') {
      return 0;
    }
    iVar4 = __printk_ratelimit(DAT_000114fc);
    if (iVar4 == 0) {
      return 0;
    }
    printk("Error! skb == NULL @func %s %d\n",DAT_000114fc,0x2cd);
    return 0;
  }
  if (param_2 == 0) {
    if ((g_eth_err_print == '\x01') && (iVar4 = __printk_ratelimit(DAT_000114fc), iVar4 != 0)) {
      printk("Error! dev == NULL @func %s %d\n",DAT_000114fc,0x2d2);
    }
    goto LAB_000113ec;
  }
  if (g_debug_mode == 7) {
    if (*(short *)(*(int *)(param_1 + 0xcc) + 0xc) == 0x81) {
      uVar1 = *(ushort *)(*(int *)(param_1 + 0xcc) + 0xe);
      uVar7 = (uint)(uVar1 >> 8);
      uVar2 = (uVar1 & 0xff) << 8;
      uVar6 = uVar2 & 0xfff | uVar7;
      g_eth_vlan = (ushort)(((uVar2 | uVar7) << 0x14) >> 0x14);
    }
    else {
      uVar6 = 0xfff;
      g_eth_vlan = 0xfff;
    }
    if (g_eth_debug_vlan != uVar6) goto LAB_000111b8;
LAB_00011168:
    uVar7 = 0;
    printk("debbug skb @:====  %s   ===\n",DAT_000114fc);
    printk("skb->dev->name = %s,skb->len = %d \n",*(undefined4 *)(param_1 + 0x18),
           *(undefined4 *)(param_1 + 100));
    printk("skbinfo: port %d\n",*(undefined1 *)(param_1 + 0xb4));
    while (uVar7 < *(uint *)(param_1 + 100)) {
      printk("%02x ",*(undefined1 *)(*(int *)(param_1 + 0xcc) + uVar7));
      __aeabi_idivmod(uVar7,0xc);
      bVar8 = uVar7 != 0;
      uVar7 = uVar7 + 1;
      if (bVar8 && extraout_r1 == 0xb) {
        printk(&_LC6);
      }
    }
    printk(&_LC6);
  }
  else {
    if ((g_debug_mode & 0xfd) == 1) goto LAB_00011168;
    if (g_debug_mode == 4) {
      __s1 = *(void **)(param_1 + 0xcc);
      iVar4 = memcmp((void *)((int)__s1 + 6),&g_eth_debug_mac,6);
      if (iVar4 != 0) {
LAB_000112a8:
        iVar4 = memcmp(__s1,&g_eth_debug_mac,6);
        if (iVar4 != 0) goto LAB_000111b8;
      }
      goto LAB_00011168;
    }
    if (g_debug_mode == 6) {
      iVar4 = memcmp((void *)(*(int *)(param_1 + 0xcc) + 6),&g_eth_debug_mac,6);
      if (iVar4 == 0) goto LAB_00011168;
    }
    else if (g_debug_mode == 5) {
      __s1 = *(void **)(param_1 + 0xcc);
      goto LAB_000112a8;
    }
  }
LAB_000111b8:
  *(code *)(param_1 + 0xb4) = zte_api_sw_mac_set_port_macfiltermode[*(byte *)(param_2 + 0x4c0)];
  ffe_learn_skb(param_1,3);
  iVar4 = CSPKernel_skb_SelectQueue(param_1,param_2);
  if (iVar4 - 1U < 8) {
    sVar3 = 8 - (short)iVar4;
  }
  else if (iVar4 == 0x8f) {
    sVar3 = 7;
  }
  else {
    sVar3 = 0;
  }
  *(short *)(param_1 + 0x78) = sVar3;
  if (*(int *)(param_2 + 0x4c4) == 0) {
    *(int *)(param_2 + 0x4e4) = *(int *)(param_2 + 0x4e4) + 1;
    __dev_kfree_skb_any(param_1);
    return 0;
  }
  if ((g_pon_work_mode & 0x10) != 0) {
    if (wanLogicPort == 0xff) {
      if (wan_to_lan != 0) {
        uVar7 = (uint)*(byte *)(param_1 + 0xb4);
LAB_00011310:
        if (_tm_vlan_check_ena_set == uVar7) {
          iVar4 = dev_get_by_name(&init_net,&_LC1);
          goto joined_r0x00011334;
        }
      }
    }
    else if (wan_to_lan != 0) {
      uVar7 = (uint)*(byte *)(param_1 + 0xb4);
      if ((byte)zte_api_sw_mac_set_port_macfiltermode[wanLogicPort] != uVar7) goto LAB_00011310;
      iVar4 = dev_get_by_name(&init_net,&_LC0);
joined_r0x00011334:
      if (iVar4 == 0) {
LAB_000113ec:
        __dev_kfree_skb_any(param_1,1);
        return 0;
      }
      *(int *)(param_1 + 0x18) = iVar4;
      disableIRQinterrupts();
      iVar5 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar5 + *(int *)(iVar4 + 0x280)) = *(int *)(iVar5 + *(int *)(iVar4 + 0x280)) + -1;
      goto LAB_00011258;
    }
  }
  *(int *)(param_1 + 0x18) = *(int *)(param_2 + 0x4c4);
LAB_00011258:
  *(int *)(param_2 + 0x4cc) = *(int *)(param_2 + 0x4cc) + 1;
  *(int *)(param_2 + 0x4d4) = *(int *)(param_2 + 0x4d4) + *(int *)(param_1 + 100);
  dev_queue_xmit_sk(*(undefined4 *)(param_1 + 0x14),param_1);
  return 0;
}


/* ============= FUNCTION: private_capfun_register @ 00011500 ============= */

void private_capfun_register(void)

{
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  fuc_table_node_create(0x3eb,sw_port_set_port_proaction);
  fuc_table_node_create(0x3ec,sw_port_get_port_proaction);
  fuc_table_node_create(0x3ed,sw_port_set_port_802dot1xen);
  fuc_table_node_create(0x3ee,sw_port_get_port_802dot1xen);
  fuc_table_node_create(0x3ef,sw_port_get_port_statistics);
  fuc_table_node_create(0x3f0,sw_port_get_port_vlanstatistics);
  fuc_table_node_create(0x3f1,sw_vlan_add_port_dsvlantranslationentry);
  fuc_table_node_create(0x3f2,sw_vlan_del_port_dsvlantranslationentry);
  fuc_table_node_create(0x3f3,sw_vlan_show_port_dsvlantranslationentry);
  fuc_table_node_create(0x3f4,sw_vlan_add_port_dsmulvlantranslationentry);
  fuc_table_node_create(0x3f5,sw_vlan_del_port_dsmulvlantranslationentry);
  fuc_table_node_create(0x3f7,sw_vlan_set_port_transparent);
  fuc_table_node_create(0x3f8,sw_vlan_get_port_transparent);
  fuc_table_node_create(0x3f9,sw_vlan_set_port_vlanfilter);
  fuc_table_node_create(0x3fa,sw_vlan_get_port_vlanfilter);
  fuc_table_node_create(0x3fb,sw_mac_get_port_learnnum);
  fuc_table_node_create(0x3fc,sw_mac_get_onu_macentrynum);
  fuc_table_node_create(0x3fd,sw_mac_add_cpu_macaddress);
  fuc_table_node_create(0x3fe,sw_mac_del_cpu_macaddress);
  fuc_table_node_create(0x3ff,sw_mac_show_cpu_macaddress);
  fuc_table_node_create(0x400,sw_mac_add_port_macadd_feature);
  fuc_table_node_create(0x401,sw_mac_del_port_macadd_feature);
  fuc_table_node_create(0x402,sw_mac_set_mac_hashmode);
  fuc_table_node_create(0x403,sw_mac_get_mac_hashmode);
  fuc_table_node_create(0x404,sw_qos_set_tcontschedule);
  fuc_table_node_create(0x405,sw_qos_get_tcontschedule);
  fuc_table_node_create(0x406,sw_qos_get_availbktid);
  fuc_table_node_create(0x407,sw_qos_set_trustppqueue);
  fuc_table_node_create(0x408,sw_qos_get_trustppqueue);
  fuc_table_node_create(0x409,sw_qos_set_opritoqueue);
  fuc_table_node_create(0x40a,sw_qos_get_opritoqueue);
  fuc_table_node_create(0x40b,sw_qos_set_mode_schedule);
  fuc_table_node_create(0x40c,sw_qos_set_rcqueue);
  fuc_table_node_create(0x40d,sw_qos_set_queue);
  fuc_table_node_create(0x40e,sw_qos_set_overall_bandwidth);
  fuc_table_node_create(0x40f,qos_info_show);
  fuc_table_node_create(0x410,sw_wancip_set);
  fuc_table_node_create(0x411,sw_wancip_get);
  fuc_table_node_create(0x412,sw_wancip_del);
  fuc_table_node_create(0x413,sw_wlan_idmessid_map);
  fuc_table_node_create(0x414,sw_essid_wlanidm_map);
  fuc_table_node_create(0x415,sw_port_set_cpu_broadcastrate);
  fuc_table_node_create(0x416,sw_port_set_ethdev_carrier);
  fuc_table_node_create(0x417,sw_port_set_cpu_queue_ratelimit);
  fuc_table_node_create(0x418,sw_other_set_area_code);
  fuc_table_node_create(0x41c,sw_other_set_wan_lan_switch);
  fuc_table_node_create(0x3ea,sw_cla_show_aclrule);
  fuc_table_node_create(0x41d,sw_set_trap_cpu_ip);
  fuc_table_node_create(0x47,sw_other_get_port_from_devname,extraout_r2,in_r3);
  return;
}


/* ============= FUNCTION: public_capfun_register @ 00011818 ============= */

void public_capfun_register(void)

{
  sw_public_port_vlan_func_reg
            (sw_vlan_set_port_inframemode,sw_vlan_get_port_inframemode,sw_vlan_set_port_pvid,
             sw_vlan_get_port_pvid,sw_vlan_set_port_vlancfg,sw_vlan_get_port_vlancfg,
             sw_set_mflow_config);
  sw_public_port_cfg_func_reg
            (sw_port_set_port_enable,sw_port_get_port_enable,sw_port_set_port_flowcontrol,
             sw_port_get_port_flowcontrol,sw_port_set_port_isolate,sw_port_get_port_isolate,
             sw_port_set_port_isolatemask,sw_port_get_port_isolatemask,sw_port_set_port_floodcontrol
             ,sw_port_get_port_floodcontrol,sw_port_set_port_floodcontrolmask,
             sw_port_get_port_floodcontrolmask,sw_port_set_port_linkmode,sw_port_get_port_linkmode,
             sw_port_get_port_linkstate,sw_port_set_port_mirror,sw_port_get_port_mirror,
             sw_port_set_port_loopback,sw_port_get_port_loopback);
  sw_public_port_ratelimit_func_reg
            (sw_port_set_port_ratelimit,sw_port_get_port_ratelimit,sw_port_set_port_multicastrate,
             sw_port_get_port_multicastrate,sw_port_set_port_broadcastrate,
             sw_port_get_port_broadcastrate);
  sw_public_onu_mactable_func_reg
            (sw_mac_set_onu_agingtime,sw_mac_get_onu_agingtime,sw_mac_set_port_learnlimit,
             sw_mac_get_port_learnlimit,sw_mac_add_port_macaddress,sw_mac_del_port_macaddress,
             sw_mac_set_port_macfiltermode,sw_mac_get_port_macfiltermode,
             sw_mac_add_port_macfilterentry,sw_mac_del_port_macfilterentry,
             sw_mac_get_port_macfilterentry,sw_mac_show_macaddress,sw_mac_clear_macaddress,
             sw_mac_show_port_mactable,sw_mac_clear_port_mactable);
  sw_public_onu_qos_func_reg
            (sw_qos_set_port_schedule,sw_qos_get_port_schedule,sw_acl_add_port_flowconfig,
             sw_acl_del_port_flowconfig,sw_acl_get_port_flowconfig);
  sw_public_onu_statistics_func_reg
            (sw_port_get_port_statistics1,sw_port_get_port_statistics2,sw_port_get_port_statistics3,
             sw_port_get_port_statistics4,sw_port_clear_port_count,sw_port_clear_port_count_byportid
             ,sw_port_get_port_rmonstats);
  sw_public_onu_other_func_reg
            (sw_mac_set_onu_stpaction,sw_mac_get_onu_stpaction,sw_mac_set_onu_proaction,
             sw_mac_get_onu_proaction,sw_other_set_onu_mtu,sw_other_get_onu_mtu,sw_reg_set_readreg,
             sw_reg_set_writereg,sw_phy_reg_set_readreg,sw_phy_reg_set_writereg);
  return;
}


/* ============= FUNCTION: sw_acl_setMtchInfo @ 00011b38 ============= */

void sw_acl_setMtchInfo(int *param_1,int param_2)

{
  short sVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  ushort uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  ushort uVar8;
  char *__s1;
  undefined4 uVar9;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 == (int *)0x0 || param_2 == 0) {
    printk("[%s] params is NULL\n","sw_acl_setMtchInfo");
    return;
  }
  uVar5 = *(ushort *)((int)param_1 + 10) << 8 | *(ushort *)((int)param_1 + 10) >> 8;
  *(ushort *)(param_2 + 0x26) = uVar5;
  uVar2 = g_switch_debug_level;
  uVar8 = *(ushort *)(param_1 + 2) << 8 | *(ushort *)(param_1 + 2) >> 8;
  *(ushort *)(param_2 + 0x24) = uVar8;
  *(char *)(param_2 + 0x28) = (char)param_1[4];
  if (uVar2 < 3) {
    if ((param_1[3] & 0xfffffffdU) != 0) {
      puVar6 = (undefined4 *)*param_1;
      sVar1 = *(short *)(param_2 + 0x2e);
      uVar3 = puVar6[2];
      uVar9 = *puVar6;
      uVar7 = puVar6[3];
      *(undefined4 *)(param_2 + 8) = puVar6[1];
      *(undefined4 *)(param_2 + 4) = uVar9;
      *(undefined4 *)(param_2 + 0xc) = uVar3;
      *(undefined4 *)(param_2 + 0x10) = uVar7;
      puVar6 = (undefined4 *)param_1[1];
      uVar3 = puVar6[1];
      uVar7 = puVar6[2];
      uVar9 = puVar6[3];
      *(undefined4 *)(param_2 + 0x14) = *puVar6;
      *(undefined4 *)(param_2 + 0x18) = uVar3;
      *(undefined4 *)(param_2 + 0x1c) = uVar7;
      *(undefined4 *)(param_2 + 0x20) = uVar9;
      goto joined_r0x00011c18;
    }
    *(int *)(param_2 + 4) = *param_1;
    *(int *)(param_2 + 0x14) = param_1[1];
  }
  else {
    printk("match dport %d,sport %d, prot %d\n",uVar5,uVar8);
    uVar2 = g_switch_debug_level;
    puVar6 = (undefined4 *)*param_1;
    if ((param_1[3] & 0xfffffffdU) == 0) {
      *(undefined4 **)(param_2 + 4) = puVar6;
      *(int *)(param_2 + 0x14) = param_1[1];
      if (2 < uVar2) {
        printk("acl filed sip 0x%08x,dip 0x%08x\n");
      }
    }
    else {
      uVar3 = puVar6[2];
      uVar9 = *puVar6;
      uVar7 = puVar6[3];
      *(undefined4 *)(param_2 + 8) = puVar6[1];
      *(undefined4 *)(param_2 + 4) = uVar9;
      *(undefined4 *)(param_2 + 0xc) = uVar3;
      *(undefined4 *)(param_2 + 0x10) = uVar7;
      puVar6 = (undefined4 *)param_1[1];
      uVar3 = puVar6[1];
      uVar7 = puVar6[2];
      uVar9 = puVar6[3];
      *(undefined4 *)(param_2 + 0x14) = *puVar6;
      *(undefined4 *)(param_2 + 0x18) = uVar3;
      *(undefined4 *)(param_2 + 0x1c) = uVar7;
      *(undefined4 *)(param_2 + 0x20) = uVar9;
      if (2 < uVar2) {
        printk("acl filed ipv6 sip %8.8x:%8.8x:%8.8x:%8.8x, dip %8.8x:%8.8x:%8.8x:%8.8x\n",
               *(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
               *(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 0x10),
               *(undefined4 *)(param_2 + 0x14),*(undefined4 *)(param_2 + 0x18),
               *(undefined4 *)(param_2 + 0x1c),*(undefined4 *)(param_2 + 0x20));
      }
    }
  }
  sVar1 = *(short *)(param_2 + 0x2e);
joined_r0x00011c18:
  if (sVar1 == 2) {
    iVar4 = get_sw_port_from_devname(param_1[7],local_1c,0);
    if (iVar4 == 0) {
      __s1 = (char *)param_1[7];
      iVar4 = strcmp(__s1,"pon");
      if ((iVar4 == 0) || (iVar4 = strcmp(__s1,"ptm0"), iVar4 == 0)) {
        *(undefined1 *)(param_2 + 0x9e) = 5;
      }
      else {
        *(char *)(param_2 + 0x9e) = (char)local_1c[0];
      }
      if (2 < g_switch_debug_level) {
        printk("[sw_acl_setMtchInfo] ptSession->inputdev_name %s, p_zteHffEntry->inport %d, g_pon_work_mode[0x%x]\n"
               ,param_1[7],*(undefined1 *)(param_2 + 0x9e),g_pon_work_mode);
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("iret = %d\n");
    }
  }
  return;
}


/* ============= FUNCTION: hf_entry_police2 @ 00011dac ============= */

undefined4 hf_entry_police2(int param_1)

{
  undefined4 uVar1;
  uint *puVar2;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  if (param_1 == 0) {
    uVar1 = 0;
    if (g_switch_debug_level != 0) {
      printk("[%s] input ERROR: ptSession=NULL\n",DAT_00011e54);
      uVar1 = 0;
    }
  }
  else {
    zte_api_sw_fast_entry_policy(&local_10,&local_c,&local_18,&local_14);
    if (*(char *)(param_1 + 4) == '\0') {
      puVar2 = &DN_MAX_FAST_ENTRY;
    }
    else {
      puVar2 = &UP_MAX_FAST_ENTRY;
      local_14 = local_18;
      local_c = local_10;
    }
    if ((uint)(local_14 + local_c) < *puVar2) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ============= FUNCTION: sw_acl_add_port_flowconfig @ 00011e58 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_acl_add_port_flowconfig(undefined1 *param_1)

{
  void *__dest;
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_30 [12];
  
  __dest = (void *)kmem_cache_alloc(_DAT_0002c340,0xd0);
  if (__dest == (void *)0x0) {
    printk("switch ERR: sw_acl_add_port_flowconfig alloc mem failed\n");
    uVar2 = 0xffffffff;
  }
  else {
    __memzero(auStack_30,8);
    __memzero(__dest,0x49c);
    if (1 < g_switch_debug_level) {
      printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %x\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n"
             ,DAT_00012008,"FlowConfig.ruleType",*param_1,"FlowConfig.rule_pri",param_1[1],
             "FlowConfig.index",*(undefined2 *)(param_1 + 2),"FlowConfig.direction",
             *(undefined4 *)(param_1 + 4),"FlowConfig.match.entrynum",param_1[8],
             "FlowConfig.fwd.fwdmode",*(undefined4 *)(param_1 + 0x24c),"FlowConfig.fwd.desportmsk",
             *(undefined4 *)(param_1 + 0x250),"FlowConfig.fwd.gemport",
             *(undefined2 *)(param_1 + 0x254),"FlowConfig.fwd.des_q",param_1[0x256],
             "FlowConfig.fwd.reserved",param_1[599],"FlowConfig.action.actionnum",param_1[600]);
    }
    memcpy(__dest,param_1,0x49c);
    iVar1 = zte_api_sw_qos_add_port_streamselect(__dest,auStack_30);
    if (iVar1 == 0) {
      kfree(__dest);
      uVar2 = 0;
    }
    else {
      printk("[%s] L%d tm sdk failed!\n",DAT_00012008,0x58);
      kfree(__dest);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}


/* ============= FUNCTION: sw_acl_del_port_flowconfig @ 0001200c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_acl_del_port_flowconfig(undefined1 *param_1)

{
  void *__dest;
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_30 [12];
  
  __dest = (void *)kmem_cache_alloc(_DAT_0002c340,0xd0);
  if (__dest == (void *)0x0) {
    printk("switch ERR: sw_acl_del_port_flowconfig alloc mem failed\n");
    uVar2 = 0xffffffff;
  }
  else {
    __memzero(auStack_30,8);
    __memzero(__dest,0x49c);
    if (1 < g_switch_debug_level) {
      printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %x\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n"
             ,DAT_000121bc,"FlowConfig.ruleType",*param_1,"FlowConfig.rule_pri",param_1[1],
             "FlowConfig.index",*(undefined2 *)(param_1 + 2),"FlowConfig.direction",
             *(undefined4 *)(param_1 + 4),"FlowConfig.match.entrynum",param_1[8],
             "FlowConfig.fwd.fwdmode",*(undefined4 *)(param_1 + 0x24c),"FlowConfig.fwd.desportmsk",
             *(undefined4 *)(param_1 + 0x250),"FlowConfig.fwd.gemport",
             *(undefined2 *)(param_1 + 0x254),"FlowConfig.fwd.des_q",param_1[0x256],
             "FlowConfig.fwd.reserved",param_1[599],"FlowConfig.action.actionnum",param_1[600]);
    }
    memcpy(__dest,param_1,0x49c);
    iVar1 = zte_api_sw_qos_del_port_streamselect(__dest,auStack_30);
    if (iVar1 == 0) {
      kfree(__dest);
      uVar2 = 0;
    }
    else {
      printk("[%s] L%d tm sdk failed!\n",DAT_000121bc,0x81);
      kfree(__dest);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}


/* ============= FUNCTION: sw_acl_get_port_flowconfig @ 000121c0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_acl_get_port_flowconfig(uint *param_1)

{
  void *__dest;
  undefined4 extraout_r1;
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  uint *puVar6;
  undefined8 uVar7;
  uint local_30;
  uint uStack_2c;
  
  local_30 = 0;
  uStack_2c = 0;
  __dest = (void *)kmem_cache_alloc(_DAT_0002c340,0xd0);
  if (__dest == (void *)0x0) {
    printk("switch ERR: sw_acl_get_port_flowconfig alloc mem failed\n");
    return -1;
  }
  __memzero(__dest,0x49c);
  if (1 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n",DAT_000123f8,
           "FlowConfig.ruleType",(char)*param_1,"FlowConfig.rule_pri",
           *(undefined1 *)((int)param_1 + 1),"FlowConfig.index",*(undefined2 *)((int)param_1 + 2),
           "FlowConfig.direction",param_1[1],"FlowConfig.match.entrynum",(char)param_1[2]);
  }
  if ((char)param_1[2] != '\0') {
    puVar4 = param_1 + 8;
    iVar5 = 0;
    do {
      if (1 < g_switch_debug_level) {
        printk("FlowConfig.match.entry[%d.]field = %d\n",iVar5,puVar4[-5]);
      }
      puVar6 = puVar4 + -4;
      iVar2 = 0;
      uVar3 = g_switch_debug_level;
      do {
        if (1 < uVar3) {
          printk("FlowConfig.match.entry[%d].value[%d] = %x\n",iVar5,iVar2,(char)*puVar6);
          uVar3 = g_switch_debug_level;
        }
        iVar2 = iVar2 + 1;
        puVar6 = (uint *)((int)puVar6 + 1);
      } while (iVar2 != 0x10);
      iVar2 = 0;
      puVar6 = puVar4;
      do {
        if (1 < uVar3) {
          printk("FlowConfig.match.entry[%d].mask[%d] = %x\n",iVar5,iVar2,(char)*puVar6);
        }
        iVar2 = iVar2 + 1;
        puVar6 = (uint *)((int)puVar6 + 1);
        uVar3 = g_switch_debug_level;
      } while (iVar2 != 0x10);
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 9;
    } while (iVar5 < (int)(uint)(byte)param_1[2]);
  }
  memcpy(__dest,param_1,0x49c);
  uVar7 = zte_api_sw_qos_get_port_streamselect(__dest,&local_30);
  uVar1 = (undefined4)((ulonglong)uVar7 >> 0x20);
  iVar5 = (int)uVar7;
  if (iVar5 != 0) {
    if (g_switch_debug_level == 0) {
      uVar3 = (uint)*(ushort *)((int)param_1 + 2);
      goto LAB_000122c8;
    }
    printk("sw_acl_get_port_flowconfig is error: %d\n ",iVar5);
    uVar1 = extraout_r1;
  }
  uVar3 = (uint)*(ushort *)((int)param_1 + 2);
  if (1 < g_switch_debug_level) {
    printk("sw_acl_get_port_flowconfig result: %lld\n",uVar1,local_30,uStack_2c);
  }
LAB_000122c8:
  *param_1 = uVar3;
  param_1[2] = local_30;
  param_1[3] = uStack_2c;
  kfree(__dest);
  return iVar5;
}


/* ============= FUNCTION: sw_cla_show_aclrule @ 000123fc ============= */

undefined4 sw_cla_show_aclrule(void)

{
  return 0;
}


/* ============= FUNCTION: l3_hardfastReg @ 00012404 ============= */

void l3_hardfastReg(void)

{
  code *local_28;
  code *local_24;
  code *local_20;
  code *local_1c;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  
  local_28 = hf_set_l3_entry;
  local_24 = hf_del_l3_entry;
  local_20 = hf_query_l3_status;
  local_1c = hf_entry_police2;
  __memzero(&local_18,0x10);
  local_18 = 0x14;
  local_16 = 0x14;
  local_14 = 0x14;
  local_12 = 0x14;
  npu_hff_register(&local_28,&local_18);
  return;
}


/* ============= FUNCTION: l3_hardfastUnReg @ 00012470 ============= */

void l3_hardfastUnReg(void)

{
  return;
}


/* ============= FUNCTION: FROM_WAN @ 00012474 ============= */

bool FROM_WAN(char *param_1)

{
  int iVar1;
  
  if (2 < g_switch_debug_level) {
    printk("xmit dev name %s\n",param_1);
  }
  iVar1 = strncmp(param_1,"pon",3);
  return iVar1 != 0;
}


/* ============= FUNCTION: TO_WAN @ 000124c4 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool TO_WAN(char *param_1)

{
  int iVar1;
  bool bVar2;
  uint local_14;
  
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("dev name %s\n",param_1);
  }
  iVar1 = strncmp(param_1,"pon",3);
  if ((iVar1 == 0) || (iVar1 = strncmp(param_1,"ptm",3), iVar1 == 0)) {
    bVar2 = true;
  }
  else {
    iVar1 = strncmp(param_1,"eth",3);
    if (iVar1 != 0) {
      return false;
    }
    sscanf(param_1,"eth%u",&local_14);
    if (local_14 < 5) {
      bVar2 = _tm_vlan_check_ena_set == (byte)zte_api_sw_mac_set_port_macfiltermode[local_14];
    }
    else {
      if (g_switch_debug_level == 0) {
        return false;
      }
      printk("[%s] name=%s, wrong port=%d\n",DAT_000125dc,param_1);
      bVar2 = false;
    }
  }
  return bVar2;
}


/* ============= FUNCTION: sw_acl_l3_hardfast_session_add.part.1 @ 000125e0 ============= */

int sw_acl_l3_hardfast_session_add_part_1(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  byte bVar8;
  uint *puVar9;
  uint *puVar10;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  char local_b8 [4];
  undefined4 local_b4;
  undefined1 local_8c;
  short local_8a;
  undefined2 local_88;
  ushort local_86;
  undefined1 local_84;
  undefined1 local_83;
  undefined4 local_82;
  undefined2 local_7e;
  undefined4 local_7c;
  undefined2 local_78;
  undefined4 local_74;
  ushort local_64;
  byte local_50;
  ushort local_4e;
  undefined1 local_4c;
  undefined4 local_48;
  undefined1 local_44;
  uint local_34 [4];
  uint local_24;
  undefined2 local_20;
  undefined2 local_1e;
  byte local_1c;
  
  __memzero(local_b8,0xa0);
  iVar4 = TO_WAN(*(undefined4 *)(param_1 + 0x18));
  local_b8[0] = iVar4 == 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] direction(0-up 1=dw)=%d\n",DAT_00012c50,local_b8[0]);
  }
  if (1 < g_switch_debug_level) {
    printk("ip4Addr=%d, dest=%d, natip=%d, natport=%d, pip6Addr=%d, destport=%d, sdports=%d\n",
           *(undefined4 *)(param_1 + 4),*(undefined2 *)(param_1 + 10),
           *(undefined4 *)(param_1 + 0x20),*(undefined2 *)(param_1 + 0x2c),
           *(undefined4 *)(param_1 + 4),*(undefined2 *)(param_1 + 10),*(undefined4 *)(param_1 + 8));
  }
  if (*(char *)(param_1 + 0x14) == '\0') {
    sVar3 = local_8a;
    if (*(char *)(param_1 + 0x15) != '\0') {
      iVar4 = *(int *)(param_1 + 0xc);
      if (iVar4 == 0) {
        sVar3 = 0;
      }
      else {
        sVar3 = 1;
        if ((iVar4 != 1) && (sVar3 = local_8a, iVar4 == 2)) {
          sVar3 = 3;
        }
      }
    }
  }
  else {
    local_8a = 2;
    sVar3 = local_8a;
  }
  local_8a = sVar3;
  if (2 < g_switch_debug_level) {
    printk("uc_l2=%d, uc_l3=%d, l3Fast.l3_num=%d\n",*(char *)(param_1 + 0x14),
           *(undefined1 *)(param_1 + 0x15),local_8a);
  }
  sw_acl_setMtchInfo(param_1,local_b8);
  if (local_8a == 2) {
    if (param_1 == 0) {
      printk("[%s] params is NULL\n",DAT_00012c5c);
      goto LAB_00012b84;
    }
    local_84 = 0;
    local_8c = (undefined1)*(undefined2 *)(param_1 + 0x52);
    if ((*(byte *)(param_1 + 0x4d) & 8) == 0) {
      if (((*(byte *)(param_1 + 0x4d) & 0xc) == 4) && (local_b8[0] == '\0')) {
        local_86 = 0xffff;
        local_8c = 0xff;
      }
      else {
        local_86 = 0xffff;
      }
    }
    else {
      local_88 = 0xffff;
      local_86 = *(ushort *)(param_1 + 0x34) << 8 | *(ushort *)(param_1 + 0x34) >> 8;
    }
    if (g_switch_debug_level < 3) goto LAB_00012740;
    printk("l2 len %d,  cvlan %d, svlan %d\n",local_8c,local_88,local_86);
LAB_00012864:
    local_cc = 0;
    uVar6 = (*(ushort *)(param_1 + 0x34) & 0xff) << 8 | (uint)(*(ushort *)(param_1 + 0x34) >> 8);
    if (2 < g_switch_debug_level) {
      printk("bTxVlan %d, vlan %d\n",((uint)*(byte *)(param_1 + 0x4d) << 0x1c) >> 0x1f,uVar6);
    }
  }
  else {
    if (param_1 == 0) {
      printk("[%s] params is NULL\n",DAT_00012c54);
LAB_00012b84:
      local_cc = 0;
      printk("[%s] params is NULL\n",DAT_00012c58);
      goto LAB_000127a8;
    }
    local_82 = **(undefined4 **)(param_1 + 0x28);
    local_7e = *(undefined2 *)(*(undefined4 **)(param_1 + 0x28) + 1);
    local_7c = **(undefined4 **)(param_1 + 0x24);
    local_78 = *(undefined2 *)(*(undefined4 **)(param_1 + 0x24) + 1);
    local_84 = 0;
    if (*(int *)(param_1 + 0xc) == 2) {
      uVar2 = *(undefined2 *)(param_1 + 0x52);
      local_8c = (undefined1)uVar2;
joined_r0x00012a24:
      if (2 < g_switch_debug_level) {
        printk("l2_len %d, bTxVlan %d, bRxVlan %d, txVlan %d, rxVlan %d\n",uVar2,
               ((uint)*(byte *)(param_1 + 0x4d) << 0x1c) >> 0x1f,
               ((uint)*(byte *)(param_1 + 0x4d) << 0x1d) >> 0x1f,
               *(ushort *)(param_1 + 0x34) << 8 | *(ushort *)(param_1 + 0x34) >> 8,
               *(ushort *)(param_1 + 0x32) << 8 | *(ushort *)(param_1 + 0x32) >> 8);
      }
    }
    else {
      local_74 = *(undefined4 *)(param_1 + 0x20);
      local_64 = *(ushort *)(param_1 + 0x2c) << 8 | *(ushort *)(param_1 + 0x2c) >> 8;
      if (2 < g_switch_debug_level) {
        printk("set nat ip:0x%08x, set nat port %d\n",local_74,local_64);
        uVar2 = *(undefined2 *)(param_1 + 0x52);
        local_8c = (undefined1)uVar2;
        goto joined_r0x00012a24;
      }
      local_8c = (undefined1)*(undefined2 *)(param_1 + 0x52);
    }
    uVar6 = (uint)*(byte *)(param_1 + 0x4d);
    if ((*(byte *)(param_1 + 0x4d) & 8) == 0) {
      if (((uVar6 & 0xc) == 4) && (local_b8[0] == '\0')) {
        local_86 = 0xffff;
        local_8c = 0xff;
      }
      else {
        local_86 = 0xffff;
      }
    }
    else {
      local_88 = 0xffff;
      local_86 = *(ushort *)(param_1 + 0x34) << 8 | *(ushort *)(param_1 + 0x34) >> 8;
    }
    local_4e = *(ushort *)(param_1 + 0x2e) << 8 | *(ushort *)(param_1 + 0x2e) >> 8;
    local_50 = (byte)((uVar6 << 0x1f) >> 0x1f);
    if (2 < g_switch_debug_level) {
      printk("is ppp %d, set sessionid %d\n",uVar6 & 1,local_4e);
      if (*(int *)(param_1 + 0xc) == 2) goto LAB_00012804;
      goto LAB_00012864;
    }
    if (*(int *)(param_1 + 0xc) == 2) {
LAB_00012804:
      if (local_b8[0] == '\0') {
        local_4c = *(undefined1 *)(param_1 + 0x3c);
        puVar10 = (uint *)(*(int *)(param_1 + 0x44) + -4);
        local_48 = *(undefined4 *)(param_1 + 0x40);
        puVar9 = (uint *)(*(int *)(param_1 + 0x48) + -4);
        local_44 = *(undefined1 *)(param_1 + 0x3d);
        iVar4 = 0;
        pcVar7 = local_b8;
        do {
          puVar10 = puVar10 + 1;
          uVar6 = *puVar10;
          iVar4 = iVar4 + 1;
          *(uint *)(pcVar7 + 0x84) =
               uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
               uVar6 >> 0x18;
          puVar9 = puVar9 + 1;
          uVar6 = *puVar9;
          *(uint *)(pcVar7 + 0x94) =
               uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
               uVar6 >> 0x18;
          pcVar7 = pcVar7 + -4;
        } while (iVar4 != 4);
      }
      goto LAB_00012864;
    }
LAB_00012740:
    local_cc = 0;
    uVar6 = (*(ushort *)(param_1 + 0x34) & 0xff) << 8;
  }
  iVar4 = TO_WAN(*(undefined4 *)(param_1 + 0x18));
  if (iVar4 != 0) {
    bVar8 = *(byte *)(param_1 + 0x4d);
    if (g_switch_debug_level < 2) {
      local_1c = bVar8 & 8;
      local_20 = 0;
      if ((bVar8 & 8) != 0) {
        local_1c = (byte)(uVar6 >> 0xd);
      }
    }
    else {
      local_1c = *(byte *)(param_1 + 0x51);
      if ((bVar8 & 0x10) != 0) {
        local_83 = *(undefined1 *)(param_1 + 0x4c);
        local_84 = 1;
      }
      if (2 < g_switch_debug_level) {
        printk("sip %d, gemport %d, tcont %d, q %d\n",local_b4,local_1e,local_20,local_1c);
      }
    }
    goto LAB_000127a8;
  }
  get_sw_port_from_devname(*(undefined4 *)(param_1 + 0x18),&local_cc);
  local_1c = *(byte *)(param_1 + 0x51);
  local_1e = (undefined2)local_cc;
  if (g_switch_debug_level < 3) {
LAB_00012960:
    bVar8 = *(byte *)(param_1 + 0x4d);
    if ((bVar8 & 8) != 0) {
      uVar1 = *(ushort *)(param_1 + 0x34);
      goto LAB_00012978;
    }
LAB_00012a68:
    local_86 = 0xffff;
  }
  else {
    printk("down ptSession->outdev_name %s\n",*(undefined4 *)(param_1 + 0x18));
    if (2 < g_switch_debug_level) {
      printk("down uni port %d\n",local_1e);
      goto LAB_00012960;
    }
    bVar8 = *(byte *)(param_1 + 0x4d);
    if ((bVar8 & 8) == 0) goto LAB_00012a68;
    uVar1 = *(ushort *)(param_1 + 0x34);
LAB_00012978:
    local_88 = 0xffff;
    local_86 = uVar1 << 8 | uVar1 >> 8;
  }
  if ((bVar8 & 0x10) != 0) {
    if (*(int *)(param_1 + 0xc) == 0) {
      local_83 = *(undefined1 *)(param_1 + 0x4c);
      local_84 = 1;
    }
    else if (*(int *)(param_1 + 0xc) == 1) {
      local_84 = 1;
      local_83 = *(undefined1 *)(param_1 + 0x4c);
    }
  }
LAB_000127a8:
  iVar4 = zte_api_fast_l3_session_add(local_b8,&local_cc);
  if ((((iVar4 != 0) && (iVar5 = __printk_ratelimit(DAT_00012c4c), iVar5 != 0)) &&
      (g_switch_debug_level != 0)) && (iVar5 = ___ratelimit(&_rs_58399,DAT_00012c4c), iVar5 != 0)) {
    printk("[%s] zte_api_fast_l3_session_add failed %d\n",DAT_00012c50,iVar4);
  }
  *(undefined4 *)(param_1 + 0x58) = local_cc;
  *(undefined4 *)(param_1 + 0x5c) = local_c8;
  *(undefined4 *)(param_1 + 0x60) = uStack_c4;
  *(undefined4 *)(param_1 + 100) = uStack_c0;
  *(undefined4 *)(param_1 + 0x68) = uStack_bc;
  return iVar4;
}


/* ============= FUNCTION: sw_acl_l3_hardfast_session_del.part.3 @ 00012c60 ============= */

int sw_acl_l3_hardfast_session_del_part_3(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined1 local_b0 [4];
  undefined1 auStack_ac [156];
  
  __memzero(local_b0,0xa0);
  __memzero(&uStack_c4,0x14);
  iVar1 = TO_WAN(*(undefined4 *)(param_1 + 0x18));
  local_b0[0] = iVar1 == 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] direction(0-up 1=dw)=%d\n",DAT_00012d58,local_b0[0]);
  }
  sw_acl_setMtchInfo(param_1,local_b0);
  uStack_c4 = *(undefined4 *)(param_1 + 0x58);
  uStack_c0 = *(undefined4 *)(param_1 + 0x5c);
  local_bc = *(undefined4 *)(param_1 + 0x60);
  local_b8 = *(undefined4 *)(param_1 + 100);
  local_b4 = *(undefined4 *)(param_1 + 0x68);
  iVar1 = zte_api_fast_l3_session_del(auStack_ac,&uStack_c4);
  if (((iVar1 != 0) && (g_switch_debug_level != 0)) &&
     (iVar2 = ___ratelimit(DAT_00012d50,DAT_00012d54), iVar2 != 0)) {
    printk("[%s] sw_acl_del_port_flowconfig failed %d\n",DAT_00012d58,iVar1);
  }
  return iVar1;
}


/* ============= FUNCTION: TO_LAN @ 00012d5c ============= */

bool TO_LAN(char *param_1)

{
  int iVar1;
  
  iVar1 = strncmp(param_1,"sw",2);
  return iVar1 == 0;
}


/* ============= FUNCTION: sw_acl_l3_hardfast_session_add @ 00012d7c ============= */

undefined4
sw_acl_l3_hardfast_session_add(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  if (2 < g_switch_debug_level) {
    printk("enter sw_acl_l3_hardfast_session_add\n");
    param_2 = extraout_r1;
    param_3 = extraout_r2;
  }
  if (param_1 != 0) {
    uVar1 = sw_acl_l3_hardfast_session_add_part_1(param_1,param_2,param_3,param_4);
    return uVar1;
  }
  if (g_switch_debug_level != 0) {
    printk("[%s] input ERROR: ptSession=NULL\n",DAT_00012de4);
  }
  return 0xffffffff;
}


/* ============= FUNCTION: hf_set_l3_entry @ 00012de8 ============= */

undefined4 hf_set_l3_entry(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    printk("[%s]param is NULL\n",DAT_00012e7c);
    return 0;
  }
  iVar1 = sw_acl_l3_hardfast_session_add();
  if (iVar1 == 0) {
    return 1;
  }
  iVar1 = __printk_ratelimit(DAT_00012e74);
  if (((iVar1 != 0) && (g_switch_debug_level != 0)) &&
     (iVar1 = ___ratelimit(DAT_00012e78,DAT_00012e74), iVar1 != 0)) {
    printk("[%s] FAIL\n",DAT_00012e7c);
  }
  return 0;
}


/* ============= FUNCTION: sw_acl_l3_hardfast_session_del @ 00012e80 ============= */

undefined4
sw_acl_l3_hardfast_session_del(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    uVar1 = sw_acl_l3_hardfast_session_del_part_3();
    return uVar1;
  }
  if (g_switch_debug_level != 0) {
    printk("[%s] input ERROR: ptSession=NULL\n",DAT_00012ec0,param_3,g_switch_debug_level,param_4);
  }
  return 0xffffffff;
}


/* ============= FUNCTION: hf_del_l3_entry @ 00012ec4 ============= */

undefined4 hf_del_l3_entry(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    printk("[%s]param is NULL\n",DAT_00012f58);
    return 0;
  }
  iVar1 = sw_acl_l3_hardfast_session_del();
  if (iVar1 == 0) {
    return 1;
  }
  iVar1 = __printk_ratelimit(DAT_00012f50);
  if (((iVar1 != 0) && (g_switch_debug_level != 0)) &&
     (iVar1 = ___ratelimit(DAT_00012f54,DAT_00012f50), iVar1 != 0)) {
    printk("[%s] FAIL\n",DAT_00012f58);
  }
  return 0;
}


/* ============= FUNCTION: sw_acl_l3_hardfast_flowstatus @ 00012f5c ============= */

uint sw_acl_l3_hardfast_flowstatus(int param_1)

{
  uint uVar1;
  byte local_25;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_25 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[%s] input ERROR: ptSession=NULL\n",DAT_00013010);
      uVar1 = 0xffffffff;
    }
  }
  else {
    local_24 = *(undefined4 *)(param_1 + 0x58);
    local_20 = *(undefined4 *)(param_1 + 0x5c);
    local_1c = *(undefined4 *)(param_1 + 0x60);
    local_18 = *(undefined4 *)(param_1 + 100);
    local_14 = *(undefined4 *)(param_1 + 0x68);
    zte_api_fast_l3_session_use(0,&local_24,&local_25);
    if (2 < g_switch_debug_level) {
      printk("[%s] status = %d \n",DAT_00013010,local_25);
    }
    uVar1 = (uint)local_25;
  }
  return uVar1;
}


/* ============= FUNCTION: hf_query_l3_status @ 00013014 ============= */

undefined4 hf_query_l3_status(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 != (undefined4 *)0x0 && param_1 != 0) {
    iVar1 = sw_acl_l3_hardfast_flowstatus();
    if (iVar1 == 1) {
      *param_2 = 1;
    }
    else {
      *param_2 = 0;
    }
    return 1;
  }
  printk("[%s]param is NULL\n",DAT_00013060,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_acl_l3_hardfast_entry_show @ 00013064 ============= */

undefined4 sw_acl_l3_hardfast_entry_show(void)

{
  return 0;
}


/* ============= FUNCTION: sw_set_idm_isolate @ 0001306c ============= */

void sw_set_idm_isolate(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r2;
  
  uVar1 = fpga_read_reg(0xe20f6);
  if (param_1 == 0) {
    if (param_2 == 1) {
      uVar1 = uVar1 & 0xffffffbf;
    }
    else {
      uVar1 = uVar1 | 0x40;
    }
  }
  else if (param_1 == 1) {
    if (param_2 == 1) {
      uVar1 = uVar1 & 0xffffff7f;
    }
    else {
      uVar1 = uVar1 | 0x80;
    }
    fpga_write_reg(0xe20f6,uVar1,extraout_r2,param_4);
    return;
  }
  fpga_write_reg(0xe20f6,uVar1,extraout_r2,param_4);
  return;
}


/* ============= FUNCTION: sw_bridge_event @ 000130d0 ============= */

undefined4 sw_bridge_event(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_11;
  
  puVar3 = (undefined1 *)*param_3;
  uVar2 = param_3[2];
  if (param_2 == 2) {
    iVar1 = get_sw_port_from_devname(uVar2,&local_11,1);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("switch clear mac [%02x:%02x:%02x:%02x:%02x:%02x],port_dev.name %s,port=%d\n",*puVar3
               ,puVar3[1],puVar3[2],puVar3[3],puVar3[4],puVar3[5],uVar2,local_11);
      }
      iVar1 = zte_api_sw_mac_del_port_macaddress(local_11,puVar3,0,0);
      if ((iVar1 != 0) && (2 < g_switch_debug_level)) {
        printk("[%s] L%d  failed!\n","sw_bridge_event",0x9a);
      }
    }
    else if (2 < g_switch_debug_level) {
      printk("get_sw_port_from_devname fail, dev name %s\n",uVar2);
    }
  }
  return 0;
}


/* ============= FUNCTION: sw_set_wanport_qos @ 000131cc ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_set_wanport_qos(void)

{
  uint *puVar1;
  
  puVar1 = (uint *)(_tm_vlan_check_ena_set * 0x14 + -0xbe2bce8);
  *puVar1 = *puVar1 & 0xfffcffff;
  return;
}


/* ============= FUNCTION: sw_set_default_mulrule @ 000131fc ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_set_default_mulrule(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 auStack_28 [12];
  
  puVar1 = (undefined1 *)kmem_cache_alloc(_DAT_0002c340,0x20);
  if (puVar1 == (undefined1 *)0x0) {
    printk("switch ERR: sw_set_default_mulrule alloc mem failed\n");
    uVar3 = 0xffffffff;
  }
  else {
    puVar5 = puVar1 + 0x1f;
    __memzero(puVar1,0x49c);
    __memzero(auStack_28,8);
    puVar1[1] = 0;
    *(undefined2 *)(puVar1 + 2) = 0;
    *puVar1 = 100;
    *(undefined4 *)(puVar1 + 4) = 1;
    puVar1[8] = 1;
    *(undefined4 *)(puVar1 + 0xc) = 2;
    puVar4 = puVar5;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x2f);
    puVar1[0x1b] = 0;
    puVar1[600] = 0;
    puVar1[0x1a] = 1;
    *(undefined4 *)(puVar1 + 0x250) = 1;
    puVar1[0x2a] = 0xff;
    puVar1[0x2b] = 0xff;
    puVar1[0x2c] = 0xff;
    puVar1[0x1c] = 0x5e;
    *(undefined4 *)(puVar1 + 0x24c) = 3;
    puVar1[0x256] = 5;
    iVar2 = zte_api_sw_qos_add_port_streamselect(puVar1,auStack_28);
    if (iVar2 == 0) {
      __memzero(puVar1,0x49c);
      __memzero(auStack_28,8);
      puVar1[1] = 0;
      *(undefined2 *)(puVar1 + 2) = 0;
      *(undefined4 *)(puVar1 + 4) = 1;
      puVar1[8] = 1;
      *puVar1 = 100;
      *(undefined4 *)(puVar1 + 0xc) = 2;
      do {
        puVar5 = puVar5 + 1;
        *puVar5 = 0;
      } while (puVar5 != puVar1 + 0x2f);
      puVar1[600] = 0;
      puVar1[0x1a] = 0x33;
      puVar1[0x1b] = 0x33;
      puVar1[0x2a] = 0xff;
      puVar1[0x2b] = 0xff;
      *(undefined4 *)(puVar1 + 0x24c) = 3;
      *(undefined4 *)(puVar1 + 0x250) = 1;
      puVar1[0x256] = 5;
      iVar2 = zte_api_sw_qos_add_port_streamselect(puVar1,auStack_28);
      if (iVar2 == 0) {
        kfree(puVar1);
        uVar3 = 0;
      }
      else {
        printk("sw_set_default_ipv6_mulrule failed!\n");
        kfree(puVar1);
        uVar3 = 0xffffffff;
      }
    }
    else {
      printk("sw_set_default_ipv4_mulrule failed!\n");
      kfree(puVar1);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}


/* ============= FUNCTION: sw_set_default_protocol_rule @ 000133c0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_set_default_protocol_rule(void)

{
  sbyte sVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  uint uVar6;
  sbyte *local_38;
  undefined1 auStack_30 [12];
  
  puVar2 = (undefined1 *)kmem_cache_alloc(_DAT_0002c340,0x20);
  if (puVar2 == (undefined1 *)0x0) {
    printk("switch ERR: sw_set_default_protocol_rule alloc mem failed\n");
  }
  else {
    puVar5 = puVar2 + 0x1f;
    __memzero(puVar2,0x49c);
    __memzero(auStack_30,8);
    *(undefined2 *)(puVar2 + 2) = 0;
    puVar2[600] = 0;
    *puVar2 = 100;
    puVar2[1] = 0x2f;
    *(undefined4 *)(puVar2 + 0x24c) = 3;
    puVar2[8] = 1;
    *(undefined4 *)(puVar2 + 4) = 1;
    *(undefined4 *)(puVar2 + 0x250) = 1;
    puVar2[0x256] = 3;
    *(undefined4 *)(puVar2 + 0xc) = 2;
    puVar4 = puVar5;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar2 + 0x2f);
    puVar2[0x1a] = 1;
    puVar2[0x2a] = 0xff;
    puVar2[0x1c] = 0xc2;
    puVar2[0x2b] = 0xff;
    puVar2[0x2c] = 0xff;
    puVar2[0x1b] = 0x80;
    iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
    if (iVar3 == 0) {
      *(undefined4 *)(puVar2 + 0xc) = 0xd;
      do {
        puVar5 = puVar5 + 1;
        *puVar5 = 0;
      } while (puVar5 != puVar2 + 0x2f);
      puVar2[0x1d] = 0;
      puVar2[0x1e] = 0;
      puVar2[0x1f] = 0;
      puVar2[0x2f] = 0;
      puVar2[0x1c] = 0xe0;
      puVar2[0x2c] = 0xff;
      puVar2[0x2d] = 0xff;
      puVar2[0x2e] = 0xff;
      iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
      if (iVar3 == 0) {
        puVar2[8] = 2;
        puVar2[0x256] = 2;
        *(undefined4 *)(puVar2 + 4) = 0;
        puVar2[600] = 0;
        *(undefined4 *)(puVar2 + 0x250) = 0;
        *(undefined4 *)(puVar2 + 0x24c) = 3;
        __memzero(puVar2 + 0xc,0x240);
        uVar6 = _tm_port_unknwn_multicast_floodport_set;
        *(undefined4 *)(puVar2 + 0xc) = 0;
        if (uVar6 != 0) {
          local_38 = (sbyte *)((int)&tm_set_p2pmode + 3);
          uVar6 = 0;
          do {
            local_38 = local_38 + 1;
            sVar1 = *local_38;
            puVar2[0x2f] = 0xff;
            puVar2[0x1f] = (char)(1 << sVar1);
            *(undefined4 *)(puVar2 + 0x30) = 2;
            puVar4 = puVar2 + 0x43;
            do {
              puVar4 = puVar4 + 1;
              *puVar4 = 0;
            } while (puVar4 != puVar2 + 0x53);
            puVar2[0x3f] = 0x80;
            puVar2[0x3e] = 1;
            puVar2[0x4e] = 0xff;
            puVar2[0x4f] = 0xff;
            puVar2[0x50] = 0xff;
            puVar2[0x40] = 0xc2;
            iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
            if (iVar3 != 0) {
              printk("sw_set_default_protocol_rule failed!\n");
              kfree(puVar2);
              return 0xffffffff;
            }
            *(undefined4 *)(puVar2 + 0x30) = 0xd;
            puVar4 = puVar2 + 0x43;
            do {
              puVar4 = puVar4 + 1;
              *puVar4 = 0;
            } while (puVar4 != puVar2 + 0x53);
            puVar2[0x41] = 0;
            puVar2[0x42] = 0;
            puVar2[0x43] = 0;
            puVar2[0x53] = 0;
            puVar2[0x40] = 0xe0;
            puVar2[0x50] = 0xff;
            puVar2[0x51] = 0xff;
            puVar2[0x52] = 0xff;
            iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
            if (iVar3 != 0) goto LAB_00013648;
            uVar6 = uVar6 + 1;
          } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
        }
        kfree(puVar2);
        return 0;
      }
    }
LAB_00013648:
    printk("sw_set_default_protocol_rule failed!\n");
    kfree(puVar2);
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_set_p2pmode @ 00013680 ============= */

void sw_set_p2pmode(void)

{
  code cVar1;
  
  cVar1 = tm_vlan_check_ena_set;
  printk("sw_set_uni_as_wan uni=%d\n",tm_vlan_check_ena_set);
  tm_set_p2pmode(cVar1);
  return;
}


/* ============= FUNCTION: chip_tm_init @ 000136ac ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void chip_tm_init(void)

{
  undefined1 uVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  undefined4 *puVar14;
  uint uVar15;
  byte *pbVar16;
  undefined1 auStack_d6 [2];
  undefined4 local_d4;
  undefined4 local_d0;
  undefined1 local_cc;
  undefined1 local_cb;
  undefined1 local_ca;
  undefined4 local_c8;
  undefined1 local_c4;
  undefined1 local_c0 [4];
  undefined1 local_bc;
  undefined1 local_bb;
  undefined4 local_b8;
  undefined1 local_b0 [4];
  undefined1 local_ac;
  undefined1 local_ab;
  undefined1 local_aa;
  undefined4 local_a8;
  undefined1 local_a0;
  undefined1 local_9f;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_90;
  undefined1 local_88 [4];
  undefined1 local_84;
  undefined4 local_80;
  undefined1 local_7c;
  undefined4 local_78;
  undefined2 local_74;
  undefined4 local_70;
  uint local_6c [11];
  undefined1 local_40;
  undefined4 local_3c;
  undefined1 local_38;
  undefined1 local_37;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  
  local_d4 = 0;
  local_70 = 8000;
  local_d0 = 0;
  local_6c[0] = 0;
  local_6c[1] = 0;
  local_6c[2] = 0;
  local_6c[3] = 0;
  local_6c[4] = 0;
  local_6c[5] = 0;
  local_6c[6] = 0;
  __memzero(local_6c + 7,0x28);
  __memzero(&local_a0,0x18);
  __memzero(&local_cc,0xc);
  __memzero(auStack_d6,2);
  __memzero(local_c0,0x10);
  __memzero(local_88,0x18);
  __memzero(local_b0,0x10);
  if ((g_switch_debug_level & 0xfffffffd) == 1) {
    local_3c = 0;
    local_40 = 0;
    local_6c[10] = 0;
    local_6c[7] = 1;
  }
  else if (g_switch_debug_level == 0) {
    local_6c[7] = g_switch_debug_level;
    local_40 = 0;
    local_3c = 1;
    local_6c[10] = 1;
  }
  else if (g_switch_debug_level == 2) {
    local_3c = 0;
    local_6c[7] = 1;
    local_40 = 1;
    local_6c[10] = 1;
  }
  local_2e = 0x88a8;
  local_6c[8] = 0;
  local_6c[9] = 1;
  local_38 = 1;
  local_37 = 1;
  local_34 = 2000;
  local_32 = 0x8100;
  local_30 = 0x9100;
  local_2c = 0x9200;
  iVar3 = zte_api_sw_global_init(local_6c + 7);
  if (iVar3 != 0) {
    printk("zte_zx_api_sw_global_init failed!!!!\n");
  }
  pbVar2 = DAT_00013cf0;
  if (_tm_set_p2pmode == 0) {
    uVar13 = 8000;
  }
  else {
    uVar10 = 0;
    uVar15 = 0;
    pbVar16 = DAT_00013cf0;
    do {
      if (uVar15 < _tm_port_unknwn_multicast_floodport_set) {
        uVar10 = (uint)*pbVar16;
      }
      else if ((uVar15 == _tm_port_unknwn_multicast_floodport_set) && (*(int *)(pbVar2 + 0x38) != 0)
              ) {
        uVar10 = (uint)ponPort;
      }
      else if ((uVar15 == _tm_port_unknwn_multicast_floodport_set + 1) && (DAT_0002c0e2 != 0)) {
        uVar10 = (uint)pbVar2[0x3c];
      }
      else if ((uVar15 == _tm_port_unknwn_multicast_floodport_set + 2) && (DAT_0002c0e6 != 0)) {
        uVar10 = (uint)pbVar2[0x40];
      }
      uVar1 = (undefined1)uVar10;
      local_cb = uVar10 != _tm_vlan_check_ena_set;
      local_c8 = 1;
      local_c4 = 1;
      local_cc = uVar1;
      local_ca = local_cb;
      uVar4 = zte_api_sw_port_init(&local_cc);
      uVar5 = zte_api_sw_vlan_set_port_pvid(uVar10,0,0);
      uVar6 = zte_api_sw_vlan_set_port_vlancfg(uVar10,0,0,3);
      uVar6 = uVar5 | uVar4 | uVar6;
      if ((g_switch_debug_level & 0xfffffffd) == 1) {
        uVar4 = zte_api_sw_vlan_set_port_vlancfg(uVar10,0,0xfff,3);
        uVar6 = uVar6 | uVar4;
      }
      else if ((g_switch_debug_level & 0xfffffffd) == 0) {
        uVar4 = zte_api_sw_vlan_set_port_vlancfg(uVar10,0,0,3);
        uVar6 = uVar6 | uVar4;
      }
      if (uVar10 == _tm_vlan_check_ena_set) {
        uVar4 = zte_api_sw_vlan_set_port_vlancfg(uVar10,0,0xfff,3);
        uVar6 = uVar6 | uVar4;
        if (wanLogicPort != -1) {
          uVar4 = zte_api_sw_vlan_set_port_vlancfg(ponPort,0,0xfff,3);
          uVar6 = uVar6 | uVar4;
        }
      }
      uVar4 = lan_up;
      if ((_zte_api_pp_set_cpu_queue_rate != uVar10) && (*(ushort *)(pbVar2 + 0x40) != uVar10)) {
        uVar4 = *(uint *)(pbVar2 + 0x44) & ~(1 << uVar10);
      }
      iVar3 = zte_api_sw_port_set_port_isolatemask(uVar10,~uVar4);
      local_bc = 0;
      local_bb = 0;
      local_b8 = 0;
      local_c0[0] = uVar1;
      iVar7 = zte_api_sw_set_port_brdcast(local_c0);
      local_84 = 1;
      if ((g_switch_debug_level & 0xfffffffd) == 1) {
        if (ponPort == uVar10) {
LAB_000139c4:
          local_7c = 1;
        }
        else {
          local_7c = 0;
        }
      }
      else if ((g_switch_debug_level & 0xfffffffd) == 0) goto LAB_000139c4;
      local_80 = 1;
      local_78 = 0;
      local_74 = 0;
      local_88[0] = uVar1;
      iVar8 = zte_api_sw_set_port_unicast(local_88);
      local_ab = 0;
      local_aa = 0;
      local_ac = 1;
      if ((_zte_api_pp_set_cpu_queue_rate == uVar10) || (*(ushort *)(pbVar2 + 0x40) == uVar10)) {
        if ((g_switch_debug_level & 0xfffffffd) == 1) {
          local_a8 = 2;
        }
        else if ((g_switch_debug_level & 0xfffffffd) == 0) goto LAB_00013954;
      }
      else {
LAB_00013954:
        local_a8 = 0;
      }
      local_b0[0] = uVar1;
      iVar9 = zte_api_sw_set_port_muticast(local_b0);
      if ((((iVar3 != 0 || iVar7 != 0) || uVar6 != 0) || iVar8 != 0) || iVar9 != 0) {
        printk("zte_zx_api_sw_port_init fails!!!!\n");
      }
      uVar15 = uVar15 + 1;
      pbVar16 = pbVar16 + 1;
      uVar13 = local_70;
    } while (uVar15 < _tm_set_p2pmode);
  }
  local_9f = 1;
  if ((g_switch_debug_level & 0xfffffffd) == 1) {
    local_a0 = 0;
    local_9c = 1;
    local_98 = 1;
  }
  else if ((g_switch_debug_level & 0xfffffffd) == 0) {
    local_9c = 1;
    local_a0 = 1;
    local_98 = 2;
  }
  local_90 = 1;
  iVar3 = zte_api_pp_global_init(&local_a0);
  if (iVar3 != 0) {
    printk("zte_zx_api_pp_global_init  fails!!!!\n",uVar13);
  }
  puVar12 = &local_70;
  uVar10 = 0;
  while( true ) {
    uVar15 = uVar10 & 0xff;
    uVar10 = uVar10 + 1;
    iVar3 = zte_api_pp_set_cpu_queue_rate(uVar15,uVar13);
    if (uVar10 == 8) break;
    puVar12 = puVar12 + 1;
    uVar13 = *puVar12;
  }
  if (iVar3 != 0) {
    printk("zte_zx_api_pp_set_cpu_queue_rate  fails!!!!\n");
  }
  puVar14 = DAT_00013cf4 + 0xa4;
  puVar12 = DAT_00013cf4;
  do {
    uVar13 = *puVar12;
    puVar11 = puVar12 + 2;
    iVar3 = zte_api_pp_set_trap_queue(0,uVar13,*(undefined1 *)(puVar12 + 1));
    iVar7 = zte_api_pp_set_trap_queue(1,uVar13,*(undefined1 *)((int)puVar12 + 5));
    iVar8 = tm_protocol_pkt_limit_pps_set(0,5,1,8000);
    iVar9 = tm_protocol_pkt_limit_pps_set(1,5,1,8000);
    puVar12 = puVar11;
  } while (puVar11 != puVar14);
  if (((iVar8 != 0 || iVar9 != 0) || iVar7 != 0) || iVar3 != 0) {
    printk("zte_zx_api_pp_set_trap_queue  fails!!!!\n");
  }
  puVar14 = DAT_00013cf8 + 0xd5;
  puVar12 = DAT_00013cf8;
  do {
    uVar13 = *puVar12;
    puVar11 = puVar12 + 3;
    iVar3 = zte_api_pp_set_pro_action(0,uVar13,puVar12[1]);
    iVar7 = zte_api_pp_set_pro_action(1,uVar13,puVar12[2]);
    puVar12 = puVar11;
  } while (puVar11 != puVar14);
  if (iVar7 != 0 || iVar3 != 0) {
    printk("zte_zx_api_pp_set_pro_action  fails!!!!\n");
  }
  iVar3 = tm_cla_outspace_cfg_get(&local_d4,&local_d0);
  iVar7 = tm_cla_outspace_cfg_set(1,local_d0);
  if (iVar7 != 0 || iVar3 != 0) {
    printk("tm_cla_outspace_cfg_get/set fails!!!!\n");
  }
  printk("-------chip_tm_init end-----\n");
  return;
}


/* ============= FUNCTION: sw_reg_set_onu_swcap @ 00013cfc ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_reg_set_onu_swcap(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined1 *puVar6;
  bool bVar7;
  byte local_2b;
  byte local_2a;
  byte local_29;
  int local_28;
  int local_24 [2];
  
  uVar3 = 0;
  local_2b = 0;
  __memzero(&g_sw_cap,0x5c);
  __memzero(&local_2a,2);
  CspGetPortInfo(local_24);
  CspGetSwInfo(&local_28);
  iVar1 = *(int *)(local_28 + 8);
  if ((8 < iVar1) || (8 < *(ushort *)(local_24[0] + 2))) {
    if (g_switch_debug_level == 0) {
      return;
    }
    printk("[%s]:get eth cnt %d is larger than %d.\n",DAT_000140b8,iVar1,8);
    return;
  }
  _tm_port_unknwn_multicast_floodport_set = iVar1;
  if (iVar1 != 0) {
    puVar6 = (undefined1 *)0x2c0a3;
    iVar1 = local_28;
    puVar4 = &g_sw_cap;
    do {
      iVar2 = iVar1 + uVar3 * 0xc;
      uVar5 = (uint)*(ushort *)(iVar2 + 0x12);
      puVar6 = puVar6 + 1;
      *puVar6 = (char)*(ushort *)(iVar2 + 0x12);
      zte_api_sw_port_set_port_isolatemask[uVar5] = SUB41(uVar3,0);
      *(undefined2 *)((int)puVar4 + 0x1e) = *(undefined2 *)(iVar2 + 0x16);
      *(char *)(puVar4 + 7) = (char)*(undefined2 *)(iVar2 + 0x14);
      *(char *)((int)puVar4 + 0x1d) = (char)*(undefined2 *)(iVar2 + 0x10);
      bVar7 = *(uint *)(iVar1 + 4) != uVar3;
      uVar3 = uVar3 + 1;
      if (bVar7) {
        if (7 < uVar5) {
          printk("the switch port is error!!!\n");
          iVar1 = local_28;
        }
        _zte_api_sw_mac_set_port_learnlimit =
             _zte_api_sw_mac_set_port_learnlimit | 1 << (uVar5 & 0xff);
      }
      puVar4 = puVar4 + 1;
    } while (uVar3 < *(uint *)(iVar1 + 8));
  }
  zte_api_sw_get_pon_port(&local_2b);
  ponPort = local_2b;
  if ((g_pon_work_mode & 0x10) == 0) {
    _tm_broadcst_vltrans_table_print_get = 1 << (uint)local_2b;
    _tm_vlan_check_ena_set = (uint)local_2b;
  }
  else {
    iVar1 = *(int *)(local_28 + 4);
    wanLogicPort = (undefined1)iVar1;
    if (iVar1 != -1) {
      local_2b = *(byte *)(iVar1 * 0xc + local_28 + 0x12);
      _tm_broadcst_vltrans_table_print_get = 1 << (uint)local_2b;
      _tm_vlan_check_ena_set = (uint)local_2b;
    }
  }
  if (*(short *)(local_24[0] + 8) == 0) {
    iVar1 = 0;
  }
  else {
    zte_api_sw_get_wlan_port(&local_2a);
    iVar1 = 2;
    DAT_0002c0e2 = (ushort)(1 << (uint)local_2a);
    _zte_api_pp_set_cpu_queue_rate = (ushort)local_2a;
    DAT_0002c0e6 = (ushort)(1 << (uint)local_29);
    _eth_type_trans = (ushort)local_29;
  }
  uVar5 = g_pon_work_mode;
  bVar7 = (g_pon_work_mode & 0x10) == 0;
  g_pon_work_mode = 1;
  lan_up = _zte_api_sw_mac_set_port_learnlimit | _tm_broadcst_vltrans_table_print_get |
           (uint)DAT_0002c0e2 | (uint)DAT_0002c0e6;
  tm_set_p2pmode = _tm_port_unknwn_multicast_floodport_set + 1 + iVar1;
  uVar3 = (uint)bVar7;
  if ((bVar7) && ((uVar5 & 0x20) == 0)) {
    if ((uVar5 & 0x40) == 0) {
      if ((uVar5 & 0x100) == 0) {
        if ((uVar5 & 0x80) == 0) {
          if ((uVar5 & 0x200) == 0) {
            if ((uVar5 & 0x400) == 0) {
              if ((uVar5 & 0x800) == 0) {
                printk("config wan_type outof range! g_pon_work_mode = %d. \n");
                uVar3 = 0;
              }
              else {
                uVar3 = 7;
              }
            }
            else {
              uVar3 = 6;
            }
          }
          else {
            uVar3 = 5;
          }
        }
        else {
          uVar3 = 3;
        }
      }
      else {
        uVar3 = 2;
      }
    }
    else {
      uVar3 = 4;
    }
  }
  if ((g_pon_work_mode & 0x1a0) == 0) {
    if ((g_pon_work_mode & 0xe40) == 0) goto LAB_00013f80;
    if (g_pon_work_mode == 1) {
      g_switch_debug_level = 3;
      goto LAB_00013f80;
    }
    if (g_pon_work_mode != 0) goto LAB_00013f80;
    uVar5 = 2;
  }
  else {
    uVar5 = g_pon_work_mode;
    if ((g_pon_work_mode != 1) && (g_pon_work_mode != 0)) goto LAB_00013f80;
  }
  g_switch_debug_level = uVar5;
LAB_00013f80:
  if ((g_pon_work_mode & 0x10) != 0) {
    g_switch_debug_level = 3;
    lan_up = lan_up | 1 << ponPort;
  }
  g_sw_cap = uVar3;
  printk("g_sw_cap.sw_uni_count=%d\n",_tm_port_unknwn_multicast_floodport_set);
  printk("g_sw_cap.sw_uni_mask=0x%x\n",_zte_api_sw_mac_set_port_learnlimit);
  printk("g_sw_cap.sw_wan_port=%d\n",_tm_vlan_check_ena_set);
  printk("g_sw_cap.sw_wan_mask=0x%x\n",_tm_broadcst_vltrans_table_print_get);
  printk("g_sw_cap.sw_all_port_count=%d\n",tm_set_p2pmode);
  printk("g_sw_cap.sw_all_port_mask=0x%x\n",lan_up);
  printk("g_sw_cap.gwtype%d\n",g_pon_work_mode);
  printk("g_sw_cap.wantype%d\n",g_sw_cap);
  printk("g_sw_cap.onutype%d\n",g_switch_debug_level);
  printk("ptSwInfo->wan_logicport=%d\n",*(undefined4 *)(local_28 + 4));
  return;
}


/* ============= FUNCTION: sw_init_switch @ 000140bc ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_init_switch(void)

{
  undefined4 uVar1;
  uint *puVar2;
  
  sw_reg_set_onu_swcap();
  sw_init_wlan_ssid();
  pdt_ethdriver_init();
  if ((g_pon_work_mode & 0x10) != 0) {
    sw_set_p2pmode();
  }
  chip_tm_init();
  if (g_pon_work_mode == 1) {
    tm_acl_l2_fast_init();
    printk("[SW][sw_init_switch] l2_fast init\n");
  }
  sw_set_default_mulrule();
  sw_set_default_protocol_rule();
  if (g_pon_work_mode == 1) {
    sw_hgu_multi_config_init();
  }
  else {
    sw_sfu_multi_config_init();
  }
  sw_alarm_init();
  printk("[SW][sw_init_switch] reg hff\n");
  l3_hardfastReg();
  sw_qos_init();
  uVar1 = DAT_0001417c;
  puVar2 = (uint *)(_tm_vlan_check_ena_set * 0x14 + -0xbe2bce8);
  *puVar2 = *puVar2 & 0xfffcffff;
  register_bridge_notifier(uVar1);
  return;
}


/* ============= FUNCTION: sw_mac_set_port_macfiltermode @ 00014180 ============= */

undefined4
sw_mac_set_port_macfiltermode(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code cVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input port %d mode %d\n","sw_mac_set_port_macfiltermode",cVar1,(char)iVar2,param_4)
    ;
  }
  iVar2 = zte_api_sw_mac_set_port_macfiltermode(cVar1,(char)iVar2);
  if (iVar2 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_mac_set_port_macfiltermode",0x27);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mac_get_port_macfiltermode @ 00014204 ============= */

undefined4
sw_mac_get_port_macfiltermode
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00014220,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_mac_add_port_macfilterentry @ 00014224 ============= */

undefined4 sw_mac_add_port_macfilterentry(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_2e;
  undefined2 local_2a;
  
  iVar3 = param_1[4];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = param_1[3];
  __memzero(&local_2e,6);
  local_2e = param_1[1];
  local_2a = (undefined2)param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n",DAT_00014344,
           "MacEntry.port",*param_1,"MacEntry.mac",(char)param_1[1],
           *(undefined1 *)((int)param_1 + 5),*(undefined1 *)((int)param_1 + 6),
           *(undefined1 *)((int)param_1 + 7),(char)param_1[2],*(undefined1 *)((int)param_1 + 9),
           "MacEntry.vid",param_1[3],"MacEntry.mode",param_1[4]);
  }
  iVar3 = zte_api_sw_mac_add_port_macfilterentry(cVar1,&local_2e,(short)iVar2,(char)iVar3);
  uVar4 = 0;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00014344,0x4c);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_mac_del_port_macfilterentry @ 00014348 ============= */

undefined4 sw_mac_del_port_macfilterentry(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_2e;
  undefined2 local_2a;
  
  iVar3 = param_1[4];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = param_1[3];
  __memzero(&local_2e,6);
  local_2e = param_1[1];
  local_2a = (undefined2)param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n",DAT_00014468,
           "MacEntry.port",*param_1,"MacEntry.mac",(char)param_1[1],
           *(undefined1 *)((int)param_1 + 5),*(undefined1 *)((int)param_1 + 6),
           *(undefined1 *)((int)param_1 + 7),(char)param_1[2],*(undefined1 *)((int)param_1 + 9),
           "MacEntry.vid",param_1[3],"MacEntry.mode",param_1[4]);
  }
  iVar3 = zte_api_sw_mac_del_port_macfilterentry(cVar1,&local_2e,(short)iVar2,(char)iVar3);
  uVar4 = 0;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00014468,0x6a);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_mac_get_port_macfilterentry @ 0001446c ============= */

undefined4
sw_mac_get_port_macfilterentry
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00014488,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_mac_set_onu_stpaction @ 0001448c ============= */

undefined4 sw_mac_set_onu_stpaction(undefined1 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  uint local_1e;
  undefined2 local_1a;
  
  uVar1 = *param_1;
  uVar2 = param_1[0xc];
  __memzero(&local_1e,6);
  local_1e = *(uint *)(param_1 + 4);
  local_1a = *(undefined2 *)(param_1 + 8);
  if (2 < g_switch_debug_level) {
    local_1a._1_1_ = (undefined1)((ushort)local_1a >> 8);
    uVar3 = local_1a._1_1_;
    uVar4 = (undefined1)local_1a;
    printk("[%s] input:\n mode = %d mac = %2x:%2x:%2x:%2x:%2x:%2x action = %d\n",DAT_00014550,uVar1,
           local_1e & 0xff,local_1e >> 8 & 0xff,local_1e >> 0x10 & 0xff,local_1e >> 0x18,uVar4,uVar3
           ,uVar2);
  }
  iVar5 = zte_api_sw_mac_set_onu_stpaction(uVar1,&local_1e,uVar2);
  uVar6 = 0;
  if (iVar5 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00014550,0x88);
    uVar6 = 0xffffffff;
  }
  return uVar6;
}


/* ============= FUNCTION: sw_mac_get_onu_stpaction @ 00014554 ============= */

undefined4
sw_mac_get_onu_stpaction
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00014570,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_mac_set_onu_proaction @ 00014574 ============= */

undefined4
sw_mac_set_onu_proaction
          (undefined1 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[4];
  if (2 < g_switch_debug_level) {
    printk("[%s] input type %d action %d\n",DAT_000145e0,uVar1,uVar2,param_4);
  }
  iVar3 = zte_api_sw_mac_set_onu_proaction(uVar1,uVar2);
  if (iVar3 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n",DAT_000145e0,0xa1);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mac_get_onu_proaction @ 000145e4 ============= */

undefined4
sw_mac_get_onu_proaction
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00014600,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_mac_set_onu_agingtime @ 00014604 ============= */

undefined4 sw_mac_set_onu_agingtime(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_mac_set_onu_agingtime","AgingTime.time",uVar2);
  }
  iVar1 = zte_api_sw_mac_set_onu_agingtime(uVar2);
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_mac_set_onu_agingtime",0x2d);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mac_get_onu_agingtime @ 00014674 ============= */

undefined4 sw_mac_get_onu_agingtime(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = zte_api_sw_mac_get_onu_agingtime(local_14);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (2 < g_switch_debug_level) {
      printk("[%s] output:\n%s = %d\n",DAT_000146fc,"AgingTime.time");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_000146fc,0x3b);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_mac_set_port_learnlimit @ 00014700 ============= */

undefined4 sw_mac_set_port_learnlimit(int *param_1)

{
  code cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = param_1[1];
  iVar3 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n",DAT_000147b0,"LearnLimit.port",*param_1,
           "LearnLimit.enable",uVar4,"LearnLimit.limit",iVar3);
  }
  iVar3 = zte_api_sw_mac_set_port_learnlimit(cVar1,uVar4 & 0xff,iVar3);
  uVar2 = 0;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_000147b0,0x56);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_mac_get_port_learnlimit @ 000147b4 ============= */

undefined4 sw_mac_get_port_learnlimit(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte local_15;
  int local_14;
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_15 = 0;
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_00014898,"LearnLimit.port");
  }
  iVar3 = zte_api_sw_mac_get_port_learnlimit(cVar1,&local_15,&local_14);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_15;
    param_1[2] = local_14;
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n%s = %d\n",DAT_00014898,"LearnLimit.enable",(uint)local_15,
             "LearnLimit.limit",local_14);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00014898,0x6a);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_mac_add_port_macaddress @ 0001489c ============= */

undefined4 sw_mac_add_port_macaddress(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_2e;
  undefined2 local_2a;
  
  iVar3 = param_1[4];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = param_1[3];
  __memzero(&local_2e,6);
  local_2e = param_1[1];
  local_2a = (undefined2)param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n",DAT_000149bc,
           "MacEntry.port",*param_1,"MacEntry.mac",(char)param_1[1],
           *(undefined1 *)((int)param_1 + 5),*(undefined1 *)((int)param_1 + 6),
           *(undefined1 *)((int)param_1 + 7),(char)param_1[2],*(undefined1 *)((int)param_1 + 9),
           "MacEntry.vid",param_1[3],"MacEntry.mode",param_1[4]);
  }
  iVar3 = zte_api_sw_mac_add_port_macaddress(cVar1,&local_2e,(short)iVar2,(char)iVar3);
  uVar4 = 0;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_000149bc,0x91);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_mac_del_port_macaddress @ 000149c0 ============= */

undefined4 sw_mac_del_port_macaddress(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_2e;
  undefined2 local_2a;
  
  iVar3 = param_1[4];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = param_1[3];
  __memzero(&local_2e,6);
  local_2e = param_1[1];
  local_2a = (undefined2)param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n",DAT_00014ae0,
           "MacEntry.port",*param_1,"MacEntry.mac",(char)param_1[1],
           *(undefined1 *)((int)param_1 + 5),*(undefined1 *)((int)param_1 + 6),
           *(undefined1 *)((int)param_1 + 7),(char)param_1[2],*(undefined1 *)((int)param_1 + 9),
           "MacEntry.vid",param_1[3],"MacEntry.mode",param_1[4]);
  }
  iVar3 = zte_api_sw_mac_del_port_macaddress(cVar1,&local_2e,(short)iVar2,(char)iVar3);
  uVar4 = 0;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00014ae0,0xb1);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_mac_show_macaddress @ 00014ae4 ============= */

undefined4 sw_mac_show_macaddress(void)

{
  int iVar1;
  
  iVar1 = tm_mactable_print_get();
  if (iVar1 == 0) {
    return 0;
  }
  printk("%s %d failed!\n",DAT_00014b10,0xbd);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mac_clear_macaddress @ 00014b14 ============= */

undefined4 sw_mac_clear_macaddress(void)

{
  int iVar1;
  
  iVar1 = zte_api_sw_mac_clear_macaddress();
  if (iVar1 == 0) {
    return 0;
  }
  printk("%s %d failed!\n",DAT_00014b40,0xc9);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mac_show_port_mactable @ 00014b44 ============= */

undefined4
sw_mac_show_port_mactable
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00014b60,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_mac_clear_port_mactable @ 00014b64 ============= */

undefined4
sw_mac_clear_port_mactable(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code cVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_00014be0,"MacTable.port",*param_1,param_4);
  }
  iVar2 = zte_api_sw_mac_clear_port_mactable(cVar1,(char)iVar2);
  if (iVar2 == 0) {
    return 0;
  }
  printk("%s %d failed!\n",DAT_00014be0,0xe1);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mac_get_port_learnnum @ 00014be4 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_mac_get_port_learnnum(uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint local_14;
  
  uVar2 = *param_1;
  local_14 = 0;
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_mac_learning_number_get(zte_api_sw_mac_set_port_macfiltermode[uVar2],&local_14);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("sw_mac_get_port_learnnum output:\nport=%d\nlearnnum=%d\n",uVar2,local_14);
      }
      iVar1 = 0;
      param_1[1] = local_14;
    }
    else if (g_switch_debug_level != 0) {
      printk("sw_mac_get_port_learnnum return error!\nerror code=%x\n",iVar1);
    }
  }
  else {
    printk("[%s]%d input port error!\n",DAT_00014ca8,0xfb);
    iVar1 = -1;
  }
  return iVar1;
}


/* ============= FUNCTION: sw_mac_get_onu_macentrynum @ 00014cac ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_mac_get_onu_macentrynum(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  int local_1c;
  
  uVar2 = 0;
  local_1c = 0;
  iVar3 = 0;
  if (_tm_port_unknwn_multicast_floodport_set != 0) {
    puVar4 = (undefined1 *)((int)&tm_set_p2pmode + 3);
    iVar3 = 0;
    do {
      puVar4 = puVar4 + 1;
      iVar1 = tm_mac_learning_number_get(*puVar4,&local_1c);
      uVar2 = uVar2 + 1;
      if (iVar1 != 0) {
        if (g_switch_debug_level != 0) {
          printk("sw_mac_get_onu_macentrynum return error!\nerror code=%x\n",iVar1);
        }
        return iVar1;
      }
      iVar3 = iVar3 + local_1c;
    } while (uVar2 < _tm_port_unknwn_multicast_floodport_set);
  }
  if (2 < g_switch_debug_level) {
    printk("sw_mac_get_onu_macentrynum output:\tlearnnum=%d\n",iVar3);
  }
  return 0;
}


/* ============= FUNCTION: sw_mac_add_cpu_macaddress @ 00014d74 ============= */

int sw_mac_add_cpu_macaddress(int param_1)

{
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  char local_27;
  undefined4 local_26;
  undefined2 local_22;
  
  if (param_1 == 0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_mac_add_cpu_macaddress] input ERROR! ioctl_data_sweth=NULL\n");
    }
  }
  else {
    __memzero(&local_27,7);
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_mac_add_cpu_macaddress] input: mac=%x:%x:%x:%x:%x:%x\n",
             *(undefined1 *)(param_1 + 4),*(undefined1 *)(param_1 + 5),*(undefined1 *)(param_1 + 6),
             *(undefined1 *)(param_1 + 7),*(undefined1 *)(param_1 + 8),*(undefined1 *)(param_1 + 9))
      ;
    }
    iVar6 = -1;
    iVar4 = 7;
    local_26 = *(undefined4 *)(param_1 + 4);
    local_22 = *(undefined2 *)(param_1 + 8);
    pcVar5 = DAT_00014f44;
    do {
      pcVar3 = &local_27;
      bVar2 = true;
      bVar1 = false;
      pcVar7 = pcVar5;
      do {
        pcVar3 = pcVar3 + 1;
        if (*pcVar7 != '\0') {
          bVar1 = true;
        }
        if (*pcVar3 != *pcVar7) {
          bVar2 = false;
        }
        pcVar7 = pcVar7 + 1;
      } while (pcVar3 != (char *)((int)&local_22 + 1));
      if (bVar2) {
        if (g_switch_debug_level < 3) {
          return 0;
        }
        printk("[SW][sw_mac_add_cpu_macaddress] output: mac exist alreay\n");
        return 0;
      }
      pcVar5 = pcVar5 + -6;
      if (!bVar1) {
        iVar6 = iVar4;
      }
      iVar4 = iVar4 + -1;
    } while (iVar4 != -1);
    if (iVar6 != -1) {
      local_27 = (char)iVar6;
      *(undefined4 *)(&g_cpu_mac + iVar6 * 6) = *(undefined4 *)(param_1 + 4);
      *(undefined2 *)(&DAT_0002b6d0 + iVar6 * 6) = *(undefined2 *)(param_1 + 8);
      iVar6 = tm_onu_mac_addr_set(&local_27);
      if (iVar6 != 0) {
        if (g_switch_debug_level == 0) {
          return iVar6;
        }
        printk("[SW][sw_mac_add_cpu_macaddress] return error! error code=0x%x\n",iVar6);
        return iVar6;
      }
      if (2 < g_switch_debug_level) {
        printk("[SW][sw_mac_add_cpu_macaddress] output: SUCCESS\n");
        return 0;
      }
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_mac_add_cpu_macaddress] output: ADD FAIL 5 cpu mac already\n");
      return -1;
    }
  }
  return -1;
}


/* ============= FUNCTION: sw_mac_del_cpu_macaddress @ 00014f48 ============= */

int sw_mac_del_cpu_macaddress(int param_1)

{
  int iVar1;
  bool bVar2;
  char *pcVar3;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  undefined4 local_25;
  undefined2 local_21;
  char local_1f;
  undefined1 auStack_1e [6];
  char *pcVar4;
  
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      iVar6 = -1;
    }
    else {
      printk("[SW][sw_mac_del_cpu_macaddress] input ERROR! ioctl_data_sweth=NULL\n");
      iVar6 = -1;
    }
  }
  else {
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_mac_del_cpu_macaddress] input: mac=%x:%x:%x:%x:%x:%x\n",
             *(undefined1 *)(param_1 + 4),*(undefined1 *)(param_1 + 5),*(undefined1 *)(param_1 + 6),
             *(undefined1 *)(param_1 + 7),*(undefined1 *)(param_1 + 8),*(undefined1 *)(param_1 + 9))
      ;
    }
    iVar6 = 0;
    pcVar5 = &g_cpu_mac;
    __memzero(&local_1f,7);
    local_25 = *(undefined4 *)(param_1 + 4);
    local_21 = *(undefined2 *)(param_1 + 8);
    do {
      bVar2 = true;
      pcVar4 = (char *)&local_25;
      pcVar7 = pcVar5;
      do {
        pcVar3 = pcVar4 + 1;
        if (*pcVar7 != *pcVar4) {
          bVar2 = false;
        }
        pcVar4 = pcVar3;
        pcVar7 = pcVar7 + 1;
      } while (pcVar3 != &local_1f);
      if (bVar2) {
        if (2 < g_switch_debug_level) {
          printk("[SW][sw_mac_del_cpu_macaddress] find the mac, index=%d\n",iVar6);
        }
        __memzero(pcVar5,6);
        __memzero(auStack_1e,6);
        local_1f = (char)iVar6;
        iVar1 = tm_onu_mac_addr_set(&local_1f);
        if (iVar1 != 0) {
          if (g_switch_debug_level == 0) {
            return iVar1;
          }
          printk("[SW][sw_mac_add_cpu_macaddress] return error! error code=0x%x\n",iVar1);
          return iVar1;
        }
        if (2 < g_switch_debug_level) {
          printk("[SW][sw_mac_del_cpu_macaddress] output: SUCCESS\n");
        }
      }
      iVar6 = iVar6 + 1;
      pcVar5 = pcVar5 + 6;
    } while (iVar6 != 8);
    iVar6 = 0;
  }
  return iVar6;
}


/* ============= FUNCTION: sw_mac_show_cpu_macaddress @ 000150d0 ============= */

undefined4 sw_mac_show_cpu_macaddress(int param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[SW][sw_mac_show_cpu_macaddress] input ERROR! ioctl_data_sweth=NULL\n");
      uVar1 = 0xffffffff;
    }
  }
  else {
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_mac_show_cpu_macaddress] output:\n");
    }
    puVar2 = &g_cpu_mac;
    iVar3 = 0;
    do {
      iVar4 = iVar3 + 1;
      printk("index=%d cpu mac=%x:%x:%x:%x:%x:%x\n",iVar3,*puVar2,puVar2[1],puVar2[2],puVar2[3],
             puVar2[4],puVar2[5]);
      puVar2 = puVar2 + 6;
      iVar3 = iVar4;
    } while (iVar4 != 8);
    uVar1 = 0;
  }
  return uVar1;
}


/* ============= FUNCTION: sw_mac_add_port_macadd_feature @ 00015180 ============= */

undefined4 sw_mac_add_port_macadd_feature(uint *param_1)

{
  uint uVar1;
  code cVar2;
  int iVar3;
  undefined4 local_42;
  undefined2 local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  
  cVar2 = zte_api_sw_mac_set_port_macfiltermode[param_1[3]];
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  __memzero(&local_42,6);
  local_3e = (undefined2)param_1[1];
  local_42 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n"
           ,DAT_00015370,"MacEntry.mac",(char)*param_1,*(undefined1 *)((int)param_1 + 1),
           *(undefined1 *)((int)param_1 + 2),*(undefined1 *)((int)param_1 + 3),(char)param_1[1],
           *(undefined1 *)((int)param_1 + 5),"MacEntry.vid",param_1[2],"MacEntry.port",
           (uint)(byte)cVar2,"MacEntry.status(0-dyn 1-static)",param_1[4],"MacEntry.smac_ctrl",
           (char)param_1[5],"MacEntry.dmac_ctrl",*(undefined1 *)((int)param_1 + 0x15));
  }
  if ((local_42 & 1) == 0) {
    __memzero(&local_3c,0x14);
    local_30 = param_1[2];
    uVar1 = 1 << (uint)(byte)cVar2;
    local_2c = CONCAT31(local_2c._1_3_,(char)uVar1);
    local_34 = CONCAT13((undefined1)local_42,
                        CONCAT12(local_42._1_1_,CONCAT11(local_42._2_1_,local_42._3_1_)));
    local_38 = CONCAT22(CONCAT11((undefined1)local_3e,local_3e._1_1_),(short)param_1[5]);
    if (2 < g_switch_debug_level) {
      printk("%s = 0x%x\n","MacEntry.port_mask",uVar1 & 0xff);
    }
    if (param_1[4] == 0) {
      local_3c = 0xe;
    }
    else {
      local_3c = 0xf;
    }
    iVar3 = tm_mactable_add_set(&local_3c);
    if (iVar3 != 0) {
      printk("%s %d failed!\n",DAT_00015370,0x22a);
      return 0xffffffff;
    }
  }
  return 0;
}


/* ============= FUNCTION: sw_mac_del_port_macadd_feature @ 00015374 ============= */

undefined4 sw_mac_del_port_macadd_feature(uint *param_1)

{
  uint uVar1;
  code cVar2;
  int iVar3;
  undefined4 local_42;
  undefined2 local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  __memzero(&local_42,6);
  local_3e = (undefined2)param_1[1];
  local_42 = *param_1;
  cVar2 = zte_api_sw_mac_set_port_macfiltermode[param_1[3]];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n"
           ,DAT_00015564,"MacEntry.mac",(char)*param_1,*(undefined1 *)((int)param_1 + 1),
           *(undefined1 *)((int)param_1 + 2),*(undefined1 *)((int)param_1 + 3),(char)param_1[1],
           *(undefined1 *)((int)param_1 + 5),"MacEntry.vid",param_1[2],"MacEntry.port",
           (uint)(byte)cVar2,"MacEntry.status(0-dyn 1-static)",param_1[4],"MacEntry.smac_ctrl",
           (char)param_1[5],"MacEntry.dmac_ctrl",*(undefined1 *)((int)param_1 + 0x15));
  }
  if ((local_42 & 1) == 0) {
    __memzero(&local_3c,0x14);
    local_30 = param_1[2];
    uVar1 = 1 << (uint)(byte)cVar2;
    local_2c = CONCAT31(local_2c._1_3_,(char)uVar1);
    local_34 = CONCAT13((undefined1)local_42,
                        CONCAT12(local_42._1_1_,CONCAT11(local_42._2_1_,local_42._3_1_)));
    local_38 = CONCAT22(CONCAT11((undefined1)local_3e,local_3e._1_1_),(short)param_1[5]);
    if (2 < g_switch_debug_level) {
      printk("%s = 0x%x\n","MacEntry.port_mask",uVar1 & 0xff);
    }
    if (param_1[4] == 0) {
      local_3c = 0xe;
    }
    else {
      local_3c = 0xf;
    }
    iVar3 = tm_mactable_delete_set(&local_3c);
    if (iVar3 != 0) {
      printk("%s %d failed!\n",DAT_00015564,0x27b);
      return 0xffffffff;
    }
  }
  return 0;
}


/* ============= FUNCTION: sw_mac_set_mac_hashmode @ 00015568 ============= */

undefined4 sw_mac_set_mac_hashmode(undefined1 *param_1)

{
  int iVar1;
  
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_000155d0,"MacHashMode.hashMode(0-mac 1-mac+vlan)",*param_1);
  }
  iVar1 = tm_hash_mode_set(*param_1);
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n",DAT_000155d0,0x2b3);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mac_get_mac_hashmode @ 000155d4 ============= */

undefined4 sw_mac_get_mac_hashmode(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_11 [5];
  
  local_11[0] = 0;
  iVar1 = tm_hash_mode_get(local_11);
  if (iVar1 == 0) {
    *param_1 = local_11[0];
    uVar2 = 0;
    if (2 < g_switch_debug_level) {
      printk("[%s] output:\n%s = %d\n",DAT_0001565c,"MacHashMode.hashMode(0-mac 1-mac+vlan)");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001565c,0x2c2);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_port_clear_port_count @ 00015660 ============= */

undefined4 sw_port_clear_port_count(void)

{
  int iVar1;
  
  iVar1 = zte_api_sw_port_clear_port_count();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_port_clear_port_count",0x32);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_port_clear_port_count_byportid @ 00015690 ============= */

undefined4 sw_port_clear_port_count_byportid(int *param_1)

{
  int iVar1;
  
  iVar1 = zte_api_sw_port_clear_count_by_portid(zte_api_sw_mac_set_port_macfiltermode[*param_1]);
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n",DAT_000156d0,0x41);
  return 0xffffffff;
}


/* ============= FUNCTION: sw_port_get_port_statistics1 @ 000156d4 ============= */

undefined4 sw_port_get_port_statistics1(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar4;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r1_07;
  undefined4 extraout_r1_08;
  undefined4 extraout_r1_09;
  undefined4 extraout_r1_10;
  undefined4 extraout_r1_11;
  int local_90;
  int iStack_8c;
  int local_88;
  int iStack_84;
  int local_80;
  int iStack_7c;
  int local_78;
  int iStack_74;
  int local_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  int local_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  int local_50;
  int iStack_4c;
  int local_48;
  int iStack_44;
  int local_40;
  int iStack_3c;
  int local_38;
  int iStack_34;
  int local_30;
  int iStack_2c;
  int local_28;
  int iStack_24;
  
  __memzero(&local_90,0x70);
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n",DAT_00015990,cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_statistics1(cVar1,&local_90);
  uVar2 = g_switch_debug_level;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00015994,0x59);
    return 0xffffffff;
  }
  param_1[2] = local_90;
  param_1[3] = iStack_8c;
  param_1[0x12] = local_70;
  param_1[0x13] = iStack_6c;
  param_1[4] = local_88;
  param_1[5] = iStack_84;
  param_1[0xe] = local_80;
  param_1[0xf] = iStack_7c;
  param_1[0x10] = local_78;
  param_1[0x11] = iStack_74;
  param_1[0x14] = local_68;
  param_1[0x15] = iStack_64;
  param_1[0x16] = local_60;
  param_1[0x17] = iStack_5c;
  param_1[0x1a] = local_58;
  param_1[0x1b] = iStack_54;
  param_1[0x1c] = local_50;
  param_1[0x1d] = iStack_4c;
  param_1[0x26] = local_48;
  param_1[0x27] = iStack_44;
  param_1[0x2a] = local_38;
  param_1[0x2b] = iStack_34;
  param_1[0x2c] = local_30;
  param_1[0x2d] = iStack_2c;
  param_1[0x28] = local_40;
  param_1[0x29] = iStack_3c;
  param_1[0x2e] = local_28;
  param_1[0x2f] = iStack_24;
  if (uVar2 < 3) {
    return 0;
  }
  printk("inbytes = %lld\n",iStack_2c,local_90,iStack_8c);
  uVar4 = extraout_r1;
  if (g_switch_debug_level < 3) {
LAB_00015854:
    if (2 < g_switch_debug_level) {
      printk("inerror = %lld\n",uVar4,local_68,iStack_64);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("indiscard = %lld\n",extraout_r1_04,local_60,iStack_5c);
      uVar4 = extraout_r1_05;
      goto LAB_00015894;
    }
LAB_000158d4:
    if (g_switch_debug_level < 3) goto LAB_00015954;
    printk("outunicast = %lld\n",uVar4,local_48,iStack_44);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outmulticast = %lld\n",extraout_r1_08,local_40,iStack_3c);
    uVar4 = extraout_r1_09;
  }
  else {
    printk("inpkts = %lld\n",extraout_r1,local_88,iStack_84);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("inunicast = %lld\n",extraout_r1_00,local_80,iStack_7c);
    uVar4 = extraout_r1_01;
    if (2 < g_switch_debug_level) {
      printk("inmulticast = %lld\n",extraout_r1_01,local_78,iStack_74);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("inbroadcast = %lld\n",extraout_r1_02,local_70,iStack_6c);
      uVar4 = extraout_r1_03;
      goto LAB_00015854;
    }
LAB_00015894:
    if (2 < g_switch_debug_level) {
      printk("outbytes = %lld\n",uVar4,local_58,iStack_54);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("outpkts = %lld\n",extraout_r1_06,local_50,iStack_4c);
      uVar4 = extraout_r1_07;
      goto LAB_000158d4;
    }
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outbroadcast = %lld\n",uVar4,local_38,iStack_34);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outerror = %lld\n",extraout_r1_10,local_30,iStack_2c);
  uVar4 = extraout_r1_11;
LAB_00015954:
  if (2 < g_switch_debug_level) {
    printk("outdiscard = %lld\n",uVar4,local_28,iStack_24);
  }
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_statistics2 @ 00015998 ============= */

undefined4 sw_port_get_port_statistics2(int *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar5;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  int local_78;
  int iStack_74;
  int local_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  int local_58;
  int iStack_54;
  int local_50;
  int iStack_4c;
  undefined4 local_40;
  undefined4 uStack_3c;
  int local_38;
  int iStack_34;
  int local_28;
  int iStack_24;
  
  __memzero(&local_78,0x58);
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n",DAT_00015b8c,cVar1);
  }
  iVar4 = zte_api_sw_port_get_port_statistics2(cVar1,&local_78);
  iVar2 = g_LinkStateChangeCount;
  if (iVar4 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00015b90,0xb9);
    return 0xffffffff;
  }
  param_1[0x10] = local_58;
  param_1[0x11] = iStack_54;
  uVar3 = g_switch_debug_level;
  param_1[0x1b] = 0;
  param_1[0x1a] = iVar2;
  param_1[6] = local_70;
  param_1[7] = iStack_6c;
  param_1[0x12] = local_50;
  param_1[0x13] = iStack_4c;
  param_1[4] = local_78;
  param_1[5] = iStack_74;
  param_1[0x1c] = local_68;
  param_1[0x1d] = iStack_64;
  param_1[0x18] = local_38;
  param_1[0x19] = iStack_34;
  param_1[0x20] = local_28;
  param_1[0x21] = iStack_24;
  if (uVar3 < 3) {
    return 0;
  }
  printk("inundersize = %lld\n");
  uVar5 = extraout_r1;
  if (2 < g_switch_debug_level) {
    printk("inoversize = %lld\n",extraout_r1,local_70,iStack_6c);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("infragments = %lld\n",extraout_r1_00,local_68,iStack_64);
    uVar5 = extraout_r1_01;
    if (g_switch_debug_level < 3) goto LAB_00015b2c;
    printk("injabbers = %lld\n",extraout_r1_01,local_60,uStack_5c);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outundersize = %lld\n",extraout_r1_02,local_58,iStack_54);
    uVar5 = extraout_r1_03;
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outoversize = %lld\n",uVar5,local_50,iStack_4c);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("statechange = %lld\n",extraout_r1_04,local_40,uStack_3c);
  uVar5 = extraout_r1_05;
LAB_00015b2c:
  if ((2 < g_switch_debug_level) &&
     (printk("outpause = %lld\n",uVar5,local_38,iStack_34), 2 < g_switch_debug_level)) {
    printk("dropevents = %lld\n",extraout_r1_06,local_28,iStack_24);
  }
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_statistics3 @ 00015b94 ============= */

undefined4 sw_port_get_port_statistics3(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar4;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r1_07;
  undefined4 extraout_r1_08;
  undefined4 extraout_r1_09;
  int local_80;
  int iStack_7c;
  int local_78;
  int iStack_74;
  int local_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  int local_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  int local_50;
  int iStack_4c;
  int local_48;
  int iStack_44;
  int local_40;
  int iStack_3c;
  int local_38;
  int iStack_34;
  int local_30;
  int iStack_2c;
  int local_28;
  int iStack_24;
  
  __memzero(&local_80,0x60);
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n",DAT_00015df8,cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_statistics3(cVar1,&local_80);
  uVar2 = g_switch_debug_level;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00015dfc,0xe1);
    return 0xffffffff;
  }
  param_1[4] = local_78;
  param_1[5] = iStack_74;
  param_1[6] = local_70;
  param_1[7] = iStack_6c;
  param_1[10] = local_60;
  param_1[0xb] = iStack_5c;
  param_1[8] = local_68;
  param_1[9] = iStack_64;
  param_1[0xe] = local_50;
  param_1[0xf] = iStack_4c;
  param_1[0xc] = local_58;
  param_1[0xd] = iStack_54;
  param_1[0x10] = local_48;
  param_1[0x11] = iStack_44;
  param_1[2] = local_80;
  param_1[3] = iStack_7c;
  param_1[0x12] = local_40;
  param_1[0x13] = iStack_3c;
  param_1[0x14] = local_38;
  param_1[0x15] = iStack_34;
  param_1[0x18] = local_28;
  param_1[0x19] = iStack_24;
  param_1[0x16] = local_30;
  param_1[0x17] = iStack_2c;
  if (uVar2 < 3) {
    return 0;
  }
  printk("in64 = %lld\n");
  uVar4 = extraout_r1;
  if (g_switch_debug_level < 3) {
LAB_00015cfc:
    if (2 < g_switch_debug_level) {
      printk("in1024tomax = %lld\n",uVar4,local_58,iStack_54);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("out64 = %lld\n",extraout_r1_04,local_50,iStack_4c);
      uVar4 = extraout_r1_05;
      goto LAB_00015d3c;
    }
  }
  else {
    printk("in65to127 = %lld\n",extraout_r1,local_78,iStack_74);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("in128to255 = %lld\n",extraout_r1_00,local_70,iStack_6c);
    uVar4 = extraout_r1_01;
    if (2 < g_switch_debug_level) {
      printk("in256to511 = %lld\n",extraout_r1_01,local_68,iStack_64);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("in512to1023 = %lld\n",extraout_r1_02,local_60,iStack_5c);
      uVar4 = extraout_r1_03;
      goto LAB_00015cfc;
    }
LAB_00015d3c:
    if (g_switch_debug_level < 3) goto LAB_00015dbc;
    printk("out65to127 = %lld\n",uVar4,local_48,iStack_44);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("out128to255 = %lld\n",extraout_r1_06,local_40,iStack_3c);
    uVar4 = extraout_r1_07;
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("out256to511 = %lld\n",uVar4,local_38,iStack_34);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("out512to1024 = %lld\n",extraout_r1_08,local_30,iStack_2c);
  uVar4 = extraout_r1_09;
LAB_00015dbc:
  if (2 < g_switch_debug_level) {
    printk("out1024tomax = %lld\n",uVar4,local_28,iStack_24);
  }
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_statistics4 @ 00015e00 ============= */

undefined4 sw_port_get_port_statistics4(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar4;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r1_07;
  int local_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  int local_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  int local_50;
  int iStack_4c;
  int local_48;
  int iStack_44;
  int local_40;
  int iStack_3c;
  int local_38;
  int iStack_34;
  int local_30;
  int iStack_2c;
  int local_28;
  int iStack_24;
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  __memzero(&local_70,0x50);
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n",DAT_00016014,cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_statistics4(cVar1,&local_70);
  uVar2 = g_switch_debug_level;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00016018,0x10e);
    return 0xffffffff;
  }
  param_1[6] = local_60;
  param_1[7] = iStack_5c;
  param_1[4] = local_68;
  param_1[5] = iStack_64;
  param_1[8] = local_58;
  param_1[9] = iStack_54;
  param_1[10] = local_50;
  param_1[0xb] = iStack_4c;
  param_1[0xc] = local_48;
  param_1[0xd] = iStack_44;
  param_1[2] = local_70;
  param_1[3] = iStack_6c;
  param_1[0xe] = local_40;
  param_1[0xf] = iStack_3c;
  param_1[0x10] = local_38;
  param_1[0x11] = iStack_34;
  param_1[0x12] = local_30;
  param_1[0x13] = iStack_2c;
  param_1[0x14] = local_28;
  param_1[0x15] = iStack_24;
  if (uVar2 < 3) {
    return 0;
  }
  printk("outexcession = %lld\n");
  uVar4 = extraout_r1;
  if (g_switch_debug_level < 3) {
LAB_00015f58:
    if (g_switch_debug_level < 3) goto LAB_00015fd8;
    printk("outdeferred = %lld\n",uVar4,local_48,iStack_44);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outmacerror = %lld\n",extraout_r1_04,local_40,iStack_3c);
    uVar4 = extraout_r1_05;
  }
  else {
    printk("outlate = %lld\n",extraout_r1,local_68,iStack_64);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outsingle = %lld\n",extraout_r1_00,local_60,iStack_5c);
    uVar4 = extraout_r1_01;
    if (2 < g_switch_debug_level) {
      printk("outmultiple = %lld\n",extraout_r1_01,local_58,iStack_54);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("SQE = %lld\n",extraout_r1_02,local_50,iStack_4c);
      uVar4 = extraout_r1_03;
      goto LAB_00015f58;
    }
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outcarrier = %lld\n",uVar4,local_38,iStack_34);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("inalignment = %lld\n",extraout_r1_06,local_30,iStack_2c);
  uVar4 = extraout_r1_07;
LAB_00015fd8:
  if (2 < g_switch_debug_level) {
    printk("inmacerror = %lld\n",uVar4,local_28,iStack_24);
  }
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_rmonstats @ 0001601c ============= */

undefined4 sw_port_get_port_rmonstats(void)

{
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_statistics @ 00016024 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_statistics(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint local_70 [2];
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  
  __memzero(local_70,0x58);
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\nport=%d\n",DAT_00016238,*param_1);
  }
  if (_tm_port_unknwn_multicast_floodport_set <= *param_1) {
    printk("[%s]%d input port error!\n",DAT_0001623c,0x140);
    return 0xffffffff;
  }
  local_70[0] = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = tm_port_statistics(local_70);
  uVar1 = g_switch_debug_level;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001623c,0x148);
    return 0xffffffff;
  }
  param_1[2] = local_5c;
  param_1[3] = local_60;
  param_1[4] = local_58;
  param_1[5] = local_4c;
  param_1[6] = local_50;
  param_1[7] = local_68;
  param_1[8] = local_64;
  param_1[9] = local_54;
  if (uVar1 < 3) {
    return 0;
  }
  printk("[%s] output:\n",DAT_00016238);
  if (2 < g_switch_debug_level) {
    printk("inframe = %d\n",local_5c);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("inoct = %d\n",local_60);
    if (g_switch_debug_level < 3) goto LAB_000161bc;
    printk("outframe = %d\n",local_58);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("disinbound = %d\n",local_4c);
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disbuffer = %d\n",local_50);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disdelay = %d\n",local_68);
LAB_000161bc:
  if ((2 < g_switch_debug_level) && (printk("diserror = %d\n",local_64), 2 < g_switch_debug_level))
  {
    printk("disingress = %d\n",local_54);
  }
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_vlanstatistics @ 00016240 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_vlanstatistics(uint *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  
  __memzero(&local_78,0x58);
  __memzero(&local_84,0xc);
  if (_tm_port_unknwn_multicast_floodport_set <= *param_1) {
    printk("[%s]%d input port error!\n",DAT_000164ac,0x16e);
    return 0xffffffff;
  }
  local_74 = param_1[1];
  local_78 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\nportid=%d\nvlanid=%d\n",DAT_000164b0,local_78,local_74);
  }
  local_84 = 1;
  local_80 = local_78;
  local_7c = local_74;
  iVar2 = tm_vlan_stat_config(&local_84);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_000164ac,0x17b);
    return 0xffffffff;
  }
  iVar2 = tm_vlan_statistics(&local_78);
  uVar1 = g_switch_debug_level;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_000164ac,0x182);
    return 0xffffffff;
  }
  param_1[2] = local_64;
  param_1[3] = local_68;
  param_1[4] = local_60;
  param_1[5] = local_54;
  param_1[6] = local_58;
  param_1[7] = local_70;
  param_1[8] = local_6c;
  param_1[9] = local_5c;
  if (uVar1 < 3) {
    return 0;
  }
  printk("[%s] output:\n",DAT_000164b0);
  if (2 < g_switch_debug_level) {
    printk("inframe = %d\n",local_64);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("inoct = %d\n",local_68);
    if (g_switch_debug_level < 3) goto LAB_00016410;
    printk("outframe = %d\n",local_60);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("disinbound = %d\n",local_54);
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disbuffer = %d\n",local_58);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disdelay = %d\n",local_70);
LAB_00016410:
  if ((2 < g_switch_debug_level) && (printk("diserror = %d\n",local_6c), 2 < g_switch_debug_level))
  {
    printk("disingress = %d\n",local_5c);
  }
  return 0;
}


/* ============= FUNCTION: sw_other_set_wan_lan_switch @ 000164b4 ============= */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_other_set_wan_lan_switch(uint *param_1)

{
  code cVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  byte *pbVar6;
  byte local_23;
  byte local_22;
  byte local_21;
  
  bVar4 = 0;
  local_23 = 0;
  local_22 = 0;
  local_21 = 0;
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_other_set_wan_lan_switch] input ERROR: ioctl_data_sweth=null\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  sweth_flag = 1;
  uVar5 = *param_1;
  printk("set wan lan switch mode=%d\n",uVar5);
  if (uVar5 < 2) {
    if (wanLogicPort == 0xff) {
      return 0;
    }
    bVar4 = 0;
    cVar1 = zte_api_sw_mac_set_port_macfiltermode[wanLogicPort];
    _tm_vlan_check_ena_set = (uint)(byte)cVar1;
    uVar5 = fpga_read_reg(0xe8007);
    fpga_write_reg(0xe8007,uVar5 & 0xc1ffffff);
    tm_set_p2pmode((uint)(byte)cVar1);
    wan_to_lan = 0;
    _zte_api_sw_mac_set_port_learnlimit = _zte_api_sw_mac_set_port_learnlimit | 0xf;
    printk("set wan lan switch WAN or AUTO\n");
    uVar5 = 0;
    while( true ) {
      uVar3 = uVar5 + 1;
      if (_tm_port_unknwn_multicast_floodport_set <= uVar5) break;
      cVar1 = zte_api_sw_mac_set_port_macfiltermode[uVar5];
      zte_api_sw_port_get_port_linkstate((uint)(byte)cVar1,&local_23,&local_22,&local_21);
      uVar5 = uVar3;
      if (_tm_vlan_check_ena_set != (byte)cVar1) {
        bVar4 = bVar4 | local_23;
      }
    }
  }
  else {
    if (uVar5 == 6) {
      _tm_vlan_check_ena_set = 0xff;
      uVar5 = fpga_read_reg(0xe8007);
      fpga_write_reg(0xe8007,uVar5 & 0xc1ffffff);
      wan_to_lan = 1;
      _zte_api_sw_mac_set_port_learnlimit = _zte_api_sw_mac_set_port_learnlimit | 0x1f;
      printk("All port change lan\n");
      return 0;
    }
    uVar5 = uVar5 - 1 & 0xff;
    if (_tm_port_unknwn_multicast_floodport_set < uVar5) {
      printk("[%s]%d input error!\n",DAT_00016744,0x92);
      return 0xffffffff;
    }
    cVar1 = zte_api_sw_mac_set_port_macfiltermode[uVar5];
    _tm_vlan_check_ena_set = (uint)(byte)cVar1;
    uVar3 = fpga_read_reg(0xe8007);
    fpga_write_reg(0xe8007,uVar3 & 0xc1ffffff);
    tm_set_p2pmode((uint)(byte)cVar1);
    _zte_api_sw_mac_set_port_learnlimit = _zte_api_sw_mac_set_port_learnlimit | 0x1f;
    wan_to_lan = 1;
    printk("set wan lan switch ,eth%d to WAN\n",uVar5);
    if (_tm_port_unknwn_multicast_floodport_set == 0) goto LAB_0001660c;
    pbVar6 = (byte *)0x2c0a3;
    uVar5 = 0;
    do {
      pbVar6 = pbVar6 + 1;
      bVar2 = *pbVar6;
      uVar5 = uVar5 + 1;
      zte_api_sw_port_get_port_linkstate((uint)bVar2,&local_23,&local_22,&local_21);
      if (_tm_vlan_check_ena_set != bVar2) {
        bVar4 = bVar4 | local_23;
      }
    } while (uVar5 < _tm_port_unknwn_multicast_floodport_set);
  }
  if (bVar4 != 0) {
    return 0;
  }
LAB_0001660c:
  LedActionSet(0xb200,1);
  g_LAN_ON_Flag = 0;
  return 0;
}


/* ============= FUNCTION: sw_other_set_onu_mtu @ 00016748 ============= */

undefined4 sw_other_set_onu_mtu(uint *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined1 *puVar4;
  
  uVar3 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_000167d4,"Mtu.mtusize",uVar3);
  }
  puVar4 = DAT_000167d0 + 5;
  puVar2 = DAT_000167d0;
  if (1999 < uVar3) {
    uVar3 = 2000;
  }
  do {
    puVar2 = puVar2 + 1;
    iVar1 = zte_api_sw_other_set_onu_mtu(*puVar2,uVar3);
    if (iVar1 != 0) {
      printk("[%s] L%d tm sdk failed!\n",DAT_000167d4,0xbf);
      return 0xffffffff;
    }
  } while (puVar2 != puVar4);
  return 0;
}


/* ============= FUNCTION: sw_other_get_onu_mtu @ 000167d8 ============= */

undefined4
sw_other_get_onu_mtu(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_000167f4,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: get_sw_port_from_devname @ 000167f8 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 get_sw_port_from_devname(char *param_1,uint *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint local_20 [4];
  
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  if (param_2 == (uint *)0x0 || param_1 == (char *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("ERROR  argument !!!!\n");
    }
LAB_00016834:
    uVar1 = 0xffffffff;
  }
  else {
    strcpy((char *)local_20,param_1);
    iVar2 = strncmp((char *)local_20,"eth",3);
    if (iVar2 == 0) {
      uVar3 = (local_20[0] >> 0x18) - 0x30;
      if (((int)uVar3 < 0) || (_tm_port_unknwn_multicast_floodport_set < uVar3)) goto LAB_00016834;
      *param_2 = (uint)(byte)zte_api_fast_l3_session_del[local_20[0] >> 0x18];
    }
    else {
      iVar2 = strcmp((char *)local_20,"pon");
      if (((iVar2 == 0) || (iVar2 = strcmp((char *)local_20,"ptm0"), iVar2 == 0)) ||
         (iVar2 = strcmp((char *)local_20,"CPU"), iVar2 == 0)) {
        *param_2 = _tm_vlan_check_ena_set;
      }
      else {
        iVar2 = IfName2WlanIdmMap(local_20);
        if (iVar2 == 0) goto LAB_00016834;
        if (*(char *)(iVar2 + 0x25) == '\0') {
          if (param_3 == 1) {
            uVar3 = 6;
          }
          else {
            uVar3 = *(byte *)(iVar2 + 0x26) + 0x10;
          }
          *param_2 = uVar3;
        }
        else if (*(char *)(iVar2 + 0x25) == '\x01') {
          if (param_3 == 1) {
            uVar3 = 7;
          }
          else {
            uVar3 = *(byte *)(iVar2 + 0x26) + 0x18;
          }
          *param_2 = uVar3;
        }
      }
    }
    if (g_switch_debug_level < 3) {
      uVar1 = 0;
    }
    else {
      printk("devname = %s,port = %d!!\n",param_1,*param_2);
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ============= FUNCTION: Alarm_Msg @ 00016994 ============= */

int Alarm_Msg(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,ushort param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char acStack_30 [16];
  undefined4 local_20;
  undefined4 local_1c;
  
  __memzero(acStack_30,0x18);
  sprintf(acStack_30,"eth%d",(uint)param_5);
  if (param_2 == 1) {
    uVar2 = 0xa401;
  }
  else {
    uVar2 = 0xa402;
  }
  uVar3 = 0;
  uVar4 = 0;
  if (param_2 == 1) {
    local_20 = param_3;
    local_1c = param_4;
  }
  iVar1 = Kernel_ASEND("cspd.cspd.switch_mgr",uVar2);
  if (2 < g_switch_debug_level) {
    printk("Alarm_Msg port_name %s, port_rate(0-1G 1-100M 2-10M 3-Down 4-Error)%d port_mode(0-Half 1-Full)%d !\n"
           ,acStack_30,local_20,local_1c,uVar3,uVar4);
  }
  return iVar1 >> 0x1f;
}


/* ============= FUNCTION: turn_on_led_green @ 00016a48 ============= */

void turn_on_led_green(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  LedActionSet(0xb100,param_1 + -1,param_3,param_4,param_4);
  g_LAN_PACKET_COUNT = 0;
  g_LAN_ON_Flag = 1;
  return;
}


/* ============= FUNCTION: turn_off_led @ 00016a74 ============= */

void turn_off_led(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  LedActionSet(0xb200,param_1 + -1,param_3,param_4,param_4);
  g_LAN_ON_Flag = 0;
  return;
}


/* ============= FUNCTION: turn_flash_led @ 00016a98 ============= */

void turn_flash_led(int param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  undefined1 auStack_88 [8];
  uint local_80;
  uint uStack_7c;
  
  __memzero(auStack_88,0x70);
  iVar2 = zte_api_sw_port_get_port_statistics1(param_2,auStack_88);
  if (iVar2 == 0) {
    uVar1 = (int)g_LAN_PACKET_COUNT >> 0x1f;
    bVar3 = uVar1 <= uStack_7c;
    if (uStack_7c == uVar1) {
      bVar3 = g_LAN_PACKET_COUNT <= local_80;
    }
    if (bVar3 && (uStack_7c != uVar1 || local_80 != g_LAN_PACKET_COUNT)) {
      LedActionSet(0x2200,param_1 + -1);
      g_LAN_PACKET_COUNT = local_80;
    }
  }
  else {
    turn_flash_led_part_1();
  }
  return;
}


/* ============= FUNCTION: sw_alarm_scanforalarm @ 00016b0c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

int sw_alarm_scanforalarm(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  byte local_4b;
  undefined1 local_4a;
  byte local_49;
  char local_48 [16];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar6 = 0;
  local_4b = 0;
  local_4a = 0;
  local_49 = 0;
  local_48[0] = '\0';
  local_48[1] = '\0';
  local_48[2] = '\0';
  local_48[3] = '\0';
  local_48[4] = '\0';
  local_48[5] = '\0';
  local_48[6] = '\0';
  local_48[7] = '\0';
  local_48[8] = '\0';
  local_48[9] = '\0';
  local_48[10] = '\0';
  local_48[0xb] = '\0';
  local_48[0xc] = '\0';
  local_48[0xd] = '\0';
  local_48[0xe] = '\0';
  local_48[0xf] = '\0';
  if (l_firstTime_48678 != '\0') {
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
    local_2c = 0;
    if (_tm_port_unknwn_multicast_floodport_set != 0) {
      do {
        sprintf((char *)&local_38,"eth%d",uVar6);
        iVar1 = dev_get_by_name(&init_net,&local_38);
        if (iVar1 == 0) {
          if (g_switch_debug_level != 0) {
            printk("sw_get_port_linkStatus@sw_alarm_scanforalarm the dev is null!\n");
          }
        }
        else {
          disableIRQinterrupts();
          iVar7 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar7 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar7 + *(int *)(iVar1 + 0x280)) + -1
          ;
          netif_carrier_off();
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
    }
    l_firstTime_48678 = '\0';
  }
  if (_tm_port_unknwn_multicast_floodport_set == 0) {
    iVar1 = -1;
  }
  else {
    iVar9 = -1;
    uVar6 = 0;
    iVar7 = DAT_00016eec;
    pbVar10 = DAT_00016ef0;
    do {
      pbVar10 = pbVar10 + 1;
      uVar8 = (uint)*pbVar10;
      iVar1 = zte_api_sw_port_get_port_linkstate(uVar8,&local_4b,&local_4a,&local_49);
      if (iVar1 != 0) goto LAB_00016b7c;
      local_4a = sw_ztespeed_to_cspplatspeed(local_4a);
      uVar2 = sw_zteduplex_to_cspplatduplex(local_49);
      uVar4 = (uint)local_4b;
      local_49 = (byte)uVar2;
      if ((int)*(short *)(iVar7 + 2) == uVar4) {
LAB_00016d14:
        if (g_LAN_ON_Flag != 1) goto LAB_00016b7c;
LAB_00016d20:
        if ((local_4b == 1) && (uVar8 != _tm_vlan_check_ena_set)) {
LAB_00016d38:
          turn_flash_led(uVar6,uVar8);
        }
      }
      else {
        if (g_LinkStateChangeCount == -1) {
          g_LinkStateChangeCount = 0;
        }
        else {
          g_LinkStateChangeCount = g_LinkStateChangeCount + 1;
        }
        if (3 < g_switch_debug_level) {
          printk("sw_alarm_scanforalarm alarm port%d state change!link=%d speed=%d duplex=%d\n",
                 uVar6,uVar4,local_4a,uVar2);
          uVar4 = (uint)local_4b;
          uVar2 = (uint)local_49;
        }
        iVar1 = Alarm_Msg(0,uVar4,local_4a,uVar2,uVar6 & 0xffff);
        if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
          printk("Alarm_Msg@sw_alarm_scanforalarm return error!\nerror code=%d\n",iVar1);
        }
        *(ushort *)(iVar7 + 2) = (ushort)local_4b;
        sprintf(local_48,"eth%d",uVar6);
        iVar3 = dev_get_by_name(&init_net,local_48);
        if (iVar3 == 0) {
          if (g_switch_debug_level != 0) {
            printk("sw_get_port_linkStatus@sw_alarm_scanforalarm the dev is null!\n");
          }
        }
        else {
          disableIRQinterrupts();
          iVar5 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) + -1
          ;
          if (local_4b == 0) {
            netif_carrier_off();
            if ((uVar8 == _tm_vlan_check_ena_set) ||
               (LedActionSet(0xb200,iVar9), g_LAN_ON_Flag = 0, uVar8 == _tm_vlan_check_ena_set)) {
              fpga_write_reg(0xd3000,0x1f40fa0);
              goto LAB_00016d14;
            }
          }
          else {
            netif_carrier_on();
            if (uVar8 != _tm_vlan_check_ena_set) {
              LedActionSet(0xb100,iVar9);
              g_LAN_PACKET_COUNT = 0;
              g_LAN_ON_Flag = 1;
              if (uVar8 == _tm_vlan_check_ena_set) goto LAB_00016db8;
              if (local_4b != 1) goto LAB_00016b7c;
              goto LAB_00016d38;
            }
LAB_00016db8:
            fpga_write_reg(0xd3000,0x3f40050);
            if (g_LAN_ON_Flag == 1) goto LAB_00016d20;
          }
        }
      }
LAB_00016b7c:
      uVar6 = uVar6 + 1;
      iVar9 = iVar9 + 1;
      iVar7 = iVar7 + 8;
    } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
  }
  return iVar1;
}


/* ============= FUNCTION: sw_port_alarm_kthread @ 00016ef4 ============= */

void sw_port_alarm_kthread(void)

{
  int iVar1;
  int iVar2;
  
  do {
    if (g_ethdev_carrierFlag != 0) {
      sw_alarm_scanforalarm();
    }
    if ((l_clk_48706 < 0x5a) && (l_clk_48706 = l_clk_48706 + 1, l_clk_48706 == 0x5a)) {
      l_clk_48706 = 0x5a;
      iVar1 = 1;
      do {
        tm_protocol_pkt_limit_pps_set(0,iVar1,0,0);
        iVar2 = iVar1 + 1;
        tm_protocol_pkt_limit_pps_set(1,iVar1,0,0);
        iVar1 = iVar2;
      } while (iVar2 != 8);
      zte_api_sw_port_set_port_ratelimit(6,1,0);
      zte_api_sw_port_set_port_ratelimit(7,1,0);
      l_clk_48706 = 0x5b;
    }
    msleep_interruptible(sw_timerbase * 500);
  } while( true );
}


/* ============= FUNCTION: sw_alarm_init @ 00016fe0 ============= */

undefined4 sw_alarm_init(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  __memzero(DAT_000170cc,0x40);
  uVar1 = kthread_create_on_node(sw_port_alarm_kthread,0,0xffffffff,"sw_port_alarm_kthread");
  if (uVar1 < 0xfffff001) {
    wake_up_process();
  }
  printk("[SW]set cpu queue rate limit to 8000pps\n");
  iVar2 = 1;
  do {
    tm_protocol_pkt_limit_pps_set(0,iVar2,1,8000);
    iVar3 = iVar2 + 1;
    tm_protocol_pkt_limit_pps_set(1,iVar2,1,8000);
    iVar2 = iVar3;
  } while (iVar3 != 7);
  tm_protocol_pkt_limit_pps_set(0,7,1,8000);
  zte_api_sw_port_set_port_ratelimit(6,1,1);
  zte_api_sw_port_set_port_ratelimit(7,1,1);
  fpga_write_reg(0xd3000,0x1f40fa0);
  return 0;
}


/* ============= FUNCTION: sw_wancip_set @ 000170d0 ============= */

undefined4 sw_wancip_set(void)

{
  return 0;
}


/* ============= FUNCTION: sw_wancip_get @ 000170d8 ============= */

undefined4 sw_wancip_get(void)

{
  return 0;
}


/* ============= FUNCTION: sw_wancip_del @ 000170e0 ============= */

undefined4 sw_wancip_del(void)

{
  return 0;
}


/* ============= FUNCTION: sw_multicast_en @ 000170e8 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_multicast_en(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_multicast_en] input:p_en = %d\n",param_1,param_3,g_switch_debug_level,param_4);
  }
  if (param_1 != 1) {
    iVar1 = tm_port_unknwn_multicast_flood_set(5,1);
    if (iVar1 != 0) {
      printk("[sw_multicast_en] tm_port_unknwn_multicast_flood_set OUT Fail!\n");
    }
    uVar2 = 0;
    do {
      if ((((DAT_0002c0e6 | DAT_0002c0e2) | _zte_api_sw_mac_set_port_learnlimit) &
          1 << (uVar2 & 0xff)) != 0) {
        iVar1 = tm_port_unknwn_multicast_fwd_set(uVar2);
        if (iVar1 != 0) {
          printk("[sw_multicast_en] tm_port_unknwn_multicast_fwd_set OUT Fail!\n");
        }
        iVar1 = tm_port_unknwn_multicast_floodport_set(5,1,uVar2);
        if (iVar1 != 0) {
          printk("[sw_multicast_en] tm_port_unknwn_multicast_floodport_set OUT Fail!\n");
        }
        iVar1 = tm_port_dft_multicst_vltrans_set(uVar2,1);
        if (iVar1 != 0) {
          printk("[sw_multicast_en] tm_port_dft_multicst_vltrans_set OUT Fail!\n");
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != 8);
    return;
  }
  iVar1 = tm_port_unknwn_multicast_flood_set(5,0);
  if (iVar1 != 0) {
    printk("[sw_multicast_en] tm_port_unknwn_multicast_flood_set OUT Fail!\n");
  }
  uVar2 = 0;
  do {
    if ((((DAT_0002c0e6 | DAT_0002c0e2) | _zte_api_sw_mac_set_port_learnlimit) & 1 << (uVar2 & 0xff)
        ) != 0) {
      iVar1 = tm_port_unknwn_multicast_fwd_set(uVar2,0);
      if (iVar1 != 0) {
        printk("[sw_multicast_en] tm_port_unknwn_multicast_fwd_set OUT Fail!\n");
      }
      iVar1 = tm_port_unknwn_multicast_floodport_set(5,0,uVar2);
      if (iVar1 != 0) {
        printk("[sw_multicast_en] tm_port_unknwn_multicast_floodport_set OUT Fail!\n");
      }
      iVar1 = tm_port_dft_multicst_vltrans_set(uVar2,0);
      if (iVar1 != 0) {
        printk("[sw_multicast_en] tm_port_dft_multicst_vltrans_set OUT Fail!\n");
      }
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 8);
  return;
}


/* ============= FUNCTION: sw_wlan_idmessid_map @ 000172c0 ============= */

undefined4 sw_wlan_idmessid_map(void)

{
  return 0;
}


/* ============= FUNCTION: sw_essid_wlanidm_map @ 000172c8 ============= */

undefined4 sw_essid_wlanidm_map(void)

{
  return 0;
}


/* ============= FUNCTION: sw_other_set_area_code @ 000172d0 ============= */

undefined4 sw_other_set_area_code(void)

{
  return 0;
}


/* ============= FUNCTION: sw_other_get_port_from_devname @ 000172d8 ============= */

undefined4 sw_other_get_port_from_devname(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  iVar1 = get_sw_port_from_devname(param_1,&local_c,1);
  if (iVar1 == 0) {
    *param_1 = local_c;
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_ztespeed_to_cspplatspeed @ 00017308 ============= */

undefined4
sw_ztespeed_to_cspplatspeed(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 1) {
    return 2;
  }
  if (param_1 != 0) {
    if (param_1 == 2) {
      return 3;
    }
    printk("%s undefined speed=%d\n","sw_ztespeed_to_cspplatspeed",param_1,param_4,param_4);
    return 0;
  }
  return 1;
}


/* ============= FUNCTION: sw_zteduplex_to_cspplatduplex @ 00017358 ============= */

undefined4
sw_zteduplex_to_cspplatduplex(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 0) {
    return 1;
  }
  if (param_1 == 1) {
    return 2;
  }
  printk("%s undefined duplex=%d\n",DAT_00017398,param_1,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: cspplatspeed_to_sw_ztespeed @ 0001739c ============= */

undefined4
cspplatspeed_to_sw_ztespeed(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 2) {
    return 1;
  }
  if (param_1 != 3) {
    if (param_1 != 1) {
      printk("%s undefined speed=%d\n",DAT_000173ec,param_1,param_4,param_4);
      return 0;
    }
    return 0;
  }
  return 2;
}


/* ============= FUNCTION: cspplatduplex_to_sw_zteduplex @ 000173f0 ============= */

undefined4
cspplatduplex_to_sw_zteduplex(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 1) {
    return 0;
  }
  if (param_1 == 2) {
    return 1;
  }
  printk("%s undefined duplex=%d\n",DAT_00017430,param_1,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_init_wlan_ssid @ 00017434 ============= */

void sw_init_wlan_ssid(void)

{
  undefined4 in_r3;
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  
  aclWlanToIdmReset();
  uVar2 = 0;
  uVar4 = 0x10;
  uVar3 = 6;
  iVar1 = DAT_000174a8;
  do {
    if (*(char *)(iVar1 + -1) != '\0') {
      if (*(char *)(iVar1 + 0x24) == '\0') {
        uVar4 = *(undefined1 *)(iVar1 + 0x26);
        uVar3 = 6;
      }
      else if (*(char *)(iVar1 + 0x24) == '\x01') {
        uVar4 = *(undefined1 *)(iVar1 + 0x26);
        uVar3 = 7;
      }
      aclWLANToIDMEssidCfg2(uVar2 & 0xff,uVar3,uVar4,iVar1,in_r3);
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x29;
  } while (uVar2 != 0x10);
  return;
}


/* ============= FUNCTION: sw_port_set_port_enable @ 000174ac ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_set_port_enable(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  cVar1 = (char)param_1[1];
  uVar4 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n",DAT_00017574,"PortEnable.port",uVar4,
           "PortEnable.enable",cVar1);
  }
  if (uVar4 == _tm_vlan_check_ena_set) {
    lan_up = (uint)(cVar1 != '\0');
  }
  iVar2 = zte_api_sw_port_set_port_enable(uVar4,cVar1);
  uVar3 = 0;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00017574,0xc9);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


/* ============= FUNCTION: sw_port_get_port_enable @ 00017578 ============= */

undefined4 sw_port_get_port_enable(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte local_11;
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_0001763c,"PortEnable.port",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_enable(cVar1,&local_11);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_11;
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[%s] output:\nPortEnable.enable = %d\n",DAT_0001763c);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001763c,0xde);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_port_set_port_flowcontrol @ 00017640 ============= */

undefined4 sw_port_set_port_flowcontrol(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n",DAT_000176e0,"FlowControl.port",*param_1,
           "FlowControl.enable",param_1[1]);
  }
  iVar1 = zte_api_sw_port_set_port_flowcontrol
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],(char)param_1[1],0xffff);
  uVar2 = 0;
  if (iVar1 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_000176e0,0xf6);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_port_get_port_flowcontrol @ 000176e4 ============= */

undefined4 sw_port_get_port_flowcontrol(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte local_15;
  undefined4 local_14;
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_15 = 0;
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_000177b4,"FlowControl.port");
  }
  iVar3 = zte_api_sw_port_get_port_flowcontrol(cVar1,&local_15,&local_14);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_15;
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n",DAT_000177b4,"FlowControl.enable");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_000177b4,0x10b);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_port_set_port_isolate @ 000177b8 ============= */

undefined4 sw_port_set_port_isolate(undefined4 *param_1)

{
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("[%s] input:\n%s = %d\n%s = %d\n",DAT_0001781c,"Isolate.port",*param_1,"Isolate.enable",
         param_1[1]);
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_isolate @ 00017820 ============= */

undefined4
sw_port_get_port_isolate
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_0001783c,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_port_set_port_isolatemask @ 00017840 ============= */

undefined4 sw_port_set_port_isolatemask(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_1[1];
  uVar2 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = 0x%x\n",DAT_00017940,"IsolateMask.port",uVar2,
           "IsolateMask.portmask",uVar3);
  }
  if ((lan_up & 1 << uVar2) == 0) {
    if (g_switch_debug_level != 0) {
      printk("[%s] input invalid port!\n",DAT_00017940);
      return 0xffffffff;
    }
  }
  else {
    if (uVar3 <= lan_up) {
      iVar1 = zte_api_sw_port_set_port_isolatemask(uVar2,uVar3);
      if (iVar1 == 0) {
        return 0;
      }
      printk("[%s] L%d tm sdk failed!\n",DAT_00017940,0x161);
      return 0xffffffff;
    }
    if (g_switch_debug_level != 0) {
      printk("[%s] input invalid portmask!\n",DAT_00017940);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_port_get_port_isolatemask @ 00017944 ============= */

undefined4
sw_port_get_port_isolatemask
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00017960,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_port_set_port_floodcontrol @ 00017964 ============= */

undefined4
sw_port_set_port_floodcontrol
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00017980,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_floodcontrol @ 00017984 ============= */

undefined4
sw_port_get_port_floodcontrol
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_000179a0,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_port_set_port_floodcontrolmask @ 000179a4 ============= */

undefined4 sw_port_set_port_floodcontrolmask(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = param_1[1];
  uVar2 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[*param_1];
  uVar3 = param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = 0x%x\n",DAT_00017ac0,"FloodMask.port",uVar2,
           "FloodMask.type",uVar4 & 0xff,"FloodMask.portmask",uVar3);
  }
  if ((lan_up & 1 << uVar2) == 0) {
    if (g_switch_debug_level != 0) {
      printk("[%s] input invalid port!\n",DAT_00017ac0);
      return 0xffffffff;
    }
  }
  else {
    if (uVar3 <= lan_up) {
      iVar1 = zte_api_sw_port_set_port_floodcontrolmask(uVar2,uVar4 & 0xff,uVar3);
      if (iVar1 == 0) {
        return 0;
      }
      printk("[%s] L%d tm sdk failed!\n",DAT_00017ac0,0x19a);
      return 0xffffffff;
    }
    if (g_switch_debug_level != 0) {
      printk("[%s] input invalid portmask!\n",DAT_00017ac0);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_port_get_port_floodcontrolmask @ 00017ac4 ============= */

undefined4
sw_port_get_port_floodcontrolmask
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00017ae0,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_port_set_port_linkmode @ 00017ae4 ============= */

undefined4 sw_port_set_port_linkmode(int *param_1)

{
  code cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar4 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = cspplatspeed_to_sw_ztespeed((char)param_1[2]);
  uVar3 = cspplatduplex_to_sw_zteduplex((char)param_1[3]);
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n",DAT_00017bd8,"LinkMode.port",*param_1
           ,"LinkMode.autoneg",param_1[1],"LinkMode.speed",param_1[2],"LinkMode.duplex",param_1[3]);
  }
  if (iVar2 == 2) {
    uVar4 = 1;
  }
  else {
    uVar4 = uVar4 & 0xff;
  }
  iVar2 = zte_api_sw_port_set_port_linkmode(cVar1,uVar4,iVar2,uVar3);
  uVar3 = 0;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00017bd8,0x1c1);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


/* ============= FUNCTION: sw_port_get_port_linkmode @ 00017bdc ============= */

undefined4 sw_port_get_port_linkmode(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte local_13;
  byte local_12;
  byte local_11;
  
  local_13 = 0;
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_00017ce0,"LinkMode.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_linkmode
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],&local_13,&local_12,&local_11);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[1] = (uint)local_13;
    param_1[2] = (uint)local_12;
    param_1[3] = (uint)local_11;
    uVar3 = 0;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n%s = %d\n",DAT_00017ce0,"LinkMode.autoneg",
             (uint)local_13,"LinkMode.speed",(uint)local_12,"LinkMode.duplex",(uint)local_11);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00017ce0,0x1d9);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


/* ============= FUNCTION: sw_port_get_port_linkstate @ 00017ce4 ============= */

undefined4 sw_port_get_port_linkstate(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  local_13 = 0;
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_00017e00,"LinkState.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_linkstate
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],&local_13,&local_12,&local_11);
  if (iVar2 == 0) {
    param_1[1] = (uint)local_13;
    iVar2 = sw_ztespeed_to_cspplatspeed(local_12);
    param_1[2] = iVar2;
    iVar2 = sw_zteduplex_to_cspplatduplex(local_11);
    uVar1 = g_switch_debug_level;
    param_1[3] = iVar2;
    uVar3 = 0;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n%s = %d\n",DAT_00017e00,"LinkState.link",param_1[1],
             "LinkState.speed",param_1[2],"LinkState.duplex",iVar2);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00017e00,0x1fb);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


/* ============= FUNCTION: sw_port_set_port_mirror @ 00017e04 ============= */

undefined4 sw_port_set_port_mirror(uint *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint unaff_r6;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar7 = *param_1;
  uVar4 = uVar7 - 5;
  if (uVar4 < 3) {
    unaff_r6 = uVar7 & 0xff;
  }
  uVar5 = param_1[2];
  uVar1 = uVar4;
  if (2 < uVar4) {
    uVar1 = (int)&g_sw_cap + uVar7;
  }
  uVar6 = param_1[3];
  if (2 < uVar4) {
    unaff_r6 = (uint)*(byte *)(uVar1 + 0xc);
  }
  uVar4 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[param_1[1]];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n",DAT_00017f64,"Mirror.sport",uVar7,
           "Mirror.enable",uVar5,"Mirror.direct",uVar6,"Mirror.dport",param_1[1]);
  }
  if (((lan_up & 1 << (unaff_r6 & 0xff)) == 0) || ((lan_up & 1 << uVar4) == 0)) {
    if (g_switch_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[%s] input invalid port!\n",DAT_00017f64);
      uVar2 = 0xffffffff;
    }
  }
  else {
    uVar6 = uVar6 & 0xff;
    iVar3 = zte_api_sw_port_set_port_mirror(unaff_r6,0,uVar6,uVar4);
    if (iVar3 == 0) {
      iVar3 = zte_api_sw_port_set_port_mirror(unaff_r6,uVar5 & 0xff,uVar6,uVar4);
      uVar2 = 0;
      if (iVar3 != 0) {
        printk("[%s] L%d tm sdk failed!\n",DAT_00017f64,0x236);
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("[%s] L%d tm sdk disable mirror failed!\n",DAT_00017f64,0x230);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}


/* ============= FUNCTION: sw_port_get_port_mirror @ 00017f68 ============= */

int sw_port_get_port_mirror(uint *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  byte local_13;
  byte local_12;
  byte local_11;
  
  local_13 = 0;
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s], the parameters coming in as follows:\n%s = %d\n",DAT_00018084,
           "ioctl_data_sweth->m_CommonArgs.Mirror.sport",*param_1);
  }
  uVar3 = *param_1;
  if (uVar3 - 6 < 2) {
    uVar3 = uVar3 & 0xff;
  }
  else {
    uVar3 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[uVar3];
  }
  iVar2 = zte_api_sw_port_get_port_mirror(uVar3,&local_13,&local_12,&local_11);
  uVar3 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[2] = (uint)local_13;
    param_1[3] = (uint)local_12;
    cVar1 = zte_api_sw_port_set_port_isolatemask[local_11];
    param_1[1] = (uint)(byte)cVar1;
    if (2 < uVar3) {
      printk("[%s], the result as follows:\n%s = %d\n%s = %d\n%s = %d\n",DAT_00018084,
             "Mirror.enable",(uint)local_13,"Mirror.direct",(uint)local_12,"Mirror.dport",
             (uint)(byte)cVar1);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00018084,0x256);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_port_set_port_loopback @ 00018088 ============= */

int sw_port_set_port_loopback(int *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = param_1[1];
  uVar4 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n",DAT_0001813c,"LoopBack.port",cVar1,
           "LLoopBack.enable",uVar3,"LoopBack.direct",uVar4);
  }
  iVar2 = zte_api_sw_port_set_port_loopback(cVar1,uVar4 & 0xff,uVar3 & 0xff);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001813c,0x276);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_port_get_port_loopback @ 00018140 ============= */

int sw_port_get_port_loopback(int *param_1)

{
  uint uVar1;
  int iVar2;
  byte local_12;
  byte local_11;
  
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_0001821c,"LoopBack.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_loopback
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],&local_11,&local_12);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[1] = (uint)local_12;
    param_1[2] = (uint)local_11;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n",DAT_0001821c,"LoopBack.direct",(uint)local_11,
             "LoopBack.enable",(uint)local_12);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001821c,0x28c);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_port_set_port_factoryloopback @ 00018220 ============= */

int sw_port_set_port_factoryloopback(undefined1 *param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = *param_1;
  uVar3 = *(uint *)(param_1 + 4);
  uVar4 = *(uint *)(param_1 + 8);
  if (2 < g_switch_debug_level) {
    printk("\n[%s] input:\n%s = %d\n%s = %d\n%s = %d\n",DAT_000182c4,"LoopBack.port",uVar1,
           "LLoopBack.enable",uVar3,"LoopBack.direct",uVar4);
  }
  iVar2 = zte_api_sw_port_set_port_loopback(uVar1,uVar4 & 0xff,uVar3 & 0xff);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_000182c4,0x2ab);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_port_get_port_factoryloopback @ 000182c8 ============= */

int sw_port_get_port_factoryloopback(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  byte local_12;
  byte local_11;
  
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_000183c8,"LoopBack.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_loopback(*(undefined1 *)param_1,&local_11,&local_12);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    uVar3 = (uint)local_12;
    param_1[1] = uVar3;
    param_1[2] = (uint)local_11;
    if (2 < uVar1) {
      pcVar4 = "LoopBack.enable";
      printk("\n[%s] output:\n%s = %d\n%s = %d\n",DAT_000183c8,"LoopBack.direct",(uint)local_11,
             "LoopBack.enable",uVar3);
      if (2 < g_switch_debug_level) {
        printk("%s = %c\n","phy_notcarelink",0x41,g_switch_debug_level,pcVar4,uVar3);
        return 0;
      }
    }
    iVar2 = 0;
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_000183c8,0x2c9);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_port_set_port_proaction @ 000183cc ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sw_port_set_port_proaction(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_set_port_protocolpktdeal] input ERROR: ioctl_data_sweth=null\n");
    }
  }
  else {
    uVar2 = *param_1;
    uVar4 = param_1[1];
    uVar3 = param_1[2];
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_port_set_port_protocolpktdeal] input: port=%d deal=%d protocal=%d\n",uVar2,
             uVar4,uVar3,param_4);
    }
    if (_tm_port_unknwn_multicast_floodport_set <= uVar2) {
      printk("[%s]%d input port error!\n",DAT_000184b4,0x301,_tm_port_unknwn_multicast_floodport_set
             ,param_4);
      return 0xffffffff;
    }
    iVar1 = tm_port_protocol_pktdeal_set(zte_api_sw_mac_set_port_macfiltermode[uVar2],uVar4,uVar3);
    if (iVar1 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_set_port_protocolpktdeal] return error: error code=0x%x\n");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_port_get_port_proaction @ 000184b8 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_proaction(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_get_port_protocolpktdeal] input ERROR: ioctl_data_sweth=null\n");
    }
    return 0xffffffff;
  }
  uVar3 = *param_1;
  uVar4 = param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_port_get_port_protocolpktdeal] input: port=%d protocal=%d\n",uVar3,uVar4);
  }
  if (uVar3 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_protocol_pktdeal_get
                      (zte_api_sw_mac_set_port_macfiltermode[uVar3],local_1c,uVar4);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][sw_port_get_port_protocolpktdeal] output: deal=%d\n",local_1c[0]);
      }
      uVar2 = 0;
      param_1[1] = local_1c[0];
    }
    else {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[SW][sw_port_get_port_protocolpktdeal] return error: error code=0x%x\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("[%s]%d input port error!\n",DAT_000185d0,0x32e);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_port_set_port_802dot1xen @ 000185d4 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sw_port_set_port_802dot1xen(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_set_port_802dot1xen] input ERROR: ioctl_data_sweth=null\n");
    }
  }
  else {
    uVar3 = *param_1;
    cVar1 = (char)param_1[1];
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_port_set_port_802dot1xen] input: port=%d enable=%d\n",uVar3,cVar1,
             g_switch_debug_level,param_4);
    }
    if (_tm_port_unknwn_multicast_floodport_set <= uVar3) {
      printk("[%s]%d input port error!\n",DAT_000186f0,0x359,_tm_port_unknwn_multicast_floodport_set
             ,param_4);
      return 0xffffffff;
    }
    if ((cVar1 == '\x01') &&
       (iVar2 = tm_port_status_set(zte_api_sw_mac_set_port_macfiltermode[uVar3],0), iVar2 != 0)) {
      if (g_switch_debug_level != 0) {
        printk("[SW][sw_port_set_port_802dot1xen] Fail: tm_port_status_set fail\n");
        return 0xffffffff;
      }
    }
    else {
      iVar2 = tm_port_802x_authen_set(zte_api_sw_mac_set_port_macfiltermode[uVar3],cVar1);
      if (iVar2 == 0) {
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("[SW][sw_port_set_port_802dot1xen] return error: error code=0x%x\n");
        return 0xffffffff;
      }
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_port_get_port_802dot1xen @ 000186f4 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_802dot1xen(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 local_11;
  
  local_11 = 0;
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_get_port_802dot1xen] input ERROR: ioctl_data_sweth=null\n");
    }
    return 0xffffffff;
  }
  uVar3 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_port_get_port_802dot1xen] input: port=%d\n",uVar3);
  }
  if (uVar3 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_802x_authen_get(zte_api_sw_mac_set_port_macfiltermode[uVar3],&local_11);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][sw_port_get_port_protocolpktdeal] output: enable=%d\n",local_11);
      }
      uVar2 = 0;
      *(undefined1 *)(param_1 + 1) = local_11;
    }
    else {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[SW][sw_port_get_port_protocolpktdeal] Fail: tm_port_802x_authen_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("[%s]%d input port error!\n",DAT_00018800,0x38c);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_port_set_ethdev_carrier @ 00018804 ============= */

undefined4 sw_port_set_ethdev_carrier(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_port_set_ethdev_carrier] input ERROR: ioctl_data_sweth=null\n");
    return 0xffffffff;
  }
  g_ethdev_carrierFlag = *param_1;
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("[SW][sw_port_set_ethdev_carrier] input: g_ethdev_carrierFlag %d \n");
  return 0;
}


/* ============= FUNCTION: sw_qos_select_queue @ 00018880 ============= */

uint sw_qos_select_queue(void)

{
  uint uVar1;
  
  uVar1 = CSPKernel_skb_SelectQueue();
  uVar1 = uVar1 & 0xff;
  if (uVar1 - 1 < 8) {
    return 8 - uVar1 & 0xff;
  }
  if (uVar1 == 0x8f) {
    uVar1 = 7;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* ============= FUNCTION: qos_global_para_clr @ 000188b4 ============= */

void qos_global_para_clr(void)

{
  __memzero(&g_qos_queue,0x60);
  g_num_weight = 0;
  g_queue_index = 0;
  if (g_switch_debug_level - 2 < 2) {
    g_tcont_size = 8;
    g_tcont_start = 1;
    return;
  }
  if (g_switch_debug_level < 2) {
    g_tcont_start = 0;
    g_tcont_size = 1;
  }
  return;
}


/* ============= FUNCTION: sw_qos_init @ 00018918 ============= */

void sw_qos_init(void)

{
  undefined4 in_r3;
  uint uVar1;
  uint uVar2;
  
  dev_qos_select_queue = sw_qos_select_queue;
  if ((g_pon_work_mode & 0x10) != 0) {
    return;
  }
  qos_global_para_clr();
  uVar2 = (uint)g_tcont_start;
  uVar1 = (uint)g_tcont_size;
  TCONT_QUEUE = 8;
  if (uVar1 <= uVar2) {
    return;
  }
  do {
    tm_tcont_secsch_hang_que_set(uVar2,0,0,uVar1,in_r3);
    tm_tcont_secsch_hang_que_set(uVar2,1,0);
    tm_tcont_secsch_hang_que_set(uVar2,2,0);
    tm_tcont_secsch_hang_que_set(uVar2,3,0);
    tm_tcont_secsch_hang_que_set(uVar2,4,0);
    tm_tcont_secsch_hang_que_set(uVar2,5,0);
    tm_tcont_secsch_hang_que_set(uVar2,6,0);
    tm_tcont_secsch_hang_que_set(uVar2,7,0);
    uVar1 = (uint)g_tcont_size;
    uVar2 = uVar2 + 1;
  } while ((int)uVar2 < (int)uVar1);
  return;
}


/* ============= FUNCTION: sw_qos_vdsl_up @ 000189fc ============= */

uint sw_qos_vdsl_up(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = dev_get_by_name(&init_net,&_LC0,param_3,param_4,param_4);
  if (iVar1 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x138);
    disableIRQinterrupts();
    iVar3 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
    *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) + -1;
    return uVar2 & 1;
  }
  return 0;
}


/* ============= FUNCTION: sw_qos_set_port_schedule @ 00018a50 ============= */

undefined4 sw_qos_set_port_schedule(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n","sw_qos_set_port_schedule",
           "Schedule.port",*param_1,"Schedule.queue",param_1[1],"Schedule.mode(0-sp 1-dwrr)",
           param_1[2],"Schedule.weight",param_1[3]);
  }
  iVar1 = zte_api_sw_qos_set_port_schedule
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],(char)param_1[1],
                     (char)param_1[2],(char)param_1[3]);
  uVar2 = 0;
  if (iVar1 != 0) {
    printk("%s failed!\n","sw_qos_set_port_schedule");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_qos_get_port_schedule @ 00018b20 ============= */

undefined4 sw_qos_get_port_schedule(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte local_12;
  byte local_11;
  
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n",DAT_00018c1c,"Schedule.port",*param_1,"Schedule.queue",
           param_1[1]);
  }
  iVar2 = zte_api_sw_qos_get_port_schedule
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],(char)param_1[1],&local_12,
                     &local_11);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[2] = (uint)local_12;
    param_1[3] = (uint)local_11;
    uVar3 = 0;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n",DAT_00018c1c,"Schedule.mode(1-sp 0-dwrr)",
             (uint)local_12,"Schedule.weight",(uint)local_11);
    }
  }
  else {
    printk("%s failed!\n",DAT_00018c1c);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


/* ============= FUNCTION: sw_qos_set_tcontschedule @ 00018c20 ============= */

undefined4 sw_qos_set_tcontschedule(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_qos_set_tcontschedule] input ERROR!\nioctl_data_sweth=NULL\n");
    return 0xffffffff;
  }
  uVar3 = *param_1;
  uVar2 = param_1[1];
  uVar5 = param_1[3];
  uVar4 = param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_qos_set_tcontschedule] input: tcont_id=%d queue=%d mod=%d weight=%d\n",uVar3,
           uVar2,uVar4,uVar4);
    if (param_1[2] == 0) {
      if (g_switch_debug_level < 3) goto LAB_00018c54;
      printk(&_LC12);
    }
    else {
      if (g_switch_debug_level < 3) goto LAB_00018c54;
      printk("dwrr ");
    }
    if (2 < g_switch_debug_level) {
      printk("weight=%d\n",uVar5);
    }
  }
LAB_00018c54:
  iVar1 = tm_tcont_que_sch_sp_dwwr_mod_set(uVar3,uVar2,uVar4 & 0xff);
  if (iVar1 == 0) {
    iVar1 = tm_tcont_que_sch_weight_set(uVar3,uVar2,uVar5);
    if (iVar1 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_qos_set_tcontschedule] return error! tm_tcont_que_sch_weight_set fail! tcont_id=%d quene=%d weight=%d\n"
             ,uVar3,uVar2,uVar5);
    }
  }
  else if (g_switch_debug_level != 0) {
    printk("[SW][sw_qos_set_tcontschedule] return error! tm_tcont_que_sch_sp_dwwr_mod_set fail! tcont_id=%d quene=%d mode=%d\n"
           ,uVar3,uVar2,uVar4);
    return 0xffffffff;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_qos_get_tcontschedule @ 00018d84 ============= */

undefined4 sw_qos_get_tcontschedule(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte local_1d;
  undefined4 local_1c;
  
  local_1c = 0;
  local_1d = 0;
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_qos_get_tcontschedule] input ERROR!\nioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  uVar4 = *param_1;
  uVar3 = param_1[1];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_qos_get_tcontschedule] input: tcont_id=%d queue=%d\n",uVar4,uVar3);
  }
  iVar1 = tm_tcont_que_sch_sp_dwwr_mod_get(uVar4,uVar3,&local_1d);
  if (iVar1 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_qos_get_tcontschedule] return error! tm_tcont_que_sch_sp_dwwr_mod_get fail!tcont_id=%d queue=%d\n"
           ,uVar4,uVar3);
    return 0xffffffff;
  }
  iVar1 = tm_tcont_que_sch_weight_get(uVar4,uVar3,&local_1c);
  if (iVar1 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_qos_get_tcontschedule] return error! tm_tcont_que_sch_weight_get fail! tcont_id=%d queue=%d\n"
           ,uVar4,uVar3);
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_qos_get_tcontschedule] output: tcont_id=%d queue=%d mode=%d ",uVar4,uVar3,
           local_1d);
    uVar2 = (uint)local_1d;
    if (uVar2 == 0) {
      if (g_switch_debug_level < 3) goto LAB_00018e1c;
      printk(&_LC12);
    }
    else {
      if (g_switch_debug_level < 3) goto LAB_00018e1c;
      printk("dwrr ");
    }
    if (2 < g_switch_debug_level) {
      printk("weight=%d\n",local_1c);
    }
  }
  uVar2 = (uint)local_1d;
LAB_00018e1c:
  param_1[2] = uVar2;
  param_1[3] = local_1c;
  return 0;
}


/* ============= FUNCTION: sw_qos_get_availbktid @ 00018f24 ============= */

undefined4 sw_qos_get_availbktid(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_14 [2];
  
  local_14[0] = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("sw_qos_get_availbktid input ERROR!\nioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  iVar1 = zte_api_sw_qos_get_availbktid(local_14);
  if (iVar1 == 0) {
    if (local_14[0] == 0x20) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("sw_qos_get_availbktid return ERROR!\nno avail bucket\n");
      uVar2 = 0xffffffff;
    }
    else {
      *param_1 = local_14[0];
      uVar2 = 0;
      if (2 < g_switch_debug_level) {
        printk("sw_qos_get_availbktid output:\nbucket index=%d\n");
      }
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00019000,0x150);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_qos_set_trustppqueue @ 00019004 ============= */

undefined4 sw_qos_set_trustppqueue(void)

{
  return 0;
}


/* ============= FUNCTION: sw_qos_get_trustppqueue @ 0001900c ============= */

undefined4 sw_qos_get_trustppqueue(void)

{
  return 0;
}


/* ============= FUNCTION: sw_qos_set_opritoqueue @ 00019014 ============= */

undefined4 sw_qos_set_opritoqueue(void)

{
  return 0;
}


/* ============= FUNCTION: sw_qos_get_opritoqueue @ 0001901c ============= */

undefined4 sw_qos_get_opritoqueue(void)

{
  return 0;
}


/* ============= FUNCTION: qos_info_show @ 00019024 ============= */

undefined4 qos_info_show(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  printk("\n***********************QOS INFO********************************\n");
  printk("\nqos mode:%d\n",g_qos_mode);
  printk("\n-----------------------QOS MODE-----------------------------\n");
  printk("\n-----------------------QOS QUEUE-----------------------------\n");
  if (TCONT_QUEUE != 0) {
    puVar1 = &DAT_0002b760;
    iVar2 = 0;
    do {
      iVar3 = iVar2 + 1;
      printk("\nindex;%d,status:%d,qos_weight;%d,weight_flag;%d\n",iVar2,*puVar1,puVar1[-2],
             puVar1[-1]);
      puVar1 = puVar1 + 3;
      iVar2 = iVar3;
    } while (iVar3 < (int)(uint)TCONT_QUEUE);
  }
  printk("\n---------------------------QUEUE-----------------------------\n");
  return 0;
}


/* ============= FUNCTION: pon_driver_adapter_schedue_mode_set @ 000190d0 ============= */

int pon_driver_adapter_schedue_mode_set
              (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (g_qos_mode != param_1) {
    g_qos_mode = (byte)param_1;
    qos_global_para_clr();
    if (2 < g_switch_debug_level) {
      printk("[%s] output mode = %d\n",DAT_000191f8,param_1,g_switch_debug_level,param_4);
    }
    if (param_1 == 1) {
      param_1 = 0;
    }
    else if (param_1 == 2) {
      param_1 = 1;
    }
    iVar4 = -1;
    uVar3 = (uint)g_tcont_start;
    if (uVar3 < g_tcont_size) {
      do {
        if (TCONT_QUEUE != 0) {
          iVar1 = 0;
          do {
            iVar2 = iVar1 + 1;
            iVar4 = tm_tcont_que_sch_sp_dwwr_mod_set(uVar3,iVar1,param_1);
            if ((iVar4 != 0) && (g_switch_debug_level != 0)) {
              printk("The function %s line:%d is error :%d\n",DAT_000191f8,0x23f,iVar4);
            }
            iVar1 = iVar2;
          } while (iVar2 < (int)(uint)TCONT_QUEUE);
        }
        uVar3 = uVar3 + 1;
      } while ((int)uVar3 < (int)(uint)g_tcont_size);
    }
    return iVar4;
  }
  qos_global_para_clr();
  if (g_switch_debug_level != 0) {
    printk("[%s] the qos mode is not changed\n",DAT_000191f8);
    return 0;
  }
  return 0;
}


/* ============= FUNCTION: wan_driver_adapter_schedue_mode_set @ 000191fc ============= */

int wan_driver_adapter_schedue_mode_set
              (uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (7 < param_1) {
    printk("queue_id = %d  >= QUEUE_SIZE=%d\n",param_1,8,param_4,param_4);
    return -1;
  }
  *(char *)((int)&g_queue_mode + param_1) = (char)param_2;
  iVar1 = sw_qos_vdsl_up();
  if (iVar1 == 0) {
    if ((param_2 != 1) && (param_2 == 2)) {
      param_2 = 0;
    }
    iVar1 = zte_api_sw_qos_set_port_schedule(tm_vlan_check_ena_set,param_1,param_2,0);
  }
  else {
    if (param_2 == 1) {
      param_2 = 0;
    }
    else if (param_2 == 2) {
      param_2 = 1;
    }
    iVar1 = tm_tcont_que_sch_sp_dwwr_mod_set(0,param_1,param_2);
  }
  if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
    printk("The function %s line:%d is error :%d\n",DAT_000192e8,0x348,iVar1,param_4);
    return iVar1;
  }
  return iVar1;
}


/* ============= FUNCTION: sw_qos_set_mode_schedule @ 000192ec ============= */

int sw_qos_set_mode_schedule(undefined1 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  if (1 < g_switch_debug_level) {
    printk("the function:%s, the parameters coming in as follows:\n%s = %d, %s = %d\n",DAT_000193a8,
           &_LC37,uVar1,"queue_id",uVar2);
  }
  if ((g_pon_work_mode & 0x10) == 0) {
    iVar3 = pon_driver_adapter_schedue_mode_set(uVar1);
  }
  else {
    iVar3 = wan_driver_adapter_schedue_mode_set(uVar2,uVar1);
  }
  if ((iVar3 != 0) && (g_switch_debug_level != 0)) {
    printk("the function:%s, qos set mode failed\n",DAT_000193a8);
  }
  return iVar3;
}


/* ============= FUNCTION: sw_qos_set_queue @ 000193ac ============= */

undefined4 sw_qos_set_queue(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  bool bVar9;
  
  uVar5 = (uint)*param_1;
  bVar1 = param_1[1];
  uVar8 = *(uint *)(param_1 + 4);
  if (1 < g_switch_debug_level) {
    printk("the function:%s, the parameters coming in as follows:\n%s = %d\n%s = %d\n%s = %d\n",
           DAT_0001966c,"queue_id",uVar5,"status",(uint)bVar1,"weight",uVar8);
  }
  if ((g_pon_work_mode & 0x10) == 0) {
    uVar2 = (uint)TCONT_QUEUE;
    bVar9 = g_qos_mode == '\x02';
    uVar5 = (uVar2 - 1) - uVar5 & 0xff;
    (&g_qos_queue)[uVar5 * 3] = uVar8;
    (&DAT_0002b760)[uVar5 * 3] = (uint)bVar1;
    (&DAT_0002b75c)[uVar5 * 3] = 1;
    if (bVar9) {
      g_queue_index = g_queue_index + 1;
      if (g_num_weight == 100) {
        if (g_queue_index <= uVar2) {
          if (uVar2 != g_queue_index) {
            return 0;
          }
          g_num_weight = 0;
          g_queue_index = 0;
          return 0;
        }
        g_queue_index = 1;
        g_num_weight = 0;
      }
      if (g_switch_debug_level != 0) {
        printk("the function:%s, num_weight = %d queue_index  = %d:\n",DAT_00019668,g_num_weight,
               g_queue_index);
      }
      g_num_weight = g_num_weight + (&g_qos_queue)[uVar5 * 3];
      if ((g_num_weight == 100) && (uVar5 = (uint)g_tcont_start, uVar5 < g_tcont_size)) {
        do {
          if (TCONT_QUEUE != 0) {
            iVar3 = 0;
            piVar7 = DAT_00019660;
            do {
              iVar4 = 0;
              iVar6 = iVar3 + 1;
              if (*piVar7 == 1) {
                iVar4 = piVar7[-1];
              }
              iVar3 = tm_tcont_que_sch_weight_set(uVar5,iVar3,iVar4);
              if ((iVar3 != 0) && (g_switch_debug_level != 0)) {
                printk("the function:%s, the error code is %d:\n",DAT_00019668);
              }
              iVar3 = iVar6;
              piVar7 = piVar7 + 3;
            } while (iVar6 < (int)(uint)TCONT_QUEUE);
          }
          uVar5 = uVar5 + 1;
        } while ((int)uVar5 < (int)(uint)g_tcont_size);
      }
    }
  }
  else {
    if (7 < uVar5) {
      printk("queue_id = %d  >= QUEUE_SIZE\n",uVar5,8);
      return 0xffffffff;
    }
    if (*(char *)((int)&g_queue_mode + uVar5) != '\x02') {
      printk("queue_id=%d, weight=%d\n",uVar5,uVar8);
      return 0;
    }
    iVar3 = sw_qos_vdsl_up();
    if (iVar3 == 0) {
      iVar3 = zte_api_sw_qos_set_port_schedule(tm_vlan_check_ena_set,uVar5,0,uVar8 & 0xff);
    }
    else {
      iVar3 = tm_tcont_que_sch_weight_set(0,uVar5,uVar8);
    }
    if ((iVar3 != 0) && (g_switch_debug_level != 0)) {
      printk("the function:%s, the error code is %d:\n",DAT_00019664);
      return 0;
    }
  }
  return 0;
}


/* ============= FUNCTION: sw_qos_set_rcqueue @ 00019670 ============= */

int sw_qos_set_rcqueue(undefined1 *param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 uVar6;
  char *pcVar7;
  uint uVar8;
  
  uVar3 = (uint)(byte)param_1[8];
  uVar1 = *param_1;
  uVar4 = *(undefined4 *)(param_1 + 4);
  if (1 < g_switch_debug_level) {
    pcVar5 = "bandwidth";
    pcVar7 = "action";
    uVar6 = uVar4;
    uVar8 = uVar3;
    printk("the function:%s, the parameters coming in as follows:\n%s = %d\n%s = %d\n%s = %d\n",
           DAT_00019758,"index",uVar1,"bandwidth",uVar4,"action",uVar3);
    if (1 < g_switch_debug_level) {
      printk("the function:%s, the parameters coming in as follows:\n%s = %d\n",DAT_0001975c,
             "rcqueue.ena",uVar3 == 0,pcVar5,uVar6,pcVar7,uVar8);
    }
  }
  iVar2 = tm_flow_rate_limit_set(uVar1,uVar3 == 0,uVar4,0);
  if ((iVar2 != 0) && (g_switch_debug_level != 0)) {
    printk("the function:%s, qos set rcqueue failed\n",DAT_00019758);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_qos_set_overall_bandwidth @ 00019760 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_qos_set_overall_bandwidth(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[%s] the input para is null\n",DAT_000198c8);
      return -1;
    }
    return -1;
  }
  if (1 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_000198c8,"Scheduler.overall",*param_1);
  }
  uVar3 = *param_1;
  if ((g_pon_work_mode & 0x10) == 0) {
    uVar2 = (uint)g_tcont_start;
    if (g_tcont_size <= uVar2) {
      iVar1 = -1;
      goto LAB_000197ec;
    }
    do {
      iVar1 = tm_tcont_sharp_set(uVar2,uVar3);
      uVar2 = uVar2 + 1;
    } while ((int)uVar2 < (int)(uint)g_tcont_size);
  }
  else {
    iVar1 = sw_qos_vdsl_up();
    if (iVar1 == 0) {
      printk("g_sw_cap.sw_wan_port = %d\n",_tm_vlan_check_ena_set);
      iVar1 = zte_api_sw_port_set_port_ratelimit(_tm_vlan_check_ena_set & 0xff,1,1,1,uVar3,0,1);
    }
    else {
      iVar1 = tm_tcont_sharp_set(0,uVar3);
    }
  }
  if (iVar1 == 0) {
    return 0;
  }
LAB_000197ec:
  if (g_switch_debug_level != 0) {
    printk("[%s] the error code is %dl\n",DAT_000198c8,iVar1);
  }
  return iVar1;
}


/* ============= FUNCTION: sw_qos_get_queue_id @ 000198cc ============= */

void sw_qos_get_queue_id(void)

{
  return;
}


/* ============= FUNCTION: sw_port_set_port_ratelimit @ 000198d0 ============= */

int sw_port_set_port_ratelimit(int *param_1)

{
  code cVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",
           "sw_port_set_port_ratelimit","RateLimit.port",cVar1,"RateLimit.direct",(char)iVar2,
           "RateLimit.enable",param_1[2] & 0xff,"RateLimit.rate",param_1[3],"RateLimit.ifgmode",
           (char)param_1[7]);
  }
  iVar2 = zte_api_sw_port_set_port_ratelimit(cVar1,(char)iVar2);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_ratelimit",0x38);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_port_get_port_ratelimit @ 000199d0 ============= */

int sw_port_get_port_ratelimit(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  byte local_1f;
  byte local_1e;
  byte local_1d;
  int local_1c [2];
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_1f = 0;
  local_1e = 0;
  local_1c[0] = 0;
  local_1d = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_00019af4,"RateLimit.port",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_ratelimit(cVar1,&local_1f,&local_1e,local_1c,&local_1d);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_1f;
    param_1[2] = (uint)local_1e;
    param_1[3] = local_1c[0];
    param_1[7] = (uint)local_1d;
    if (2 < uVar2) {
      printk("[%s] output:\n %s = %d \n %s = %d \n %s = %d kbps\n %s = %d\n",DAT_00019af4,
             "RateLimit.direct",(uint)local_1f,"RateLimit.enable",(uint)local_1e,"RateLimit.rate",
             local_1c[0],"RateLimit.ifgmode",(uint)local_1d);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00019af4,0x50);
  }
  return iVar3;
}


/* ============= FUNCTION: sw_port_set_port_broadcastrate @ 00019af8 ============= */

undefined4 sw_port_set_port_broadcastrate(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  
  iVar4 = param_1[1];
  iVar2 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar6 = param_1[3];
  iVar3 = param_1[7];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",DAT_00019be4,
           "RateLimit.port",cVar1,"RateLimit.direct",(char)iVar4,"RateLimit.enable",(char)iVar2,
           "RateLimit.rate",iVar6,"RateLimit.ifgmode",(char)iVar3);
  }
  iVar4 = zte_api_sw_port_set_port_broadcastrate
                    (cVar1,(char)iVar4,(char)iVar2,0,iVar6,0,(char)iVar3);
  uVar5 = 0;
  if (iVar4 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00019be4,0x77);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}


/* ============= FUNCTION: sw_port_get_port_broadcastrate @ 00019be8 ============= */

int sw_port_get_port_broadcastrate(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  byte local_1f;
  byte local_1e;
  byte local_1d;
  int local_1c [2];
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_1f = 0;
  local_1e = 0;
  local_1c[0] = 0;
  local_1d = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_00019d0c,"RateLimit.port",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_broadcastrate(cVar1,&local_1f,&local_1e,local_1c,&local_1d);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_1f;
    param_1[2] = (uint)local_1e;
    param_1[3] = local_1c[0];
    param_1[7] = (uint)local_1d;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",DAT_00019d0c,
             "RateLimit.direct",(uint)local_1f,"RateLimit.enable",(uint)local_1e,"RateLimit.rate",
             local_1c[0],"RateLimit.ifgmode",(uint)local_1d);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00019d0c,0x90);
  }
  return iVar3;
}


/* ============= FUNCTION: sw_port_set_cpu_broadcastrate @ 00019d10 ============= */

undefined4 sw_port_set_cpu_broadcastrate(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[%s] cpu broadcast rate limit = %d\n",DAT_00019d80,iVar1);
  }
  if (3999 < iVar1 - 1U) {
    iVar1 = 4000;
  }
  tm_protocol_pkt_limit_pps_set(0,0,1,iVar1);
  tm_protocol_pkt_limit_pps_set(1,1,1,iVar1);
  return 0;
}


/* ============= FUNCTION: sw_port_set_cpu_queue_ratelimit @ 00019d84 ============= */

undefined4 sw_port_set_cpu_queue_ratelimit(void)

{
  return 0;
}


/* ============= FUNCTION: sw_port_set_port_multiprorate @ 00019d8c ============= */

undefined4
sw_port_set_port_multiprorate
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00019da8,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_port_get_port_multiprorate @ 00019dac ============= */

undefined4
sw_port_get_port_multiprorate
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n",DAT_00019dc8,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: sw_port_set_port_multicastrate @ 00019dcc ============= */

undefined4 sw_port_set_port_multicastrate(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  
  iVar4 = param_1[1];
  iVar2 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar6 = param_1[3];
  iVar3 = param_1[7];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",DAT_00019eb8,
           "RateLimit.port",cVar1,"RateLimit.direct",(char)iVar4,"RateLimit.enable",(char)iVar2,
           "RateLimit.rate",iVar6,"RateLimit.ifgmode",(char)iVar3);
  }
  iVar4 = zte_api_sw_port_set_port_multicastrate
                    (cVar1,(char)iVar4,(char)iVar2,0,iVar6,0,(char)iVar3);
  uVar5 = 0;
  if (iVar4 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_00019eb8,0xde);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}


/* ============= FUNCTION: sw_port_get_port_multicastrate @ 00019ebc ============= */

int sw_port_get_port_multicastrate(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  byte local_1f;
  byte local_1e;
  byte local_1d;
  int local_1c [2];
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_1f = 0;
  local_1e = 0;
  local_1c[0] = 0;
  local_1d = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_00019fe0,"RateLimit.port",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_multicastrate(cVar1,&local_1f,&local_1e,local_1c,&local_1d);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_1f;
    param_1[2] = (uint)local_1e;
    param_1[3] = local_1c[0];
    param_1[7] = (uint)local_1d;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",DAT_00019fe0,
             "RateLimit.direct",(uint)local_1f,"RateLimit.enable",(uint)local_1e,"RateLimit.rate",
             local_1c[0],"RateLimit.ifgmode",(uint)local_1d);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_00019fe0,0xf6);
  }
  return iVar3;
}


/* ============= FUNCTION: sw_reg_set_readreg @ 00019fe4 ============= */

undefined4 sw_reg_set_readreg(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_1[1];
  if (g_switch_debug_level < 3) {
    uVar1 = fpga_read_reg(*param_1);
  }
  else {
    printk("[%s] input:\n%s = 0x%x\n","sw_reg_set_readreg","Reg.addr");
    uVar1 = fpga_read_reg(*param_1);
  }
  uVar2 = g_switch_debug_level;
  param_1[2] = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
               uVar1 >> 0x18;
  if (uVar2 < 3) {
    if (uVar3 == 0) {
      return 0;
    }
  }
  else {
    printk("[%s] output:\nReg.value = 0x","sw_reg_set_readreg");
    uVar2 = g_switch_debug_level;
    if (uVar3 == 0) goto LAB_0001a06c;
  }
  param_1 = param_1 + 2;
  uVar1 = 0;
  do {
    uVar1 = uVar1 + 1;
    if (2 < uVar2) {
      printk("%02x ",*(undefined1 *)param_1);
      uVar2 = g_switch_debug_level;
    }
    param_1 = (undefined4 *)((int)param_1 + 1);
  } while (uVar1 < uVar3);
LAB_0001a06c:
  if (2 < uVar2) {
    printk(&_LC4);
  }
  return 0;
}


/* ============= FUNCTION: sw_reg_set_writereg @ 0001a0f4 ============= */

undefined4 sw_reg_set_writereg(undefined4 *param_1)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar3 = param_1 + 2;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = 0x%x\n",DAT_0001a1d8,"Reg.addr",*param_1);
    if (2 < g_switch_debug_level) {
      printk("Reg.value = 0x");
    }
  }
  uVar1 = g_switch_debug_level;
  puVar2 = puVar3;
  do {
    if (2 < uVar1) {
      printk("%02x ",(char)*puVar2);
      uVar1 = g_switch_debug_level;
    }
    puVar2 = (uint *)((int)puVar2 + 1);
  } while (puVar2 != param_1 + 3);
  if (uVar1 < 3) {
    uVar1 = *puVar3;
  }
  else {
    printk(&_LC4);
    uVar1 = *puVar3;
  }
  fpga_write_reg(*param_1,uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8
                          | uVar1 >> 0x18);
  return 0;
}


/* ============= FUNCTION: sw_phy_reg_set_readreg @ 0001a1dc ============= */

undefined4 sw_phy_reg_set_readreg(int *param_1)

{
  code cVar1;
  undefined4 uVar2;
  uint uVar3;
  ushort local_1a [3];
  
  uVar3 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_1a[0] = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = 0x%x\n",DAT_0001a2b4,"PhyReg.port",cVar1,"PhyReg.addr",
           uVar3 & 0xffff);
  }
  if ((byte)cVar1 < 5) {
    uVar2 = zte_api_sw_phy_read(cVar1,uVar3 & 0xffff,local_1a);
    uVar3 = g_switch_debug_level;
    if (g_switch_debug_level < 3) {
      uVar2 = 0;
    }
    param_1[3] = (uint)local_1a[0];
    if (2 < uVar3) {
      printk("[%s] output:\nPhyReg.data = 0x%x\n",DAT_0001a2b4);
      uVar2 = 0;
    }
  }
  else {
    printk("sw_phy_reg_set_readreg port invalid!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_phy_reg_set_writereg @ 0001a2b8 ============= */

undefined4 sw_phy_reg_set_writereg(int *param_1)

{
  code cVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = param_1[2];
  uVar3 = param_1[3];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = 0x%x\n%s = 0x%x\n",DAT_0001a370,"PhyReg.port",cVar1,
           "PhyReg.addr",uVar4 & 0xffff,"PhyReg.data",uVar3 & 0xffff);
  }
  if ((byte)cVar1 < 5) {
    zte_api_sw_phy_write(cVar1,uVar4 & 0xffff,uVar3 & 0xffff);
    uVar2 = 0;
  }
  else {
    printk("sw_phy_reg_set_readreg port invalid!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_vlan_set_port_inframemode @ 0001a374 ============= */

int sw_vlan_set_port_inframemode(int *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n","sw_vlan_set_port_inframemode","InframeMode.port",
           *param_1,"InframeMode.mode",uVar3);
  }
  iVar2 = zte_api_sw_vlan_set_port_inframemode(cVar1,uVar3 & 0xff);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed![zte_api_sw_vlan_set_port_inframemode]\n",
           "sw_vlan_set_port_inframemode",0x2d);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_vlan_get_port_inframemode @ 0001a414 ============= */

int sw_vlan_get_port_inframemode(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  byte local_19 [5];
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_19[0] = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_0001a5a8,"InframeMode.port");
  }
  iVar3 = zte_api_sw_vlan_get_port_inframemode(cVar1,local_19);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    uVar4 = (uint)local_19[0];
    param_1[1] = uVar4;
    if (uVar4 == 0) {
      iVar3 = 0;
      if (2 < uVar2) {
        printk("[%s] output:\n%s = discard none\n",DAT_0001a5a8,"InframeMode.mode");
      }
    }
    else if (uVar4 == 0x3f) {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard all\n",DAT_0001a5a8,"InframeMode.mode");
    }
    else if (uVar4 == 1) {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard untag\n",DAT_0001a5a8,"InframeMode.mode");
    }
    else if (uVar4 == 0x3e) {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard tagged\n",DAT_0001a5a8,"InframeMode.mode");
    }
    else {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard hybrid\n",DAT_0001a5a8,"InframeMode.mode");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001a5a8,0x43);
  }
  return iVar3;
}


/* ============= FUNCTION: sw_vlan_set_port_pvid @ 0001a5ac ============= */

int sw_vlan_set_port_pvid(uint *param_1)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = param_1;
  if (2 < g_switch_debug_level) {
    puVar3 = (uint *)printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n",DAT_0001a670,"Pvid.port",
                            *param_1,"Pvid.pvid",param_1[1],"Pvid.priority",param_1[2]);
  }
  uVar5 = *param_1;
  uVar4 = uVar5 - 6;
  puVar1 = (uint *)uVar5;
  if (1 < uVar4) {
    uVar5 = (int)&g_sw_cap + uVar5;
    puVar1 = puVar3;
  }
  if (1 < uVar4) {
    puVar1 = (uint *)(uint)*(byte *)(uVar5 + 0xc);
  }
  iVar2 = zte_api_sw_vlan_set_port_pvid((uint)puVar1 & 0xff,(short)param_1[1],(char)param_1[2]);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001a670,0x7d);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_vlan_get_port_pvid @ 0001a674 ============= */

int sw_vlan_get_port_pvid(uint *param_1)

{
  int iVar1;
  uint uVar2;
  byte local_13;
  ushort local_12;
  
  local_12 = 0;
  local_13 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_0001a764,"Pvid.port",*param_1);
  }
  uVar2 = *param_1;
  if (1 < uVar2 - 6) {
    uVar2 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[uVar2];
  }
  iVar1 = zte_api_sw_vlan_get_port_pvid(uVar2 & 0xff,&local_12,&local_13);
  uVar2 = g_switch_debug_level;
  if (iVar1 == 0) {
    param_1[1] = (uint)local_12;
    param_1[2] = (uint)local_13;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n%s = %d\n",DAT_0001a764,"Pvid.pvid",(uint)local_12,
             "Pvid.priority",(uint)local_13);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n",DAT_0001a764,0x9c);
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_set_port_vlancfg @ 0001a768 ============= */

int sw_vlan_set_port_vlancfg(uint *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint unaff_r7;
  uint uVar5;
  uint uVar6;
  
  uVar5 = *param_1;
  uVar6 = param_1[2];
  uVar2 = uVar5 - 6;
  uVar4 = param_1[1];
  uVar3 = param_1[3];
  if (uVar2 < 2) {
    unaff_r7 = uVar5 & 0xff;
  }
  if (1 < uVar2) {
    param_2 = (int)&g_sw_cap + uVar5;
  }
  if (1 < uVar2) {
    unaff_r7 = (uint)*(byte *)(param_2 + 0xc);
  }
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n",DAT_0001a848,"VlanCfg.port",uVar5,
           "VlanCfg.minvlan",uVar6,"VlanCfg.maxvlan",uVar3,"VlanCfg.mode",uVar4);
  }
  iVar1 = zte_api_sw_vlan_set_port_vlancfg(unaff_r7,uVar6 & 0xffff,uVar3 & 0xffff,uVar4 & 0xff);
  if (iVar1 != 0) {
    printk("[%s] L%d tm sdk failed![zte_api_sw_vlan_set_port_vlancfg]\n",DAT_0001a848,199);
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_get_port_vlancfg @ 0001a84c ============= */

int sw_vlan_get_port_vlancfg(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = 0;
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n",DAT_0001a910,"Vlan.vlan",*param_1);
  }
  iVar2 = zte_api_sw_vlan_get_port_vlancfg(*(undefined2 *)param_1,&local_18,&local_14);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[1] = local_18;
    param_1[2] = local_14;
    if (2 < uVar1) {
      printk("%s = 0x%x\n%s = 0x%x\n","Vlan.mbmask",local_18,"Vlan.untagmask",local_14);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed![zte_api_sw_vlan_get_port_vlancfg]\n",DAT_0001a910,0xda);
  }
  return iVar2;
}


/* ============= FUNCTION: sw_vlan_add_port_vlantranslationentry @ 0001a914 ============= */

undefined4 sw_vlan_add_port_vlantranslationentry(void)

{
  return 0;
}


/* ============= FUNCTION: sw_vlan_del_port_vlantranslationentry @ 0001a91c ============= */

undefined4 sw_vlan_del_port_vlantranslationentry(void)

{
  return 0;
}


/* ============= FUNCTION: sw_vlan_add_port_dsvlantranslationentry @ 0001a924 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_add_port_dsvlantranslationentry(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  uint local_2c;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      iVar1 = -1;
    }
    else {
      printk("sw_vlan_add_port_dsvlantranslationentry input ERROR!\nioctl_data_sweth=NULL\n");
      iVar1 = -1;
    }
  }
  else {
    uVar2 = param_1[1];
    if ((2 < g_switch_debug_level) &&
       (printk("sw_vlan_add_port_dsvlantranslationentry input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\n"
               ,*param_1,uVar2,param_1[2],param_1[3]), 2 < g_switch_debug_level)) {
      printk("[SW][sw_vlan_add_port_dsvlantranslationentry] input:\tvalid=%d\tvlan_en=%d\tuni_pri=%d\tpon_pri=%d\tpri_use=%d\tpri_en=%d\n"
             ,*(undefined1 *)(param_1 + 4),*(undefined1 *)((int)param_1 + 0x11),
             *(undefined1 *)((int)param_1 + 0x12),*(undefined1 *)((int)param_1 + 0x13),
             *(undefined1 *)(param_1 + 5),*(undefined1 *)((int)param_1 + 0x15));
    }
    if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
      __memzero(&local_38,0x18);
      local_34 = *param_1;
      local_30 = param_1[3];
      local_2c = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[uVar2];
      local_25 = *(undefined1 *)((int)param_1 + 0x13);
      local_23 = *(undefined1 *)((int)param_1 + 0x15);
      local_24 = *(undefined1 *)(param_1 + 5);
      local_26 = *(undefined1 *)((int)param_1 + 0x12);
      local_27 = *(undefined1 *)((int)param_1 + 0x11);
      local_28 = 1;
      local_38 = param_1[2];
      if (local_30 == 0) {
        local_38 = local_34;
      }
      if (2 < g_switch_debug_level) {
        printk("[SW][tm_broadcst_vltrans_table_add_set] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\tpon_pri=%d\tpri_en=%d\tpri_use=%d\nuni_pri=%d\tvalid=%d\tvlan_en=%d\n"
               ,local_34,local_2c,local_38,local_30,local_25,local_23,local_24,local_26,1,local_27);
      }
      iVar1 = tm_broadcst_vltrans_table_add_set(&local_38);
      if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
        printk("sw_vlan_add_port_dsvlantranslationentry return error!\nerror code=0x%x\n",iVar1);
      }
    }
    else {
      printk("[%s]%d input port error!\n",DAT_0001aaec,300);
      iVar1 = -1;
    }
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_del_port_dsvlantranslationentry @ 0001aaf0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_del_port_dsvlantranslationentry(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      iVar1 = -1;
    }
    else {
      printk("sw_vlan_del_port_dsvlantranslationentry input ERROR!\nioctl_data_sweth=NULL\n");
      iVar1 = -1;
    }
  }
  else {
    uVar2 = param_1[1];
    if ((2 < g_switch_debug_level) &&
       (printk("sw_vlan_del_port_dsvlantranslationentry input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\n"
               ,*param_1,uVar2,param_1[2],param_1[3]), 2 < g_switch_debug_level)) {
      printk("[SW][sw_vlan_del_port_dsvlantranslationentry] input:\tvalid=%d\tvlan_en=%d\tuni_pri=%d\tpon_pri=%d\tpri_use=%d\tpri_en=%d\n"
             ,*(undefined1 *)(param_1 + 4),*(undefined1 *)((int)param_1 + 0x11),
             *(undefined1 *)((int)param_1 + 0x12),*(undefined1 *)((int)param_1 + 0x13),
             *(undefined1 *)(param_1 + 5),*(undefined1 *)((int)param_1 + 0x15));
    }
    if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
      __memzero(&local_38,0x18);
      local_2c = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[uVar2];
      local_34 = *param_1;
      local_30 = param_1[3];
      local_38 = param_1[2];
      local_25 = *(undefined1 *)((int)param_1 + 0x13);
      local_23 = *(undefined1 *)((int)param_1 + 0x15);
      local_24 = *(undefined1 *)(param_1 + 5);
      local_26 = *(undefined1 *)((int)param_1 + 0x12);
      local_27 = *(undefined1 *)((int)param_1 + 0x11);
      local_28 = 0;
      if (2 < g_switch_debug_level) {
        printk(
              "[SW][sw_vlan_del_port_dsvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\tpon_pri=%d\tpri_en=%d\tpri_use=%d\nuni_pri=%d\tvalid=%d\tvlan_en=%d\n"
              );
      }
      iVar1 = tm_broadcst_vltrans_table_delete_set(&local_38);
      if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
        printk("sw_vlan_del_port_dsvlantranslationentry return error!\nerror code=0x%x\n",iVar1);
      }
    }
    else {
      printk("[%s]%d input port error!\n",DAT_0001acac,0x17d);
      iVar1 = -1;
    }
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_show_port_dsvlantranslationentry @ 0001acb0 ============= */

int sw_vlan_show_port_dsvlantranslationentry(void)

{
  int iVar1;
  
  iVar1 = tm_broadcst_vltrans_table_print_get();
  if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
    printk("sw_vlan_show_port_dsvlantranslationentry return error!\nerror code=0x%x\n",iVar1);
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_set_port_defaultunivlantrans @ 0001acf0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_set_port_defaultunivlantrans(uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *param_1;
  uVar3 = param_1[1];
  if (2 < g_switch_debug_level) {
    printk("sw_vlan_set_port_defaultunivlantrans input:\tport=%d\taction=%d\n",uVar2,uVar3);
  }
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_dft_unkunicst_vltrans_set(zte_api_sw_mac_set_port_macfiltermode[uVar2],uVar3);
    if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
      printk("sw_vlan_set_port_defaultunivlantrans return error!\nerror code=0x%x\n",iVar1);
      return iVar1;
    }
    return iVar1;
  }
  printk("[%s]%d input port error!\n",DAT_0001ad9c,0x1d0);
  return -1;
}


/* ============= FUNCTION: sw_vlan_get_port_defaultunivlantrans @ 0001ada0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_get_port_defaultunivlantrans(uint *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 local_14 [2];
  
  uVar2 = *param_1;
  local_14[0] = 0;
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_dft_unkunicst_vltrans_get(zte_api_sw_mac_set_port_macfiltermode[uVar2],local_14)
    ;
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("sw_vlan_get_port_defaultunivlantrans output:\tport=%d\taction=%d\n",uVar2,
               local_14[0]);
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("sw_vlan_get_port_defaultunivlantrans return error!\nerror code=0x%x\n",iVar1);
    }
  }
  else {
    printk("[%s]%d input port error!\n",DAT_0001ae58,0x1f1);
    iVar1 = -1;
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_set_port_defaultbrdvlantrans @ 0001ae5c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_set_port_defaultbrdvlantrans(uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *param_1;
  uVar3 = param_1[1];
  if (2 < g_switch_debug_level) {
    printk("sw_vlan_set_port_defaultbrdvlantrans input:\tport=%d\taction=%d\n",uVar2,uVar3);
  }
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_dft_broadcst_vltrans_set(zte_api_sw_mac_set_port_macfiltermode[uVar2],uVar3);
    if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
      printk("sw_vlan_set_port_defaultbrdvlantrans return error!\nerror code=0x%x\n",iVar1);
      return iVar1;
    }
    return iVar1;
  }
  printk("[%s]%d input port error!\n",DAT_0001af08,0x216);
  return -1;
}


/* ============= FUNCTION: sw_vlan_get_port_defaultbrdvlantrans @ 0001af0c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_get_port_defaultbrdvlantrans(uint *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 local_14 [2];
  
  uVar2 = *param_1;
  local_14[0] = 0;
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_dft_broadcst_vltrans_get(zte_api_sw_mac_set_port_macfiltermode[uVar2],local_14);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("sw_vlan_get_port_defaultbrdvlantrans output:\tport=%d\taction=%d\n",uVar2,
               local_14[0]);
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("sw_vlan_get_port_defaultbrdvlantrans return error!\nerror code=0x%x\n",iVar1);
    }
  }
  else {
    printk("[%s]%d input port error!\n",DAT_0001afc4,0x236);
    iVar1 = -1;
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_add_port_dsmulvlantranslationentry @ 0001afc8 ============= */

undefined4 sw_vlan_add_port_dsmulvlantranslationentry(undefined4 *param_1)

{
  int iVar1;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  undefined4 local_4c;
  undefined1 local_48;
  undefined1 local_47;
  char local_46;
  byte local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 auStack_40 [8];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  undefined1 local_28;
  undefined1 local_27;
  byte local_26;
  undefined1 local_25;
  char local_24;
  undefined1 local_23;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_add_port_dsmulvlantranslationentry] input ERROR! ioctl_data_sweth=NULL\n"
            );
      return 0xffffffff;
    }
  }
  else {
    if ((2 < g_switch_debug_level) &&
       (printk("[SW][sw_vlan_add_port_dsmulvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\n"
               ,*param_1,param_1[1],param_1[2],param_1[3]), 2 < g_switch_debug_level)) {
      printk("[SW][sw_vlan_add_port_dsmulvlantranslationentry] input:\tvalid=%d\tvlan_en=%d\tuni_pri=%d\tpon_pri=%d\tpri_use=%d\tpri_en=%d\n"
             ,*(undefined1 *)(param_1 + 4),*(undefined1 *)((int)param_1 + 0x11),
             *(undefined1 *)((int)param_1 + 0x12),*(undefined1 *)((int)param_1 + 0x13),
             *(undefined1 *)(param_1 + 5),*(undefined1 *)((int)param_1 + 0x15));
    }
    __memzero(auStack_40,0x20);
    local_26 = *(byte *)((int)param_1 + 0x13);
    local_28 = 1;
    if (*(char *)((int)param_1 + 0x15) == '\0') {
      if (local_26 == 8) {
        local_27 = 0;
        local_25 = 0;
      }
      else if (local_26 < 8) {
        local_27 = 1;
        local_25 = 0;
      }
    }
    else if (local_26 == 8) {
      local_25 = 1;
      local_27 = 0;
    }
    else if (local_26 < 8) {
      local_27 = 1;
      local_25 = 1;
    }
    local_2c = param_1[3];
    local_38 = *param_1;
    local_34 = param_1[1];
    local_24 = *(char *)((int)param_1 + 0x12);
    local_30 = param_1[2];
    if (local_2c < 2) {
      local_30 = local_38;
    }
    if (local_26 == 8) {
      local_26 = 0;
    }
    local_23 = *(undefined1 *)((int)param_1 + 0x11);
    if (local_24 == '\b') {
      local_24 = '\0';
    }
    if (2 < g_switch_debug_level) {
      printk(
            "[SW][sw_vlan_add_port_dsmulvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\tpon_pri=%d\tpri_en=%d\tpri_use=%d\nuni_pri=%d\tvalid=%d\tvlan_en=%d\n"
            );
    }
    local_58 = local_30;
    local_54 = local_38;
    local_50 = local_2c;
    local_4c = local_34;
    local_48 = local_28;
    local_47 = local_23;
    local_46 = local_24;
    local_45 = local_26;
    local_44 = local_25;
    local_43 = local_27;
    iVar1 = tm_multicst_vltrans_table_add_set(&local_58);
    if (iVar1 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][tm_multicst_vltrans_table_add_set]  portlist3 FAIL!!!\n");
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_vlan_del_port_dsmulvlantranslationentry @ 0001b214 ============= */

undefined4 sw_vlan_del_port_dsmulvlantranslationentry(undefined4 *param_1)

{
  int iVar1;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  undefined4 local_4c;
  undefined1 local_48;
  undefined1 local_47;
  char local_46;
  byte local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 auStack_40 [8];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  undefined1 local_28;
  undefined1 local_27;
  byte local_26;
  undefined1 local_25;
  char local_24;
  undefined1 local_23;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_del_port_dsmulvlantranslationentry] input ERROR! ioctl_data_sweth=NULL\n"
            );
      return 0xffffffff;
    }
  }
  else {
    if ((2 < g_switch_debug_level) &&
       (printk("[SW][sw_vlan_del_port_dsmulvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\n"
               ,*param_1,param_1[1],param_1[2],param_1[3]), 2 < g_switch_debug_level)) {
      printk("[SW][sw_vlan_del_port_dsmulvlantranslationentry] input:\tvalid=%d\tvlan_en=%d\tuni_pri=%d\tpon_pri=%d\tpri_use=%d\tpri_en=%d\n"
             ,*(undefined1 *)(param_1 + 4),*(undefined1 *)((int)param_1 + 0x11),
             *(undefined1 *)((int)param_1 + 0x12),*(undefined1 *)((int)param_1 + 0x13),
             *(undefined1 *)(param_1 + 5),*(undefined1 *)((int)param_1 + 0x15));
    }
    __memzero(auStack_40,0x20);
    local_26 = *(byte *)((int)param_1 + 0x13);
    if (*(char *)((int)param_1 + 0x15) == '\0') {
      if (local_26 == 8) {
        local_27 = 0;
        local_25 = 0;
      }
      else if (local_26 < 8) {
        local_27 = 1;
        local_25 = 0;
      }
    }
    else if (local_26 == 8) {
      local_27 = 0;
      local_25 = 1;
    }
    else if (local_26 < 8) {
      local_27 = 1;
      local_25 = 1;
    }
    local_2c = param_1[3];
    local_38 = *param_1;
    local_34 = param_1[1];
    local_24 = *(char *)((int)param_1 + 0x12);
    local_30 = param_1[2];
    if (local_2c < 2) {
      local_30 = local_38;
    }
    local_28 = 0;
    if (local_26 == 8) {
      local_26 = 0;
    }
    local_23 = *(undefined1 *)((int)param_1 + 0x11);
    if (local_24 == '\b') {
      local_24 = '\0';
    }
    if (2 < g_switch_debug_level) {
      printk(
            "[SW][sw_vlan_del_port_dsmulvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\tpon_pri=%d\tpri_en=%d\tpri_use=%d\nuni_pri=%d\tvalid=%d\tvlan_en=%d\n"
            );
    }
    local_58 = local_30;
    local_54 = local_38;
    local_50 = local_2c;
    local_4c = local_34;
    local_48 = local_28;
    local_47 = local_23;
    local_46 = local_24;
    local_45 = local_26;
    local_44 = local_25;
    local_43 = local_27;
    iVar1 = tm_multicst_vltrans_table_delete_set(&local_58);
    if (iVar1 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][tm_multicst_vltrans_table_delete_set]  portlist3 FAIL!!!\n");
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_vlan_set_port_defaultmulvlantrans @ 0001b464 ============= */

int sw_vlan_set_port_defaultmulvlantrans(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = *param_1;
  uVar2 = param_1[1];
  if (2 < g_switch_debug_level) {
    printk("sw_vlan_set_port_defaultmulvlantrans input:\tport=%d\taction=%d\n",uVar3,uVar2);
  }
  iVar1 = tm_port_dft_multicst_vltrans_set(uVar3,uVar2 & 0xff);
  if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
    printk("sw_vlan_set_port_defaultmulvlantrans return error!\nerror code=0x%x\n",iVar1);
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_get_port_defaultmulvlantrans @ 0001b4d8 ============= */

int sw_vlan_get_port_defaultmulvlantrans(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *param_1;
  iVar1 = tm_port_dft_multicst_vltrans_get(uVar2);
  if (iVar1 == 0) {
    if (2 < g_switch_debug_level) {
      printk("sw_vlan_get_port_defaultmulvlantrans output:\tport=%d\taction=%d\n",uVar2,0);
    }
  }
  else if (g_switch_debug_level != 0) {
    printk("sw_vlan_get_port_defaultmulvlantrans return error!\nerror code=0x%x\n",iVar1);
  }
  return iVar1;
}


/* ============= FUNCTION: sw_vlan_set_port_transparent @ 0001b554 ============= */

undefined4
sw_vlan_set_port_transparent(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  code cVar2;
  int iVar3;
  
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_set_port_transparent] input ERROR: ioctl_data_sweth=NULL\n");
    }
  }
  else {
    cVar1 = (char)param_1[1];
    cVar2 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_vlan_set_port_transparent] input: port=%d enable=%d\n",cVar2,cVar1,
             (int)&g_sw_cap + *param_1,param_4);
    }
    iVar3 = tm_port_tls_set(cVar2,cVar1);
    if (iVar3 == 0) {
      if (cVar1 != '\x01') {
        tm_vlan_check_ena_set(cVar2,0,1);
        tm_vlan_check_ena_set(cVar2,1,1);
        return 0;
      }
      tm_vlan_check_ena_set(cVar2,0,0);
      tm_vlan_check_ena_set(cVar2,1,0);
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_set_port_transparent] return ERROR! error code=0x%x\n",iVar3);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_vlan_get_port_transparent @ 0001b658 ============= */

undefined4 sw_vlan_get_port_transparent(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_19 [5];
  
  local_19[0] = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_get_port_transparent] input ERROR: ioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_vlan_get_port_transparent] input: port=%d\n",cVar1);
  }
  iVar3 = tm_port_tls_get(cVar1,local_19);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    *(undefined1 *)(param_1 + 1) = local_19[0];
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[SW][sw_vlan_get_port_transparent] output: port=%d enable=%d\n",cVar1);
    }
  }
  else {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_vlan_get_port_transparent] return ERROR! error code=0x%x\n",iVar3);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ============= FUNCTION: sw_vlan_set_port_vlanfilter @ 0001b748 ============= */

undefined4 sw_vlan_set_port_vlanfilter(int *param_1)

{
  code cVar1;
  int iVar2;
  
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("sw_vlan_set_port_vlanfilter input ERROR!\nioctl_data_sweth=NULL\n");
    }
  }
  else {
    iVar2 = param_1[1];
    cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
    if (2 < g_switch_debug_level) {
      printk("sw_vlan_set_port_vlanfilter input:\nport=%d\nvlan_mask=%d\n",cVar1,iVar2);
    }
    iVar2 = tm_port_vlan_filter_set(cVar1,iVar2);
    if (iVar2 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("sw_vlan_set_port_vlanfilter return ERROR!\nerror code=0x%x\n");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_vlan_get_port_vlanfilter @ 0001b800 ============= */

undefined4 sw_vlan_get_port_vlanfilter(int *param_1)

{
  code cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("sw_vlan_get_port_vlanfilter input ERROR!\nioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("sw_vlan_get_port_vlanfilter input:\nport=%d\n",cVar1);
  }
  iVar2 = tm_port_vlan_filter_get(cVar1,&local_14);
  if (iVar2 == 0) {
    uVar3 = 0;
    if (2 < g_switch_debug_level) {
      printk("sw_vlan_get_port_vlanfilter output:\tport=%d\tvlan_mask=%d\n",cVar1,local_14);
    }
  }
  else {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("sw_vlan_get_port_vlanfilter return ERROR!\nerror code=0x%x\n",iVar2);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


/* ============= FUNCTION: sw_set_mflow_config @ 0001b8ec ============= */

undefined4 sw_set_mflow_config(void)

{
  return 0;
}


/* ============= FUNCTION: drv_get_igmp_portlistBCD @ 0001b8f4 ============= */

undefined4 drv_get_igmp_portlistBCD(int *param_1,int param_2,uint *param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint local_34;
  uint local_2c [2];
  
  local_2c[0] = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] input ERROR: sipnode=null\n");
    uVar3 = 0xffffffff;
  }
  else if (param_2 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] input ERROR: igmpentry=null\n");
    uVar3 = 0xffffffff;
  }
  else if (param_3 == (uint *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] input ERROR: portlist=null\n");
    uVar3 = 0xffffffff;
  }
  else {
    if ((((2 < g_switch_debug_level) &&
         (printk("[SW][drv_get_igmp_portlistBCD] input: portName=%s\n"), 2 < g_switch_debug_level))
        && (printk("[SW][drv_get_igmp_portlistBCD] input: dip=%3d.%3d.%3d.%3d\n",
                   *(undefined1 *)(param_2 + 0x17),*(undefined1 *)(param_2 + 0x16),
                   *(undefined1 *)(param_2 + 0x15),*(undefined1 *)(param_2 + 0x14)),
           2 < g_switch_debug_level)) &&
       ((printk("[SW][drv_get_igmp_portlistBCD] input: sip=%3d.%3d.%3d.%3d\n",
                *(undefined1 *)((int)param_1 + 3),*(undefined1 *)((int)param_1 + 2),
                *(undefined1 *)((int)param_1 + 1),(char)*param_1), 2 < g_switch_debug_level &&
        (printk("[SW][drv_get_igmp_portlistBCD] input: mode(1-in 2-EX)=%d\n",
                *(undefined4 *)(param_2 + 0x1c)), 2 < g_switch_debug_level)))) {
      printk("[SW][drv_get_igmp_portlistBCD] input: vlan=%d\n",*(undefined2 *)(param_2 + 0x10));
    }
    iVar5 = *(int *)(param_2 + 0x24);
    iVar7 = *param_1;
    if (iVar5 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][drv_get_igmp_portlistBCD] input: portInfo=null\n");
      }
      uVar4 = 0;
      local_34 = 0;
      uVar6 = uVar4;
    }
    else {
      uVar4 = 0;
      uVar6 = 0;
      local_34 = 0;
      do {
        iVar1 = get_sw_port_from_devname(iVar5,local_2c,1);
        if (iVar1 == -1) {
          if (g_switch_debug_level != 0) {
            printk("%s %d Error\n","drv_get_igmp_portlistBCD",0x78);
            return 0xffffffff;
          }
          return 0xffffffff;
        }
        local_2c[0] = 1 << (local_2c[0] & 0xff);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_get_igmp_portlistBCD] input: curPort=%d mode=%d\n",local_2c[0],
                 *(undefined4 *)(iVar5 + 0x14));
        }
        piVar2 = *(int **)(iVar5 + 0x10);
        if (piVar2 == (int *)0x0) {
          if (*(int *)(iVar5 + 0x14) == 2) {
            uVar4 = uVar4 | local_2c[0];
          }
        }
        else {
          do {
            if (*(int *)(param_2 + 0x1c) == 1) {
              if (*(int *)(iVar5 + 0x14) != 1) break;
              if (*piVar2 == iVar7) {
                local_34 = local_34 | local_2c[0];
                break;
              }
            }
            else {
              if ((*(int *)(param_2 + 0x1c) != 2) || (*(int *)(iVar5 + 0x14) != 2)) break;
              uVar4 = uVar4 | local_2c[0];
              if ((iVar7 != 0) &&
                 ((*piVar2 == iVar7 && (((DAT_0002c0e6 | DAT_0002c0e2) & local_2c[0]) == 0)))) {
                uVar6 = uVar6 | local_2c[0];
              }
            }
            piVar2 = (int *)piVar2[2];
          } while (piVar2 != (int *)0x0);
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        local_2c[0] = 0;
      } while (iVar5 != 0);
    }
    uVar3 = 0;
    param_3[1] = uVar6;
    *param_3 = local_34;
    param_3[2] = uVar4;
  }
  return uVar3;
}


/* ============= FUNCTION: drv_get_mld_portlistBCD @ 0001bc2c ============= */

undefined4 drv_get_mld_portlistBCD(undefined4 *param_1,int param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  void *__s1;
  uint local_54;
  uint local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined1 auStack_38 [20];
  
  local_4c = 0;
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar5 = 0xffffffff;
    printk("[SW][drv_get_mld_portlistBCD] input ERROR: sipnode=null\n");
  }
  else if (param_2 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar5 = 0xffffffff;
    printk("[SW][drv_get_mld_portlistBCD] input ERROR: mldEntry=null\n");
  }
  else if (param_3 == (uint *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar5 = 0xffffffff;
    printk("[SW][drv_get_mld_portlistBCD] input ERROR: portlist=null\n");
  }
  else {
    if ((((2 < g_switch_debug_level) &&
         (printk("[SW][drv_get_mld_portlistBCD] input: portname=%s\n"), 2 < g_switch_debug_level))
        && (printk("[SW][drv_get_mld_portlistBCD] input: dip=%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x\n"
                   ,*(undefined1 *)(param_2 + 0x12),*(undefined1 *)(param_2 + 0x13),
                   *(undefined1 *)(param_2 + 0x14),*(undefined1 *)(param_2 + 0x15),
                   *(undefined1 *)(param_2 + 0x16),*(undefined1 *)(param_2 + 0x17),
                   *(undefined1 *)(param_2 + 0x18),*(undefined1 *)(param_2 + 0x19),
                   *(undefined1 *)(param_2 + 0x1a),*(undefined1 *)(param_2 + 0x1b),
                   *(undefined1 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x1d),
                   *(undefined1 *)(param_2 + 0x1e),*(undefined1 *)(param_2 + 0x1f),
                   *(undefined1 *)(param_2 + 0x20),*(undefined1 *)(param_2 + 0x21)),
           2 < g_switch_debug_level)) &&
       ((printk("[SW][drv_get_mld_portlistBCD] input: sip=%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x\n"
                ,*(undefined1 *)param_1,*(undefined1 *)((int)param_1 + 1),
                *(undefined1 *)((int)param_1 + 2),*(undefined1 *)((int)param_1 + 3),
                *(undefined1 *)(param_1 + 1),*(undefined1 *)((int)param_1 + 5),
                *(undefined1 *)((int)param_1 + 6),*(undefined1 *)((int)param_1 + 7),
                *(undefined1 *)(param_1 + 2),*(undefined1 *)((int)param_1 + 9),
                *(undefined1 *)((int)param_1 + 10),*(undefined1 *)((int)param_1 + 0xb),
                *(undefined1 *)(param_1 + 3),*(undefined1 *)((int)param_1 + 0xd),
                *(undefined1 *)((int)param_1 + 0xe),*(undefined1 *)((int)param_1 + 0xf)),
        2 < g_switch_debug_level &&
        (printk("[SW][drv_get_mld_portlistBCD] input: mode(1-in 2-EX)=%d\n",
                *(undefined4 *)(param_2 + 0x24)), 2 < g_switch_debug_level)))) {
      printk("[SW][drv_get_mld_portlistBCD] input: vlan=%d\n",*(undefined2 *)(param_2 + 0x10));
    }
    __memzero(&local_48,0x10);
    __memzero(auStack_38,0x10);
    local_48 = *param_1;
    uStack_44 = param_1[1];
    uStack_40 = param_1[2];
    iVar6 = *(int *)(param_2 + 0x2c);
    uStack_3c = param_1[3];
    if (iVar6 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][drv_get_mld_portlistBCD] input: portInfo=null\n");
      }
      uVar4 = 0;
      local_54 = 0;
      uVar8 = uVar4;
    }
    else {
      uVar4 = 0;
      uVar8 = 0;
      local_54 = 0;
      do {
        iVar2 = get_sw_port_from_devname(iVar6,&local_4c,1);
        if (iVar2 == -1) {
          if (g_switch_debug_level != 0) {
            printk("%s %d Error\n",DAT_0001c064,0xe8);
            return 0xffffffff;
          }
          return 0xffffffff;
        }
        local_4c = 1 << (local_4c & 0xff);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_get_mld_portlistBCD] input: curPort=%d mode=%d\n",local_4c,
                 *(undefined4 *)(iVar6 + 0x14));
        }
        uVar1 = local_4c;
        __s1 = *(void **)(iVar6 + 0x10);
        if (__s1 == (void *)0x0) {
          if (*(int *)(iVar6 + 0x14) == 2) {
            uVar4 = uVar4 | local_4c;
          }
        }
        else {
          uVar7 = (DAT_0002c0e6 | DAT_0002c0e2) & local_4c;
          iVar2 = *(int *)(param_2 + 0x24);
          do {
            if (iVar2 == 1) {
              if (*(int *)(iVar6 + 0x14) != 1) break;
              iVar3 = memcmp(__s1,&local_48,0x10);
              if (iVar3 == 0) {
                local_54 = local_54 | uVar1;
                break;
              }
            }
            else {
              if ((iVar2 != 2) || (*(int *)(iVar6 + 0x14) != 2)) break;
              iVar3 = memcmp(auStack_38,&local_48,0x10);
              uVar4 = uVar4 | uVar1;
              if ((iVar3 != 0) &&
                 ((iVar3 = memcmp(__s1,&local_48,0x10), iVar3 == 0 && (uVar7 == 0)))) {
                uVar8 = uVar8 | uVar1;
              }
            }
            __s1 = *(void **)((int)__s1 + 0x14);
          } while (__s1 != (void *)0x0);
        }
        iVar6 = *(int *)(iVar6 + 0x1c);
        local_4c = 0;
      } while (iVar6 != 0);
    }
    uVar5 = 0;
    param_3[1] = uVar8;
    *param_3 = local_54;
    param_3[2] = uVar4;
  }
  return uVar5;
}


/* ============= FUNCTION: drv_add_igmp_addr_epon_sfu @ 0001c068 ============= */

undefined4 drv_add_igmp_addr_epon_sfu(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined2 uVar4;
  uint local_24;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  byte local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_24 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("[SW][drv_add_igmp_addr] input ERROR: igmpEntry=null\n");
  }
  else {
    iVar1 = get_sw_port_from_devname(param_1,&local_24,1);
    if (iVar1 == -1) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("%s %d Error\n",DAT_0001c234,0x133);
      uVar2 = 0xffffffff;
    }
    else {
      if (g_switch_debug_level < 3) {
        uVar3 = *(uint *)(param_1 + 0x14);
        uVar4 = *(undefined2 *)(param_1 + 0x10);
      }
      else {
        printk("[SW][drv_add_igmp_addr] portname = %s, dwPort = %d \n",param_1,local_24);
        uVar3 = *(uint *)(param_1 + 0x14);
        uVar4 = *(undefined2 *)(param_1 + 0x10);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_add_igmp_addr] IGMP_dip = %x, IGMP_vlan = %d \n",uVar3,uVar4);
        }
      }
      __memzero(&local_1e,6);
      local_1b = (byte)(uVar3 >> 0x10) & 0x7f;
      local_19 = (undefined1)uVar3;
      local_1e = 1;
      local_1d = 0;
      local_1c = 0x5e;
      local_1a = (undefined1)(uVar3 >> 8);
      if (((2 < g_switch_debug_level) &&
          (printk("[SW][drv_add_igmp_addr] p1 = %d\n",uVar3 & 0xff), 2 < g_switch_debug_level)) &&
         (printk("[SW][drv_add_igmp_addr] p2 = %d\n",uVar3 >> 8 & 0xff), 2 < g_switch_debug_level))
      {
        printk("[SW][drv_add_igmp_addr] p3 = %d\n",uVar3 >> 0x10 & 0xff);
      }
      iVar1 = zte_api_sw_mac_add_port_macaddress(local_24 & 0xff,&local_1e,uVar4,0);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = 0xffffffff;
        printk("zte_api_sw_mac_add_port_macaddress failed!\n");
      }
    }
  }
  return uVar2;
}


/* ============= FUNCTION: drv_del_igmp_addr_epon_sfu @ 0001c238 ============= */

undefined4 drv_del_igmp_addr_epon_sfu(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint local_24;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  byte local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_24 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar3 = 0xffffffff;
    printk("[SW][drv_add_igmp_addr] input ERROR: igmpEntry=null\n");
  }
  else {
    iVar2 = get_sw_port_from_devname(param_1,&local_24,1);
    if (iVar2 == -1) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("%s %d Error\n",DAT_0001c3dc,0x16f);
      uVar3 = 0xffffffff;
    }
    else {
      uVar4 = *(uint *)(param_1 + 0x14);
      uVar1 = *(undefined2 *)(param_1 + 0x10);
      if (2 < g_switch_debug_level) {
        printk("[SW][drv_add_igmp_addr] IGMP_dip = %x, IGMP_vlan = %d \n",uVar4,uVar1);
      }
      __memzero(&local_1e,6);
      local_1b = (byte)(uVar4 >> 0x10) & 0x7f;
      local_19 = (undefined1)uVar4;
      local_1e = 1;
      local_1d = 0;
      local_1c = 0x5e;
      local_1a = (undefined1)(uVar4 >> 8);
      if (((2 < g_switch_debug_level) &&
          (printk("[SW][change_portmask] IGMP_dip & 0xff = %d\n",uVar4 & 0xff),
          2 < g_switch_debug_level)) &&
         (printk("[SW][change_portmask] IGMP_dip>> 8 & 0xff = %d\n",uVar4 >> 8 & 0xff),
         2 < g_switch_debug_level)) {
        printk("[SW][change_portmask] IGMP_dip>> 16 & 0xff = %d\n",uVar4 >> 0x10 & 0xff);
      }
      iVar2 = zte_api_sw_mac_del_port_macaddress(local_24 & 0xff,&local_1e,uVar1,0);
      if (iVar2 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0xffffffff;
        printk("zte_api_sw_mac_del_port_macaddress failed!\n");
      }
    }
  }
  return uVar3;
}


/* ============= FUNCTION: drv_add_mld_addr_epon_sfu @ 0001c3e0 ============= */

undefined4 drv_add_mld_addr_epon_sfu(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  uint local_24;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_24 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("[SW][drv_add_mld_addr] input ERROR: mldEntry=null\n");
  }
  else {
    iVar1 = get_sw_port_from_devname(param_1,&local_24,1);
    if (iVar1 == -1) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("%s %d Error\n",DAT_0001c5b4,0x1a9);
      uVar2 = 0xffffffff;
    }
    else {
      if (g_switch_debug_level < 3) {
        uVar3 = *(undefined2 *)(param_1 + 0x10);
      }
      else {
        printk("[SW][drv_add_mld_addr] portName = %s, dwPort = %d \n",param_1,local_24);
        uVar3 = *(undefined2 *)(param_1 + 0x10);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_add_mld_addr] IGMP_vlan = %d\n",uVar3);
        }
      }
      __memzero(&local_1e,6);
      local_1c = *(undefined1 *)(param_1 + 0x1e);
      local_1b = *(undefined1 *)(param_1 + 0x1f);
      local_1a = *(undefined1 *)(param_1 + 0x20);
      local_19 = *(undefined1 *)(param_1 + 0x21);
      local_1e = 0x33;
      local_1d = 0x33;
      if ((((2 < g_switch_debug_level) &&
           (printk("[SW][drv_add_mld_addr] p1 = %d\n"), 2 < g_switch_debug_level)) &&
          (printk("[SW][drv_add_mld_addr] p2 = %d\n",*(undefined1 *)(param_1 + 0x1f)),
          2 < g_switch_debug_level)) &&
         (printk("[SW][drv_add_mld_addr] p3 = %d\n",*(undefined1 *)(param_1 + 0x20)),
         2 < g_switch_debug_level)) {
        printk("[SW][drv_add_mld_addr] p4 = %d\n",*(undefined1 *)(param_1 + 0x21));
      }
      iVar1 = zte_api_sw_mac_add_port_macaddress(local_24 & 0xff,&local_1e,uVar3,0);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = 0xffffffff;
        printk("zte_api_sw_mac_add_port_macaddress failed!\n");
      }
    }
  }
  return uVar2;
}


/* ============= FUNCTION: drv_del_mld_addr_epon_sfu @ 0001c5b8 ============= */

undefined4 drv_del_mld_addr_epon_sfu(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  uint local_24;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_24 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("[SW][drv_del_mld_addr] input ERROR: mldEntry=null\n");
  }
  else {
    iVar1 = get_sw_port_from_devname(param_1,&local_24,1);
    if (iVar1 == -1) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("%s %d Error\n",DAT_0001c78c,0x1e6);
      uVar2 = 0xffffffff;
    }
    else {
      if (g_switch_debug_level < 3) {
        uVar3 = *(undefined2 *)(param_1 + 0x10);
      }
      else {
        printk("[SW][drv_del_mld_addr] portName = %s, dwPort = %d \n",param_1,local_24);
        uVar3 = *(undefined2 *)(param_1 + 0x10);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_del_mld_addr] IGMP_vlan = %d\n",uVar3);
        }
      }
      __memzero(&local_1e,6);
      local_1c = *(undefined1 *)(param_1 + 0x1e);
      local_1b = *(undefined1 *)(param_1 + 0x1f);
      local_1a = *(undefined1 *)(param_1 + 0x20);
      local_19 = *(undefined1 *)(param_1 + 0x21);
      local_1e = 0x33;
      local_1d = 0x33;
      if ((((2 < g_switch_debug_level) &&
           (printk("[SW][drv_del_mld_addr] p1 = %d\n"), 2 < g_switch_debug_level)) &&
          (printk("[SW][drv_del_mld_addr] p2 = %d\n",*(undefined1 *)(param_1 + 0x1f)),
          2 < g_switch_debug_level)) &&
         (printk("[SW][drv_del_mld_addr] p3 = %d\n",*(undefined1 *)(param_1 + 0x20)),
         2 < g_switch_debug_level)) {
        printk("[SW][drv_del_mld_addr] p4 = %d\n",*(undefined1 *)(param_1 + 0x21));
      }
      iVar1 = zte_api_sw_mac_del_port_macaddress(local_24 & 0xff,&local_1e,uVar3,0);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = 0xffffffff;
        printk("zte_api_sw_mac_add_port_macaddress failed!\n");
      }
    }
  }
  return uVar2;
}


/* ============= FUNCTION: drv_add_igmp_addr_gpon_sfu @ 0001c790 ============= */

undefined4 drv_add_igmp_addr_gpon_sfu(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  uint local_64;
  int local_60;
  uint local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  int local_34;
  
  local_64 = 0;
  local_60 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_add_igmp_addr] input ERROR: igmpEntry=null\n");
    return 0xffffffff;
  }
  iVar4 = tm_mac_ramaddr_sel_get(&local_60);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_add_igmp_addr] FAIL: tm_mac_ramaddr_sel_get error\n");
    return 0xffffffff;
  }
  if (local_60 == 0 || local_60 == 3) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][tm_mac_ramaddr_sel_get] no ram for ipv4tabel FAIL\n");
    return 0xffffffff;
  }
  __memzero(&local_5c,0xc);
  __memzero(&local_50,0xc);
  __memzero(&local_44,0x1c);
  iVar4 = get_sw_port_from_devname(param_1,&local_64,1);
  if (iVar4 == -1) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("%s %d Error\n",DAT_0001cfa8,0x238);
    return 0xffffffff;
  }
  local_64 = 1 << (local_64 & 0xff);
  if (g_switch_debug_level < 3) {
    puVar6 = *(uint **)(param_1 + 0x20);
    if (puVar6 != (uint *)0x0) {
LAB_0001c8d0:
      do {
        iVar5 = drv_get_igmp_portlistBCD(puVar6,param_1,&local_50);
        iVar3 = local_48;
        iVar2 = local_4c;
        iVar4 = local_50;
        if (iVar5 != 0) {
          if (g_switch_debug_level == 0) {
            return 0xffffffff;
          }
          printk("[SW][drv_get_igmp_portlistBCD] Fail!\n");
          return 0xffffffff;
        }
        if (g_switch_debug_level < 3) {
          if (*(int *)(param_1 + 0x1c) == 1) {
LAB_0001c9b4:
            if (iVar4 != 0) {
              __memzero(&local_44,0x1c);
              local_3c = *(uint *)(param_1 + 0x14);
              local_38 = (uint)*(ushort *)(param_1 + 0x10);
              local_44 = 1;
              local_40 = *puVar6;
              local_43 = 1;
              local_34 = iVar4;
              local_42 = 0;
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001cdfc:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                         local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                           local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                       2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001cdfc;
                    }
                  }
                }
              }
              iVar4 = tm_ipv4table_add_set(&local_44);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set]  portlist1 FAIL!!!\n");
                return 0xffffffff;
              }
            }
          }
          else {
            if (*puVar6 == 0) goto LAB_0001c8bc;
LAB_0001c918:
            if (iVar2 != 0) {
              __memzero(&local_44,0x1c);
              local_3c = *(uint *)(param_1 + 0x14);
              local_38 = (uint)*(ushort *)(param_1 + 0x10);
              local_44 = 1;
              local_40 = *puVar6;
              local_42 = 1;
              local_43 = 1;
              local_34 = iVar2;
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001cf88:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                         local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                           local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                       2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001cf88;
                    }
                  }
                }
              }
              iVar4 = tm_ipv4table_add_set(&local_44);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set] portlist2 FAIL!!!\n");
                return 0xffffffff;
              }
            }
            if (iVar3 != 0) {
              __memzero(&local_44,0x1c);
              local_3c = *(uint *)(param_1 + 0x14);
              uVar1 = *(ushort *)(param_1 + 0x10);
              local_40 = 0;
              goto joined_r0x0001ca74;
            }
          }
        }
        else {
          printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n"
                 ,local_50,local_4c,local_48);
          if (*(int *)(param_1 + 0x1c) == 1) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_add_igmp_addr] IGMPv3 mode=IN\n");
            }
            goto LAB_0001c9b4;
          }
          if (*puVar6 != 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_add_igmp_addr] IGMPv3 mode=EX\n");
            }
            goto LAB_0001c918;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][drv_add_igmp_addr] IGMPv2 mode=EX\n");
          }
LAB_0001c8bc:
          if (iVar3 == 0) goto LAB_0001c8c4;
          __memzero(&local_44,0x1c);
          local_3c = *(uint *)(param_1 + 0x14);
          uVar1 = *(ushort *)(param_1 + 0x10);
          local_40 = *puVar6;
joined_r0x0001ca74:
          local_43 = 1;
          local_42 = 1;
          local_44 = 1;
          local_38 = (uint)uVar1;
          local_34 = iVar3;
          if (2 < g_switch_debug_level) {
            local_42 = 1;
            local_43 = 1;
            local_44 = 1;
            printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
            if (g_switch_debug_level < 3) {
LAB_0001cb14:
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
              }
            }
            else {
              printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                     local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                       local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                if ((2 < g_switch_debug_level) &&
                   (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                   2 < g_switch_debug_level)) {
                  printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                  goto LAB_0001cb14;
                }
              }
            }
          }
          iVar4 = tm_ipv4table_add_set(&local_44);
          if (iVar4 != 0) goto LAB_0001c97c;
        }
LAB_0001c8c4:
        puVar6 = (uint *)puVar6[2];
        if (puVar6 == (uint *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  else {
    printk("[SW][drv_add_igmp_addr] input: dwPortListA=%d\n");
    puVar6 = *(uint **)(param_1 + 0x20);
    if (puVar6 != (uint *)0x0) goto LAB_0001c8d0;
    if (2 < g_switch_debug_level) {
      printk("[SW][drv_add_igmp_addr] IGMPv2 mode=EX\n");
    }
  }
  local_5c = 0;
  local_54 = 0;
  local_58 = 0;
  iVar4 = drv_get_igmp_portlistBCD(&local_5c,param_1,&local_50);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] Fail!!!\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
           local_50,local_4c,local_48);
  }
  if (local_48 == 0) {
    return 0;
  }
  __memzero(&local_44,0x1c);
  local_3c = *(uint *)(param_1 + 0x14);
  local_38 = (uint)*(ushort *)(param_1 + 0x10);
  local_34 = local_48;
  local_40 = local_5c;
  local_44 = 1;
  local_42 = 1;
  local_43 = 1;
  if (g_switch_debug_level < 3) goto LAB_0001ccd4;
  printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,local_3c._2_1_,
           local_3c._1_1_,local_3c & 0xff);
    if (g_switch_debug_level < 3) goto LAB_0001ccd4;
    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,local_40._2_1_,
           local_40._1_1_,local_40 & 0xff);
    if ((g_switch_debug_level < 3) ||
       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
       g_switch_debug_level < 3)) goto LAB_0001ccd4;
    printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
  }
LAB_0001ccd4:
  iVar4 = tm_ipv4table_add_set(&local_44);
  if (iVar4 == 0) {
    return 0;
  }
LAB_0001c97c:
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][tm_ipv4table_add_set] portlist3 FAIL!!!\n");
  return 0xffffffff;
}


/* ============= FUNCTION: drv_del_igmp_addr_gpon_sfu @ 0001cfac ============= */

/* WARNING: Type propagation algorithm not settling */

undefined4 drv_del_igmp_addr_gpon_sfu(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint local_64;
  int local_60;
  uint local_5c [4];
  int local_4c;
  int local_48;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  int local_34;
  
  local_64 = 0;
  local_60 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_igmp_addr] input ERROR: igmpEntry=null\n");
    return 0xffffffff;
  }
  iVar3 = tm_mac_ramaddr_sel_get(&local_60);
  if (iVar3 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_igmp_addr] FAIL: tm_mac_ramaddr_sel_get error\n");
    return 0xffffffff;
  }
  if (local_60 == 0 || local_60 == 3) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_igmp_addr] Fail: no ram for ipv4tabel\n");
    return 0xffffffff;
  }
  __memzero(local_5c,0xc);
  __memzero(local_5c + 3,0xc);
  __memzero(&local_44,0x1c);
  iVar3 = get_sw_port_from_devname(param_1,&local_64,1);
  if (iVar3 == -1) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("%s %d Error\n",DAT_0001db44,0x33c);
    return 0xffffffff;
  }
  local_64 = 1 << (local_64 & 0xff);
  if (g_switch_debug_level < 3) {
    puVar5 = *(uint **)(param_1 + 0x20);
    if (puVar5 != (uint *)0x0) {
LAB_0001d0d4:
      while (iVar4 = drv_get_igmp_portlistBCD(puVar5,param_1,local_5c + 3), iVar2 = local_48,
            iVar3 = local_4c, uVar1 = local_5c[3], iVar4 == 0) {
        if (g_switch_debug_level < 3) {
          if (*(int *)(param_1 + 0x1c) == 1) {
LAB_0001d284:
            __memzero(&local_44,0x1c);
            local_3c = *(uint *)(param_1 + 0x14);
            local_38 = (uint)*(ushort *)(param_1 + 0x10);
            local_44 = 1;
            local_40 = *puVar5;
            local_42 = 0;
            local_43 = 1;
            local_34 = uVar1;
            if (uVar1 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001d9ac:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: port_mask 1=%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_
                         ,local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",
                           local_40._3_1_,local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42)
                       , 2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001d9ac;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_delete_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_delete_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001d834:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask 1=%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                         local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                           local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                       2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001d834;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_add_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
          else {
            if (*puVar5 == 0) goto LAB_0001d11c;
LAB_0001d1e0:
            __memzero(&local_44,0x1c);
            local_3c = *(uint *)(param_1 + 0x14);
            local_38 = (uint)*(ushort *)(param_1 + 0x10);
            local_44 = 1;
            local_40 = *puVar5;
            local_42 = 1;
            local_43 = 1;
            local_34 = iVar3;
            if (iVar3 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001d778:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: port_mask 2=%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_
                         ,local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",
                           local_40._3_1_,local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42)
                       , 2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001d778;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_delete_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_delete_set portlist2] FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001da68:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask 2=%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                         local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                           local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                       2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001da68;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_add_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set] portlist2 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
        }
        else {
          printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n"
                 ,local_5c[3],local_4c,local_48);
          if (*(int *)(param_1 + 0x1c) == 1) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_del_igmp_addr] IGMPv3 mode=IN\n");
            }
            goto LAB_0001d284;
          }
          if (*puVar5 != 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_del_igmp_addr] IGMPv3 mode=EX\n");
            }
            goto LAB_0001d1e0;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][drv_del_igmp_addr] IGMPv2 mode=EX\n");
          }
LAB_0001d11c:
          __memzero(&local_44,0x1c);
          local_3c = *(uint *)(param_1 + 0x14);
          local_38 = (uint)*(ushort *)(param_1 + 0x10);
          local_44 = 1;
          local_40 = *puVar5;
          local_42 = 1;
          local_43 = 1;
          local_34 = iVar2;
          if (iVar2 == 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
              if (g_switch_debug_level < 3) {
LAB_0001d8f0:
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv4table_delete_set] input: port_mask 3=%d\n",local_34);
                }
              }
              else {
                printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                       local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_
                         ,local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                  if ((2 < g_switch_debug_level) &&
                     (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                     2 < g_switch_debug_level)) {
                    printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
                    goto LAB_0001d8f0;
                  }
                }
              }
            }
            iVar3 = tm_ipv4table_delete_set(&local_44);
            if (iVar3 != 0) {
              if (g_switch_debug_level == 0) {
                return 0xffffffff;
              }
              printk("[SW][tm_ipv4table_delete_set] portlist3 FAIL!\n");
              return 0xffffffff;
            }
            goto LAB_0001d25c;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
            if (g_switch_debug_level < 3) {
LAB_0001d6bc:
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: port_mask 3=%d\n",local_34);
              }
            }
            else {
              printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                     local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                       local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                if ((2 < g_switch_debug_level) &&
                   (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                   2 < g_switch_debug_level)) {
                  printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                  goto LAB_0001d6bc;
                }
              }
            }
          }
          iVar3 = tm_ipv4table_add_set(&local_44);
          if (iVar3 != 0) {
            if (g_switch_debug_level == 0) {
              return 0xffffffff;
            }
            printk("[SW][tm_ipv4table_add_set] portlist3 FAIL!\n");
            return 0xffffffff;
          }
        }
LAB_0001d25c:
        puVar5 = (uint *)puVar5[2];
        if (puVar5 == (uint *)0x0) {
          return 0;
        }
      }
      goto LAB_0001d4d0;
    }
  }
  else {
    printk("[SW][drv_del_igmp_addr] input: dwPortListA=%d\n");
    puVar5 = *(uint **)(param_1 + 0x20);
    if (puVar5 != (uint *)0x0) goto LAB_0001d0d4;
    if (2 < g_switch_debug_level) {
      printk("[SW][drv_del_igmp_addr] IGMPv2 mode=EX\n");
    }
  }
  local_5c[0] = 0;
  local_5c[2] = 0;
  local_5c[1] = 0;
  iVar3 = drv_get_igmp_portlistBCD(local_5c,param_1,local_5c + 3);
  if (iVar3 != 0) {
LAB_0001d4d0:
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] FAIL!\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
           local_5c[3],local_4c,local_48);
  }
  __memzero(&local_44,0x1c);
  local_3c = *(uint *)(param_1 + 0x14);
  local_38 = (uint)*(ushort *)(param_1 + 0x10);
  local_34 = local_48;
  local_40 = local_5c[0];
  local_44 = 1;
  local_42 = 1;
  local_43 = 1;
  if (local_48 == 0) {
    if (g_switch_debug_level < 3) goto LAB_0001d4f4;
    printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
             local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
      if (g_switch_debug_level < 3) goto LAB_0001d4f4;
      printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
             local_40._2_1_,local_40._1_1_,local_40 & 0xff);
      if ((g_switch_debug_level < 3) ||
         (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42),
         g_switch_debug_level < 3)) goto LAB_0001d4f4;
      printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
    }
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv4table_delete_set] input: port_mask 3=%d\n",local_34);
    }
LAB_0001d4f4:
    iVar3 = tm_ipv4table_delete_set(&local_44);
    if (iVar3 == 0) {
      return 0;
    }
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][tm_ipv4table_delete_set] portlist3 FAIL\n");
    return 0xffffffff;
  }
  if (g_switch_debug_level < 3) goto LAB_0001d4a0;
  printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,local_3c._2_1_,
           local_3c._1_1_,local_3c & 0xff);
    if (g_switch_debug_level < 3) goto LAB_0001d4a0;
    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,local_40._2_1_,
           local_40._1_1_,local_40 & 0xff);
    if ((g_switch_debug_level < 3) ||
       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
       g_switch_debug_level < 3)) goto LAB_0001d4a0;
    printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: port_mask 3=%d\n",local_34);
  }
LAB_0001d4a0:
  iVar3 = tm_ipv4table_add_set(&local_44);
  if (iVar3 == 0) {
    return 0;
  }
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][tm_ipv4table_add_set] portlist3 FAIL\n");
  return 0xffffffff;
}


/* ============= FUNCTION: drv_add_mld_addr_gpon_sfu @ 0001db48 ============= */

undefined4 drv_add_mld_addr_gpon_sfu(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  int *piVar7;
  undefined2 *puVar8;
  int *piVar9;
  undefined2 *puVar10;
  void *__s1;
  uint local_98;
  uint local_94;
  int local_90;
  int local_8c;
  int local_88;
  undefined1 auStack_84 [16];
  undefined1 auStack_74 [16];
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  uint local_58;
  undefined4 local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  int local_44;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 auStack_30 [6];
  
  local_98 = 0;
  local_94 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_add_mld_addr] input ERROR: mldEntry=null\n");
    return 0xffffffff;
  }
  iVar4 = tm_mac_ramaddr_sel_get(&local_94);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_add_mld_addr] FAIL: tm_mac_ramaddr_sel_get error\n");
    return 0xffffffff;
  }
  if ((local_94 & 0xfffffffd) == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_add_mld_addr] Fail: no ram for ipv6tabel\n");
    return 0xffffffff;
  }
  __memzero(auStack_74,0x18);
  __memzero(&local_90,0xc);
  __memzero(&local_5c,0x34);
  __memzero(auStack_84,0x10);
  iVar4 = get_sw_port_from_devname(param_1,&local_98,1);
  if (iVar4 == -1) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("%s %d Error\n",DAT_0001e538,0x46c);
    return 0xffffffff;
  }
  local_98 = 1 << (local_98 & 0xff);
  if (g_switch_debug_level < 3) {
    __s1 = *(void **)(param_1 + 0x28);
    if (__s1 != (void *)0x0) {
LAB_0001dc94:
      do {
        iVar5 = drv_get_mld_portlistBCD(__s1,param_1,&local_90);
        iVar3 = local_88;
        iVar2 = local_8c;
        iVar4 = local_90;
        if (iVar5 != 0) {
          if (g_switch_debug_level == 0) {
            return 0xffffffff;
          }
          printk("[SW][drv_get_mld_portlistBCD] Fail!\n");
          return 0xffffffff;
        }
        if (g_switch_debug_level < 3) {
          if (*(int *)(param_1 + 0x24) == 1) {
LAB_0001ddac:
            if (iVar4 != 0) {
              __memzero(&local_5c,0x34);
              puVar6 = (undefined1 *)(param_1 + 0x22);
              local_5c = 1;
              piVar7 = &local_54;
              do {
                puVar6 = puVar6 + -1;
                piVar9 = (int *)((int)piVar7 + 1);
                *(undefined1 *)piVar7 = *puVar6;
                piVar7 = piVar9;
              } while (piVar9 != &local_44);
              puVar6 = (undefined1 *)((int)__s1 + 0x10);
              puVar8 = &local_40;
              do {
                puVar6 = puVar6 + -1;
                puVar10 = (undefined2 *)((int)puVar8 + 1);
                *(undefined1 *)puVar8 = *puVar6;
                puVar8 = puVar10;
              } while (puVar10 != auStack_30);
              local_58 = (uint)*(ushort *)(param_1 + 0x10);
              local_5a = 0;
              local_5b = 1;
              local_44 = iVar4;
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001de2c;
                  printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001de2c:
              iVar4 = tm_ipv6table_add_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_add_set]  portlist1 FAIL!!!\n");
                return 0xffffffff;
              }
            }
          }
          else {
            iVar4 = memcmp(__s1,auStack_84,0x10);
            if (iVar4 == 0) goto LAB_0001dc80;
LAB_0001dce8:
            if (iVar2 != 0) {
              __memzero(&local_5c,0x34);
              puVar6 = (undefined1 *)(param_1 + 0x22);
              local_5c = 1;
              piVar7 = &local_54;
              do {
                puVar6 = puVar6 + -1;
                piVar9 = (int *)((int)piVar7 + 1);
                *(undefined1 *)piVar7 = *puVar6;
                piVar7 = piVar9;
              } while (piVar9 != &local_44);
              puVar6 = (undefined1 *)((int)__s1 + 0x10);
              puVar8 = &local_40;
              do {
                puVar6 = puVar6 + -1;
                puVar10 = (undefined2 *)((int)puVar8 + 1);
                *(undefined1 *)puVar8 = *puVar6;
                puVar8 = puVar10;
              } while (puVar10 != auStack_30);
              local_58 = (uint)*(ushort *)(param_1 + 0x10);
              local_44 = iVar2;
              local_5a = 1;
              local_5b = 1;
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001df14;
                  printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001df14:
              iVar4 = tm_ipv6table_add_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_add_set] portlist2 FAIL!!!\n");
                return 0xffffffff;
              }
            }
            if (iVar3 != 0) {
              __memzero(&local_5c,0x34);
              puVar6 = (undefined1 *)(param_1 + 0x22);
              piVar7 = &local_54;
              do {
                puVar6 = puVar6 + -1;
                piVar9 = (int *)((int)piVar7 + 1);
                *(undefined1 *)piVar7 = *puVar6;
                piVar7 = piVar9;
              } while (piVar9 != &local_44);
              puVar8 = &local_40;
              do {
                puVar10 = (undefined2 *)((int)puVar8 + 1);
                *(undefined1 *)puVar8 = 0;
                puVar8 = puVar10;
              } while (puVar10 != auStack_30);
              goto LAB_0001dd3c;
            }
          }
        }
        else {
          printk("[SW][drv_get_mld_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
                 local_90,local_8c,local_88);
          uVar1 = g_switch_debug_level;
          if (*(int *)(param_1 + 0x24) == 1) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_add_mld_addr] MLDv2 mode=IN\n");
            }
            goto LAB_0001ddac;
          }
          iVar4 = memcmp(__s1,auStack_84,0x10);
          if (iVar4 != 0) {
            if (2 < uVar1) {
              printk("[SW][drv_add_mld_addr] MLDv2 mode=EX\n");
            }
            goto LAB_0001dce8;
          }
          if (2 < uVar1) {
            printk("[SW][drv_add_mld_addr] MLDv1 mode=EX\n");
          }
LAB_0001dc80:
          if (iVar3 == 0) goto LAB_0001dc88;
          __memzero(&local_5c,0x34);
          puVar6 = (undefined1 *)(param_1 + 0x22);
          piVar7 = &local_54;
          do {
            puVar6 = puVar6 + -1;
            piVar9 = (int *)((int)piVar7 + 1);
            *(undefined1 *)piVar7 = *puVar6;
            piVar7 = piVar9;
          } while (piVar9 != &local_44);
          puVar8 = &local_40;
          do {
            puVar10 = (undefined2 *)((int)puVar8 + 1);
            *(undefined1 *)puVar8 = 0;
            puVar8 = puVar10;
          } while (puVar10 != auStack_30);
LAB_0001dd3c:
          local_5c = 1;
          local_58 = (uint)*(ushort *)(param_1 + 0x10);
          local_44 = iVar3;
          local_5a = 1;
          local_5b = 1;
          if (2 < g_switch_debug_level) {
            printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                     local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                     (undefined2)local_54);
              if (((g_switch_debug_level < 3) ||
                  (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                          local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
                  g_switch_debug_level < 3)) ||
                 (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                 g_switch_debug_level < 3)) goto LAB_0001dd60;
              printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
            }
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
            }
          }
LAB_0001dd60:
          iVar4 = tm_ipv6table_add_set(&local_5c);
          if (iVar4 != 0) goto LAB_0001dd70;
        }
LAB_0001dc88:
        __s1 = *(void **)((int)__s1 + 0x14);
        if (__s1 == (void *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  else {
    printk("[SW][drv_add_mld_addr] input: dwPortListA=%d\n");
    __s1 = *(void **)(param_1 + 0x28);
    if (__s1 != (void *)0x0) goto LAB_0001dc94;
    if (2 < g_switch_debug_level) {
      printk("[SW][drv_add_mld_addr] MLDv1 mode=EX\n");
    }
  }
  local_60 = 0;
  local_64 = 0;
  iVar4 = drv_get_mld_portlistBCD(auStack_74,param_1,&local_90);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_mld_portlistBCD] Fail!!!\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][drv_get_mld_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
           local_90,local_8c,local_88);
  }
  if (local_88 == 0) {
    return 0;
  }
  __memzero(&local_5c,0x34);
  puVar6 = (undefined1 *)(param_1 + 0x22);
  local_5c = 1;
  piVar7 = &local_54;
  do {
    puVar6 = puVar6 + -1;
    piVar9 = (int *)((int)piVar7 + 1);
    *(undefined1 *)piVar7 = *puVar6;
    piVar7 = piVar9;
  } while (piVar9 != &local_44);
  puVar8 = &local_40;
  do {
    puVar10 = (undefined2 *)((int)puVar8 + 1);
    *(undefined1 *)puVar8 = 0;
    puVar8 = puVar10;
  } while (puVar10 != auStack_30);
  local_58 = (uint)*(ushort *)(param_1 + 0x10);
  local_44 = local_88;
  local_5a = 1;
  local_5b = 1;
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_46,
             local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,(undefined2)local_54);
      if (((g_switch_debug_level < 3) ||
          (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_32
                  ,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
          g_switch_debug_level < 3)) ||
         (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
         g_switch_debug_level < 3)) goto LAB_0001e094;
      printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
    }
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
    }
  }
LAB_0001e094:
  iVar4 = tm_ipv6table_add_set(&local_5c);
  if (iVar4 == 0) {
    return 0;
  }
LAB_0001dd70:
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][tm_ipv6table_add_set] portlist3 FAIL!!!\n");
  return 0xffffffff;
}


/* ============= FUNCTION: drv_del_mld_addr_gpon_sfu @ 0001e53c ============= */

undefined4 drv_del_mld_addr_gpon_sfu(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  int *piVar7;
  undefined2 *puVar8;
  int *piVar9;
  undefined2 *puVar10;
  void *__s1;
  uint local_98;
  uint local_94;
  int local_90;
  int local_8c;
  int local_88;
  undefined1 auStack_84 [16];
  undefined1 auStack_74 [16];
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  uint local_58;
  undefined4 local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  int local_44;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 auStack_30 [6];
  
  local_98 = 0;
  local_94 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_mld_addr] input ERROR: mldEntry=null\n");
    return 0xffffffff;
  }
  iVar4 = tm_mac_ramaddr_sel_get(&local_94);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_mld_addr] FAIL: tm_mac_ramaddr_sel_get error\n");
    return 0xffffffff;
  }
  if ((local_94 & 0xfffffffd) == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_mld_addr] Fail: no ram for ipv6tabel\n");
    return 0xffffffff;
  }
  __memzero(auStack_74,0x18);
  __memzero(&local_90,0xc);
  __memzero(&local_5c,0x34);
  __memzero(auStack_84,0x10);
  iVar4 = get_sw_port_from_devname(param_1,&local_98,1);
  if (iVar4 == -1) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("%s %d Error\n",DAT_0001f3b8,0x5b4);
    return 0xffffffff;
  }
  local_98 = 1 << (local_98 & 0xff);
  if (g_switch_debug_level < 3) {
    __s1 = *(void **)(param_1 + 0x28);
    if (__s1 != (void *)0x0) {
LAB_0001e66c:
      while (iVar5 = drv_get_mld_portlistBCD(__s1,param_1,&local_90), iVar3 = local_88,
            iVar2 = local_8c, iVar4 = local_90, iVar5 == 0) {
        if (g_switch_debug_level < 3) {
          if (*(int *)(param_1 + 0x24) == 1) {
LAB_0001e888:
            __memzero(&local_5c,0x34);
            puVar6 = (undefined1 *)(param_1 + 0x22);
            local_5c = 1;
            piVar7 = &local_54;
            do {
              puVar6 = puVar6 + -1;
              piVar9 = (int *)((int)piVar7 + 1);
              *(undefined1 *)piVar7 = *puVar6;
              piVar7 = piVar9;
            } while (piVar9 != &local_44);
            puVar6 = (undefined1 *)((int)__s1 + 0x10);
            puVar8 = &local_40;
            do {
              puVar6 = puVar6 + -1;
              puVar10 = (undefined2 *)((int)puVar8 + 1);
              *(undefined1 *)puVar8 = *puVar6;
              puVar8 = puVar10;
            } while (puVar10 != auStack_30);
            local_58 = (uint)*(ushort *)(param_1 + 0x10);
            local_5b = 1;
            local_44 = iVar4;
            local_5a = 0;
            if (iVar4 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001e9dc;
                  printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001e9dc:
              iVar4 = tm_ipv6table_delete_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_delete_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001e904;
                  printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001e904:
              iVar4 = tm_ipv6table_add_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_add_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
          else {
            iVar4 = memcmp(__s1,auStack_84,0x10);
            if (iVar4 != 0) goto LAB_0001e7b8;
LAB_0001e6c0:
            __memzero(&local_5c,0x34);
            puVar6 = (undefined1 *)(param_1 + 0x22);
            local_5c = 1;
            piVar7 = &local_54;
            do {
              puVar6 = puVar6 + -1;
              piVar9 = (int *)((int)piVar7 + 1);
              *(undefined1 *)piVar7 = *puVar6;
              piVar7 = piVar9;
            } while (piVar9 != &local_44);
            puVar8 = &local_40;
            do {
              puVar10 = (undefined2 *)((int)puVar8 + 1);
              *(undefined1 *)puVar8 = 0;
              puVar8 = puVar10;
            } while (puVar10 != auStack_30);
            local_58 = (uint)*(ushort *)(param_1 + 0x10);
            local_44 = iVar3;
            local_5a = 1;
            local_5b = 1;
            if (iVar3 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001e9a4;
                  printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001e9a4:
              iVar4 = tm_ipv6table_delete_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_delete_set] portlist3 FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001e734;
                  printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001e734:
              iVar4 = tm_ipv6table_add_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_add_set] portlist3 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
        }
        else {
          printk("[SW][drv_get_mld_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
                 local_90,local_8c,local_88);
          uVar1 = g_switch_debug_level;
          if (*(int *)(param_1 + 0x24) == 1) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_del_mld_addr] MLDv2 mode=IN\n");
            }
            goto LAB_0001e888;
          }
          iVar4 = memcmp(__s1,auStack_84,0x10);
          if (iVar4 == 0) {
            if (2 < uVar1) {
              printk("[SW][drv_del_mld_addr] MLDv1 mode=EX\n");
            }
            goto LAB_0001e6c0;
          }
          if (2 < uVar1) {
            printk("[SW][drv_del_mld_addr] MLDv2 mode=EX\n");
          }
LAB_0001e7b8:
          __memzero(&local_5c,0x34);
          puVar6 = (undefined1 *)(param_1 + 0x22);
          local_5c = 1;
          piVar7 = &local_54;
          do {
            puVar6 = puVar6 + -1;
            piVar9 = (int *)((int)piVar7 + 1);
            *(undefined1 *)piVar7 = *puVar6;
            piVar7 = piVar9;
          } while (piVar9 != &local_44);
          puVar6 = (undefined1 *)((int)__s1 + 0x10);
          puVar8 = &local_40;
          do {
            puVar6 = puVar6 + -1;
            puVar10 = (undefined2 *)((int)puVar8 + 1);
            *(undefined1 *)puVar8 = *puVar6;
            puVar8 = puVar10;
          } while (puVar10 != auStack_30);
          local_58 = (uint)*(ushort *)(param_1 + 0x10);
          local_44 = iVar2;
          local_5a = 1;
          local_5b = 1;
          if (iVar2 == 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                       local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                       (undefined2)local_54);
                if (((g_switch_debug_level < 3) ||
                    (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                            ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40
                           ), g_switch_debug_level < 3)) ||
                   (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                   g_switch_debug_level < 3)) goto LAB_0001e96c;
                printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
              }
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
              }
            }
LAB_0001e96c:
            iVar4 = tm_ipv6table_delete_set(&local_5c);
            if (iVar4 != 0) {
              if (g_switch_debug_level == 0) {
                return 0xffffffff;
              }
              printk("[SW][tm_ipv6table_delete_set portlist2] FAIL!\n");
              return 0xffffffff;
            }
            goto LAB_0001e860;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                     local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                     (undefined2)local_54);
              if (((g_switch_debug_level < 3) ||
                  (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                          local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
                  g_switch_debug_level < 3)) ||
                 (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                 g_switch_debug_level < 3)) goto LAB_0001e830;
              printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
            }
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
            }
          }
LAB_0001e830:
          iVar4 = tm_ipv6table_add_set(&local_5c);
          if (iVar4 != 0) {
            if (g_switch_debug_level == 0) {
              return 0xffffffff;
            }
            printk("[SW][tm_ipv6table_add_set] portlist2 FAIL!\n");
            return 0xffffffff;
          }
        }
LAB_0001e860:
        __s1 = *(void **)((int)__s1 + 0x14);
        if (__s1 == (void *)0x0) {
          return 0;
        }
      }
      goto LAB_0001eb24;
    }
  }
  else {
    printk("[SW][drv_del_mld_addr] input: dwPortListA=%d\n");
    __s1 = *(void **)(param_1 + 0x28);
    if (__s1 != (void *)0x0) goto LAB_0001e66c;
    if (2 < g_switch_debug_level) {
      printk("[SW][drv_del_mld_addr] MLDv1 mode=EX\n");
    }
  }
  local_60 = 0;
  local_64 = 0;
  iVar4 = drv_get_mld_portlistBCD(auStack_74,param_1,&local_90);
  if (iVar4 != 0) {
LAB_0001eb24:
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_mld_portlistBCD] FAIL!\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][drv_get_mld_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
           local_90,local_8c,local_88);
  }
  __memzero(&local_5c,0x34);
  puVar6 = (undefined1 *)(param_1 + 0x22);
  local_5c = 1;
  piVar7 = &local_54;
  do {
    puVar6 = puVar6 + -1;
    piVar9 = (int *)((int)piVar7 + 1);
    *(undefined1 *)piVar7 = *puVar6;
    piVar7 = piVar9;
  } while (piVar9 != &local_44);
  puVar8 = &local_40;
  do {
    puVar10 = (undefined2 *)((int)puVar8 + 1);
    *(undefined1 *)puVar8 = 0;
    puVar8 = puVar10;
  } while (puVar10 != auStack_30);
  local_58 = (uint)*(ushort *)(param_1 + 0x10);
  local_44 = local_88;
  local_5a = 1;
  local_5b = 1;
  if (local_88 == 0) {
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
      if (2 < g_switch_debug_level) {
        printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_46,
               local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,(undefined2)local_54);
        if (((g_switch_debug_level < 3) ||
            (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                    local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
            g_switch_debug_level < 3)) ||
           (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
           g_switch_debug_level < 3)) goto LAB_0001eb48;
        printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
      }
      if (2 < g_switch_debug_level) {
        printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
      }
    }
LAB_0001eb48:
    iVar4 = tm_ipv6table_delete_set(&local_5c);
    if (iVar4 == 0) {
      return 0;
    }
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][tm_ipv6table_delete_set] portlist3 FAIL\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_46,
             local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,(undefined2)local_54);
      if (((g_switch_debug_level < 3) ||
          (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_32
                  ,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
          g_switch_debug_level < 3)) ||
         (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
         g_switch_debug_level < 3)) goto LAB_0001eaf4;
      printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
    }
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
    }
  }
LAB_0001eaf4:
  iVar4 = tm_ipv6table_add_set(&local_5c);
  if (iVar4 == 0) {
    return 0;
  }
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][tm_ipv6table_add_set] portlist3 FAIL\n");
  return 0xffffffff;
}


/* ============= FUNCTION: sw_sfu_multi_config_init @ 0001f3bc ============= */

void sw_sfu_multi_config_init(void)

{
  return;
}


/* ============= FUNCTION: sw_multi_vlan_trans_deal @ 0001f3c0 ============= */

undefined4 sw_multi_vlan_trans_deal(char *param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  undefined2 *puVar9;
  uint uVar10;
  uint uVar11;
  uint local_4c;
  ushort local_48;
  ushort local_46;
  short local_44;
  undefined1 local_41;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  undefined1 local_30;
  undefined1 local_2f;
  
  local_4c = 0;
  if (param_1 != (char *)0x0) {
    if (lg_firstTime_58377 != '\0') {
      __memzero(&g_vlanTransEntryTbl,0x140);
      lg_firstTime_58377 = '\0';
      printk("init multi vlan trans table end\n");
    }
    iVar5 = get_sw_port_from_devname(param_1,&local_4c,1);
    if (iVar5 == 0) {
      if (*param_1 == 'w') {
        if (g_switch_debug_level < 3) {
          return 0;
        }
        printk(" wifi port ,return ok\n");
        return 0;
      }
      uVar2 = *(ushort *)(param_1 + 0x12);
      uVar3 = *(ushort *)(param_1 + 0x10);
      uVar8 = uVar2 & 0xfff;
      uVar11 = uVar3 & 0xfff;
      if ((uVar2 & 0xfff) == 0) {
        uVar10 = 1;
      }
      else {
        uVar10 = 2;
      }
      if (2 < g_switch_debug_level) {
        printk("sw_multi_vlan_trans_deal ponvlan %d, univlan %d, vlanoper %d, port %d, act %d\n",
               uVar11,uVar8,param_2,local_4c,uVar10);
      }
      __memzero(&local_48,8);
      local_48 = (ushort)(((uint)uVar3 << 0x14) >> 0x14);
      local_44 = (short)local_4c;
      if (2 < g_switch_debug_level) {
        printk("sw_query_multi_vlan_trans_entry ponvlan %d, port %d\n",uVar11,local_4c & 0xffff);
      }
      iVar5 = 0;
      pcVar7 = DAT_0001f7b0;
      do {
        uVar3 = (ushort)(((uint)uVar2 << 0x14) >> 0x14);
        uVar4 = (undefined1)uVar10;
        local_40 = uVar8;
        local_3c = uVar11;
        local_38 = uVar10;
        if (((*pcVar7 != '\0') && (*(ushort *)(pcVar7 + -6) == local_48)) &&
           (*(short *)(pcVar7 + -2) == local_44)) {
          __memzero(&local_40,0x18);
          local_34 = local_4c;
          local_2f = 1;
          local_30 = 1;
          if (param_2 != 0) {
            iVar6 = tm_multicst_vltrans_table_delete_set(&local_40);
            if (iVar6 == 0) {
              if (2 < g_switch_debug_level) {
                printk("sw_del_multi_vlan_trans_entry idx %d\n",iVar5);
              }
              (&g_vlanTransEntryTbl)[iVar5 * 4] = 0;
              (&DAT_0002b7cc)[iVar5 * 4] = 0;
              (&DAT_0002b7ca)[iVar5 * 4] = 0;
              (&DAT_0002b7ce)[iVar5 * 8] = 0;
              (&DAT_0002b7cf)[iVar5 * 8] = 0;
              return 0;
            }
            goto LAB_0001f66c;
          }
          uVar2 = (&DAT_0002b7ca)[iVar5 * 4];
          bVar1 = (&DAT_0002b7cf)[iVar5 * 8];
          if (2 < g_switch_debug_level) {
            printk("sw_get_multi_vlan_trans_entry univlan %d, act %d, idx %d\n",(uint)uVar2,
                   (uint)bVar1,iVar5);
          }
          local_40 = (uint)uVar2;
          local_38 = (uint)bVar1;
          iVar6 = tm_multicst_vltrans_table_delete_set(&local_40);
          if (iVar6 != 0) goto LAB_0001f66c;
          if (2 < g_switch_debug_level) {
            printk("sw_update_multi_vlan_trans_entry univlan %d, idx %d\n",uVar8,iVar5);
          }
          (&DAT_0002b7ca)[iVar5 * 4] = uVar3;
          (&DAT_0002b7cf)[iVar5 * 8] = uVar4;
          goto LAB_0001f61c;
        }
        iVar5 = iVar5 + 1;
        pcVar7 = pcVar7 + 8;
      } while (iVar5 != 0x28);
      __memzero(&local_40,0x18);
      local_34 = local_4c;
      local_2f = 1;
      local_30 = 1;
      if (param_2 != 0) {
        iVar5 = tm_multicst_vltrans_table_delete_set(&local_40);
        if (iVar5 == 0) {
          return 0;
        }
LAB_0001f66c:
        printk("tm multi vltrans tbl delete fail\n");
        return 0xffffffff;
      }
      local_46 = uVar3;
      local_41 = uVar4;
      if (2 < g_switch_debug_level) {
        printk("sw_set_multi_vlan_trans_entry ponvlan %d, uniVlan %d, port %d\n",local_48,uVar8,
               local_44);
      }
      iVar5 = 0;
      puVar9 = &g_vlanTransEntryTbl;
      do {
        pcVar7 = (char *)(puVar9 + 3);
        puVar9 = puVar9 + 4;
        if (*pcVar7 == '\0') {
          (&g_vlanTransEntryTbl)[iVar5 * 4] = local_48;
          (&DAT_0002b7cc)[iVar5 * 4] = local_44;
          (&DAT_0002b7ca)[iVar5 * 4] = local_46;
          (&DAT_0002b7cf)[iVar5 * 8] = local_41;
          (&DAT_0002b7ce)[iVar5 * 8] = 1;
          break;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 != 0x28);
LAB_0001f61c:
      local_40 = uVar8;
      local_38 = uVar10;
      tm_multicst_vltrans_table_add_set(&local_40);
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("curPort ERROR: portname=%s\n",param_1);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_igmp_mulrule_deal @ 0001f7b4 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_igmp_mulrule_deal(undefined4 param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 auStack_20 [12];
  
  puVar1 = (undefined1 *)kmem_cache_alloc(_DAT_0002c340,0x20);
  if (puVar1 == (undefined1 *)0x0) {
    printk("switch ERR: sw_set_default_mulrule alloc mem failed\n");
    uVar3 = 0xffffffff;
  }
  else {
    __memzero(puVar1,0x49c);
    __memzero(auStack_20,8);
    puVar4 = puVar1 + 0x1f;
    *(undefined2 *)(puVar1 + 2) = 0;
    puVar1[1] = 0xf;
    *puVar1 = 100;
    puVar1[8] = 3;
    *(undefined4 *)(puVar1 + 4) = 1;
    *(undefined4 *)(puVar1 + 0xc) = 0xd;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x2f);
    puVar4 = puVar1 + 0x43;
    puVar1[0x1f] = (char)param_1;
    puVar1[0x1c] = (char)((uint)param_1 >> 0x18);
    puVar1[0x2c] = 0xff;
    puVar1[0x2d] = 0xff;
    puVar1[0x2e] = 0xff;
    puVar1[0x2f] = 0xff;
    puVar1[0x1d] = (char)((uint)param_1 >> 0x10);
    puVar1[0x1e] = (char)((uint)param_1 >> 8);
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x53);
    puVar1[0x43] = (char)param_2;
    if (param_2 != 0) {
      *(undefined4 *)(puVar1 + 0x30) = 6;
    }
    puVar1[0x53] = 0xff;
    puVar4 = puVar1 + 0x67;
    if (param_2 != 0) {
      puVar1[0x42] = (char)((uint)param_2 >> 8);
    }
    else {
      *(undefined4 *)(puVar1 + 0x30) = 4;
    }
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x77);
    puVar1[600] = 0;
    *(undefined4 *)(puVar1 + 0x54) = 2;
    puVar1[0x72] = 0xff;
    puVar1[0x62] = 1;
    *(undefined4 *)(puVar1 + 0x24c) = 1;
    *(undefined4 *)(puVar1 + 0x250) = 1;
    puVar1[0x256] = 5;
    if (param_3 == 1) {
      iVar2 = zte_api_sw_qos_add_port_streamselect(puVar1,auStack_20);
    }
    else {
      iVar2 = zte_api_sw_qos_del_port_streamselect();
    }
    if (iVar2 == 0) {
      kfree(puVar1);
      uVar3 = 0;
    }
    else {
      printk("zte_api_sw_qos_add_port_streamselect failed!\n");
      kfree(puVar1);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}


/* ============= FUNCTION: sw_add_igmp_addr_e8v4 @ 0001f96c ============= */

undefined4 sw_add_igmp_addr_e8v4(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_44,0x10);
    local_44 = *param_1;
    local_40 = param_1[1];
    local_3c = param_1[2];
    local_38 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_add_igmp_addr_e8v4 portname %s\n",&local_44);
    }
    iVar2 = get_sw_port_from_devname(&local_44,&local_48,1);
    if (iVar2 == 0) {
      uVar1 = 1 << (local_48 & 0xff);
      uVar4 = param_1[5];
      uVar3 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_add_igmp_addr_e8v4 portMsk 0x%8.8x, sip 0x%8.8x, dip 0x%8.8x, vlan %d\n",uVar1,0,
               uVar4,uVar3);
      }
      __memzero(&local_34);
      local_30 = 0;
      local_2c = uVar4;
      local_28 = uVar3;
      iVar2 = tm_ipv4table_lookup_get(&local_34);
      if (iVar2 == 0) {
        if (g_switch_debug_level < 3) {
          local_24 = uVar1 | local_24;
        }
        else {
          printk("tm_ipv4table_lookup_get, l_portMsk=%d\n",local_24);
          local_24 = uVar1 | local_24;
          if (2 < g_switch_debug_level) {
            printk("after, l_portMsk=%d\n",local_24);
          }
        }
        local_33 = 0;
        local_34 = 1;
        local_32 = 1;
        tm_ipv4table_add_set(&local_34);
        sw_igmp_mulrule_deal(uVar4,uVar3,1);
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("tm_ipv4table_lookup_get ERROR: sip=%d, dip=%d, vlan_id=%d\n",local_30,local_2c,
               local_28);
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_44);
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_del_igmp_addr_e8v4 @ 0001fb54 ============= */

undefined4 sw_del_igmp_addr_e8v4(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (2 < g_switch_debug_level) {
    printk("sw_del_igmp_addr_e8v411\n");
  }
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_44,0x10);
    local_44 = *param_1;
    local_40 = param_1[1];
    local_3c = param_1[2];
    local_38 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_del_igmp_addr_e8v4 portname %s\n",&local_44);
    }
    iVar2 = get_sw_port_from_devname(&local_44,&local_48,1);
    if (iVar2 == 0) {
      uVar4 = param_1[5];
      uVar1 = 1 << (local_48 & 0xff);
      uVar3 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_del_igmp_addr_e8v4 portMsk 0x%8.8x, sip 0x%8.8x, dip 0x%8.8x, vlan %d\n",uVar1,0,
               uVar4,uVar3);
      }
      __memzero(&local_34);
      local_30 = 0;
      local_2c = uVar4;
      local_28 = uVar3;
      if (uVar1 == 0) {
        tm_ipv4table_delete_set(&local_34);
        sw_igmp_mulrule_deal(uVar4,uVar3,0);
        return 0;
      }
      iVar2 = tm_ipv4table_lookup_get();
      if (iVar2 == 0) {
        if (uVar1 != local_24) {
          local_24 = local_24 & ~uVar1;
          local_33 = 0;
          local_34 = 1;
          local_32 = 1;
          if (2 < g_switch_debug_level) {
            printk("sw_del_igmp_addr_e8v4 2 portmask %d\n");
          }
          tm_ipv4table_add_set(&local_34);
          return 0;
        }
        if (2 < g_switch_debug_level) {
          printk("sw_del_igmp_addr_e8v4 1portmask %d\n",uVar1);
        }
        tm_ipv4table_delete_set(&local_34);
        sw_igmp_mulrule_deal(uVar4,uVar3,0);
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("tm_ipv4table_lookup_get ERROR: sip=%d, dip=%d, vlan_id=%d\n",local_30,local_2c,
               local_28);
        return 0xffffffff;
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_44);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_mld_mulrule_deal @ 0001fd80 ============= */

undefined4 sw_mld_mulrule_deal(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined1 auStack_4b4 [8];
  undefined1 local_4ac;
  undefined1 local_4ab;
  undefined2 local_4aa;
  undefined4 local_4a8;
  undefined1 local_4a4;
  undefined4 local_4a0;
  undefined1 local_49c [16];
  undefined1 local_48c [16];
  undefined4 local_47c;
  undefined1 local_46a;
  undefined1 local_469;
  undefined1 local_468 [16];
  undefined4 local_458;
  undefined1 local_44a;
  undefined1 uStack_445;
  undefined1 local_444 [484];
  undefined4 local_260;
  undefined4 local_25c;
  undefined1 local_256;
  undefined1 local_254;
  
  __memzero(&local_4ac,0x49c);
  __memzero(auStack_4b4,8);
  puVar6 = local_49c + 0xf;
  local_4aa = 0;
  local_4ac = 100;
  local_4ab = 0xf;
  local_4a8 = 1;
  local_4a4 = 3;
  local_4a0 = 0x12;
  puVar3 = puVar6;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != local_48c + 0xf);
  puVar3 = (undefined1 *)(param_1 + 0x10);
  puVar4 = (undefined1 *)((int)&local_4a0 + 3);
  do {
    puVar3 = puVar3 + -1;
    puVar4 = puVar4 + 1;
    *puVar4 = *puVar3;
    puVar6 = puVar6 + 1;
    *puVar6 = 0xff;
  } while (puVar4 != local_49c + 0xf);
  puVar3 = &local_469;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != local_468 + 0xf);
  local_469 = (undefined1)param_2;
  if (param_2 != 0) {
    uVar5 = (undefined1)((uint)param_2 >> 8);
    local_47c = 6;
  }
  else {
    uVar5 = 0;
  }
  local_468[0xf] = 0xff;
  puVar3 = &uStack_445;
  if (param_2 == 0) {
    local_47c = 4;
    uVar5 = local_46a;
  }
  do {
    local_46a = uVar5;
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
    uVar5 = local_46a;
  } while (puVar3 != local_444 + 0xf);
  local_254 = 0;
  local_458 = 2;
  local_44a = 0x33;
  local_444[10] = 0xff;
  local_260 = 1;
  local_25c = 1;
  local_256 = 5;
  if (param_3 == 1) {
    iVar1 = zte_api_sw_qos_add_port_streamselect(&local_4ac,auStack_4b4);
  }
  else {
    iVar1 = zte_api_sw_qos_del_port_streamselect();
  }
  uVar2 = 0;
  if (iVar1 != 0) {
    printk("zte_api_sw_qos_add_port_streamselect failed!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: sw_add_mld_addr_e8v4 @ 0001fef8 ============= */

undefined4 sw_add_mld_addr_e8v4(undefined4 *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  uint local_50;
  int aiStack_4c [4];
  int local_3c [7];
  
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_64,0x10);
    local_64 = *param_1;
    local_60 = param_1[1];
    local_5c = param_1[2];
    local_58 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_add_mld_addr_e8v4 portname %s\n",&local_64);
    }
    iVar1 = get_sw_port_from_devname(&local_64,&local_68,1);
    if (iVar1 == 0) {
      iVar1 = 1 << (local_68 & 0xff);
      __memzero(&local_54,0x34);
      uVar5 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_add_mld_addr_e8v4 dip:");
      }
      puVar2 = (undefined1 *)((int)param_1 + 0x22);
      piVar3 = aiStack_4c;
      uVar6 = g_switch_debug_level;
      do {
        puVar2 = puVar2 + -1;
        piVar4 = (int *)((int)piVar3 + 1);
        *(undefined1 *)piVar3 = *puVar2;
        if (2 < uVar6) {
          printk("%2.2x.\n");
          uVar6 = g_switch_debug_level;
        }
        piVar3 = piVar4;
      } while (piVar4 != local_3c);
      if (2 < uVar6) {
        printk("\nsw_add_mld_addr_e8v4 portMsk 0x%8.8x, vlan %d\n",iVar1,uVar5);
      }
      local_53 = 0;
      local_54 = 1;
      local_52 = 1;
      local_50 = uVar5;
      local_3c[0] = iVar1;
      tm_ipv6table_add_set(&local_54);
      sw_mld_mulrule_deal(aiStack_4c,uVar5,1);
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_64);
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_del_mld_addr_e8v4 @ 0002009c ============= */

undefined4 sw_del_mld_addr_e8v4(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  uint local_50;
  uint auStack_4c [4];
  uint local_3c [7];
  
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_64,0x10);
    local_64 = *param_1;
    local_60 = param_1[1];
    local_5c = param_1[2];
    local_58 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_del_mld_addr_e8v4 portname %s\n",&local_64);
    }
    iVar2 = get_sw_port_from_devname(&local_64,&local_68,1);
    if (iVar2 == 0) {
      uVar1 = 1 << (local_68 & 0xff);
      __memzero(&local_54,0x34);
      uVar6 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_add_mld_addr_e8v4 dip:");
      }
      puVar3 = (undefined1 *)((int)param_1 + 0x22);
      puVar4 = auStack_4c;
      uVar7 = g_switch_debug_level;
      do {
        puVar3 = puVar3 + -1;
        puVar5 = (uint *)((int)puVar4 + 1);
        *(undefined1 *)puVar4 = *puVar3;
        if (2 < uVar7) {
          printk("%2.2x.\n");
          uVar7 = g_switch_debug_level;
        }
        puVar4 = puVar5;
      } while (puVar5 != local_3c);
      if (2 < uVar7) {
        printk("\nsw_add_mld_addr_e8v4 portMsk 0x%8.8x, vlan %d\n",uVar1,uVar6);
      }
      local_50 = uVar6;
      if (uVar1 == 0) {
        tm_ipv6table_delete_set(&local_54);
        sw_mld_mulrule_deal(auStack_4c,uVar6,0);
        return 0;
      }
      iVar2 = tm_ipv6table_lookup_get();
      if (iVar2 == 0) {
        if (uVar1 != local_3c[0]) {
          local_3c[0] = local_3c[0] & ~uVar1;
          local_53 = 0;
          local_54 = 1;
          local_52 = 1;
          tm_ipv6table_add_set();
          return 0;
        }
        tm_ipv6table_delete_set(&local_54);
        sw_mld_mulrule_deal(auStack_4c,uVar6,0);
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("tm_ipv6table_lookup_get ERROR: vlan_id=%d\n",local_50);
        return 0xffffffff;
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_64);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sw_hgu_multi_config_init @ 000202a8 ============= */

void sw_hgu_multi_config_init(void)

{
  return;
}


/* ============= FUNCTION: npu_drv_indev_learn @ 000202ac ============= */

undefined4 npu_drv_indev_learn(undefined4 param_1,int param_2,int param_3)

{
  *(short *)(param_2 + 0x98) =
       (short)*(undefined4 *)(param_3 + 0x24) - (short)*(undefined4 *)(param_3 + 0x28);
  return 0;
}


/* ============= FUNCTION: npu_drv_outdev_learn @ 000202c4 ============= */

undefined4 npu_drv_outdev_learn(undefined4 param_1,int param_2)

{
  *(undefined2 *)(param_2 + 0x9a) = 0;
  return 0;
}


/* ============= FUNCTION: npu_hff_register @ 000202d4 ============= */

undefined4
npu_hff_register(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&npu_hff_func_tbl,0x10,param_3,param_4,param_4);
    npu_hff_func_tbl = *param_1;
    DAT_0002b90c = param_1[1];
    DAT_0002b910 = param_1[2];
    DAT_0002b914 = param_1[3];
    printk("register npu driver %d\n",0xc);
    npu_register_driver(&npu_drv);
  }
  __memzero(DAT_00020350,0x420);
  g_multivlan_lock = 0;
  return 0;
}


/* ============= FUNCTION: npu_drv_free_flow @ 00020354 ============= */

undefined4 npu_drv_free_flow(undefined4 param_1,int param_2)

{
  if ((1 < *(int *)(*(int *)(param_2 + 0x34) + 0x14) - 4U) && (*(int *)(param_2 + 0x9c) != 0)) {
    kfree();
    *(undefined4 *)(param_2 + 0x9c) = 0;
    return 0;
  }
  return 0;
}


/* ============= FUNCTION: npu_drv_refresh_flow @ 00020398 ============= */

undefined4 npu_drv_refresh_flow(undefined4 param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  char *__s2;
  undefined4 local_d0;
  byte *local_cc;
  byte *local_c8;
  undefined2 local_c4;
  undefined2 local_c2;
  byte local_c0;
  byte local_bf;
  byte *local_bc;
  byte *local_b8;
  undefined2 local_b4;
  undefined2 local_b2;
  byte local_b0;
  byte local_af;
  byte *local_ac;
  byte *local_a8;
  undefined2 local_a4;
  undefined2 local_a2;
  byte local_a0;
  byte local_9f;
  byte *local_9c;
  byte *local_98;
  undefined2 local_94;
  undefined2 local_92;
  byte local_90;
  byte local_8f;
  byte *local_8c;
  byte *local_88;
  undefined2 local_84;
  undefined2 local_82;
  int local_80;
  ushort local_7c;
  undefined1 local_78;
  undefined1 local_77;
  char *local_74;
  int local_70;
  byte *local_6c;
  byte *local_68;
  byte *local_64;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_58;
  undefined4 local_54;
  byte local_50;
  byte local_4f;
  uint local_4c;
  byte *local_48;
  byte *local_44;
  byte local_40;
  byte local_3f;
  short local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_d0 = 0;
  if (DAT_0002b910 == (code *)0x0) {
    return 0;
  }
  if (*(int *)(*(int *)(param_2 + 0x34) + 0x14) - 4U < 2) {
    return 1;
  }
  __memzero(&local_8c,0x6c);
  __memzero(&local_cc,0x10);
  __memzero(&local_bc,0x10);
  __memzero(&local_ac,0x10);
  __memzero(&local_9c,0x10);
  if (param_2 == 0) {
    return 0;
  }
  pbVar7 = *(byte **)(param_2 + 0x14);
  __s2 = *(char **)(pbVar7 + *pbVar7);
  if (__s2 == (char *)0x0) {
    return 0;
  }
  local_74 = __s2;
  iVar3 = strcmp("pon0",__s2);
  if (((((iVar3 == 0) || (iVar3 = strcmp("pon",__s2), iVar3 == 0)) ||
       (iVar3 = strcmp("gpon0",__s2), iVar3 == 0)) ||
      ((iVar3 = strcmp("epon0",__s2), iVar3 == 0 || (iVar3 = strcmp("mii1",__s2), iVar3 == 0)))) ||
     (iVar3 = strcmp("eth0",__s2), iVar3 == 0)) {
    bVar2 = true;
  }
  else {
    iVar3 = strcmp("ptm0",__s2);
    bVar2 = iVar3 == 0;
  }
  pbVar5 = *(byte **)(param_2 + 0x10);
  local_70 = *(int *)(pbVar5 + *pbVar5);
  if (local_70 == 0) {
    return 0;
  }
  if ((*(uint *)(param_2 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_2 + 0x28) & 0x2000000) != 0) {
      local_77 = 1;
    }
  }
  else {
    local_78 = 1;
  }
  uVar4 = *(uint *)(param_2 + 0x28);
  if ((uVar4 & 0x1c) == 0) {
    if ((uVar4 & 0x700) != 0) {
      local_80 = 1;
      uVar4 = (uint)pbVar5[7];
      local_a8 = pbVar5 + uVar4 + 0x18;
      local_a0 = pbVar5[uVar4 + 6];
      local_ac = pbVar5 + uVar4 + 8;
      local_9f = pbVar5[uVar4 + 1] >> 4 | pbVar5[uVar4] << 4;
      if (local_a0 == 6) {
        bVar1 = pbVar5[9];
LAB_000208c0:
        local_a4 = *(undefined2 *)(pbVar5 + bVar1);
        local_a2 = *(undefined2 *)(pbVar5 + bVar1 + 2);
      }
      else {
        if (local_a0 == 0x11) {
          bVar1 = pbVar5[10];
          goto LAB_000208c0;
        }
        local_a4 = 0;
        local_a2 = 0;
      }
      local_7c = (ushort)local_a0;
      uVar4 = (uint)pbVar7[7];
      local_98 = pbVar7 + uVar4 + 0x18;
      local_90 = pbVar7[uVar4 + 6];
      local_9c = pbVar7 + uVar4 + 8;
      local_8f = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
      if (local_90 == 6) {
        bVar1 = pbVar7[9];
LAB_000209a0:
        local_94 = *(undefined2 *)(pbVar7 + bVar1);
        local_92 = *(undefined2 *)(pbVar7 + bVar1 + 2);
      }
      else {
        if (local_90 == 0x11) {
          bVar1 = pbVar7[10];
          goto LAB_000209a0;
        }
        local_94 = 0;
        local_92 = local_94;
      }
      local_8c = local_ac;
      local_88 = local_a8;
      local_84 = local_a4;
      local_82 = local_a2;
      if (local_9f != local_8f) {
        local_3f = local_3f | 0x10;
        local_40 = local_8f;
      }
      goto LAB_0002074c;
    }
    if ((uVar4 & 0x60) == 0) {
      return 0;
    }
    local_80 = 2;
  }
  else {
    local_80 = 0;
  }
  uVar4 = (uint)pbVar5[5];
  local_cc = *(byte **)(pbVar5 + uVar4);
  local_c0 = pbVar5[uVar4 + 9];
  local_c8 = *(byte **)(pbVar5 + uVar4 + 4);
  local_bf = pbVar5[uVar4 + 8];
  if (local_c0 == 6) {
    bVar1 = pbVar5[9];
LAB_000208dc:
    local_c4 = *(undefined2 *)(pbVar5 + bVar1);
    local_c2 = *(undefined2 *)(pbVar5 + bVar1 + 2);
  }
  else {
    if (local_c0 == 0x11) {
      bVar1 = pbVar5[10];
      goto LAB_000208dc;
    }
    local_c4 = 0;
    local_c2 = 0;
  }
  local_7c = (ushort)local_c0;
  uVar4 = (uint)pbVar7[5];
  local_bc = *(byte **)(pbVar7 + uVar4);
  local_b0 = pbVar7[uVar4 + 9];
  local_b8 = *(byte **)(pbVar7 + uVar4 + 4);
  local_af = pbVar7[uVar4 + 8];
  if (local_b0 == 6) {
    bVar1 = pbVar7[9];
LAB_000206f8:
    local_b4 = *(undefined2 *)(pbVar7 + bVar1);
    local_b2 = *(undefined2 *)(pbVar7 + bVar1 + 2);
  }
  else {
    if (local_b0 == 0x11) {
      bVar1 = pbVar7[10];
      goto LAB_000206f8;
    }
    local_b4 = 0;
    local_b2 = local_b4;
  }
  if (local_c8 == local_b8) {
    if (local_cc != local_bc) {
      local_60 = local_b4;
      local_54 = 1;
      local_6c = local_bc;
      goto LAB_00020724;
    }
    local_54 = 0;
    if (bVar2) {
      local_60 = local_b4;
      local_6c = local_cc;
      goto LAB_00020930;
    }
    local_60 = local_b2;
    local_6c = local_c8;
  }
  else {
    if (local_cc != local_bc) {
      return 0;
    }
    local_54 = 2;
    local_60 = local_b2;
    local_6c = local_b8;
LAB_00020724:
    if (bVar2) {
LAB_00020930:
      if (local_80 == 2) {
        uVar4 = (uint)pbVar7[7];
        local_48 = pbVar7 + uVar4 + 8;
        local_44 = pbVar7 + uVar4 + 0x18;
        local_50 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
        local_4c = (uint)CONCAT11(pbVar7[uVar4 + 2],pbVar7[uVar4 + 3]) |
                   (pbVar7[uVar4 + 1] & 0xf) << 0x10;
        local_4f = pbVar7[uVar4 + 7];
      }
    }
  }
  local_8c = local_cc;
  local_88 = local_c8;
  local_84 = local_c4;
  local_82 = local_c2;
  if (local_bf != local_af) {
    local_3f = local_3f | 0x10;
    local_40 = local_af;
  }
LAB_0002074c:
  local_64 = pbVar7 + pbVar7[1] + 6;
  local_68 = pbVar7 + pbVar7[1];
  local_3f = local_3f & 0xfc | pbVar5[3] & 1 ^ 1 | (pbVar7[3] & 1 ^ 1) << 1;
  if ((pbVar5[3] & 1) == 0) {
    local_5c = *(undefined2 *)(pbVar5 + pbVar5[3] + 2);
  }
  else {
    local_5c = 0;
  }
  if ((pbVar7[3] & 1) == 0) {
    local_5e = *(undefined2 *)(pbVar7 + pbVar7[3] + 2);
  }
  else {
    local_5e = 0;
  }
  if (((pbVar5[2] & 1) == 0) && (*(short *)(pbVar5 + pbVar5[2]) != -1)) {
    local_3f = local_3f | 4;
    if ((pbVar5[2] & 1) == 0) {
      local_5a = *(undefined2 *)(pbVar5 + pbVar5[2]);
    }
    else {
      local_5a = 0xffff;
    }
  }
  if (((pbVar7[2] & 1) == 0) && (*(short *)(pbVar7 + pbVar7[2]) != -1)) {
    local_3f = local_3f | 8;
    if ((pbVar7[2] & 1) == 0) {
      local_58 = *(undefined2 *)(pbVar7 + pbVar7[2]);
    }
    else {
      local_58 = 0xffff;
    }
  }
  local_3a = *(short *)(param_2 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_80 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_3a = local_3a + -0x28;
  }
  puVar6 = *(undefined4 **)(param_2 + 0x9c);
  local_38 = *puVar6;
  local_34 = puVar6[1];
  local_30 = puVar6[2];
  local_2c = puVar6[3];
  local_28 = puVar6[4];
  local_24 = puVar6[5];
  iVar3 = (*DAT_0002b910)(&local_8c,&local_d0);
  if (iVar3 == 0) {
    return 0;
  }
  return local_d0;
}


/* ============= FUNCTION: npu_drv_lookup_multientry @ 000209d4 ============= */

char * npu_drv_lookup_multientry(char *param_1)

{
  short sVar1;
  int iVar2;
  char *__s1;
  char *pcVar3;
  
  sVar1 = *(short *)(param_1 + 0x10);
  pcVar3 = DAT_00020a38 + 0x420;
  __s1 = DAT_00020a38;
  while (((*(short *)(__s1 + 0x10) != sVar1 ||
          (*(short *)(__s1 + 0x12) != *(short *)(param_1 + 0x12))) ||
         (iVar2 = strcmp(__s1,param_1), iVar2 != 0))) {
    __s1 = __s1 + 0x16;
    if (__s1 == pcVar3) {
      return (char *)0x0;
    }
  }
  return __s1;
}


/* ============= FUNCTION: npu_drv_delete_multivlan @ 00020a3c ============= */

undefined4 npu_drv_delete_multivlan(undefined4 param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  short sVar4;
  byte *pbVar5;
  char acStack_26 [16];
  ushort local_16;
  ushort local_14;
  
  pbVar5 = *(byte **)(param_2 + 0x14);
  bVar1 = *pbVar5;
  __memzero(acStack_26,0x16);
  strncpy(acStack_26,*(char **)(pbVar5 + bVar1),0xf);
  bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
  if ((bVar1 & 1) == 0) {
    uVar2 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
    iVar3 = *(int *)(param_2 + 0x14);
    local_16 = (ushort)((((uVar2 & 0xff) << 8 | (uint)(uVar2 >> 8)) << 0x14) >> 0x14);
    bVar1 = *(byte *)(iVar3 + 2);
  }
  else {
    iVar3 = *(int *)(param_2 + 0x14);
    bVar1 = *(byte *)(iVar3 + 2);
  }
  if ((bVar1 & 1) == 0) {
    local_14 = (ushort)((((*(ushort *)(iVar3 + (uint)bVar1) & 0xff) << 8 |
                         (uint)(*(ushort *)(iVar3 + (uint)bVar1) >> 8)) << 0x14) >> 0x14);
  }
  _raw_spin_lock_bh(DAT_00020b2c);
  iVar3 = npu_drv_lookup_multientry(acStack_26);
  if (iVar3 == 0) {
    printk(" multi_vlan_table no has this entry\n");
  }
  else {
    sVar4 = *(short *)(iVar3 + 0x14) + -1;
    *(short *)(iVar3 + 0x14) = sVar4;
    if (sVar4 == 0) {
      sw_multi_vlan_trans_deal(iVar3,1);
      __memzero(iVar3,0x16);
    }
  }
  _raw_spin_unlock_bh(DAT_00020b2c);
  return 0;
}


/* ============= FUNCTION: npu_drv_create_multivlan @ 00020b30 ============= */

undefined4 npu_drv_create_multivlan(undefined4 param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  char *pcVar4;
  byte *pbVar5;
  undefined4 local_26;
  undefined4 local_22;
  undefined4 local_1e;
  undefined4 local_1a;
  undefined4 local_16;
  undefined2 local_12;
  
  pbVar5 = *(byte **)(param_2 + 0x14);
  bVar1 = *pbVar5;
  __memzero(&local_26,0x16);
  strncpy((char *)&local_26,*(char **)(pbVar5 + bVar1),0xf);
  bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
  if ((bVar1 & 1) == 0) {
    uVar2 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
    iVar3 = *(int *)(param_2 + 0x14);
    local_16 = CONCAT22(local_16._2_2_,
                        (ushort)((((uVar2 & 0xff) << 8 | (uint)(uVar2 >> 8)) << 0x14) >> 0x14));
    bVar1 = *(byte *)(iVar3 + 2);
  }
  else {
    iVar3 = *(int *)(param_2 + 0x14);
    bVar1 = *(byte *)(iVar3 + 2);
  }
  if ((bVar1 & 1) == 0) {
    local_16 = CONCAT22((ushort)((((*(ushort *)(iVar3 + (uint)bVar1) & 0xff) << 8 |
                                  (uint)(*(ushort *)(iVar3 + (uint)bVar1) >> 8)) << 0x14) >> 0x14),
                        (undefined2)local_16);
  }
  _raw_spin_lock_bh(DAT_00020c70);
  iVar3 = npu_drv_lookup_multientry(&local_26);
  if (iVar3 == 0) {
    pcVar4 = DAT_00020c74;
    do {
      if (*pcVar4 == '\0') {
        *(undefined4 *)pcVar4 = local_26;
        *(undefined4 *)(pcVar4 + 4) = local_22;
        *(undefined4 *)(pcVar4 + 8) = local_1e;
        *(undefined4 *)(pcVar4 + 0xc) = local_1a;
        *(undefined4 *)(pcVar4 + 0x10) = local_16;
        *(undefined2 *)(pcVar4 + 0x14) = local_12;
        if (pcVar4 != (char *)0x0) {
          *(short *)(pcVar4 + 0x14) = *(short *)(pcVar4 + 0x14) + 1;
          sw_multi_vlan_trans_deal(pcVar4);
          goto LAB_00020bb4;
        }
        break;
      }
      pcVar4 = pcVar4 + 0x16;
    } while (pcVar4 != DAT_00020c74 + 0x420);
    printk("multi_vlan_table full\n");
  }
  else {
    *(short *)(iVar3 + 0x14) = *(short *)(iVar3 + 0x14) + 1;
  }
LAB_00020bb4:
  _raw_spin_unlock_bh(DAT_00020c70);
  return 0;
}


/* ============= FUNCTION: npu_drv_dup_flow @ 00020c78 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 npu_drv_dup_flow(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (1 < *(int *)(*(int *)(param_2 + 0x34) + 0x14) - 4U) {
    uVar4 = *(undefined4 *)(param_2 + 0x98);
    uVar1 = *(undefined4 *)(param_2 + 0x9c);
    *(undefined4 *)(param_3 + 0x94) = *(undefined4 *)(param_2 + 0x94);
    *(undefined4 *)(param_3 + 0x98) = uVar4;
    *(undefined4 *)(param_3 + 0x9c) = uVar1;
    if (*(int *)(param_2 + 0x9c) != 0) {
      puVar2 = (undefined4 *)
               kmem_cache_alloc(_CspGetPortInfo,0x80d0,param_3,&kmalloc_caches,param_4);
      if (puVar2 != (undefined4 *)0x0) {
        *(undefined4 **)(param_3 + 0x9c) = puVar2;
        puVar3 = *(undefined4 **)(param_2 + 0x9c);
        uVar1 = puVar3[1];
        uVar4 = puVar3[2];
        uVar5 = puVar3[3];
        *puVar2 = *puVar3;
        puVar2[1] = uVar1;
        puVar2[2] = uVar4;
        puVar2[3] = uVar5;
        uVar1 = puVar3[5];
        puVar2[4] = puVar3[4];
        puVar2[5] = uVar1;
        return 0;
      }
      return 0xffffffff;
    }
  }
  return 0;
}


/* ============= FUNCTION: npu_drv_delete_flow.part.1 @ 00020d2c ============= */

int npu_drv_delete_flow_part_1(int param_1)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  char *__s2;
  byte *local_c4;
  byte *local_c0;
  undefined2 local_bc;
  undefined2 local_ba;
  byte local_b8;
  byte local_b7;
  byte *local_b4;
  byte *local_b0;
  undefined2 local_ac;
  undefined2 local_aa;
  byte local_a8;
  byte local_a7;
  byte *local_a4;
  byte *local_a0;
  undefined2 local_9c;
  undefined2 local_9a;
  byte local_98;
  byte local_97;
  byte *local_94;
  byte *local_90;
  undefined2 local_8c;
  undefined2 local_8a;
  byte local_88;
  byte local_87;
  byte *local_84;
  byte *local_80;
  undefined2 local_7c;
  undefined2 local_7a;
  int local_78;
  ushort local_74;
  undefined1 local_70;
  undefined1 local_6f;
  char *local_6c;
  int local_68;
  byte *local_64;
  byte *local_60;
  byte *local_5c;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 local_50;
  undefined4 local_4c;
  byte local_48;
  byte local_47;
  uint local_44;
  byte *local_40;
  byte *local_3c;
  byte local_38;
  byte local_37;
  short local_32;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  __memzero(&local_84,0x6c);
  __memzero(&local_c4,0x10);
  __memzero(&local_b4,0x10);
  __memzero(&local_a4,0x10);
  __memzero(&local_94,0x10);
  if (param_1 == 0) {
    return -1;
  }
  pbVar7 = *(byte **)(param_1 + 0x14);
  __s2 = *(char **)(pbVar7 + *pbVar7);
  if (__s2 == (char *)0x0) {
    return -1;
  }
  local_6c = __s2;
  iVar3 = strcmp("pon0",__s2);
  if (((((iVar3 == 0) || (iVar3 = strcmp("pon",__s2), iVar3 == 0)) ||
       (iVar3 = strcmp("gpon0",__s2), iVar3 == 0)) ||
      ((iVar3 = strcmp("epon0",__s2), iVar3 == 0 || (iVar3 = strcmp("mii1",__s2), iVar3 == 0)))) ||
     (iVar3 = strcmp("eth0",__s2), iVar3 == 0)) {
    bVar2 = true;
  }
  else {
    iVar3 = strcmp("ptm0",__s2);
    bVar2 = iVar3 == 0;
  }
  pbVar5 = *(byte **)(param_1 + 0x10);
  local_68 = *(int *)(pbVar5 + *pbVar5);
  if (local_68 == 0) {
    return -1;
  }
  if ((*(uint *)(param_1 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_1 + 0x28) & 0x2000000) != 0) {
      local_6f = 1;
    }
  }
  else {
    local_70 = 1;
  }
  uVar4 = *(uint *)(param_1 + 0x28);
  if ((uVar4 & 0x1c) == 0) {
    if ((uVar4 & 0x700) != 0) {
      local_78 = 1;
      uVar4 = (uint)pbVar5[7];
      local_a0 = pbVar5 + uVar4 + 0x18;
      local_98 = pbVar5[uVar4 + 6];
      local_a4 = pbVar5 + uVar4 + 8;
      local_97 = pbVar5[uVar4 + 1] >> 4 | pbVar5[uVar4] << 4;
      if (local_98 == 6) {
        bVar1 = pbVar5[9];
LAB_0002130c:
        local_9c = *(undefined2 *)(pbVar5 + bVar1);
        local_9a = *(undefined2 *)(pbVar5 + bVar1 + 2);
      }
      else {
        if (local_98 == 0x11) {
          bVar1 = pbVar5[10];
          goto LAB_0002130c;
        }
        local_9c = 0;
        local_9a = 0;
      }
      local_74 = (ushort)local_98;
      uVar4 = (uint)pbVar7[7];
      local_90 = pbVar7 + uVar4 + 0x18;
      local_88 = pbVar7[uVar4 + 6];
      local_94 = pbVar7 + uVar4 + 8;
      local_87 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
      if (local_88 == 6) {
        bVar1 = pbVar7[9];
LAB_00021328:
        local_8c = *(undefined2 *)(pbVar7 + bVar1);
        local_8a = *(undefined2 *)(pbVar7 + bVar1 + 2);
      }
      else {
        if (local_88 == 0x11) {
          bVar1 = pbVar7[10];
          goto LAB_00021328;
        }
        local_8c = 0;
        local_8a = local_8c;
      }
      local_84 = local_a4;
      local_80 = local_a0;
      local_7c = local_9c;
      local_7a = local_9a;
      if (local_97 != local_87) {
        local_37 = local_37 | 0x10;
        local_38 = local_87;
      }
      goto LAB_00020eec;
    }
    if ((uVar4 & 0x60) == 0) {
      return -1;
    }
    local_78 = 2;
  }
  else {
    local_78 = 0;
  }
  uVar4 = (uint)pbVar5[5];
  local_c4 = *(byte **)(pbVar5 + uVar4);
  local_b8 = pbVar5[uVar4 + 9];
  local_c0 = *(byte **)(pbVar5 + uVar4 + 4);
  local_b7 = pbVar5[uVar4 + 8];
  if (local_b8 == 6) {
    bVar1 = pbVar5[9];
LAB_00021218:
    local_bc = *(undefined2 *)(pbVar5 + bVar1);
    local_ba = *(undefined2 *)(pbVar5 + bVar1 + 2);
  }
  else {
    if (local_b8 == 0x11) {
      bVar1 = pbVar5[10];
      goto LAB_00021218;
    }
    local_bc = 0;
    local_ba = 0;
  }
  local_74 = (ushort)local_b8;
  uVar4 = (uint)pbVar7[5];
  local_b4 = *(byte **)(pbVar7 + uVar4);
  local_a8 = pbVar7[uVar4 + 9];
  local_b0 = *(byte **)(pbVar7 + uVar4 + 4);
  local_a7 = pbVar7[uVar4 + 8];
  if (local_a8 == 6) {
    bVar1 = pbVar7[9];
LAB_00021234:
    local_ac = *(undefined2 *)(pbVar7 + bVar1);
    local_aa = *(undefined2 *)(pbVar7 + bVar1 + 2);
  }
  else {
    if (local_a8 == 0x11) {
      bVar1 = pbVar7[10];
      goto LAB_00021234;
    }
    local_ac = 0;
    local_aa = local_ac;
  }
  if (local_c0 == local_b0) {
    if (local_c4 != local_b4) {
      local_58 = local_ac;
      local_4c = 1;
      local_64 = local_b4;
      goto LAB_00020ec4;
    }
    local_4c = 0;
    if (bVar2) {
      local_58 = local_ac;
      local_64 = local_c4;
      goto LAB_00021290;
    }
    local_58 = local_aa;
    local_64 = local_c0;
  }
  else {
    if (local_c4 != local_b4) {
      return -1;
    }
    local_4c = 2;
    local_58 = local_aa;
    local_64 = local_b0;
LAB_00020ec4:
    if (bVar2) {
LAB_00021290:
      if (local_78 == 2) {
        uVar4 = (uint)pbVar7[7];
        local_40 = pbVar7 + uVar4 + 8;
        local_3c = pbVar7 + uVar4 + 0x18;
        local_48 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
        local_44 = (uint)CONCAT11(pbVar7[uVar4 + 2],pbVar7[uVar4 + 3]) |
                   (pbVar7[uVar4 + 1] & 0xf) << 0x10;
        local_47 = pbVar7[uVar4 + 7];
      }
    }
  }
  local_84 = local_c4;
  local_80 = local_c0;
  local_7c = local_bc;
  local_7a = local_ba;
  if (local_b7 != local_a7) {
    local_37 = local_37 | 0x10;
    local_38 = local_a7;
  }
LAB_00020eec:
  local_5c = pbVar7 + pbVar7[1] + 6;
  local_60 = pbVar7 + pbVar7[1];
  local_37 = local_37 & 0xfc | pbVar5[3] & 1 ^ 1 | (pbVar7[3] & 1 ^ 1) << 1;
  if ((pbVar5[3] & 1) == 0) {
    local_54 = *(undefined2 *)(pbVar5 + pbVar5[3] + 2);
  }
  else {
    local_54 = 0;
  }
  if ((pbVar7[3] & 1) == 0) {
    local_56 = *(undefined2 *)(pbVar7 + pbVar7[3] + 2);
  }
  else {
    local_56 = 0;
  }
  if (((pbVar5[2] & 1) == 0) && (*(short *)(pbVar5 + pbVar5[2]) != -1)) {
    local_37 = local_37 | 4;
    if ((pbVar5[2] & 1) == 0) {
      local_52 = *(undefined2 *)(pbVar5 + pbVar5[2]);
    }
    else {
      local_52 = 0xffff;
    }
  }
  if (((pbVar7[2] & 1) == 0) && (*(short *)(pbVar7 + pbVar7[2]) != -1)) {
    local_37 = local_37 | 8;
    if ((pbVar7[2] & 1) == 0) {
      local_50 = *(undefined2 *)(pbVar7 + pbVar7[2]);
    }
    else {
      local_50 = 0xffff;
    }
  }
  local_32 = *(short *)(param_1 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_78 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_32 = local_32 + -0x28;
  }
  puVar6 = *(undefined4 **)(param_1 + 0x9c);
  local_30 = *puVar6;
  local_2c = puVar6[1];
  local_28 = puVar6[2];
  local_24 = puVar6[3];
  local_20 = puVar6[4];
  local_1c = puVar6[5];
  kfree(puVar6);
  *(undefined4 *)(param_1 + 0x9c) = 0;
  uVar4 = (*DAT_0002b90c)(&local_84);
  return -((uVar4 ^ 1) & 0xff);
}


/* ============= FUNCTION: npu_drv_delete_flow @ 00021348 ============= */

undefined4 npu_drv_delete_flow(undefined4 param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  char acStack_44 [16];
  ushort local_34;
  undefined2 local_32;
  ushort uStack_30;
  ushort local_2e;
  undefined2 uStack_2c;
  undefined4 local_2a;
  undefined4 local_26;
  
  if (DAT_0002b90c == 0) {
    return 0xffffffff;
  }
  iVar5 = *(int *)(*(int *)(param_2 + 0x34) + 0x14);
  if (iVar5 == 4) {
    iVar5 = *(int *)(param_2 + 0x10);
    pbVar7 = *(byte **)(param_2 + 0x14);
    bVar1 = *(byte *)(iVar5 + 5);
    bVar2 = *pbVar7;
    __memzero(acStack_44,0x18);
    uVar6 = *(uint *)(iVar5 + (uint)bVar1 + 4);
    local_2e = (ushort)((uVar6 << 0x18) >> 0x10) | (ushort)(uVar6 >> 8) & 0xff;
    uStack_30 = (ushort)((uVar6 >> 0x10 & 0xff) << 8) | (ushort)(byte)(uVar6 >> 0x18);
    strncpy(acStack_44,*(char **)(pbVar7 + bVar2),0xf);
    bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
    if ((bVar1 & 1) == 0) {
      uVar3 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
      local_34 = (uVar3 & 0xf) << 8 | uVar3 >> 8;
    }
    sw_del_igmp_addr_e8v4(acStack_44);
    npu_drv_delete_multivlan(param_1,param_2);
    uVar4 = 0;
  }
  else {
    if (iVar5 == 5) {
      pbVar7 = *(byte **)(param_2 + 0x14);
      bVar1 = *pbVar7;
      iVar5 = *(int *)(param_2 + 0x10) + (uint)*(byte *)(*(int *)(param_2 + 0x10) + 7);
      __memzero(acStack_44,0x22);
      local_2a = *(undefined4 *)(iVar5 + 0x20);
      local_26 = *(undefined4 *)(iVar5 + 0x24);
      local_32 = (undefined2)*(undefined4 *)(iVar5 + 0x18);
      uStack_30 = (ushort)((uint)*(undefined4 *)(iVar5 + 0x18) >> 0x10);
      local_2e = (ushort)*(undefined4 *)(iVar5 + 0x1c);
      uStack_2c = (undefined2)((uint)*(undefined4 *)(iVar5 + 0x1c) >> 0x10);
      strncpy(acStack_44,*(char **)(pbVar7 + bVar1),0xf);
      bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
      if ((bVar1 & 1) == 0) {
        uVar3 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
        local_34 = (uVar3 & 0xf) << 8 | uVar3 >> 8;
      }
      sw_del_mld_addr_e8v4(acStack_44);
      npu_drv_delete_multivlan(param_1,param_2);
      return 0;
    }
    uVar4 = npu_drv_delete_flow_part_1(param_2);
  }
  return uVar4;
}


/* ============= FUNCTION: npu_drv_create_flow.part.2 @ 000214a8 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 npu_drv_create_flow_part_2(int param_1)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  byte *pbVar8;
  char cVar9;
  char *pcVar10;
  byte *pbVar11;
  undefined4 local_d4;
  undefined1 local_d0;
  byte *local_cc;
  byte *local_c8;
  undefined2 local_c4;
  undefined2 local_c2;
  byte local_c0;
  byte local_bf;
  byte *local_bc;
  byte *local_b8;
  undefined2 local_b4;
  undefined2 local_b2;
  byte local_b0;
  byte local_af;
  byte *local_ac;
  byte *local_a8;
  undefined2 local_a4;
  undefined2 local_a2;
  byte local_a0;
  byte local_9f;
  byte *local_9c;
  byte *local_98;
  undefined2 local_94;
  undefined2 local_92;
  byte local_90;
  byte local_8f;
  byte *local_8c;
  byte *local_88;
  undefined2 local_84;
  undefined2 local_82;
  int local_80;
  ushort local_7c;
  undefined1 local_78;
  undefined1 local_77;
  char *local_74;
  int local_70;
  byte *local_6c;
  byte *local_68;
  byte *local_64;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_58;
  undefined4 local_54;
  byte local_50;
  byte local_4f;
  uint local_4c;
  byte *local_48;
  byte *local_44;
  byte local_40;
  byte local_3f;
  char local_3b;
  short local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  __memzero(&local_d4,8);
  __memzero(&local_8c,0x6c);
  if (param_1 == 0) {
    return 0xffffffff;
  }
  pcVar10 = *(char **)(*(byte **)(param_1 + 0x14) + **(byte **)(param_1 + 0x14));
  if (pcVar10 == (char *)0x0) {
    return 0xffffffff;
  }
  iVar3 = strcmp("pon0",pcVar10);
  if (((((iVar3 == 0) || (iVar3 = strcmp("pon",pcVar10), iVar3 == 0)) ||
       (iVar3 = strcmp("gpon0",pcVar10), iVar3 == 0)) ||
      ((iVar3 = strcmp("epon0",pcVar10), iVar3 == 0 || (iVar3 = strcmp("mii1",pcVar10), iVar3 == 0))
      )) || ((iVar3 = strcmp("eth0",pcVar10), iVar3 == 0 ||
             (iVar3 = strcmp("ptm0",pcVar10), iVar3 == 0)))) {
    local_d0 = 1;
  }
  else {
    local_d0 = 0;
  }
  uVar7 = *(uint *)(param_1 + 0x28);
  if ((uVar7 & 0x1c) == 0) {
    if ((uVar7 & 0x700) == 0) {
      if ((uVar7 & 0x60) == 0) {
        return 0xffffffff;
      }
      local_d4 = 2;
    }
    else {
      local_d4 = 1;
    }
  }
  else {
    local_d4 = 0;
  }
  if ((DAT_0002b914 != (code *)0x0) && (iVar3 = (*DAT_0002b914)(&local_d4), iVar3 == 0)) {
    return 0xffffffff;
  }
  __memzero(&local_cc,0x10);
  __memzero(&local_bc,0x10);
  __memzero(&local_ac,0x10);
  __memzero(&local_9c,0x10);
  pbVar11 = *(byte **)(param_1 + 0x14);
  pcVar10 = *(char **)(pbVar11 + *pbVar11);
  if (pcVar10 == (char *)0x0) {
    return 0xffffffff;
  }
  local_74 = pcVar10;
  iVar3 = strcmp("pon0",pcVar10);
  if ((((iVar3 == 0) || (iVar3 = strcmp("pon",pcVar10), iVar3 == 0)) ||
      (iVar3 = strcmp("gpon0",pcVar10), iVar3 == 0)) ||
     (((iVar3 = strcmp("epon0",pcVar10), iVar3 == 0 || (iVar3 = strcmp("mii1",pcVar10), iVar3 == 0))
      || (iVar3 = strcmp("eth0",pcVar10), iVar3 == 0)))) {
    bVar2 = true;
  }
  else {
    iVar3 = strcmp("ptm0",pcVar10);
    bVar2 = iVar3 == 0;
  }
  pcVar10 = local_74;
  pbVar8 = *(byte **)(param_1 + 0x10);
  local_70 = *(int *)(pbVar8 + *pbVar8);
  if (local_70 == 0) {
    return 0xffffffff;
  }
  if ((*(uint *)(param_1 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_1 + 0x28) & 0x2000000) != 0) {
      local_77 = 1;
    }
  }
  else {
    local_78 = 1;
  }
  uVar7 = *(uint *)(param_1 + 0x28);
  if ((uVar7 & 0x1c) == 0) {
    if ((uVar7 & 0x700) != 0) {
      local_80 = 1;
      uVar7 = (uint)pbVar8[7];
      local_a8 = pbVar8 + uVar7 + 0x18;
      local_a0 = pbVar8[uVar7 + 6];
      local_ac = pbVar8 + uVar7 + 8;
      local_9f = pbVar8[uVar7 + 1] >> 4 | pbVar8[uVar7] << 4;
      if (local_a0 == 6) {
        bVar1 = pbVar8[9];
LAB_00021cd4:
        local_a4 = *(undefined2 *)(pbVar8 + bVar1);
        local_a2 = *(undefined2 *)(pbVar8 + bVar1 + 2);
      }
      else {
        if (local_a0 == 0x11) {
          bVar1 = pbVar8[10];
          goto LAB_00021cd4;
        }
        local_a4 = 0;
        local_a2 = 0;
      }
      local_7c = (ushort)local_a0;
      uVar7 = (uint)pbVar11[7];
      local_98 = pbVar11 + uVar7 + 0x18;
      local_90 = pbVar11[uVar7 + 6];
      local_9c = pbVar11 + uVar7 + 8;
      local_8f = pbVar11[uVar7 + 1] >> 4 | pbVar11[uVar7] << 4;
      if (local_90 == 6) {
        bVar1 = pbVar11[9];
LAB_00021cf0:
        local_94 = *(undefined2 *)(pbVar11 + bVar1);
        local_92 = *(undefined2 *)(pbVar11 + bVar1 + 2);
      }
      else {
        if (local_90 == 0x11) {
          bVar1 = pbVar11[10];
          goto LAB_00021cf0;
        }
        local_94 = 0;
        local_92 = local_94;
      }
      local_8c = local_ac;
      local_88 = local_a8;
      local_84 = local_a4;
      local_82 = local_a2;
      if (local_9f != local_8f) {
        local_3f = local_3f | 0x10;
        local_40 = local_8f;
      }
      goto LAB_000218ac;
    }
    if ((uVar7 & 0x60) == 0) {
      return 0xffffffff;
    }
    local_80 = 2;
  }
  else {
    local_80 = 0;
  }
  uVar7 = (uint)pbVar8[5];
  local_cc = *(byte **)(pbVar8 + uVar7);
  local_c0 = pbVar8[uVar7 + 9];
  local_c8 = *(byte **)(pbVar8 + uVar7 + 4);
  local_bf = pbVar8[uVar7 + 8];
  if (local_c0 == 6) {
    bVar1 = pbVar8[9];
LAB_00021ba0:
    local_c4 = *(undefined2 *)(pbVar8 + bVar1);
    local_c2 = *(undefined2 *)(pbVar8 + bVar1 + 2);
  }
  else {
    if (local_c0 == 0x11) {
      bVar1 = pbVar8[10];
      goto LAB_00021ba0;
    }
    local_c4 = 0;
    local_c2 = 0;
  }
  local_7c = (ushort)local_c0;
  uVar7 = (uint)pbVar11[5];
  local_bc = *(byte **)(pbVar11 + uVar7);
  local_b0 = pbVar11[uVar7 + 9];
  local_b8 = *(byte **)(pbVar11 + uVar7 + 4);
  local_af = pbVar11[uVar7 + 8];
  if (local_b0 == 6) {
    bVar1 = pbVar11[9];
LAB_00021bfc:
    local_b4 = *(undefined2 *)(pbVar11 + bVar1);
    local_b2 = *(undefined2 *)(pbVar11 + bVar1 + 2);
  }
  else {
    if (local_b0 == 0x11) {
      bVar1 = pbVar11[10];
      goto LAB_00021bfc;
    }
    local_b4 = 0;
    local_b2 = local_b4;
  }
  if (local_c8 == local_b8) {
    if (local_cc != local_bc) {
      local_60 = local_b4;
      local_54 = 1;
      local_6c = local_bc;
      goto LAB_00021884;
    }
    local_54 = 0;
    if (bVar2) {
      local_60 = local_b4;
      local_6c = local_cc;
      goto LAB_00021c58;
    }
    local_60 = local_b2;
    local_6c = local_c8;
  }
  else {
    if (local_cc != local_bc) {
      return 0xffffffff;
    }
    local_54 = 2;
    local_60 = local_b2;
    local_6c = local_b8;
LAB_00021884:
    if (bVar2) {
LAB_00021c58:
      if (local_80 == 2) {
        uVar7 = (uint)pbVar11[7];
        local_48 = pbVar11 + uVar7 + 8;
        local_44 = pbVar11 + uVar7 + 0x18;
        local_50 = pbVar11[uVar7 + 1] >> 4 | pbVar11[uVar7] << 4;
        local_4c = (uint)CONCAT11(pbVar11[uVar7 + 2],pbVar11[uVar7 + 3]) |
                   (pbVar11[uVar7 + 1] & 0xf) << 0x10;
        local_4f = pbVar11[uVar7 + 7];
      }
    }
  }
  local_8c = local_cc;
  local_88 = local_c8;
  local_84 = local_c4;
  local_82 = local_c2;
  if (local_bf != local_af) {
    local_3f = local_3f | 0x10;
    local_40 = local_af;
  }
LAB_000218ac:
  local_64 = pbVar11 + pbVar11[1] + 6;
  local_68 = pbVar11 + pbVar11[1];
  local_3f = local_3f & 0xfc | pbVar8[3] & 1 ^ 1 | (pbVar11[3] & 1 ^ 1) << 1;
  if ((pbVar8[3] & 1) == 0) {
    local_5c = *(undefined2 *)(pbVar8 + pbVar8[3] + 2);
  }
  else {
    local_5c = 0;
  }
  if ((pbVar11[3] & 1) == 0) {
    local_5e = *(undefined2 *)(pbVar11 + pbVar11[3] + 2);
  }
  else {
    local_5e = 0;
  }
  if (((pbVar8[2] & 1) == 0) && (*(short *)(pbVar8 + pbVar8[2]) != -1)) {
    local_3f = local_3f | 4;
    if ((pbVar8[2] & 1) == 0) {
      local_5a = *(undefined2 *)(pbVar8 + pbVar8[2]);
    }
    else {
      local_5a = 0xffff;
    }
  }
  if (((pbVar11[2] & 1) == 0) && (*(short *)(pbVar11 + pbVar11[2]) != -1)) {
    local_3f = local_3f | 8;
    if ((pbVar11[2] & 1) == 0) {
      local_58 = *(undefined2 *)(pbVar11 + pbVar11[2]);
    }
    else {
      local_58 = 0xffff;
    }
  }
  local_3a = *(short *)(param_1 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_80 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_3a = local_3a + -0x28;
  }
  bVar1 = *pbVar11;
  iVar3 = strcmp("eth0",local_74);
  if (iVar3 == 0) {
    iVar3 = dev_get_by_name(&init_net,&_LC2);
  }
  else {
    iVar3 = dev_get_by_name(&init_net,pcVar10);
  }
  if (iVar3 == 0) {
    local_3b = '\0';
  }
  else {
    iVar4 = __alloc_skb(0x40,0x20,0,0xffffffff);
    if (iVar4 == 0) {
      disableIRQinterrupts();
      iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar4 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar4 + *(int *)(iVar3 + 0x280)) + -1;
      local_3b = '\0';
    }
    else {
      *(undefined4 *)(iVar4 + 0x80) = *(undefined4 *)(pbVar11 + bVar1 + 4);
      iVar5 = CSPKernel_skb_SelectQueue(iVar4,iVar3);
      if (iVar5 - 1U < 8) {
        cVar9 = '\b' - (char)iVar5;
      }
      else if (iVar5 == 0x8f) {
        cVar9 = '\a';
      }
      else {
        cVar9 = '\0';
      }
      disableIRQinterrupts();
      iVar5 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) + -1;
      kfree_skb(iVar4);
      local_3b = cVar9;
    }
  }
  iVar3 = (*npu_hff_func_tbl)(&local_8c);
  if ((iVar3 != 0) &&
     (puVar6 = (undefined4 *)kmem_cache_alloc(_CspGetPortInfo,0x80d0), puVar6 != (undefined4 *)0x0))
  {
    *(undefined4 **)(param_1 + 0x9c) = puVar6;
    *puVar6 = local_38;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 4) = local_34;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 8) = local_30;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0xc) = local_2c;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x10) = local_28;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x14) = local_24;
    return 0;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: npu_drv_create_flow @ 00021d10 ============= */

undefined4 npu_drv_create_flow(undefined4 param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  char acStack_44 [16];
  ushort local_34;
  undefined2 local_32;
  ushort uStack_30;
  ushort local_2e;
  undefined2 uStack_2c;
  undefined4 local_2a;
  undefined4 local_26;
  
  if (npu_hff_func_tbl == 0) {
    return 0xffffffff;
  }
  iVar5 = *(int *)(*(int *)(param_2 + 0x34) + 0x14);
  if (iVar5 == 4) {
    iVar5 = *(int *)(param_2 + 0x10);
    pbVar7 = *(byte **)(param_2 + 0x14);
    bVar1 = *(byte *)(iVar5 + 5);
    bVar2 = *pbVar7;
    __memzero(acStack_44,0x18);
    uVar6 = *(uint *)(iVar5 + (uint)bVar1 + 4);
    local_2e = (ushort)((uVar6 << 0x18) >> 0x10) | (ushort)(uVar6 >> 8) & 0xff;
    uStack_30 = (ushort)((uVar6 >> 0x10 & 0xff) << 8) | (ushort)(byte)(uVar6 >> 0x18);
    strncpy(acStack_44,*(char **)(pbVar7 + bVar2),0xf);
    bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
    if ((bVar1 & 1) == 0) {
      uVar3 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
      local_34 = (uVar3 & 0xf) << 8 | uVar3 >> 8;
    }
    sw_add_igmp_addr_e8v4(acStack_44);
    npu_drv_create_multivlan(param_1,param_2);
    uVar4 = 0;
  }
  else {
    if (iVar5 == 5) {
      pbVar7 = *(byte **)(param_2 + 0x14);
      bVar1 = *pbVar7;
      iVar5 = *(int *)(param_2 + 0x10) + (uint)*(byte *)(*(int *)(param_2 + 0x10) + 7);
      __memzero(acStack_44,0x22);
      local_2a = *(undefined4 *)(iVar5 + 0x20);
      local_26 = *(undefined4 *)(iVar5 + 0x24);
      local_32 = (undefined2)*(undefined4 *)(iVar5 + 0x18);
      uStack_30 = (ushort)((uint)*(undefined4 *)(iVar5 + 0x18) >> 0x10);
      local_2e = (ushort)*(undefined4 *)(iVar5 + 0x1c);
      uStack_2c = (undefined2)((uint)*(undefined4 *)(iVar5 + 0x1c) >> 0x10);
      strncpy(acStack_44,*(char **)(pbVar7 + bVar1),0xf);
      bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 2);
      if ((bVar1 & 1) == 0) {
        uVar3 = *(ushort *)(*(int *)(param_2 + 0x10) + (uint)bVar1);
        local_34 = (uVar3 & 0xf) << 8 | uVar3 >> 8;
      }
      sw_add_mld_addr_e8v4(acStack_44);
      npu_drv_create_multivlan(param_1,param_2);
      return 0;
    }
    uVar4 = npu_drv_create_flow_part_2(param_2);
  }
  return uVar4;
}


/* ============= FUNCTION: sw_update_match_rule_ip @ 00021e70 ============= */

void sw_update_match_rule_ip(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 uStack_1b8;
  undefined1 local_1b2;
  undefined1 local_1b1;
  undefined1 local_1b0;
  undefined1 local_1af;
  undefined1 local_1ae;
  undefined1 local_1ad;
  undefined2 local_1ac;
  undefined2 local_1aa;
  undefined4 auStack_1a8 [12];
  undefined4 local_178 [23];
  uint local_11c;
  uint local_fc;
  
  memcpy(local_178,&_LANCHOR0,0x160);
  puVar7 = DAT_00021f64;
  puVar6 = &uStack_1b8;
  do {
    puVar8 = puVar7 + 4;
    uVar1 = puVar7[1];
    uVar2 = puVar7[2];
    uVar3 = puVar7[3];
    puVar6[4] = *puVar7;
    puVar6[5] = uVar1;
    puVar6[6] = uVar2;
    puVar6[7] = uVar3;
    puVar7 = puVar8;
    puVar6 = puVar6 + 4;
  } while (puVar8 != DAT_00021f64 + 0xc);
  local_11c = param_1 >> 0x10;
  local_fc = param_1 & 0xffff;
  puVar6 = local_178;
  do {
    __memzero(&local_1b2,10);
    puVar7 = puVar6 + 8;
    local_1b2 = (undefined1)*puVar6;
    local_1b1 = (undefined1)puVar6[1];
    local_1b0 = (undefined1)puVar6[2];
    local_1af = (undefined1)puVar6[3];
    local_1ae = (undefined1)puVar6[4];
    local_1ad = (undefined1)puVar6[5];
    local_1ac = (undefined2)puVar6[6];
    local_1aa = (undefined2)puVar6[7];
    spa_set_matchram(&local_1b2);
    puVar6 = puVar7;
  } while (puVar7 != (undefined4 *)&stack0xffffffe8);
  puVar6 = auStack_1a8;
  iVar4 = 0;
  do {
    iVar5 = iVar4 + 1;
    spa_set_hashram(iVar4,puVar6);
    puVar6 = (undefined4 *)((int)puVar6 + 6);
    iVar4 = iVar5;
  } while (iVar5 != 8);
  return;
}


/* ============= FUNCTION: sw_set_trap_cpu_ip @ 00021f68 ============= */

undefined4 sw_set_trap_cpu_ip(int *param_1)

{
  if (*param_1 != 0) {
    sw_update_match_rule_ip();
    return 0;
  }
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][sw_set_trap_cpu_ip] input ERROR: ip is zero\n");
  return 0xffffffff;
}


/* ============= FUNCTION: init_module @ 00021fb4 ============= */

undefined4 init_module(void)

{
  printk("Init switch module\n");
  sw_init_switch();
  public_capfun_register();
  private_capfun_register();
  printk("Init personal switch module Success\n");
  return 0;
}


/* ============= FUNCTION: cleanup_module @ 00021fe4 ============= */

void cleanup_module(void)

{
  l3_hardfastUnReg();
  fuc_table_node_clear();
  return;
}


/* ============= FUNCTION: turn_flash_led.part.1 @ 00021ff4 ============= */

void turn_flash_led_part_1(void)

{
  printk("[%s] L%d tm sdk failed!\n","turn_flash_led",0x1db);
  return;
}


/* ============= FUNCTION: zte_api_sw_port_get_port_loopback @ 0002c000 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_loopback(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_ipv6table_delete_set @ 0002c004 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_ipv6table_delete_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: alloc_etherdev_mqs @ 0002c008 ============= */

/* WARNING: Control flow encountered bad instruction data */

void alloc_etherdev_mqs(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_clear_macaddress @ 0002c00c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_clear_macaddress(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strcpy @ 0002c014 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strcpy(char *__dest,char *__src)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: Kernel_ASEND @ 0002c018 ============= */

/* WARNING: Control flow encountered bad instruction data */

void Kernel_ASEND(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_flowcontrol @ 0002c01c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_flowcontrol(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: rtnl_unlock @ 0002c020 ============= */

/* WARNING: Control flow encountered bad instruction data */

void rtnl_unlock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: aclEssidToWlanIDMMap2 @ 0002c024 ============= */

/* WARNING: Control flow encountered bad instruction data */

void aclEssidToWlanIDMMap2(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_ratelimit @ 0002c028 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_ratelimit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: npu_register_driver @ 0002c02c ============= */

/* WARNING: Control flow encountered bad instruction data */

void npu_register_driver(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_ipv6table_add_set @ 0002c030 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_ipv6table_add_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_unknwn_multicast_flood_set @ 0002c034 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_unknwn_multicast_flood_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_public_port_cfg_func_reg @ 0002c038 ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_public_port_cfg_func_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_global_init @ 0002c03c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_global_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_set_onu_stpaction @ 0002c040 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_set_onu_stpaction(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_vlan_set_port_inframemode @ 0002c044 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_vlan_set_port_inframemode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_statistics1 @ 0002c04c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_statistics1(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: unregister_netdev @ 0002c050 ============= */

/* WARNING: Control flow encountered bad instruction data */

void unregister_netdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_statistics @ 0002c054 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_statistics(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_mirror @ 0002c058 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_mirror(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: fuc_table_node_clear @ 0002c05c ============= */

/* WARNING: Control flow encountered bad instruction data */

void fuc_table_node_clear(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_set_onu_agingtime @ 0002c060 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_set_onu_agingtime(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_802x_authen_get @ 0002c064 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_802x_authen_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_vlan_set_port_vlancfg @ 0002c068 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_vlan_set_port_vlancfg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __printk_ratelimit @ 0002c06c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __printk_ratelimit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_public_onu_other_func_reg @ 0002c070 ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_public_onu_other_func_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_fast_l3_session_del @ 0002c074 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_fast_l3_session_del(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_onu_mac_addr_set @ 0002c078 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_onu_mac_addr_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_qos_get_availbktid @ 0002c07c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_qos_get_availbktid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: memcpy @ 0002c080 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kfree @ 0002c084 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kfree(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_linkstate @ 0002c088 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_linkstate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_mac_learning_number_get @ 0002c08c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_mac_learning_number_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_vlan_filter_get @ 0002c094 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_vlan_filter_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_unknwn_multicast_floodport_set @ 0002c09c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_unknwn_multicast_floodport_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_set_p2pmode @ 0002c0a0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_set_p2pmode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_set_port_macfiltermode @ 0002c0a4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_set_port_macfiltermode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_vlan_get_port_inframemode @ 0002c0a8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_vlan_get_port_inframemode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_isolatemask @ 0002c0ac ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_isolatemask(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_public_onu_statistics_func_reg @ 0002c0b0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_public_onu_statistics_func_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_qos_add_port_streamselect @ 0002c0b4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_qos_add_port_streamselect(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_ipv4table_add_set @ 0002c0b8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_ipv4table_add_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_public_port_vlan_func_reg @ 0002c0bc ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_public_port_vlan_func_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: msleep_interruptible @ 0002c0c0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void msleep_interruptible(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_pp_global_init @ 0002c0c8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_pp_global_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: wake_up_process @ 0002c0cc ============= */

/* WARNING: Control flow encountered bad instruction data */

void wake_up_process(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_tcont_que_sch_weight_get @ 0002c0d0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_tcont_que_sch_weight_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_set_port_learnlimit @ 0002c0d4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_set_port_learnlimit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_vlan_check_ena_set @ 0002c0d8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_vlan_check_ena_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_broadcst_vltrans_table_print_get @ 0002c0dc ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_broadcst_vltrans_table_print_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_pp_set_cpu_queue_rate @ 0002c0e0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_pp_set_cpu_queue_rate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: eth_type_trans @ 0002c0e4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void eth_type_trans(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_enable @ 0002c0f4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_enable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_clear_port_count @ 0002c0f8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_clear_port_count(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: aclWlanToIdmReset @ 0002c0fc ============= */

/* WARNING: Control flow encountered bad instruction data */

void aclWlanToIdmReset(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_statistics4 @ 0002c100 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_statistics4(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_statistics3 @ 0002c104 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_statistics3(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kfree_skb @ 0002c108 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kfree_skb(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: ___ratelimit @ 0002c10c ============= */

/* WARNING: Control flow encountered bad instruction data */

void ___ratelimit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_mactable_add_set @ 0002c110 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_mactable_add_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_tls_get @ 0002c114 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_tls_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: msecs_to_jiffies @ 0002c118 ============= */

/* WARNING: Control flow encountered bad instruction data */

void msecs_to_jiffies(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_unlock_bh @ 0002c11c ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_unlock_bh(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_get_port_learnlimit @ 0002c120 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_get_port_learnlimit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: spa_set_hashram @ 0002c124 ============= */

/* WARNING: Control flow encountered bad instruction data */

void spa_set_hashram(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_vlan_statistics @ 0002c128 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_vlan_statistics(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __alloc_skb @ 0002c12c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __alloc_skb(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_clear_port_mactable @ 0002c130 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_clear_port_mactable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_status_set @ 0002c134 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_status_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_init @ 0002c138 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: dev_queue_xmit_sk @ 0002c13c ============= */

/* WARNING: Control flow encountered bad instruction data */

void dev_queue_xmit_sk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kmem_cache_alloc @ 0002c140 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kmem_cache_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_qos_get_port_streamselect @ 0002c144 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_qos_get_port_streamselect(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: ffe_receive_skb @ 0002c148 ============= */

/* WARNING: Control flow encountered bad instruction data */

void ffe_receive_skb(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: capable @ 0002c14c ============= */

/* WARNING: Control flow encountered bad instruction data */

void capable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_receive_skb_sk @ 0002c150 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_receive_skb_sk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_linkmode @ 0002c154 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_linkmode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: CspGetSwInfo @ 0002c158 ============= */

/* WARNING: Control flow encountered bad instruction data */

void CspGetSwInfo(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_dft_multicst_vltrans_get @ 0002c15c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_dft_multicst_vltrans_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_qos_get_port_schedule @ 0002c160 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_qos_get_port_schedule(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_enable @ 0002c164 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_enable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_del_port_macfilterentry @ 0002c168 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_del_port_macfilterentry(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_unknwn_multicast_fwd_set @ 0002c16c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_unknwn_multicast_fwd_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_hash_mode_set @ 0002c170 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_hash_mode_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_public_onu_qos_func_reg @ 0002c174 ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_public_onu_qos_func_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_set_onu_proaction @ 0002c178 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_set_onu_proaction(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_vlan_get_port_vlancfg @ 0002c180 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_vlan_get_port_vlancfg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_add_port_macfilterentry @ 0002c184 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_add_port_macfilterentry(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_mac_ramaddr_sel_get @ 0002c188 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_mac_ramaddr_sel_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_qos_del_port_streamselect @ 0002c18c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_qos_del_port_streamselect(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_floodcontrolmask @ 0002c190 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_floodcontrolmask(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strncmp @ 0002c194 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strncmp(char *__s1,char *__s2,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: register_netdev @ 0002c198 ============= */

/* WARNING: Control flow encountered bad instruction data */

void register_netdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_protocol_pktdeal_get @ 0002c19c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_protocol_pktdeal_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strncpy @ 0002c1a0 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strncpy(char *__dest,char *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_set_port_brdcast @ 0002c1a8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_set_port_brdcast(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_get_pon_port @ 0002c1ac ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_get_pon_port(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: free_netdev @ 0002c1b0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void free_netdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_set_port_unicast @ 0002c1b4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_set_port_unicast(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_mactable_print_get @ 0002c1b8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_mactable_print_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_protocol_pkt_limit_pps_set @ 0002c1bc ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_protocol_pkt_limit_pps_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: memcmp @ 0002c1c0 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int memcmp(void *__s1,void *__s2,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sysfs_create_group @ 0002c1c4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void sysfs_create_group(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sscanf @ 0002c1c8 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sscanf(char *__s,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: printk @ 0002c1cc ============= */

/* WARNING: Control flow encountered bad instruction data */

void printk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_qos_set_port_schedule @ 0002c1d4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_qos_set_port_schedule(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_broadcst_vltrans_table_delete_set @ 0002c1d8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_broadcst_vltrans_table_delete_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_del_port_macaddress @ 0002c1dc ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_del_port_macaddress(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_fast_entry_policy @ 0002c1e0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_fast_entry_policy(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_phy_read @ 0002c1e4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_phy_read(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_dft_unkunicst_vltrans_set @ 0002c1e8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_dft_unkunicst_vltrans_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: LedActionSet @ 0002c1ec ============= */

/* WARNING: Control flow encountered bad instruction data */

void LedActionSet(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: fpga_write_reg @ 0002c1f0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void fpga_write_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_set_port_muticast @ 0002c1f4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_set_port_muticast(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __memzero @ 0002c1f8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __memzero(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_statistics2 @ 0002c1fc ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_statistics2(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_acl_l2_fast_init @ 0002c200 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_acl_l2_fast_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: CSPKernel_skb_SelectQueue @ 0002c204 ============= */

/* WARNING: Control flow encountered bad instruction data */

void CSPKernel_skb_SelectQueue(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_rx @ 0002c208 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_rx(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strcmp @ 0002c210 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strcmp(char *__s1,char *__s2)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_hash_mode_get @ 0002c218 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_hash_mode_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kthread_create_on_node @ 0002c21c ============= */

/* WARNING: Control flow encountered bad instruction data */

void kthread_create_on_node(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sprintf @ 0002c220 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sprintf(char *__s,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_flowcontrol @ 0002c224 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_flowcontrol(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_tcont_que_sch_sp_dwwr_mod_get @ 0002c228 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_tcont_que_sch_sp_dwwr_mod_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_public_onu_mactable_func_reg @ 0002c22c ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_public_onu_mactable_func_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_multicastrate @ 0002c230 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_multicastrate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_tcont_sharp_set @ 0002c234 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_tcont_sharp_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_add_port_macaddress @ 0002c238 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_add_port_macaddress(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_multicst_vltrans_table_delete_set @ 0002c23c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_multicst_vltrans_table_delete_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: aclWLANToIDMEssidCfg2 @ 0002c240 ============= */

/* WARNING: Control flow encountered bad instruction data */

void aclWLANToIDMEssidCfg2(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_dft_broadcst_vltrans_set @ 0002c244 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_dft_broadcst_vltrans_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_flow_rate_limit_set @ 0002c248 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_flow_rate_limit_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __dev_kfree_skb_any @ 0002c24c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __dev_kfree_skb_any(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: ffe_learn_skb @ 0002c250 ============= */

/* WARNING: Control flow encountered bad instruction data */

void ffe_learn_skb(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: register_bridge_notifier @ 0002c254 ============= */

/* WARNING: Control flow encountered bad instruction data */

void register_bridge_notifier(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_get_wlan_port @ 0002c258 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_get_wlan_port(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_carrier_off @ 0002c25c ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_carrier_off(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_phy_write @ 0002c260 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_phy_write(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_vlan_filter_set @ 0002c264 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_vlan_filter_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_dft_multicst_vltrans_set @ 0002c268 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_dft_multicst_vltrans_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_ipv4table_lookup_get @ 0002c26c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_ipv4table_lookup_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_broadcastrate @ 0002c270 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_broadcastrate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_ipv6table_lookup_get @ 0002c274 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_ipv6table_lookup_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_public_port_ratelimit_func_reg @ 0002c278 ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_public_port_ratelimit_func_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: dev_get_by_name @ 0002c27c ============= */

/* WARNING: Control flow encountered bad instruction data */

void dev_get_by_name(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: fuc_table_node_create @ 0002c280 ============= */

/* WARNING: Control flow encountered bad instruction data */

void fuc_table_node_create(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_vlan_get_port_pvid @ 0002c284 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_vlan_get_port_pvid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_lock_bh @ 0002c288 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_lock_bh(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_tcont_secsch_hang_que_set @ 0002c28c ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_tcont_secsch_hang_que_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_carrier_on @ 0002c290 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_carrier_on(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_ipv4table_delete_set @ 0002c294 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_ipv4table_delete_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_pp_set_pro_action @ 0002c298 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_pp_set_pro_action(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_fast_l3_session_use @ 0002c29c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_fast_l3_session_use(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_cla_outspace_cfg_set @ 0002c2a0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_cla_outspace_cfg_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_other_set_onu_mtu @ 0002c2a4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_other_set_onu_mtu(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: rtnl_lock @ 0002c2a8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void rtnl_lock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_tcont_que_sch_sp_dwwr_mod_set @ 0002c2ac ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_tcont_que_sch_sp_dwwr_mod_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_pp_set_trap_queue @ 0002c2b0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_pp_set_trap_queue(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: spa_set_matchram @ 0002c2b4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void spa_set_matchram(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: fpga_read_reg @ 0002c2b8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void fpga_read_reg(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_dft_unkunicst_vltrans_get @ 0002c2bc ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_dft_unkunicst_vltrans_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_tls_set @ 0002c2c0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_tls_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_mactable_delete_set @ 0002c2c4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_mactable_delete_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_get_port_broadcastrate @ 0002c2c8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_get_port_broadcastrate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_linkmode @ 0002c2cc ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_linkmode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_loopback @ 0002c2d4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_loopback(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_mirror @ 0002c2d8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_mirror(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_ratelimit @ 0002c2dc ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_ratelimit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: IfName2WlanIdmMap @ 0002c2e0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void IfName2WlanIdmMap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_broadcst_vltrans_table_add_set @ 0002c2e4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_broadcst_vltrans_table_add_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_set_port_multicastrate @ 0002c2e8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_set_port_multicastrate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_vlan_set_port_pvid @ 0002c2ec ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_vlan_set_port_pvid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: dev_change_flags @ 0002c2f0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void dev_change_flags(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_vlan_stat_config @ 0002c2f4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_vlan_stat_config(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_protocol_pktdeal_set @ 0002c2f8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_protocol_pktdeal_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_multicst_vltrans_table_add_set @ 0002c2fc ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_multicst_vltrans_table_add_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_port_clear_count_by_portid @ 0002c300 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_port_clear_count_by_portid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_cla_outspace_cfg_get @ 0002c304 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_cla_outspace_cfg_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_sw_mac_get_onu_agingtime @ 0002c308 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_sw_mac_get_onu_agingtime(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __aeabi_idivmod @ 0002c30c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __aeabi_idivmod(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: msleep @ 0002c310 ============= */

/* WARNING: Control flow encountered bad instruction data */

void msleep(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_tcont_que_sch_weight_set @ 0002c318 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_tcont_que_sch_weight_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_api_fast_l3_session_add @ 0002c31c ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_api_fast_l3_session_add(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_dft_broadcst_vltrans_get @ 0002c320 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_dft_broadcst_vltrans_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: tm_port_802x_authen_set @ 0002c324 ============= */

/* WARNING: Control flow encountered bad instruction data */

void tm_port_802x_authen_set(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: CspGetPortInfo @ 0002c328 ============= */

/* WARNING: Control flow encountered bad instruction data */

void CspGetPortInfo(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


