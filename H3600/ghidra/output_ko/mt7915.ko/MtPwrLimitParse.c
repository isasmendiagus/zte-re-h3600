// module: mt7915.ko
// function: MtPwrLimitParse @ 0x151b0c
// size: 424 bytes
//

undefined4 MtPwrLimitParse(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte local_2a [2];
  int local_28;
  int local_24;
  
  uVar5 = 0;
  local_28 = 0;
  local_24 = 0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_2a[0] = *(byte *)(iVar2 + 0x1fa);
  local_2a[1] = *(undefined1 *)(iVar2 + 0x1fe);
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: null pointer for buffer to update power limit table after parsing !!\n",
             "MtPwrLimitParse");
    }
  }
  else {
    MtPwrGetPwrLimitInstance(param_1,param_4,1,&local_28);
    if ((local_28 != 0) && (MtPwrGetPwrLimitInstance(param_1,param_4,4,&local_24), local_24 != 0)) {
      bVar1 = local_2a[param_4];
      if (bVar1 != 0) {
        uVar6 = 0;
        iVar2 = local_28;
        do {
          uVar3 = (uint)*(byte *)(iVar2 + uVar5);
          if ((((int)*(char *)(local_24 + uVar5) & param_3 + 1U) != 0) &&
             ('\0' < (char)*(byte *)(iVar2 + uVar5))) {
            uVar4 = 0;
            do {
              iVar2 = rstrtok(0,&_LC3);
              if (iVar2 == 0) {
                uVar3 = (uint)*(byte *)(local_28 + uVar5);
                iVar2 = local_28;
                break;
              }
              MtPowerLimitFormatTrans(param_1,param_2 + uVar4 + uVar6);
              uVar4 = uVar4 + 1 & 0xff;
              uVar3 = (uint)*(byte *)(local_28 + uVar5);
              iVar2 = local_28;
            } while ((int)uVar4 < (int)(char)*(byte *)(local_28 + uVar5));
          }
          uVar5 = uVar5 + 1;
          uVar6 = uVar6 + uVar3 & 0xff;
        } while ((uVar5 & 0xff) < (uint)bVar1);
      }
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s: null pointer for parameter related to parse power limit table proc !!\n",
             "MtPwrLimitParse");
    }
  }
  return 1;
}

