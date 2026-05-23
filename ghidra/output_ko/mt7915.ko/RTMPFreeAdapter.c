// module: mt7915.ko
// function: RTMPFreeAdapter @ 0x14fcbc
// size: 320 bytes
//

void RTMPFreeAdapter(int *param_1)

{
  int iVar1;
  int iVar2;
  
  hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar2 = *param_1;
  if (*(char *)((int)param_1 + 0x36790d) == '\x01') {
    AsicSetReptFuncEnable(param_1,0,0);
    AsicSetReptFuncEnable(param_1,0,1);
  }
  if (param_1[0x29deef] != 0) {
    os_free_mem();
    param_1[0x29deef] = 0;
  }
  if (param_1[0x29def0] != 0) {
    os_free_mem();
    param_1[0x29def0] = 0;
  }
  iVar1 = hc_get_hif_type(param_1[0x29e5e8]);
  if ((iVar1 == 2) && (*(char *)((int)param_1 + 0x286285) == '\x01')) {
    if (param_1 == (int *)0xffd48db8) {
      printk(&_LC50,0x71e);
      dump_stack();
      if (DebugLevel < 0) {
        return;
      }
      printk("%s():func_dev is NULL!\n","RTMPFreeAdapter");
      return;
    }
    bcn_buf_deinit(param_1,param_1 + 0xadee4);
  }
  hif_core_ops_unregister(param_1[0x29e5e8],param_1[0xa18a0]);
  hdev_ctrl_exit(param_1);
  RtmpOsVfree(param_1);
  if (iVar2 == 0) {
    return;
  }
  os_free_mem(iVar2);
  return;
}

