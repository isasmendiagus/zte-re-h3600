// module: mt7915.ko
// function: a4_apcli_peer_disable @ 0x9feac
// size: 168 bytes
//

undefined4 a4_apcli_peer_disable(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  if (param_3 != 0 && param_2 != 0) {
    if ((*(byte *)(param_3 + 0xe8) == param_4) || (*(char *)(param_2 + 0x213392) != '\0')) {
      if (1 < DebugLevel) {
        printk("a4_apcli_peer_disable, Disable A4 for entry:%02x:%02x:%02x:%02x:%02x:%02x\n",
               *(undefined1 *)(param_3 + 0xec),*(undefined1 *)(param_3 + 0xed),
               *(undefined1 *)(param_3 + 0xee),*(undefined1 *)(param_3 + 0xef),
               *(undefined1 *)(param_3 + 0xf0),*(undefined1 *)(param_3 + 0xf1));
      }
      *(undefined1 *)(param_2 + 0x213392) = 0;
      *(undefined1 *)(param_3 + 0xe8) = 0;
    }
    return 1;
  }
  return 0;
}

