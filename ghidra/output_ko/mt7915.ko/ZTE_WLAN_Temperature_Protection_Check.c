// module: mt7915.ko
// function: ZTE_WLAN_Temperature_Protection_Check @ 0x15fdd0
// size: 368 bytes
//

void ZTE_WLAN_Temperature_Protection_Check(int param_1,int param_2,int param_3)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 == 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("\nTemperature_Protection_Check parameter\n");
    return;
  }
  iVar1 = param_2 * 10;
  if (param_3 <= (int)(uint)(byte)(&DAT_0034d531)[iVar1]) {
    (&DAT_0034d534)[iVar1] = 0;
    (&DAT_0034d535)[iVar1] = 0;
    if ((&DAT_0034d533)[iVar1] == 'd') {
      return;
    }
    AsicThermalProtectAdmitDuty(param_1,param_2,100,100,100,100);
    (&DAT_0034d533)[iVar1] = 100;
    return;
  }
  if (param_3 < (int)(uint)(byte)(&DAT_0034d52d)[iVar1]) {
    if ((int)(uint)(byte)(&DAT_0034d52e)[iVar1] < param_3) {
      return;
    }
    bVar2 = 0;
    (&DAT_0034d534)[iVar1] = 0;
    (&DAT_0034d535)[iVar1] = (&DAT_0034d535)[iVar1] + '\x01';
  }
  else {
    (&DAT_0034d535)[iVar1] = 0;
    bVar2 = (&DAT_0034d534)[iVar1] + 1;
    (&DAT_0034d534)[iVar1] = bVar2;
  }
  iVar1 = param_2 * 10;
  if (bVar2 < (byte)(&DAT_0034d530)[iVar1]) {
    if ((byte)(&DAT_0034d535)[iVar1] < (byte)(&DAT_0034d530)[iVar1]) {
      return;
    }
    (&DAT_0034d535)[iVar1] = 0;
    uVar3 = (uint)(byte)(&DAT_0034d533)[iVar1] + (uint)(byte)(&DAT_0034d52f)[iVar1];
    if (100 < uVar3) {
      return;
    }
  }
  else {
    (&DAT_0034d534)[iVar1] = 0;
    if ((uint)(byte)(&DAT_0034d533)[iVar1] <= (uint)(byte)(&DAT_0034d52f)[iVar1]) {
      return;
    }
    uVar3 = (uint)(byte)(&DAT_0034d533)[iVar1] - (uint)(byte)(&DAT_0034d52f)[iVar1];
    if ((int)uVar3 < (int)(uint)(byte)(&DAT_0034d532)[iVar1]) {
      return;
    }
  }
  uVar4 = uVar3 & 0xff;
  (&DAT_0034d533)[iVar1] = (char)uVar3;
  AsicThermalProtectAdmitDuty(param_1,param_2,uVar4,uVar4,uVar4,uVar4);
  return;
}

