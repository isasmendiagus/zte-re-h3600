// module: mt7915.ko
// function: Get_System_Bw_Info @ 0xeb93c
// size: 460 bytes
//

char Get_System_Bw_Info(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  undefined4 uVar4;
  undefined1 auStack_1b [3];
  byte local_18;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    uVar2 = HcGetRadioChannel(param_1);
    if (0xe < uVar2) goto LAB_000eba80;
LAB_000eba00:
    uVar4 = 1;
  }
  else {
    if ((((*(int *)(iVar1 + 0x194) == param_2) || (*(int *)(iVar1 + 0x198) == param_2)) ||
        (*(int *)(iVar1 + 0x1a4) == param_2)) ||
       ((((*(int *)(iVar1 + 0x1a8) == param_2 || (*(int *)(iVar1 + 0x1b4) == param_2)) ||
         (*(int *)(iVar1 + 0x1b8) == param_2)) ||
        (((*(int *)(iVar1 + 0x19c) != param_2 && (*(int *)(iVar1 + 0x1a0) != param_2)) &&
         ((*(int *)(iVar1 + 0x1ac) != param_2 &&
          (((*(int *)(iVar1 + 0x1b0) != param_2 && (*(int *)(iVar1 + 0x1bc) != param_2)) &&
           (*(int *)(iVar1 + 0x1c0) != param_2)))))))))) goto LAB_000eba00;
LAB_000eba80:
    uVar4 = 2;
  }
  iVar1 = hc_radio_query_by_rf(param_1,uVar4,auStack_1b);
  if (iVar1 != 0) {
    if (-1 < DebugLevel) {
      printk("%s : can\'t find radio for RFIC:%d\n","Get_System_Bw_Info",uVar4);
    }
    return -1;
  }
  if (DebugLevel < 1) {
    uVar2 = local_18 - 1 & 0xff;
    if (5 < uVar2) {
      return '\0';
    }
  }
  else {
    printk("%s : Bw = %d\n","Get_System_Bw_Info",(int)(char)local_18);
    uVar2 = local_18 - 1 & 0xff;
    cVar3 = '\0';
    if (5 < uVar2) goto LAB_000ebac0;
  }
  cVar3 = (&DAT_00296cb4)[uVar2];
LAB_000ebac0:
  if (0 < DebugLevel) {
    printk("%s : CaptureBw = %d\n","Get_System_Bw_Info",(int)cVar3);
  }
  return cVar3;
}

