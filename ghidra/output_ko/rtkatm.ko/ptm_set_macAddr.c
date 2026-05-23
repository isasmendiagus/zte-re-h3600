// module: rtkatm.ko
// function: ptm_set_macAddr @ 0x109f4
// size: 128 bytes
//

uint ptm_set_macAddr(int param_1,int param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_2 + 2);
  if (((bVar1 & 1) == 0) && (*(short *)(param_2 + 6) != 0 || *(int *)(param_2 + 2) != 0)) {
    memcpy(*(void **)(param_1 + 0x1dc),(void *)(param_2 + 2),(uint)*(byte *)(param_1 + 0x179));
    return bVar1 & 1;
  }
  ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x107,"ptm_set_macAddr",
              0,4,0,"\nERROR: wrong MAC address\n");
  return 0xfffffffb;
}

