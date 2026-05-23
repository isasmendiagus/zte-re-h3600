// module: rtkatm.ko
// function: rtk_atm_close @ 0x10164
// size: 368 bytes
//

undefined4 rtk_atm_close(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  
  iVar4 = *(int *)(*(int *)(param_1 + 500) + 0x10);
  pcVar9 = "rtk_atm_close";
  uVar5 = *(uint *)(*(int *)(param_1 + 500) + 0xc);
  iVar8 = (int)*(short *)(param_1 + 0x1e4);
  iVar3 = 0;
  uVar6 = *(undefined4 *)(param_1 + 0x1e8);
  ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x163,"rtk_atm_close",0,
              7,0,"[%s] delete vcc %d.%d.%d\n","rtk_atm_close",uVar5,iVar8,uVar6);
  iVar2 = iVar4;
  while (((*(int *)(iVar2 + 0x10) != 1 ||
          (pcVar1 = (char *)(uint)*(byte *)(iVar2 + 5),
          pcVar1 != (char *)(int)*(short *)(param_1 + 0x1e4))) ||
         (uVar7 = (uint)*(ushort *)(iVar2 + 6), uVar7 != *(uint *)(param_1 + 0x1e8)))) {
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 0x3c;
    if (iVar3 == 0x11) {
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x16c,
                  "rtk_atm_close",0,4,0,"WARNING: Can NOT clear vcc table\n",pcVar9,uVar5,iVar8,
                  uVar6);
LAB_00010294:
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x16e,
                  "rtk_atm_close",0,7,0,"rtk_atm_close\n",pcVar9,uVar5,iVar8,uVar6);
      return 0;
    }
  }
  ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x166,"rtk_atm_close",0,
              7,0,"clear vcc table(%d.%d)\n",pcVar1,uVar7,iVar8,uVar6);
  __memzero(iVar4 + iVar3 * 0x3c + 4,0x3c);
  pcVar9 = pcVar1;
  uVar5 = uVar7;
  goto LAB_00010294;
}

