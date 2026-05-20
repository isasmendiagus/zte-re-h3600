// module: mt7915.ko
// function: ge_schedule_tx_que @ 0xcfc68
// size: 200 bytes
//

undefined4 ge_schedule_tx_que(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  if (*(short *)(param_1 + (*(int *)(param_1 + 0x28a350) + 0x1431a4) * 2 + 4) == 0) {
    piVar3 = (int *)(param_1 + 0x28e368);
    iVar1 = 1;
    do {
      iVar4 = *piVar3;
      piVar3 = piVar3 + 0x1006;
      iVar2 = iVar1 + 1;
      if (*(short *)(param_1 + (iVar4 + iVar1 * 0x200c + 0x1431a4) * 2 + 4) != 0) goto LAB_000cfd04;
      iVar1 = iVar2;
    } while (iVar2 != 4);
    if ((*(int *)(param_1 + 0x285b54) == 0) && (*(int *)(param_1 + 0x285ba4) == 0)) {
      return 0;
    }
  }
LAB_000cfd04:
  (**(code **)(*(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10) + 8))(param_1,0,0);
  return 0;
}

