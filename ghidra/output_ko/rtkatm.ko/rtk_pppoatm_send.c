// module: rtkatm.ko
// function: rtk_pppoatm_send @ 0x10e1c
// size: 168 bytes
//

undefined4 rtk_pppoatm_send(int param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_1c [2];
  
  iVar4 = *(int *)(param_1 + 0x310);
  if (remote_dev == 0) {
    iRam000000dc = iRam000000dc + 1;
    return 0;
  }
  local_1c[0] = param_2;
  insert_ether_header(local_1c);
  insert_mpoatag(local_1c,param_3);
  iVar2 = remote_dev;
  *(int *)(local_1c[0] + 0x18) = remote_dev;
  (**(code **)(*(int *)(iVar2 + 300) + 0x10))(local_1c[0],iVar2);
  (**(code **)(param_1 + 0x1d0))(param_1);
  piVar3 = (int *)(iVar4 + 0x18);
  HintPreloadDataForWrite(piVar3);
  do {
    bVar1 = (bool)hasExclusiveAccess(piVar3);
  } while (!bVar1);
  *piVar3 = *piVar3 + -1;
  return 0;
}

