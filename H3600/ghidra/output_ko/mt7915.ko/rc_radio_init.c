// module: mt7915.ko
// function: rc_radio_init @ 0xabfd0
// size: 660 bytes
//

void rc_radio_init(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined2 uVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  
  uVar5 = (uint)(*(int *)(param_1 + 0xb58) << 0x1a) >> 0x1f;
  if (param_3 == 0) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    uVar3 = 1;
  }
  else {
    uVar3 = 2;
  }
  bVar10 = DebugLevel < 0;
  *(undefined1 *)(param_1 + 0x32d8) = uVar3;
  if ((bVar10) ||
     (printk("%s(): DBDC MODE=%d, ConcurrentBand=%d\n","rc_radio_init"),
     *(char *)(param_1 + 0x32d8) != '\0')) {
    uVar5 = 0;
    iVar9 = param_1 + 0x1000;
    do {
      iVar8 = uVar5 * 0x354 + param_1 + 0x1360 + 0x33c;
      os_zero_mem(iVar8,0xe);
      uVar7 = (uint)(byte)"rtmp_read_dot11v_mbssid_cfg_from_file"[*(int *)(param_1 + 0x4328) + 0x1e]
      ;
      if ((uVar7 - 0x1e & 0xfb) == 0) {
        uVar3 = 2;
      }
      else if (((uVar7 - 2 & 0xfd) == 0 ||
                (uVar7 - 0x1f < 2 ||
                (uVar7 - 0x1c < 2 ||
                (uVar7 - 0x18 < 3 ||
                (uVar7 - 0x13 < 2 ||
                (uVar7 - 0xd < 5 || (uVar7 - 9 < 2 || (uVar7 == 0x23 || uVar7 == 0xff)))))))) &&
              (uVar5 != 0)) {
        if (uVar5 == 1) {
          uVar3 = 2;
        }
        else {
          uVar3 = 3;
        }
      }
      else {
        uVar3 = 1;
      }
      iVar6 = param_1 + uVar5 * 0x354;
      iVar4 = iVar9 + uVar5 * 0x354;
      *(undefined1 *)(iVar6 + 0x1360) = uVar3;
      *(undefined1 *)(iVar4 + 0x6a4) = 0xf;
      *(char *)(iVar4 + 0x69c) = (char)uVar5;
      if ((*(byte *)(iVar6 + 0x1360) & 1) == 0) {
        uVar3 = 0x24;
      }
      else {
        uVar3 = 1;
      }
      *(undefined1 *)(iVar4 + 0x6a0) = uVar3;
      uVar3 = *(undefined1 *)(param_1 + 0xba4);
      if ((*(byte *)(iVar6 + 0x1360) & 2) != 0) {
        uVar3 = *(undefined1 *)(param_1 + 0xba5);
      }
      init_default_ppe(param_1 + 0x1360 + uVar5 * 0x354 + 0x34c,*(undefined1 *)(param_1 + 0xba1),
                       uVar3);
      iVar4 = iVar9 + uVar5 * 0x354;
      if (*(byte *)(iVar4 + 0x6a0) < 0xf) {
        uVar2 = 2;
      }
      else {
        uVar2 = 1;
      }
      *(undefined2 *)(iVar4 + 0x69e) = uVar2;
      *(undefined1 *)(iVar4 + 0x69d) = 0;
      iVar1 = DebugLevel;
      if (*(char *)(param_1 + 0x32d8) == '\x01') {
        *(undefined1 *)(iVar4 + 0x6a6) = 1;
      }
      iVar4 = iVar9 + uVar5 * 0x354;
      *(undefined1 *)(iVar4 + 0x6a8) = 0;
      if (-1 < iVar1) {
        printk("%s(): radio_ctrl=%p,Band=%d,rfcap=%d,channel=%d,PhyMode=%d extCha=0x%x\n",
               "rc_radio_init",iVar8,uVar5,*(undefined1 *)(iVar6 + 0x1360),
               *(undefined1 *)(iVar4 + 0x6a0),*(undefined2 *)(iVar4 + 0x69e),
               *(undefined1 *)(iVar4 + 0x6a4));
      }
      HdevInit(param_1,uVar5,iVar8);
      uVar5 = uVar5 + 1 & 0xff;
    } while (uVar5 < *(byte *)(param_1 + 0x32d8));
  }
  RcUpdateBandCtrl(param_1);
  return;
}

