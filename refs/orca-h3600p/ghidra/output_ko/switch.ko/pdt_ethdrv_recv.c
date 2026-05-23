// module: switch.ko
// function: pdt_ethdrv_recv @ 0x109c8
// size: 1484 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 pdt_ethdrv_recv(int param_1)

{
  ushort uVar1;
  uint uVar2;
  undefined2 uVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  void *__s1;
  int extraout_r1;
  uint uVar7;
  uint uVar8;
  int iVar9;
  bool bVar10;
  undefined1 local_2a;
  undefined1 local_29;
  undefined1 auStack_28 [20];
  
  local_2a = 0;
  local_29 = 0;
  if (param_1 == 0) {
    if (g_eth_err_print != '\x01') {
      return 0xffffffff;
    }
    iVar4 = __printk_ratelimit("pdt_ethdrv_recv");
    if (iVar4 != 0) {
      printk("Error! skb == NULL @func %s %d\n","pdt_ethdrv_recv",0x1b7);
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  uVar7 = (uint)g_debug_mode;
  if (uVar7 == 7) {
    if (*(short *)(*(int *)(param_1 + 0xd4) + 0xc) == 0x81) {
      uVar1 = *(ushort *)(*(int *)(param_1 + 0xd4) + 0xe);
      uVar7 = (uint)(uVar1 >> 8);
      uVar2 = (uVar1 & 0xff) << 8;
      uVar8 = uVar2 & 0xfff | uVar7;
      g_eth_vlan = (ushort)(((uVar2 | uVar7) << 0x14) >> 0x14);
    }
    else {
      uVar8 = 0xfff;
      g_eth_vlan = 0xfff;
    }
    if (g_eth_debug_vlan != uVar8) goto LAB_00010a1c;
LAB_00010b18:
    printk("debbug skb @:====  %s   ===\n","pdt_ethdrv_recv");
    uVar7 = 0;
    printk("skb->dev->name = %s,skb->len = %d \n",*(undefined4 *)(param_1 + 0x18),
           *(undefined4 *)(param_1 + 100));
    printk("skbinfo: port %d\n",*(undefined1 *)(param_1 + 0xbc));
    while (uVar7 < *(uint *)(param_1 + 100)) {
      printk("%02x ",*(undefined1 *)(*(int *)(param_1 + 0xd4) + uVar7));
      __aeabi_idivmod(uVar7,0xc);
      bVar10 = uVar7 != 0;
      uVar7 = uVar7 + 1;
      if (bVar10 && extraout_r1 == 0xb) {
        printk(&_LC6);
      }
    }
    printk(&_LC6);
  }
  else {
    if (uVar7 - 1 < 2) goto LAB_00010b18;
    if (uVar7 == 4) {
      __s1 = *(void **)(param_1 + 0xd4);
      iVar4 = memcmp((void *)((int)__s1 + 6),&g_eth_debug_mac,6);
      if (iVar4 != 0) {
LAB_00010d6c:
        iVar4 = memcmp(__s1,&g_eth_debug_mac,6);
        if (iVar4 != 0) goto LAB_00010a1c;
      }
      goto LAB_00010b18;
    }
    if (uVar7 == 6) {
      iVar4 = memcmp((void *)(*(int *)(param_1 + 0xd4) + 6),&g_eth_debug_mac,6);
      if (iVar4 == 0) goto LAB_00010b18;
    }
    else if (uVar7 == 5) {
      __s1 = *(void **)(param_1 + 0xd4);
      goto LAB_00010d6c;
    }
  }
LAB_00010a1c:
  iVar4 = jiffies;
  if (**(char **)(param_1 + 0x18) == 'p') {
    if (g_debug_ratelimit_action != '\0') {
      if (g_timestamp_1 == 0) {
        g_timestamp_1 = jiffies;
      }
      g_rev_packet_100ms = g_rev_packet_100ms + 1;
      if (g_debug_ratelimit_maxinum < g_rev_packet_100ms) {
        g_timestamp_2 = jiffies;
        iVar9 = msecs_to_jiffies(1000);
        if ((iVar4 - g_timestamp_1) - iVar9 < 0) goto LAB_00010ecc;
        g_timestamp_1 = jiffies;
        g_rev_packet_100ms = 0;
      }
    }
    iVar4 = ffe_receive_skb(param_1,3);
    if ((iVar4 != 0) && ((g_pon_work_mode & 0x10) != 0)) {
      *(undefined4 *)(param_1 + 0x18) =
           *(undefined4 *)
            (g_sw_netInfo +
            (uint)(byte)zte_api_sw_vlan_get_port_inframemode[_zte_api_sw_mac_set_port_learnlimit] *
            4 + 4);
      piVar5 = (int *)ethdrv_port_dev_get_stats();
      *piVar5 = *piVar5 + 1;
      piVar5[2] = piVar5[2] + *(int *)(param_1 + 100);
      uVar3 = eth_type_trans(param_1,*(undefined4 *)(param_1 + 0x18));
      iVar4 = jiffies;
      *(undefined2 *)(param_1 + 0xac) = uVar3;
      *(int *)(*(int *)(param_1 + 0x18) + 0x1d8) = iVar4;
      if ((*(byte *)(param_1 + 0x74) & 7) == 2) {
        piVar5[8] = piVar5[8] + 1;
      }
      uVar6 = netif_receive_skb_sk(*(undefined4 *)(param_1 + 0x14),param_1);
      return uVar6;
    }
  }
  else {
    uVar7 = (uint)*(byte *)(param_1 + 0xbc);
    if ((_tm_tcont_que_sch_weight_get & 1 << uVar7) == 0) {
      iVar4 = aclEssidToWlanIDMMap2(uVar7 + 1 & 0xff,&local_2a,&local_29,auStack_28);
      if (iVar4 == 0) {
        iVar4 = dev_get_by_name(&init_net,auStack_28);
        if ((iVar4 != 0) && (*(char *)(iVar4 + 0x294) != '\0')) {
          *(int *)(param_1 + 0x18) = iVar4;
          iVar9 = ffe_receive_skb(param_1,3);
          if (iVar9 == 0) {
            disableIRQinterrupts();
            iVar9 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
            *(int *)(iVar9 + *(int *)(iVar4 + 0x280)) =
                 *(int *)(iVar9 + *(int *)(iVar4 + 0x280)) + -1;
            return 0;
          }
          uVar3 = eth_type_trans(param_1,iVar4);
          iVar9 = jiffies;
          *(undefined2 *)(param_1 + 0xac) = uVar3;
          *(int *)(*(int *)(param_1 + 0x18) + 0x1d8) = iVar9;
          netif_rx(param_1);
          disableIRQinterrupts();
          iVar9 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar9 + *(int *)(iVar4 + 0x280)) = *(int *)(iVar9 + *(int *)(iVar4 + 0x280)) + -1
          ;
          return 0;
        }
        __dev_kfree_skb_any(param_1,1);
        if (g_eth_err_print != '\x01') {
          return 0xffffffff;
        }
        iVar4 = __printk_ratelimit("pdt_ethdrv_recv");
        if (iVar4 == 0) {
          return 0xffffffff;
        }
        printk("pdt_ethdrv_recv meet error pdev==NULL || pdev->reg_state== 0,when dev_name = %s\n",
               auStack_28);
        return 0xffffffff;
      }
      if ((g_eth_err_print == '\x01') && (iVar4 = __printk_ratelimit("pdt_ethdrv_recv"), iVar4 != 0)
         ) {
        printk("Error! skb->port = %d @func %s %d\n",*(undefined1 *)(param_1 + 0xbc),
               "pdt_ethdrv_recv",0x2b6);
      }
LAB_00010ecc:
      __dev_kfree_skb_any(param_1,1);
      return 0xffffffff;
    }
    iVar9 = *(int *)(g_sw_netInfo + (uint)(byte)zte_api_sw_vlan_get_port_inframemode[uVar7] * 4 + 4)
    ;
    *(int *)(param_1 + 0x18) = iVar9;
    iVar4 = ffe_receive_skb(param_1,3);
    if (iVar4 != 0) {
      if (iVar9 == 0) {
        __dev_kfree_skb_any(param_1,1);
        return 0;
      }
      piVar5 = (int *)ethdrv_port_dev_get_stats(iVar9);
      *piVar5 = *piVar5 + 1;
      piVar5[2] = piVar5[2] + *(int *)(param_1 + 100);
      uVar3 = eth_type_trans(param_1,iVar9);
      *(int *)(param_1 + 0x18) = iVar9;
      iVar4 = jiffies;
      *(undefined2 *)(param_1 + 0xac) = uVar3;
      *(int *)(iVar9 + 0x1d8) = iVar4;
      if ((*(byte *)(param_1 + 0x74) & 7) == 2) {
        piVar5[8] = piVar5[8] + 1;
      }
      netif_receive_skb_sk(*(undefined4 *)(param_1 + 0x14),param_1);
    }
  }
  return 0;
}

