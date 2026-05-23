// module: mt7915.ko
// function: wdev_attr_update_mac @ 0x14dc70
// size: 188 bytes
//

void wdev_attr_update_mac(undefined4 param_1,int *param_2)

{
  if ((param_2[5] != 1) && (param_2[5] != 0x20)) {
    return;
  }
  AsicSetWdevIfAddr(param_1,param_2,1);
  if (0 < DebugLevel) {
    printk("%s(): wdevId%d = %02x:%02x:%02x:%02x:%02x:%02x\n","wdev_attr_update_mac",
           (char)param_2[3],*(undefined1 *)((int)param_2 + 0x1b),(char)param_2[7],
           *(undefined1 *)((int)param_2 + 0x1d),*(undefined1 *)((int)param_2 + 0x1e),
           *(undefined1 *)((int)param_2 + 0x1f),(char)param_2[8]);
  }
  if (*param_2 != 0) {
    memmove(*(void **)(*param_2 + 0x1dc),(undefined4 *)((int)param_2 + 0x1b),6);
  }
  *(undefined4 *)((int)param_2 + 0x21) = *(undefined4 *)((int)param_2 + 0x1b);
  *(undefined2 *)((int)param_2 + 0x25) = *(undefined2 *)((int)param_2 + 0x1f);
  return;
}

