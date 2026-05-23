// module: mt7915.ko
// function: eFuse_init @ 0x1d37ac
// size: 256 bytes
//

undefined4 eFuse_init(int param_1)

{
  int iVar1;
  uint local_14;
  
  local_14 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (-1 < DebugLevel) {
    printk("NVM is Efuse and its size =%x[%x-%x]\n",*(undefined1 *)(iVar1 + 0xea),
           *(undefined2 *)(iVar1 + 0xe6),*(undefined2 *)(iVar1 + 0xe8));
  }
  eFuseGetFreeBlockCount(param_1,&local_14);
  if (*(byte *)(iVar1 + 0xeb) <= local_14) {
    if (0 < DebugLevel) {
      printk("NVM is efuse and the information is too less to bring up the interface\n");
      if (0 < DebugLevel) {
        printk("Load EEPROM buffer from BIN, and force to use BIN buffer mode\n");
      }
    }
    "Set_IRR_TTGOnOff"[param_1 + 1] = '\0';
    rtmp_ee_load_from_bin(param_1);
    RtmpChipOpsEepromHook(param_1,*(undefined4 *)(param_1 + 0x286280),4);
    return 0;
  }
  rtmp_ee_load_from_efuse(param_1);
  return 0;
}

