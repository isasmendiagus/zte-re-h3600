// module: rtkatm.ko
// function: cleanup_module @ 0x111dc
// size: 32 bytes
//

void cleanup_module(void)

{
  atm_dev_deregister(rtk_atmdev);
  kfree(rtk_atmdev);
  return;
}

