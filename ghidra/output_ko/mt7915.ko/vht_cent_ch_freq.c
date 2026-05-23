// module: mt7915.ko
// function: vht_cent_ch_freq @ 0x2027a4
// size: 296 bytes
//

uint vht_cent_ch_freq(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  byte *pbVar2;
  code *UNRECOVERED_JUMPTABLE_00;
  byte *pbVar3;
  bool bVar4;
  bool bVar5;
  
  if (param_3 < 2) {
    pbVar2 = &_LANCHOR1;
LAB_002027d8:
    if (param_3 < 2) {
      pbVar3 = &DAT_005dfe60;
      if (param_2 == 0) {
        return param_1;
      }
    }
    else {
      if (param_3 == 2) goto LAB_002027c0;
      pbVar3 = (byte *)0x0;
      if (param_2 == 0) {
        return param_1;
      }
    }
    bVar4 = param_1 == 0x23;
    if (param_1 < 0x24) {
      bVar4 = param_3 == 1;
    }
    if (bVar4) {
      return param_1;
    }
  }
  else {
    if (param_3 != 2) {
      pbVar2 = (byte *)0x0;
      goto LAB_002027d8;
    }
    pbVar2 = &DAT_005dfe6c;
LAB_002027c0:
    if (param_2 == 0) {
      return param_1;
    }
    pbVar3 = &DAT_005dfe9c;
  }
  if ((param_2 & 0xfd) == 1) {
    uVar1 = (uint)pbVar2[1];
    if (uVar1 == 0) {
      return param_1;
    }
    bVar5 = param_1 <= *pbVar2;
    bVar4 = *pbVar2 == param_1;
    if (!bVar5 || bVar4) {
      bVar5 = uVar1 <= param_1;
      bVar4 = param_1 == uVar1;
    }
    pbVar3 = pbVar2;
    if (bVar5 && !bVar4) {
      do {
        pbVar2 = pbVar3 + 3;
        uVar1 = (uint)pbVar3[4];
        if (uVar1 == 0) {
          return param_1;
        }
        bVar5 = param_1 <= *pbVar2;
        bVar4 = *pbVar2 == param_1;
        if (!bVar5 || bVar4) {
          bVar5 = uVar1 <= param_1;
          bVar4 = param_1 == uVar1;
        }
        pbVar3 = pbVar2;
      } while (bVar5 && !bVar4);
    }
    return (uint)pbVar2[2];
  }
  if (param_2 != 2) {
    return param_1;
  }
  uVar1 = (uint)pbVar3[1];
  if (uVar1 == 0) {
    return param_1;
  }
  bVar5 = param_1 <= *pbVar3;
  bVar4 = *pbVar3 == param_1;
  if (!bVar5 || bVar4) {
    bVar5 = uVar1 <= param_1;
    bVar4 = param_1 == uVar1;
  }
  pbVar2 = pbVar3;
  if (bVar5 && !bVar4) {
    do {
      pbVar3 = pbVar2 + 3;
      uVar1 = (uint)pbVar2[4];
      if (uVar1 == 0) {
                    /* WARNING: Could not recover jumptable at 0x0020285c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar1 = (*UNRECOVERED_JUMPTABLE_00)();
        return uVar1;
      }
      bVar5 = param_1 <= *pbVar3;
      bVar4 = *pbVar3 == param_1;
      if (!bVar5 || bVar4) {
        bVar5 = uVar1 <= param_1;
        bVar4 = param_1 == uVar1;
      }
      pbVar2 = pbVar3;
    } while (bVar5 && !bVar4);
  }
                    /* WARNING: Could not recover jumptable at 0x002028c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (*UNRECOVERED_JUMPTABLE_00)(pbVar3[2]);
  return uVar1;
}

