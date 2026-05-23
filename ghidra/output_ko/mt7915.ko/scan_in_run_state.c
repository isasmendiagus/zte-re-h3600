// module: mt7915.ko
// function: scan_in_run_state @ 0x143e7c
// size: 276 bytes
//

bool scan_in_run_state(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  bool bVar6;
  
  if (param_2 == 0) {
    piVar4 = (int *)(param_1 + 0x829300);
    iVar1 = 0;
    bVar5 = false;
    do {
      iVar3 = HcGetAutoChCtrlbyBandIdx(param_1,iVar1);
      if (*piVar4 == 3 || *piVar4 == 0) {
        if ((iVar3 != 0) && (*(int *)(iVar3 + 0x58) == 1)) {
          bVar5 = true;
        }
      }
      else {
        bVar5 = true;
      }
      bVar6 = iVar1 != 1;
      iVar1 = 1;
      piVar4 = piVar4 + 0x2bd76;
    } while (bVar6);
    return bVar5;
  }
  iVar1 = get_scan_ctrl_by_wdev();
  uVar2 = HcGetBandByWdev(param_2);
  iVar3 = HcGetAutoChCtrlbyBandIdx(param_1,uVar2);
  iVar1 = *(int *)(iVar1 + 0x90);
  if (iVar1 == 3 || iVar1 == 0) {
    if (iVar3 == 0) {
      return false;
    }
    if (*(int *)(iVar3 + 0x58) != 1) {
      return false;
    }
  }
  if (*(byte *)(param_2 + 0xe) < 2) {
    bVar5 = iVar1 != 2;
    if ((&DAT_00580e8d)[param_1 + (uint)*(byte *)(param_2 + 0xe) * 0x2137b0] == '\0') {
      bVar5 = true;
    }
  }
  else {
    bVar5 = true;
  }
  return bVar5;
}

