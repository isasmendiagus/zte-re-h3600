// module: mt7915.ko
// function: pci_map_io_read32 @ 0x1cac78
// size: 204 bytes
//

void pci_map_io_read32(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_24 [2];
  undefined4 local_1c;
  
  local_24[0] = param_2;
  iVar2 = hc_get_hif_ctrl();
  uVar3 = hc_get_hdev_privdata(param_1);
  iVar4 = mt_mac_cr_range_mapping(uVar3,local_24);
  iVar1 = local_24[0];
  if (iVar4 == 1) {
    if (*(char *)(iVar2 + 0x90) == '\0') {
      uVar3 = fixed_pci_read_u32(0,*(int *)(iVar2 + 0x84) + local_24[0]);
      *param_3 = uVar3;
      return;
    }
    *param_3 = 0;
  }
  else {
    iVar2 = hc_get_chip_ops(param_1);
    iVar4 = hc_get_hif_ctrl(param_1);
    local_1c = 0;
    if (*(int *)(iVar2 + 0x1b8) != 0) {
      OS_SPIN_LOCK_IRQSAVE(iVar4 + 0x9c,&local_1c);
      (**(code **)(iVar2 + 0x1b8))(param_1,iVar1,param_3);
      OS_SPIN_UNLOCK_IRQRESTORE(iVar4 + 0x9c,&local_1c);
    }
  }
  return;
}

