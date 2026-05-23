// module: mt7915.ko
// function: mt_service_open @ 0x13d060
// size: 232 bytes
//

undefined4 mt_service_open(int param_1)

{
  int iVar1;
  int *local_14;
  int local_10;
  int local_c;
  
  os_alloc_mem(param_1,&local_14,0x1fb0);
  os_alloc_mem(param_1,&local_10,0x88);
  os_alloc_mem(param_1,&local_c,0x1ec);
  if (local_14 != (int *)0x0) {
    os_zero_mem(local_14,0x1fb0);
  }
  if (local_10 != 0) {
    os_zero_mem(local_10,0x88);
  }
  if (local_c != 0) {
    os_zero_mem(local_c,0x1ec);
  }
  if (local_14 != (int *)0x0) {
    *local_14 = local_10;
    local_14[0x7c4] = local_c;
    *(undefined1 *)(local_14 + 0x7d1) = 0;
  }
  iVar1 = DebugLevel;
  *(int **)(param_1 + 0xa77bb8) = local_14;
  *(undefined4 *)(param_1 + 0xa77bb4) = 1;
  if (0 < iVar1) {
    printk("%s: wlan service opens successfully!\n","mt_service_open");
  }
  return 0;
}

