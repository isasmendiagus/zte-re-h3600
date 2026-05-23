// module: mt7915.ko
// function: MtATERSSIOffset @ 0x28b0f8
// size: 140 bytes
//

int MtATERSSIOffset(int param_1,int param_2,uint param_3,uint param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  if ((((param_4 <= eeprom_rssi_offset._8_4_ - 1) &&
       (iVar3 = *(int *)(eeprom_rssi_offset._0_4_ + param_4 * 4), iVar3 != 0)) &&
      (param_3 <= *(int *)(eeprom_rssi_offset._4_4_ + param_4 * 4) - 1U)) &&
     ((iVar3 = *(int *)(iVar3 + param_3 * 4), iVar3 != 0 &&
      (*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) != 0)))) {
    bVar1 = *(byte *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + iVar3);
    if ((bVar1 ^ 0x80) < 0x7f) {
      uVar2 = bVar1 & 0x3f;
      if ((bVar1 & 0x40) == 0) {
        uVar2 = -uVar2;
      }
      return uVar2 + param_2;
    }
  }
  return param_2;
}

