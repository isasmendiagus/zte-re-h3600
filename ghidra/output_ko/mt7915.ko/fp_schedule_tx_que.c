// module: mt7915.ko
// function: fp_schedule_tx_que @ 0xd3c44
// size: 148 bytes
//

undefined4 fp_schedule_tx_que(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10);
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0x20) == '\0') {
    param_2 = 0;
  }
  iVar1 = param_1 + param_2 * 0x10;
  if ((((*(int *)(iVar1 + 0x285af4) != 0) || (*(int *)(iVar1 + 0x285b14) != 0)) ||
      (*(int *)(iVar1 + 0x285b54) != 0)) || (*(int *)(iVar1 + 0x285b74) != 0)) {
    (**(code **)(iVar2 + 8))(param_1,0,param_2);
  }
  return 0;
}

