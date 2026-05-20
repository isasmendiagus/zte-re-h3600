// module: mt7915.ko
// function: WscScanExec @ 0x1e6ecc
// size: 388 bytes
//

void WscScanExec(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  uint uVar5;
  undefined *puVar6;
  bool bVar7;
  
  bVar1 = *(byte *)(param_2 + 0x1c54);
  iVar2 = get_scan_ctrl_by_wdev(param_1,*(undefined4 *)(param_2 + 0x29ec));
  if ((*(int *)(param_2 + 0xc) != 2) && (*(int *)(param_2 + 0x10) != 0)) {
    if (0 < DebugLevel) {
      printk("!!! WscScanExec !!!\n");
    }
    *(undefined4 *)(param_2 + 0xc) = 0x23;
    uVar3 = HcGetBandByWdev(*(undefined4 *)(param_2 + 0x29ec));
    uVar5 = bVar1 & 0xf;
    RTMPSetLED(param_1,8,uVar3);
    cVar4 = *(char *)(param_1 + 0x286285);
    bVar7 = uVar5 == 1;
    if ((bVar1 & 0xf) == 0 || bVar7) {
      bVar7 = cVar4 == '\x01';
    }
    if (bVar7) {
      if ((*(char *)(param_2 + 0x2c4d) == '\x01') && ((*(uint *)(iVar2 + 0x17c) & 0xff00ff) == 0)) {
        *(undefined1 *)(iVar2 + 0x17c) = 1;
        puVar6 = &DAT_0036db58 + param_1 + uVar5 * 0x2137b0;
        *(undefined **)(iVar2 + 0x1bc) = puVar6;
      }
      else {
        puVar6 = &DAT_0036db58 + param_1 + uVar5 * 0x2137b0;
      }
      *(undefined4 *)(&DAT_00580ed8 + param_1 + uVar5 * 0x2137b0) = 1;
      ApSiteSurvey_by_wdev(param_1,0,3,0,puVar6);
      cVar4 = *(char *)(param_1 + 0x286285);
    }
    if (cVar4 == '\0') {
      (&DAT_00580360)[param_1] = 1;
      StaSiteSurvey(param_1,param_2 + 0x28,3,*(undefined4 *)(param_2 + 0x29ec));
      return;
    }
  }
  return;
}

