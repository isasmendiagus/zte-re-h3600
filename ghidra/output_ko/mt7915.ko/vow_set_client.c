// module: mt7915.ko
// function: vow_set_client @ 0x431a0
// size: 200 bytes
//

void vow_set_client(int param_1,undefined1 param_2,uint param_3,undefined1 param_4)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk("%s: sta_id %u\n","vow_set_client");
  }
  if (0x11f < param_3) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: sta_id %u is exceed max num\n","vow_set_client",param_3);
    return;
  }
  iVar1 = param_1 + param_3 * 8;
  *(undefined1 *)(iVar1 + 0xa799ec) = param_2;
  *(undefined1 *)(iVar1 + 0xa799ed) = param_4;
  vow_set_sta(param_1,param_3,1);
  vow_set_sta(param_1,param_3,0);
  vow_set_sta(param_1,param_3,0x30);
  return;
}

