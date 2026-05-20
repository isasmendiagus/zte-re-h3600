// module: mt7915.ko
// function: pci_init_task_group @ 0x1cc340
// size: 552 bytes
//

undefined4
pci_init_task_group(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  iVar2 = hc_get_chip_cap();
  iVar3 = hc_get_hif_ctrl(param_1);
  iVar4 = hc_get_hdev_privdata(param_1);
  uVar5 = (uint)*(byte *)(iVar3 + 0xa8);
  if (uVar5 != 0) {
    uVar7 = 0;
    do {
      while( true ) {
        iVar6 = *(int *)(*(int *)(iVar3 + 0xac) + uVar7 * 4);
        if (*(char *)(iVar2 + 0x15d) != '\0') break;
        *(undefined ***)(iVar6 + 0x6c0) = &_LANCHOR2;
        tasklet_init(iVar6 + 0xe0,pci_tx_dma_done_func,iVar6,&_LANCHOR2,param_4);
        uVar7 = uVar7 + 1 & 0xff;
        tasklet_init(iVar6 + 0xf4,pci_rx_data_done_func,iVar6);
        tasklet_init(iVar6 + 0x108,pci_rx_event_done_func,iVar6);
        tasklet_init(iVar6 + 0x11c,pci_rx_dly_done_func,iVar6);
        tasklet_init(iVar6 + 0x130,pci_mac_recovery_func,iVar6);
        tasklet_init(iVar6 + 0x144,pci_mac_fw_own_func,iVar6);
        tasklet_init(iVar6 + 0x158,pci_subsys_int_func,iVar6);
        tasklet_init(iVar6 + 0x16c,pci_sw_int_func,iVar6);
        uVar5 = (uint)*(byte *)(iVar3 + 0xa8);
        if (uVar5 <= uVar7) {
          return 0;
        }
      }
      if (*(char *)(iVar2 + 0x15d) == '\x01') {
        *(undefined ***)(iVar6 + 0x6c0) = &PTR_tasklet_schedule_tx_done_005df330;
        init_dummy_netdev(iVar6 + 0x180);
        *(int *)(iVar6 + 0x6b0) = iVar6;
        netif_napi_add(iVar6 + 0x180,iVar6 + 0x640,pci_rx_data_done_poll_func,0x40);
        *(int *)(iVar4 + 0xa1904) = iVar6 + 0x640;
        if ((*(uint *)(iVar6 + 0x648) & 1) == 0) {
                    /* WARNING: Does not return */
          pcVar1 = (code *)software_udf(0x12,0x1cc564);
          (*pcVar1)();
        }
        DataMemoryBarrier(0xb);
        _clear_bit(0,iVar6 + 0x648);
        tasklet_init(iVar6 + 0x108,pci_rx_event_done_func,iVar6);
        tasklet_init(iVar6 + 0x11c,pci_rx_dly_done_func,iVar6);
        tasklet_init(iVar6 + 0xe0,pci_tx_dma_done_func,iVar6);
        tasklet_init(iVar6 + 0x130,pci_mac_recovery_func,iVar6);
        tasklet_init(iVar6 + 0x144,pci_mac_fw_own_func,iVar6);
        tasklet_init(iVar6 + 0x158,pci_subsys_int_func,iVar6);
        tasklet_init(iVar6 + 0x16c,pci_sw_int_func,iVar6);
        uVar5 = (uint)*(byte *)(iVar3 + 0xa8);
      }
      uVar7 = uVar7 + 1 & 0xff;
    } while (uVar7 < uVar5);
  }
  return 0;
}

