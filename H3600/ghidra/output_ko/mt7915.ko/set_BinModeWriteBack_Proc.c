// module: mt7915.ko
// function: set_BinModeWriteBack_Proc @ 0x1d3908
// size: 72 bytes
//

undefined4 set_BinModeWriteBack_Proc(undefined4 param_1)

{
  if (2 < DebugLevel) {
    printk("%s::Write EEPROM buffer back to BIN\n","set_BinModeWriteBack_Proc");
  }
  Set_EepromBufferWriteBack_Proc(param_1,&_LC39);
  return 1;
}

