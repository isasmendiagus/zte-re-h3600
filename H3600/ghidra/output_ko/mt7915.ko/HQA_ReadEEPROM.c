// module: mt7915.ko
// function: HQA_ReadEEPROM @ 0x275af0
// size: 248 bytes
//

undefined4 HQA_ReadEEPROM(undefined4 param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  ushort local_1a;
  
  local_1a = 0;
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_ReadEEPROM");
  }
  uVar1 = *(ushort *)(param_3 + 0xc) >> 8;
  chip_eeprom_read16(param_1,*(ushort *)(param_3 + 0xc) << 8 | uVar1,&local_1a);
  if (1 < DebugLevel) {
    printk("e2p r %02Xh = 0x%02X\n",uVar1,(undefined1)local_1a);
    if (1 < DebugLevel) {
      printk("e2p r %02Xh = 0x%02X\n",uVar1 + 1,local_1a >> 8);
    }
  }
  local_1a = local_1a << 8 | local_1a >> 8;
  *(ushort *)(param_3 + 0xe) = local_1a;
  FUN_0026cdd0(param_3,param_2,4,0);
  return 0;
}

