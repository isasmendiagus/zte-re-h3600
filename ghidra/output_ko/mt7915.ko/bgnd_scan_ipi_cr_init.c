// module: mt7915.ko
// function: bgnd_scan_ipi_cr_init @ 0x22f550
// size: 100 bytes
//

void bgnd_scan_ipi_cr_init(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 local_1c [3];
  undefined1 local_19;
  
  os_zero_mem(local_1c,0x14);
  local_1c[0] = 0;
  local_19 = 0;
  uVar1 = mt_cmd_set_rdd_ipi_hist(param_1,local_1c);
  if (2 < DebugLevel) {
    printk("%s(): ret = %d\n","bgnd_scan_ipi_cr_init",uVar1);
  }
  return;
}

