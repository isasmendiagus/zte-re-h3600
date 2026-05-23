// module: mt7915.ko
// function: fp_schedule_tx_que_on @ 0xd3ba8
// size: 156 bytes
//

undefined4 fp_schedule_tx_que_on(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10);
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0x20) == '\0') {
    param_3 = 0;
  }
  iVar1 = param_1 + param_3 * 0x10;
  if ((((*(int *)(iVar1 + 0x285af4) != 0) || (*(int *)(iVar1 + 0x285b14) != 0)) ||
      (*(int *)(iVar1 + 0x285b54) != 0)) || (*(int *)(iVar1 + 0x285b74) != 0)) {
    (**(code **)(iVar2 + 0xc))(param_1,param_2,0,param_3,param_4);
  }
  return 0;
}

