// module: mt7915.ko
// function: set_eFuseBufferModeWriteBack_Proc @ 0x1d38bc
// size: 72 bytes
//

undefined4 set_eFuseBufferModeWriteBack_Proc(undefined4 param_1)

{
  if (2 < DebugLevel) {
    printk("%s::Write EEPROM buffer back to eFuse\n","set_eFuseBufferModeWriteBack_Proc");
  }
  Set_EepromBufferWriteBack_Proc(param_1,&_LC37);
  return 1;
}

