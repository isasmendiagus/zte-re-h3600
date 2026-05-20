// module: mt7915.ko
// function: eventExtCmdTxcmdShow @ 0x97b18
// size: 380 bytes
//

void eventExtCmdTxcmdShow(undefined4 param_1,byte *param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk("%s: cmdid=%x, rsp_len=%d\n","eventExtCmdTxcmdShow",*param_2 & 0x3f,param_3);
  }
  switch(*param_2 & 0x3f) {
  case 0x10:
    if (0 < DebugLevel) {
      printk("Sxn Global(%d): \n",(uint)(*(int *)param_2 << 10) >> 0x10);
    }
    break;
  case 0x11:
    if (0 < DebugLevel) {
      printk("Sxn Proctect(%d): \n",(uint)(*(int *)param_2 << 10) >> 0x10);
    }
    break;
  case 0x12:
    if (0 < DebugLevel) {
      printk("Sxn TXDATA(%d): \n",(uint)(*(int *)param_2 << 10) >> 0x10);
    }
    break;
  case 0x13:
    if (0 < DebugLevel) {
      printk("Sxn TrigDATA(%d): \n",(uint)(*(int *)param_2 << 10) >> 0x10);
    }
    break;
  case 0x14:
  case 0x17:
    if (0 < DebugLevel) {
      printk("Sxn TF TXD(%d): \n",(uint)(*(int *)param_2 << 10) >> 0x10);
    }
    break;
  case 0x15:
    if (0 < DebugLevel) {
      printk("Sxn TF Basic(%d): \n",(uint)(*(int *)param_2 << 10) >> 0x10);
    }
    break;
  case 0x16:
    if (0 < DebugLevel) {
      printk("Sxn SW FID(%d): \n",(uint)(*(int *)param_2 << 10) >> 0x10);
    }
    break;
  default:
    display_dbg_status(param_2);
    os_free_mem(param_2);
    return;
  }
  display_sxn_all(param_2);
  os_free_mem(param_2);
  return;
}

