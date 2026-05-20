// module: mt7915.ko
// function: show_UpdateEfuse_Example @ 0x127628
// size: 188 bytes
//

undefined4 show_UpdateEfuse_Example(int param_1)

{
  undefined1 local_11 [5];
  
  local_11[0] = 0xb3;
  if (0 < DebugLevel) {
    printk(&_LC29,"show_UpdateEfuse_Example",0xb6,
           *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0xb6));
  }
  rtmp_eeprom_WfCmm_update(param_1,2,1,1,0,4,local_11);
  if (0 < DebugLevel) {
    printk(&_LC30,"show_UpdateEfuse_Example",0xb6,
           *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0xb6));
  }
  return 1;
}

