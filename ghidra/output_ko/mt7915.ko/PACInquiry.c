// module: mt7915.ko
// function: PACInquiry @ 0x17ba8
// size: 44 bytes
//

int PACInquiry(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = HcGetMaxStaNum();
  if (param_2 < uVar1) {
    iVar2 = param_2 * 0x14c0 + param_1 + 0xa1d20;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

