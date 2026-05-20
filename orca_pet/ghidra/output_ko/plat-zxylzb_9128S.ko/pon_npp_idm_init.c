// module: plat-zxylzb_9128S.ko
// function: pon_npp_idm_init @ 0x15dcc
// size: 1040 bytes
//

int pon_npp_idm_init(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  
  idm_netdev._4_4_ = idm_net_register(1,&_LC47);
  if (idm_netdev._4_4_ == 0) {
    iVar4 = -1;
    printk("failed to register idm1 net\n");
  }
  else {
    idm_netdev._0_4_ = idm_net_register(0,&_LC37);
    if ((int)idm_netdev == 0) {
      iVar4 = -1;
      printk("failed to register idm0 net\n");
    }
    else {
      netif_napi_add((int)idm_netdev,(int)idm_netdev + 0x528,idm_net_poll,0xff);
      *(undefined4 *)(npp_base + 0x8024) = 0x1f;
      idm_int_mask = 0x1f;
      *(undefined4 *)(npp_base + 0x8018) = 0x40;
      *(undefined4 *)(npp_base + 0x801c) = 5000;
      *(undefined4 *)(npp_base + 0x8010) = 0x40;
      *(uint *)(npp_base + 0x8000) = *(uint *)(npp_base + 0x8000) | 0xf0000;
      *(uint *)(npp_base + 0x8000) = *(uint *)(npp_base + 0x8000) & 0xf00fffff | 0x2000000;
      iVar4 = (int)idm_netdev;
      idm_creat_status_proc();
      pcVar1 = "failed to register idm1 net\n" + pp_base + 4;
      pcVar1[0] = '@';
      pcVar1[1] = '\x06';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      idm_desc_addr._0_4_ = (*arm_dma_ops)(0,0x6020,0x2ed2c,0xd0,0);
      if (((uint)idm_desc_addr == 0) || (((uint)idm_desc_addr & 0x1f) != 0)) {
        iVar4 = -1;
      }
      else {
        *(undefined4 *)(npp_base + 0x80c0) = 0;
        printk("idm_desc_init %x/%x\n",(uint)idm_desc_addr,idm_desc_addr._4_4_);
        *(int *)(npp_base + 0x8008) = idm_desc_addr._4_4_;
        *(int *)(npp_base + 0x8004) = idm_desc_addr._4_4_ + 0x4000;
        rx_desc = (int *)(idm_desc_addr._4_4_ + -0x80000000);
        __memzero(rx_desc,0x6000);
        piVar5 = rx_desc + 0x1000;
        piVar7 = rx_desc;
        tx_desc = piVar5;
        do {
          iVar2 = _idm_skb_stack_pop(0);
          if (iVar2 == 0) {
            iVar2 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
            if (iVar2 == 0) {
              printk("idm failed to alloc skb\n");
              return -1;
            }
            *(int *)(iVar2 + 0x18) = iVar4;
            *(int *)(iVar2 + 0xd4) = *(int *)(iVar2 + 0xd4) + 0x20;
            *(int *)(iVar2 + 200) = *(int *)(iVar2 + 200) + 0x20;
          }
          iVar8 = *(int *)(iVar2 + 0xd4);
          iVar3 = (int)piVar7 - (int)rx_desc;
          *(int *)(iVar2 + 0xd4) = iVar8 + 0x20;
          *(int *)(iVar2 + 200) = *(int *)(iVar2 + 200) + 0x20;
          piVar6 = piVar7 + 2;
          *piVar7 = iVar8 + -0x7fffffe0;
          iVar8 = npp_base;
          *(int *)(skb_rq + (iVar3 >> 3) * 4) = iVar2;
          *(ushort *)(iVar2 + 0xc4) = *(ushort *)(iVar2 + 0xc4) | 0x10;
          *(undefined4 *)(iVar8 + 0x8048) = 0x10000;
          piVar7 = piVar6;
        } while (piVar5 != piVar6);
        idm_rx_index = 0;
        idm_tx_index = 0;
        idm_tx_done = 0;
        *(undefined4 *)(npp_base + 0x800c) = 0x4000800;
        iVar2 = 0x200;
        do {
          iVar8 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
          if (iVar8 == 0) {
            printk("idm failed to alloc skb\n");
            break;
          }
          *(int *)(iVar8 + 0x18) = iVar4;
          *(int *)(iVar8 + 0xd4) = *(int *)(iVar8 + 0xd4) + 0x20;
          *(int *)(iVar8 + 200) = *(int *)(iVar8 + 200) + 0x20;
          _idm_skb_stack_push(iVar8,0);
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        hwnat_set_hook_ptr();
        iVar4 = 0;
        init_timer_key(idm_timer,0,0,0);
        idm_timer._20_4_ = 0;
        idm_timer._8_4_ = jiffies + 100;
        idm_timer._16_4_ = idm_timer_func;
        add_timer(idm_timer);
        iVar2 = request_threaded_irq(g_idm_irq,idm_net_int,0,0,&_LC43,0);
        if (iVar2 < 0) {
          printk("request idm irq failed\n");
          return iVar2;
        }
        printk("request idm irq succeed \n");
        idm_net_check_speed = 0;
        printk("idm net init ok\n");
      }
    }
  }
  return iVar4;
}

