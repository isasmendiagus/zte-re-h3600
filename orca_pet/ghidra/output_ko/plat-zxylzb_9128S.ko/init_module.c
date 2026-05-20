// module: plat-zxylzb_9128S.ko
// function: init_module @ 0x1d9a8
// size: 1292 bytes
//

int init_module(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  printk("pon init\n");
  bp_max_number._0_4_ = u32_BPPE_POOL_SIZE;
  bp_max_number._4_4_ = u32_JUMBO_BPPE_POOL_SIZE;
  reserve_mem_info();
  g_pon_work_mode = zte_get_pon_mode();
  if (g_pon_work_mode == 0x10) {
    lan_up = 1;
  }
  printk("lan_up=%d, lan_up_port=%d\n",lan_up,lan_up_port);
  uVar5 = u32_BP_SIZE * u32_BPPE_POOL_SIZE;
  uVar1 = u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE + uVar5;
  if (uVar1 <= uVar5 && uVar5 - uVar1 != 0) {
    printk("bmu config error!");
  }
  if ((uint)(ZX_RESERVE_MEM_SIZE * 0x100000) <
      u32_BP_SIZE * u32_BPPE_POOL_SIZE + u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE + 0x600000U) {
    printk("error:bmu no enough reserved mem! bmutotal_size=0x%0x reserve_mem=0x%0x\n");
  }
  iVar2 = of_find_matching_node_and_match(0,&zx_pon_match,0);
  do {
    if (iVar2 == 0) {
      pon_reset(0xffffffff);
      msleep(10);
      iVar2 = register_pon_int();
      if (-1 < iVar2) {
        *(undefined4 *)(pon_base + 0x40044) = 0xffffff7f;
        *(undefined4 *)(pon_base + 0x4001c) = 0xf;
        msleep(1);
        tm_pon_tm_init();
        netdebug_module_init();
        tm_pon_pp_init();
        tm_pon_npp_init();
        iVar2 = 0;
        if (lan_up != 0) {
          zx_pon_clk_reset();
          iVar2 = 0;
        }
      }
      return iVar2;
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-pon");
    if (iVar3 != 0) {
      pon_base = of_iomap(iVar2,0);
      top_crm_base = of_iomap(iVar2,1);
      sys_ctrl_base = of_iomap(iVar2,2);
      pin_mux_base = of_iomap(iVar2,3);
      pon_serdes_base = of_iomap(iVar2,4);
      if (pon_base == 0) {
        printk(&_LC27);
        goto LAB_0001de30;
      }
      g_pon_irq = irq_of_parse_and_map(iVar2,0);
      if (g_pon_irq < 1) {
        printk("%s: failed to get pon irq\n","zx_pon_irq_base_of_init");
        goto LAB_0001de30;
      }
      printk("g_pon_irq=%d,%x,%x,%x,%x,%x\n",g_pon_irq,pon_base,top_crm_base,sys_ctrl_base,
             pin_mux_base,pon_serdes_base);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-gephy");
    if (iVar3 != 0) {
      iVar3 = 0;
      do {
        iVar4 = irq_of_parse_and_map(iVar2,iVar3);
        *(int *)(g_phy_irq + iVar3 * 4) = iVar4;
        iVar3 = iVar3 + 1;
        if (iVar4 < 0) {
          printk("fail to get gephy irq");
          goto LAB_0001de30;
        }
      } while (iVar3 != 4);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-npp");
    if (iVar3 != 0) {
      npp_base = of_iomap(iVar2,0);
      if (npp_base == 0) {
        printk(&_LC33);
        goto LAB_0001de30;
      }
      g_npp_irq = irq_of_parse_and_map(iVar2,0);
      g_idm_irq = irq_of_parse_and_map(iVar2,1);
      if (g_npp_irq < 1) {
        printk("%s: failed to get npp irq\n","zx_pon_irq_base_of_init");
        goto LAB_0001de30;
      }
      printk("get npp irq succeed,g_npp_irq:%d\n");
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-tm");
    if (iVar3 != 0) {
      tm_base = of_iomap(iVar2,0);
      if (tm_base == 0) {
        printk(&_LC37);
        goto LAB_0001de30;
      }
      g_tm_irq = irq_of_parse_and_map(iVar2,0);
      if (g_tm_irq < 1) {
        printk("%s: failed to get tm irq\n","zx_pon_irq_base_of_init");
        goto LAB_0001de30;
      }
      printk("get tm irq succeed,g_tm_irq:%d\n",g_tm_irq);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-pp");
    if (iVar3 != 0) {
      pp_base = of_iomap(iVar2,0);
      if (pp_base == 0) {
        printk(&_LC41);
        goto LAB_0001de30;
      }
      g_pp_irq = irq_of_parse_and_map(iVar2,0);
      if (g_pp_irq < 1) {
        printk("%s: failed to get pp irq\n","zx_pon_irq_base_of_init");
        goto LAB_0001de30;
      }
      printk("get pp irq succeed,g_pp_irq:%d\n",g_pp_irq);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-idm");
    if (iVar3 != 0) {
      idm_base = of_iomap(iVar2,0);
      if (idm_base == 0) {
        printk(&_LC45);
LAB_0001de30:
        printk("get pon irq fail!\n");
        return -0x13;
      }
      g_idm_irq = irq_of_parse_and_map(iVar2,0);
      if (g_idm_irq < 1) {
        printk("%s: failed to get idm irq\n","zx_pon_irq_base_of_init");
        goto LAB_0001de30;
      }
      printk("get idm irq succeed,g_idm_irq:%d\n",g_idm_irq);
    }
    iVar2 = of_find_matching_node_and_match(iVar2,&zx_pon_match,0);
  } while( true );
}

