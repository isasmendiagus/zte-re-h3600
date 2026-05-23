// module: tm.ko
// function: tm_sch_secsch_sp_dwrr_cfg_set @ 0x4c040
// size: 92 bytes
//

int tm_sch_secsch_sp_dwrr_cfg_set(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 == 0) {
    iVar3 = 0;
  }
  else {
    iVar4 = 0;
    iVar3 = 0;
    do {
      iVar1 = 0;
      do {
        iVar2 = iVar1 + 1;
        iVar1 = sch_set_secsch_sp_dwrr_cfg(iVar4,iVar1,param_2);
        iVar3 = iVar3 + iVar1;
        iVar1 = iVar2;
      } while (iVar2 != 4);
      iVar4 = iVar4 + 1;
    } while (iVar4 != param_1);
  }
  return iVar3;
}

