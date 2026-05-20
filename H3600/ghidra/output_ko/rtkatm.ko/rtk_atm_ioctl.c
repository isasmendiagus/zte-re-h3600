// module: rtkatm.ko
// function: rtk_atm_ioctl @ 0x10920
// size: 208 bytes
//

undefined4 rtk_atm_ioctl(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == 0) {
    return 0xfffffff2;
  }
  iVar1 = 0;
  iVar2 = cfg;
  while ((*(char *)(iVar2 + 5) != *(char *)(param_3 + 1) ||
         (*(short *)(iVar2 + 6) != *(short *)(param_3 + 2)))) {
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 0x3c;
    if (iVar1 == 0x10) {
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x17f,
                  "rtk_atm_ioctl",0,4,0,"%s: set encapsulation failed!\n","RTK ATM Module");
      return 0xfffffff2;
    }
  }
  iVar2 = cfg + iVar1 * 0x3c;
  *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(param_3 + 4);
  *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(param_3 + 8);
  return 0;
}

