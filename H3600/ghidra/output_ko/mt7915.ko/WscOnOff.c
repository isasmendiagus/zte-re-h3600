// module: mt7915.ko
// function: WscOnOff @ 0x2010a4
// size: 356 bytes
//

void WscOnOff(int param_1,uint param_2,int param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = DebugLevel;
  uVar3 = param_2 & 0xf;
  if (param_3 == 0) {
    iVar4 = uVar3 * 0x5834 + param_1;
    "%-10d, %d, %d%%\n"[iVar4 + 0xc] = '\x01';
    if (*(int *)(
                "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                + iVar4 + 0x2b) != 0) {
      cVar1 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
              [iVar4 + 0x33];
      WscBuildBeaconIE(param_1,cVar1,0,0,0,uVar3,0,0,0);
      WscBuildProbeRespIE(param_1,3,cVar1,0,0,0,param_2 & 0xff,0,0,0);
      if (DebugLevel < 3) {
        return;
      }
      printk("WscOnOff - ON.\n");
    }
  }
  else {
    iVar2 = uVar3 * 0x5834 + param_1;
    "%-10d, %d, %d%%\n"[iVar2 + 0xc] = '\0';
    ("Quantum ID 1 value(unit 256us): %d\n" + iVar2)[0] = '\0';
    ("Quantum ID 1 value(unit 256us): %d\n" + iVar2)[1] = '\0';
    ("AVG mbss%d: tx -> %u(%u), rx -> %u(%u)\n" + iVar2 + 0xe)[0] = '\0';
    ("AVG mbss%d: tx -> %u(%u), rx -> %u(%u)\n" + iVar2 + 0xe)[1] = '\0';
    if (iVar4 < 3) {
      return;
    }
    printk("WscOnOff - OFF.\n");
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("WscOnOff - bWpsEnable = %d\n","%-10d, %d, %d%%\n"[uVar3 * 0x5834 + param_1 + 0xc]);
  return;
}

