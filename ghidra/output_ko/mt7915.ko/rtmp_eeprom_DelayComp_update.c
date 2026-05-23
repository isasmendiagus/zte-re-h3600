// module: mt7915.ko
// function: rtmp_eeprom_DelayComp_update @ 0x1275b8
// size: 112 bytes
//

undefined4
rtmp_eeprom_DelayComp_update
          (int param_1,int param_2,int param_3,int param_4,byte param_5,undefined1 *param_6)

{
  int iVar1;
  
  if (param_4 == 0) {
    iVar1 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 0xc);
  }
  else {
    if (param_4 != 1) {
      return 1;
    }
    if (param_2 == 2) {
      iVar1 = *(int *)("Set_Rx_Vector_Control" + param_1 + 8);
    }
    else {
      iVar1 = *(int *)("Show_Rx_Statistic" + param_1 + 0x10);
    }
  }
  if (iVar1 == 0) {
    return 1;
  }
  if (param_3 == 1) {
    *(undefined1 *)(iVar1 + (uint)param_5) = *param_6;
  }
  else {
    *param_6 = *(undefined1 *)(iVar1 + (uint)param_5);
  }
  return 0;
}

