// module: mt7915.ko
// function: rtmp_eeprom_TxPwr_update @ 0x1274c0
// size: 144 bytes
//

undefined4
rtmp_eeprom_TxPwr_update
          (int param_1,int param_2,int param_3,uint param_4,byte param_5,undefined1 *param_6)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (uint)param_5;
  if (param_3 == 0) {
    uVar1 = 3;
    iVar2 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 0x10);
  }
  else {
    if (param_3 != 1) {
      return 1;
    }
    if (param_2 == 2) {
      uVar1 = 0x19;
      iVar2 = *(int *)("Set_Rx_Vector_Control" + param_1 + 4);
    }
    else {
      uVar1 = 0x22;
      iVar2 = *(int *)("Show_Rx_Statistic" + param_1 + 0xc);
    }
  }
  if (1 < param_4 || (iVar2 == 0 || uVar1 <= uVar3)) {
    return 1;
  }
  if (param_4 == 1) {
    *(undefined1 *)(iVar2 + uVar3) = *param_6;
  }
  else {
    *param_6 = *(undefined1 *)(iVar2 + uVar3);
  }
  return 0;
}

