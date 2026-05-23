// module: mt7915.ko
// function: rtmp_eeprom_Sys_update @ 0x127230
// size: 60 bytes
//

undefined4 rtmp_eeprom_Sys_update(int param_1,int param_2,int param_3,undefined1 *param_4)

{
  int iVar1;
  
  iVar1 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 8);
  if (iVar1 == 0) {
    return 1;
  }
  if (param_2 == 1) {
    *(undefined1 *)(iVar1 + param_3) = *param_4;
  }
  else {
    *param_4 = *(undefined1 *)(iVar1 + param_3);
  }
  return 0;
}

