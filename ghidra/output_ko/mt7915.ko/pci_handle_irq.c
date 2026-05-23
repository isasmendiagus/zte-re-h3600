// module: mt7915.ko
// function: pci_handle_irq @ 0x1d031c
// size: 8 bytes
//

void pci_handle_irq(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x001d0320. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_1 + 0xd8))();
  return;
}

