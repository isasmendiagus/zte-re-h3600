// module: plat-zxylzb_9128S.ko
// function: pp_upload_fun @ 0x19a24
// size: 156 bytes
//

void pp_upload_fun(int param_1)

{
  if (param_1 != 0) {
    _raw_spin_lock_bh(&net_lock_tx);
    if (upload_count == 0) {
      printk("upload test begin\n");
      pp_gso_upload_enable();
    }
    DataMemoryBarrier(0xb);
    upload_count = upload_count + 1;
    _raw_spin_unlock_bh(&net_lock_tx);
    return;
  }
  _raw_spin_lock_bh(&net_lock_tx);
  if (0 < upload_count) {
    upload_count = upload_count + -1;
  }
  DataMemoryBarrier(0xb);
  if (upload_count == 0) {
    printk("upload test end\n");
    pp_gso_upload_disable();
  }
  _raw_spin_unlock_bh(&net_lock_tx);
  return;
}

