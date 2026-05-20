// module: mt7915.ko
// function: ap_cntl_error_handle @ 0x4af98
// size: 44 bytes
//

void ap_cntl_error_handle(int param_1)

{
  if (*(int *)(*(int *)(param_1 + 0x92c) + 8) != 0) {
    return;
  }
  printk(&_LC0,0x80);
  dump_stack();
  return;
}

