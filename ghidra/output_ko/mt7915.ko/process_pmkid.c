// module: mt7915.ko
// function: process_pmkid @ 0x117268
// size: 284 bytes
//

void process_pmkid(undefined4 param_1,int param_2,int param_3,int param_4)

{
  if (param_4 == -1) {
    store_pmkid_cache_in_sec_config(param_1,param_3,0xffffffff);
    if (-1 < DebugLevel) {
      printk("ASSOC - 2.PMKID not found\n");
    }
    if (*(char *)(param_3 + 0x17b) == '\0') {
      *(undefined1 *)(param_3 + 0x17b) = 2;
      RTMPSetTimer(param_3 + 0x404,100);
      return;
    }
  }
  else {
    if ((*(char *)(param_3 + 0x17b) == '\0') && (*(char *)(param_3 + 0xd24) == '\0')) {
      *(undefined1 *)(param_3 + 0x17b) = 1;
      *(undefined1 *)(param_3 + 0x514) = 7;
      os_move_mem((void *)(param_3 + 0x4a0),(void *)(param_2 + 0x21),6);
      os_move_mem((void *)(param_3 + 0x4a6),(void *)(param_3 + 0xec),6);
      RTMPSetTimer(param_3 + 0x404,100);
    }
    store_pmkid_cache_in_sec_config(param_1,param_3,param_4);
    if (-1 < DebugLevel) {
      printk("ASSOC - 2.PMKID matched and start key cache algorithm\n");
      return;
    }
  }
  return;
}

