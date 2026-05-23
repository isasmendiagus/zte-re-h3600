// module: mt7915.ko
// function: HwCtrlThermalProtRadioOff @ 0xaf08c
// size: 72 bytes
//

undefined4 HwCtrlThermalProtRadioOff(undefined4 param_1)

{
  if (-1 < DebugLevel) {
    printk(&_LC1,"HwCtrlThermalProtRadioOff");
  }
  Set_RadioOn_Proc(param_1,&_LC2);
  return 0;
}

