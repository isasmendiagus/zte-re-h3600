// module: mt7915.ko
// function: rtmp_ee_load_from_efuse @ 0x1d3684
// size: 296 bytes
//

void rtmp_ee_load_from_efuse(int param_1)

{
  int iVar1;
  void *__dest;
  uint uVar2;
  undefined2 local_26;
  uint local_24 [2];
  
  local_26 = 0;
  local_24[0] = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("Load EEPROM buffer from efuse, and change to BIN buffer mode\n");
  }
  eFuseGetFreeBlockCount(param_1,local_24);
  if (local_24[0] < *(byte *)(iVar1 + 0xeb)) {
    if ((*(short *)(iVar1 + 0xf4) != 0) &&
       (__memzero(*(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4)), *(short *)(iVar1 + 0xf4) != 0)
       ) {
      uVar2 = 0;
      do {
        if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7663 ||
            (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
          rtmp_ee_efuse_read16(param_1,uVar2,&local_26,2);
        }
        else {
          eFuseRead(param_1,uVar2 & 0xffff);
        }
        __dest = (void *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar2);
        uVar2 = uVar2 + 2;
        memmove(__dest,&local_26,2);
      } while (uVar2 < *(ushort *)(iVar1 + 0xf4));
    }
    "cp_support_is_enabled"[param_1 + 5] = '\x01';
    "cp_support_is_enabled"[param_1 + 6] = '\x01';
    RtmpChipOpsEepromHook(param_1,*(undefined4 *)(param_1 + 0x286280),4);
  }
  return;
}

