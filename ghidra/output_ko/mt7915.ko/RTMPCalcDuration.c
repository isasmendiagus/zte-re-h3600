// module: mt7915.ko
// function: RTMPCalcDuration @ 0xc6cf4
// size: 208 bytes
//

short RTMPCalcDuration(int param_1,uint param_2,int param_3)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  int extraout_r1;
  int extraout_r1_00;
  int iVar4;
  
  if (param_2 < 4) {
    if (param_2 == 0) {
      sVar3 = 0xc0;
    }
    else if ((*(uint *)(param_1 + 0x795124) & 0x10) == 0) {
      sVar3 = 0xc0;
    }
    else {
      sVar3 = 0x60;
    }
    uVar1 = *(undefined2 *)(RateIdTo500Kbps + param_2 * 2);
    sVar2 = __aeabi_uidiv(param_3 << 4,uVar1);
    sVar3 = sVar3 + sVar2;
    __aeabi_uidivmod(param_3 << 4,uVar1);
    if (extraout_r1 != 0) {
      sVar3 = sVar3 + 1;
    }
    return sVar3;
  }
  if (param_2 < 0xc) {
    uVar1 = *(undefined2 *)(RateIdTo500Kbps + param_2 * 2);
    iVar4 = param_3 * 4 + 0xb;
    sVar3 = __aeabi_uidiv(iVar4,uVar1);
    __aeabi_uidivmod(iVar4,uVar1);
    if (extraout_r1_00 == 0) {
      sVar3 = sVar3 * 4 + 0x1a;
    }
    else {
      sVar3 = sVar3 * 4 + 0x1e;
    }
    return sVar3;
  }
  return 0x1a;
}

