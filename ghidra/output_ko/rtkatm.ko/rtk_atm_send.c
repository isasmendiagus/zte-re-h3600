// module: rtkatm.ko
// function: rtk_atm_send @ 0x10cdc
// size: 260 bytes
//

undefined4 rtk_atm_send(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  int local_14;
  
  uVar3 = 0;
  iVar2 = cfg;
  do {
    uVar5 = uVar3 & 0xff;
    uVar3 = uVar3 + 1;
    if ((*(int *)(iVar2 + 0x10) != 0) && (*(int *)(iVar2 + 0x38) == param_1)) goto LAB_00010d2c;
    iVar2 = iVar2 + 0x3c;
  } while (uVar3 != 0x10);
  uVar5 = 0x10;
LAB_00010d2c:
  local_14 = param_2;
  if (remote_dev == 0) {
    ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x1ea,"rtk_atm_send",0
                ,7,0,"remote_dev = null \n");
    return 0;
  }
  insert_ether_header(&local_14);
  insert_mpoatag(&local_14,uVar5);
  piVar4 = (int *)(param_1 + 0xdc);
  *(int *)(local_14 + 0x18) = remote_dev;
  HintPreloadDataForWrite(piVar4);
  do {
    bVar1 = (bool)hasExclusiveAccess(piVar4);
  } while (!bVar1);
  *piVar4 = *piVar4 - *(int *)(local_14 + 0xd0);
  (**(code **)(*(int *)(remote_dev + 300) + 0x10))();
  (**(code **)(param_1 + 0x1d0))(param_1);
  return 0;
}

