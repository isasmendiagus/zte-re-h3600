// module: mt7915.ko
// function: RTMPSetCountryCode @ 0xef4a8
// size: 132 bytes
//

void RTMPSetCountryCode(int param_1,void *param_2)

{
  void *__dest;
  
  __dest = (void *)(param_1 + 0x794c31);
  __memzero(__dest,4);
  memmove(__dest,param_2,2);
  *(undefined1 *)(param_1 + 0x794c34) = 0;
  *(undefined1 *)(param_1 + 0x794c33) = 0x20;
  if (*(char *)(param_1 + 0x794c31) != '\0') {
    *(undefined1 *)(param_1 + 0x794c30) = 1;
  }
  if (3 < DebugLevel) {
    printk("CountryCode=%s\n",__dest);
    return;
  }
  return;
}

