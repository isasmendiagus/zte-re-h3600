// module: mt7915.ko
// function: sae_check_big_sync @ 0x20948c
// size: 96 bytes
//

undefined4 sae_check_big_sync(int param_1)

{
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_check_big_sync");
  }
  if (*(char *)(param_1 + 0x2e) < '\x06') {
    *(char *)(param_1 + 0x2e) = *(char *)(param_1 + 0x2e) + '\x01';
    return 0;
  }
  delete_sae_instance(param_1);
  return 1;
}

