// module: mt7915.ko
// function: GetStaTxRateStart @ 0x158480
// size: 124 bytes
//

void GetStaTxRateStart(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_20 = 0;
  local_1c[0] = 0;
  if (param_1 != 0) {
    piVar2 = (int *)(param_1 + 0xa31e0);
    iVar3 = 1;
    while( true ) {
      iVar1 = HcGetMaxStaNum(param_1);
      if (iVar1 <= iVar3) break;
      if (*piVar2 == 0x20001) {
        ZTE_GetRealTimeTxRxRate(param_1,piVar2,&local_20,local_1c);
      }
      piVar2 = piVar2 + 0x530;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}

