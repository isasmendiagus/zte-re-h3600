// module: mt7915.ko
// function: ZTE_tx_ctrl_rate @ 0x15bdb0
// size: 148 bytes
//

void ZTE_tx_ctrl_rate(int *param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if ((*param_1 == 0) || (iVar3 = *param_1 + -1, iVar3 < 0)) {
    ZTE_tx_ctrl_rate_insert(param_1,param_2,0);
    return;
  }
  iVar1 = iVar3 >> 1;
  uVar2 = param_1[iVar1 * 2 + 2];
  if (uVar2 != param_2) {
    iVar4 = 0;
    do {
      if (param_2 < uVar2) {
        iVar3 = iVar1 + -1;
      }
      else {
        iVar4 = iVar1 + 1;
      }
      if (iVar3 < iVar4) {
        ZTE_tx_ctrl_rate_insert();
        return;
      }
      iVar1 = (iVar4 + iVar3) / 2;
      uVar2 = param_1[iVar1 * 2 + 2];
    } while (uVar2 != param_2);
  }
  param_1[iVar1 * 2 + 1] = param_1[iVar1 * 2 + 1] + 1;
  return;
}

