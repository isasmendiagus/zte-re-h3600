// module: mt7915.ko
// function: hif_free_rx_buf @ 0xaad24
// size: 52 bytes
//

void hif_free_rx_buf(int param_1)

{
  if (*(code **)(param_1 + 0xab4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aad30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0xab4))();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_free_rx_buf");
  return;
}

