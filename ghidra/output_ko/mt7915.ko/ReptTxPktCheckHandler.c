// module: mt7915.ko
// function: ReptTxPktCheckHandler @ 0x83114
// size: 800 bytes
//

undefined4 ReptTxPktCheckHandler(int param_1,int param_2,int param_3,undefined2 *param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  
  iVar6 = *(int *)(param_3 + 0xcc);
  iVar8 = *(int *)(param_2 + 4);
  iVar7 = iVar6 + 6;
  bVar1 = *(byte *)(iVar6 + 0xd);
  uVar5 = (uint)CONCAT11(*(undefined1 *)(iVar6 + 0xc),bVar1);
  bVar9 = uVar5 == 0x8100;
  if (bVar9) {
    uVar5 = (uint)*(byte *)(iVar6 + 0x10);
    bVar1 = *(byte *)(iVar6 + 0x11);
  }
  if (bVar9) {
    uVar5 = (uint)bVar1 | uVar5 << 8;
  }
  iVar2 = RTMPLookupRepeaterCliEntry(param_1,1,iVar7,1);
  if ((iVar2 != 0) && (*(char *)(iVar2 + 1) != '\0')) {
    if (*(char *)(*(int *)(iVar2 + 0x4140) + 0xe) == *(char *)(iVar8 + 0xe)) {
      *param_4 = *(undefined2 *)(*(int *)(iVar2 + 0x4144) + 0xe0);
      return 0;
    }
    RepeaterDisconnectRootAP(param_1,iVar2,9);
    return 1;
  }
  uVar3 = HcGetBandByWdev(param_2);
  iVar2 = RTMPRepeaterVaildMacEntry(param_1,iVar7,uVar3);
  if (iVar2 != 0) {
    iVar8 = (uint)*(ushort *)(iVar8 + 0x2132e0) * 0x620;
    if ((param_1 + 0x1c0 + iVar8 + 0x2f4e0 != 0) && (*(char *)(param_1 + iVar8 + 0x2f762) == '\x01')
       ) {
      piVar4 = (int *)MacTableLookup(param_1,iVar7);
      if (uVar5 == 0x888e) {
        return 3;
      }
      if ((piVar4 == (int *)0x0) || (*piVar4 != 0x20001)) {
        if ((*(int *)(param_2 + 0x12e4) == 0) || (*(char *)(param_2 + 0x3cc8) != '\x01')) {
          HW_ADD_REPT_ENTRY(param_1,param_2,iVar7);
          if (DebugLevel < 2) {
            return 1;
          }
          printk("pAddr(%02x:%02x:%02x:%02x:%02x:%02x) use CliLink:%d to RootAP\n",
                 *(undefined1 *)(iVar6 + 6),*(undefined1 *)(iVar6 + 7),*(undefined1 *)(iVar6 + 8),
                 *(undefined1 *)(iVar6 + 9),*(undefined1 *)(iVar6 + 10),*(undefined1 *)(iVar6 + 0xb)
                 ,*(undefined1 *)(param_2 + 0xe));
          return 1;
        }
      }
      else {
        if ((param_1 + 0x1c0 + (uint)*(ushort *)(piVar4 + 0x38) * 0x620 + 0x2f4e0 != 0) &&
           (*(char *)(param_1 + (uint)*(ushort *)(piVar4 + 0x38) * 0x620 + 0x2f762) != '\x01')) {
          if (DebugLevel < 3) {
            return 1;
          }
          printk(" wireless client is not ready !!!\n");
          return 1;
        }
        iVar2 = piVar4[2];
        iVar8 = *(int *)(param_1 + (*(byte *)(iVar2 + 0xe) + 0x6d0d5) * 8 + 4);
        if (param_2 != iVar8 && *(char *)(iVar8 + 0x888) == '\x01') {
          return 2;
        }
        if ((*(int *)(param_2 + 0x12e4) == 0) || (*(char *)(param_2 + 0x3cc8) != '\x01')) {
          HW_ADD_REPT_ENTRY(param_1,param_2,iVar7);
          if (DebugLevel < 2) {
            return 1;
          }
          printk("pMacEntry(%02x:%02x:%02x:%02x:%02x:%02x) connect to mbss idx:%d, use CliLink:%d to RootAP\n"
                 ,*(undefined1 *)(iVar6 + 6),*(undefined1 *)(iVar6 + 7),*(undefined1 *)(iVar6 + 8),
                 *(undefined1 *)(iVar6 + 9),*(undefined1 *)(iVar6 + 10),*(undefined1 *)(iVar6 + 0xb)
                 ,*(undefined1 *)(iVar2 + 0xe),*(undefined1 *)(param_2 + 0xe));
          return 1;
        }
      }
      if (2 < DebugLevel) {
        printk("%s() WPS is triggered now, don\'t add entry\n","ReptTxPktCheckHandler");
      }
    }
  }
  return 2;
}

