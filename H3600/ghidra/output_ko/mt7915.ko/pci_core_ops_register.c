// module: mt7915.ko
// function: pci_core_ops_register @ 0x1d0324
// size: 560 bytes
//

void pci_core_ops_register(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = hc_get_hif_ctrl();
  *(undefined4 *)(iVar1 + 0x9c) = 0;
  *(undefined1 *)(iVar1 + 0x90) = 0;
  puVar2 = (undefined4 *)hc_get_io_ops(param_1);
  puVar2[2] = int_pci_io_force_read32;
  puVar2[3] = int_pci_io_force_write32;
  puVar2[8] = CmdIORead32;
  puVar2[9] = CmdIOWrite32;
  *puVar2 = int_pci_io_read32;
  puVar2[10] = int_pci_io_read32;
  puVar2[1] = int_pci_io_write32;
  puVar2[0xb] = int_pci_io_write32;
  puVar2[4] = pci_map_io_read32;
  puVar2[6] = pci_map_io_read32;
  puVar2[5] = pci_map_io_write32;
  puVar2[7] = pci_map_io_write32;
  puVar2 = (undefined4 *)hc_get_hif_ops(param_1);
  *puVar2 = pci_get_resouce_type;
  puVar2[1] = pci_free_txd;
  puVar2[2] = pci_free_rx_buf;
  puVar2[6] = pci_get_tx_buf;
  puVar2[3] = pci_init_txrx_ring_mem;
  puVar2[4] = pci_reset_txrx_ring_mem;
  puVar2[0xd] = pci_dma_reset;
  puVar2[0xe] = pci_dma_enable;
  puVar2[0xf] = pci_dma_disable;
  puVar2[5] = pci_poll_txrx_empty;
  puVar2[7] = pci_get_tx_resource_free_num;
  puVar2[8] = pci_get_resource_idx;
  puVar2[9] = pci_init_task_group;
  puVar2[10] = pci_reset_task_group;
  puVar2[0xb] = pci_register_irq;
  puVar2[0xc] = pci_free_irq_local;
  puVar2[0x16] = pci_kick_out_cmd_msg;
  puVar2[0x17] = pci_kick_out_fwdl_msg;
  puVar2[0x18] = pci_kick_out_data_tx;
  puVar2[0x19] = MiniportMMRequest;
  puVar2[0x1a] = pci_rx_event_process;
  puVar2[0x10] = pci_mcu_init;
  puVar2[0x11] = pci_mcu_exit;
  puVar2[0x12] = pci_mcu_fw_init;
  puVar2[0x13] = pci_mcu_fw_exit;
  puVar2[0x14] = pci_mcu_unlink_ackq;
  puVar2[0x1b] = pci_sys_init;
  puVar2[0x1d] = EnqueuePsPoll;
  puVar2[0x1f] = RT28xxPciStaAsicSleepAutoWakeup;
  puVar2[0x1e] = RT28xxPciStaAsicWakeup;
  puVar2[0x1c] = RTPCICmdThread;
  puVar2[0x20] = pci_get_tx_res_num;
  puVar2[0x21] = pci_get_rx_res_num;
  return;
}

