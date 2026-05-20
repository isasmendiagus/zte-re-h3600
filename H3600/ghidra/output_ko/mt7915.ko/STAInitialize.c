// module: mt7915.ko
// function: STAInitialize @ 0x68420
// size: 276 bytes
//

undefined4 STAInitialize(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 != 0) {
    iVar2 = memcmp((void *)(param_1 + 0xa77bc9),&ZERO_MAC_ADDR,6);
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0xa77bc9) = *(undefined4 *)(param_1 + 0x794b5b);
      iVar2 = DebugLevel;
      *(undefined2 *)(param_1 + 0xa77bcd) = *(undefined2 *)(param_1 + 0x794b5f);
      if (0 < iVar2) {
        printk("Read EEPROM, EthCloneMac is %02x:%02x:%02x:%02x:%02x:%02x!\n",
               *(undefined1 *)(param_1 + 0xa77bc9),*(undefined1 *)(param_1 + 0xa77bca),
               *(undefined1 *)(param_1 + 0xa77bcb),*(undefined1 *)(param_1 + 0xa77bcc),
               *(undefined1 *)(param_1 + 0xa77bcd),*(undefined1 *)(param_1 + 0xa77bce));
      }
    }
    *(undefined2 *)(iVar1 + 0x212404) = *(undefined2 *)(*(int *)(param_1 + 4) + 0x150);
    *(undefined1 *)(param_1 + 0x794ab8) = 1;
    if (*(char *)(param_1 + 0x794ab9) == '\0') {
      *(undefined1 *)(param_1 + 0x794ab9) = 1;
    }
    return 0;
  }
  printk(&_LC9,99);
  dump_stack();
  return 0;
}

