// module: mt7915.ko
// function: chip_hif_pci_data_ring_assign @ 0x1376a4
// size: 44 bytes
//

void chip_hif_pci_data_ring_assign(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops();
  if (*(code **)(iVar1 + 0x290) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001376cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x290))(param_1,param_2);
  return;
}

