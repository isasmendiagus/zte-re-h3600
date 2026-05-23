// module: mt7915.ko
// function: rt_pci_slave_probe @ 0x1d901c
// size: 152 bytes
//

int rt_pci_slave_probe(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_14;
  
  iVar1 = FUN_001d8af0(param_1,&local_2c);
  if (iVar1 != 0) {
    if (-1 < DebugLevel) {
      printk("<=== %s() failed with rv = %d!\n","rt_pci_slave_probe",iVar1);
    }
    return iVar1;
  }
  local_20 = *(undefined4 *)(param_2 + 4);
  local_1c = *(undefined4 *)(param_1 + 0x1c4);
  local_24 = param_1 + 0x68;
  local_14 = local_2c;
  pci_hif_chip_init(&local_28,&local_24);
  *(undefined4 *)(param_1 + 0xc0) = local_28;
  return 0;
}

