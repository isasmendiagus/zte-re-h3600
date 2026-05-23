// module: switch.ko
// function: pdt_ethdrv_recv @ 0x109c8
// size: 1896 bytes
//

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

