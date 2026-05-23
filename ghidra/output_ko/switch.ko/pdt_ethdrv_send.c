// module: switch.ko
// function: pdt_ethdrv_send @ 0x11130
// size: 972 bytes
//

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
    iVar4 = __printk_ratelimit("pdt_ethdrv_send");
    if (iVar4 == 0) {
      return 0;
    }
    printk("Error! skb == NULL @func %s %d\n","pdt_ethdrv_send",0x2cd);
    return 0;
  }
  if (param_2 == 0) {
    if ((g_eth_err_print == '\x01') && (iVar4 = __printk_ratelimit("pdt_ethdrv_send"), iVar4 != 0))
    {
      printk("Error! dev == NULL @func %s %d\n","pdt_ethdrv_send",0x2d2);
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
    printk("debbug skb @:====  %s   ===\n","pdt_ethdrv_send");
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

