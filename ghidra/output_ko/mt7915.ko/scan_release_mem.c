// module: mt7915.ko
// function: scan_release_mem @ 0x1444a4
// size: 88 bytes
//

undefined4 scan_release_mem(int param_1)

{
  *(undefined1 *)(param_1 + 0x8292e9) = 0;
  if (*(int *)(param_1 + 0x8292ec) != 0) {
    os_free_mem();
    *(undefined4 *)(param_1 + 0x8292ec) = 0;
  }
  *(undefined1 *)(param_1 + 0x8d88c1) = 0;
  if (*(int *)(param_1 + 0x8d88c4) != 0) {
    os_free_mem();
    *(undefined4 *)(param_1 + 0x8d88c4) = 0;
  }
  return 1;
}

