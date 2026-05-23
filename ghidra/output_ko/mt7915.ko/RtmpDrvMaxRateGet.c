// module: mt7915.ko
// function: RtmpDrvMaxRateGet @ 0x142750
// size: 368 bytes
//

void RtmpDrvMaxRateGet(undefined4 param_1,uint param_2,int param_3,int param_4,byte param_5,
                      byte param_6,int *param_7)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (uint)param_5;
  if (param_2 < 4) {
    if (param_2 - 2 < 2) {
      if (7 < uVar2) {
        uVar2 = uVar2 & 7;
      }
      uVar1 = (short)param_3 * 0x30 + (short)param_4 * 0x18 + 0x10 + uVar2;
      goto LAB_00142788;
    }
    uVar1 = uVar2;
    if (param_2 == 1) {
      iVar3 = getLegacyOFDMMCSIndex(uVar2);
      uVar1 = iVar3 + 4;
      if ((int)uVar1 < 0) {
        uVar1 = 0;
      }
      else if (0xff < (int)uVar1) {
        *param_7 = RalinkRate._1020_4_ * 500000;
        goto LAB_001427d4;
      }
    }
  }
  else {
    if (param_4 == 0) {
      uVar1 = param_3 * 0x1d + uVar2 + 0x70;
    }
    else if (param_4 == 1) {
      uVar1 = param_3 * 0x1d + uVar2 + 0x79;
    }
    else if (param_4 == 2) {
      uVar1 = param_3 * 0x1d + uVar2 + 0x83;
    }
    else {
      uVar1 = param_3 * 10 + uVar2 + 0xaa;
    }
LAB_00142788:
    if (0xfe < (int)uVar1) {
      uVar1 = 0xff;
    }
  }
  iVar3 = *(int *)(RalinkRate + uVar1 * 4) * 500000;
  if (1 < param_2) {
    iVar3 = (uint)param_6 * iVar3;
  }
  *param_7 = iVar3;
LAB_001427d4:
  if (2 < DebugLevel) {
    printk("%s - MODE: %d shortGI: %d BW: %d MCS: %d Antenna num: %d  Rate = %d\n",
           "RtmpDrvMaxRateGet",param_2,param_3,param_4,uVar2,(uint)param_6,*param_7);
  }
  return;
}

