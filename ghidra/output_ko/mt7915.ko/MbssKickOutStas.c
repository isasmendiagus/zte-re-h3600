// module: mt7915.ko
// function: MbssKickOutStas @ 0x5196c
// size: 128 bytes
//

void MbssKickOutStas(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_1 + 0xa1e0c;
  iVar3 = 0;
  while( true ) {
    iVar1 = HcGetMaxStaNum(param_1);
    if (iVar1 <= iVar3) break;
    if (((iVar2 != 0xec) && (*(int *)(iVar2 + -0xec) == 0x20001)) &&
       (*(byte *)(iVar2 + -8) == param_2)) {
      APMlmeKickOutSta(param_1,iVar2,*(undefined2 *)(iVar2 + -0xc),param_3,param_4);
    }
    iVar2 = iVar2 + 0x14c0;
    iVar3 = iVar3 + 1;
  }
  return;
}

