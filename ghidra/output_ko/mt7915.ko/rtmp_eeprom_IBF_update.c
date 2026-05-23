// module: mt7915.ko
// function: rtmp_eeprom_IBF_update @ 0x127550
// size: 104 bytes
//

undefined4
rtmp_eeprom_IBF_update(int param_1,int param_2,uint param_3,uint param_4,undefined1 *param_5)

{
  uint uVar1;
  int iVar2;
  
  if (param_2 == 2) {
    uVar1 = 0x18;
    iVar2 = *(int *)("Show_Rx_Statistic" + param_1 + 4);
  }
  else {
    uVar1 = 0xc0;
    iVar2 = *(int *)("cp_support_is_enabled" + param_1);
  }
  if (param_3 < 2 && (iVar2 != 0 && param_4 < uVar1)) {
    if (param_3 == 1) {
      *(undefined1 *)(iVar2 + param_4) = *param_5;
    }
    else {
      *param_5 = *(undefined1 *)(iVar2 + param_4);
    }
    return 0;
  }
  return 1;
}

