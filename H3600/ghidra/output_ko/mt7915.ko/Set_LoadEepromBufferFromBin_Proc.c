// module: mt7915.ko
// function: Set_LoadEepromBufferFromBin_Proc @ 0x1282ec
// size: 208 bytes
//

undefined4
Set_LoadEepromBufferFromBin_Proc
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  size_t __n;
  
  iVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if (-1 < iVar1) {
    if (2 < DebugLevel) {
      printk("Load EEPROM buffer from BIN, and change to BIN buffer mode\n");
    }
    iVar1 = rtmp_ee_load_from_bin(param_1);
    if (iVar1 == 0) {
      iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(void **)(iVar1 + 0xf0) != (void *)0x0) {
        __n = (size_t)*(ushort *)(iVar1 + 0xf4);
        if (0x3ff < __n) {
          __n = 0x400;
        }
        memmove(*(void **)("Set_IRR_TTGOnOff" + param_1 + 4),*(void **)(iVar1 + 0xf0),__n);
        if (2 < DebugLevel) {
          printk("Load EEPROM Buffer from default BIN.\n");
        }
      }
    }
    RtmpChipOpsEepromHook(param_1,*(undefined4 *)(param_1 + 0x286280),4);
    return 1;
  }
  return 0;
}

