// module: rtkatm.ko
// function: rtk_atm_open @ 0x102d8
// size: 480 bytes
//

undefined4 rtk_atm_open(int param_1)

{
  int *piVar1;
  short sVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  
  puVar6 = *(undefined4 **)(*(int *)(param_1 + 500) + 0x10);
  ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x11f,"rtk_atm_open",0,7
              ,0,"rtk_atm_open VC: vpi: %d, vci%d\n",(int)*(short *)(param_1 + 0x1e4),
              *(undefined4 *)(param_1 + 0x1e8));
  sVar2 = *(short *)(param_1 + 0x1e4);
  iVar7 = *(int *)(param_1 + 0x1e8);
  if ((sVar2 != -2 && iVar7 != -2) && (*(char *)(param_1 + 0x260) == '\x05')) {
    if (-1 < *(int *)(param_1 + 0x1e0) << 0x1d) {
      *(undefined4 *)(param_1 + 0x2a0) = 0;
    }
    _set_bit(0,param_1 + 0x1e0);
    if (-1 < *(int *)(param_1 + 0x1e0) << 0x1d) {
      iVar4 = 0;
      puVar5 = puVar6;
      while (piVar1 = puVar5 + 4, puVar5 = puVar5 + 0xf, *piVar1 != 0) {
        iVar4 = iVar4 + 1;
        if (iVar4 == 0x11) {
          return 0xffffffff;
        }
      }
      *(undefined4 **)(param_1 + 0x2a0) = puVar6 + iVar4 * 0xf + 1;
      *(char *)(puVar6 + iVar4 * 0xf + 1) = (char)iVar4;
      puVar6[iVar4 * 0xf + 0xe] = param_1;
      *(char *)((int)puVar6 + iVar4 * 0x3c + 5) = (char)sVar2;
      *(short *)((int)puVar6 + iVar4 * 0x3c + 6) = (short)iVar7;
      puVar6[iVar4 * 0xf + 2] = 0;
      puVar6[iVar4 * 0xf + 3] = 0;
      puVar6[iVar4 * 0xf + 0xd] = 0;
      if (*(byte *)(param_1 + 0x1f8) < 4) {
        uVar3 = CSWTCH_120[(uint)*(byte *)(param_1 + 0x1f8) * 4];
      }
      else {
        uVar3 = 3;
      }
      iVar8 = 0;
      *(undefined1 *)(puVar6 + iVar4 * 0xf + 9) = uVar3;
      iVar7 = *(int *)(param_1 + 0x200);
      if (iVar7 == 0) {
        iVar7 = -0xe201;
      }
      *(short *)((int)puVar6 + iVar4 * 0x3c + 0x26) = (short)iVar7;
      *(undefined1 *)(puVar6 + iVar4 * 0xf + 0xb) = 0;
      puVar6[iVar4 * 0xf + 0xc] = 0;
      puVar5 = puVar6;
      do {
        piVar1 = puVar5 + 4;
        puVar5 = puVar5 + 0xf;
        if (*piVar1 != 0) {
          iVar8 = iVar8 + 1;
        }
      } while (puVar5 != puVar6 + 0xf0);
      iVar8 = iVar8 + 1;
      if (iVar8 < 0x11) {
        puVar5 = &cfg;
      }
      puVar6[iVar4 * 0xf + 4] = 1;
      if (iVar8 < 0x11) {
        puVar5[1] = iVar8;
      }
      puVar6[iVar4 * 0xf + 0xf] = 0;
    }
    atm_dev_signal_change(*(undefined4 *)(param_1 + 500),2);
    _set_bit(1,param_1 + 0x1e0);
    return 0;
  }
  return 0xffffffea;
}

