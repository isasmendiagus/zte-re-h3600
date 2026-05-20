// module: mt7915.ko
// function: RT_CfgSetCountryRegion @ 0xb7e98
// size: 248 bytes
//

undefined4 RT_CfgSetCountryRegion(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  bool bVar4;
  
  iVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if (param_3 == 2) {
    uVar2 = 0x4c44;
  }
  else {
    uVar2 = 0x4c45;
  }
  pcVar3 = (char *)(param_1 + (uVar2 | 0x790000));
  if (((*(uint *)(param_1 + 0xa39f84) & 2) == 0) || (-1 < *pcVar3)) {
    if (-1 < iVar1) {
      if (param_3 == 2) {
        if (iVar1 - 0x1fU < 3 || iVar1 < 8) goto LAB_000b7f08;
      }
      else {
        bVar4 = iVar1 == 0x25;
        if (iVar1 < 0x26) {
          bVar4 = param_3 == 1;
        }
        if (bVar4) {
LAB_000b7f08:
          *pcVar3 = (char)iVar1;
          return 1;
        }
      }
    }
    if (-1 < DebugLevel) {
      printk("CfgSetCountryRegion():region(%ld) out of range!\n");
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("CfgSetCountryRegion():CountryRegion in eeprom was programmed\n");
    return 0;
  }
  return 0;
}

