// module: mt7915.ko
// function: set_qiscdump_proc @ 0x2901c
// size: 116 bytes
//

undefined4 set_qiscdump_proc(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)
           get_wdev_by_ioctl_idx_and_iftype
                     (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (puVar1 != (undefined4 *)0x0) {
    if (0 < DebugLevel) {
      printk("%s(): wdev=%p, idx=%d, dev=%p, %s\n","set_qiscdump_proc",puVar1,
             *(undefined1 *)(puVar1 + 3),*puVar1,*puVar1);
    }
    return 1;
  }
  return 0;
}

