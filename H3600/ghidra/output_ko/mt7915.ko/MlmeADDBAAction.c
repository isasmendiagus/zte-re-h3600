// module: mt7915.ko
// function: MlmeADDBAAction @ 0xa2754
// size: 684 bytes
//

void MlmeADDBAAction(int param_1,ushort *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 auStack_41 [24];
  undefined1 local_29;
  undefined1 local_28;
  undefined1 local_27;
  byte local_26;
  undefined1 local_25;
  ushort local_24;
  byte local_22;
  byte local_21;
  
  local_4c = 0;
  iVar1 = MlmeAddBAReqSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x484));
  if (iVar1 == 1) {
    __memzero(auStack_41,0x21);
    iVar1 = os_alloc_mem(param_1,&local_4c,0x900);
    if (iVar1 == 0) {
      uVar3 = (uint)*param_2;
      iVar1 = uVar3 * 0x14c0 + param_1;
      iVar4 = *(int *)(iVar1 + 0xa1d28);
      if (iVar4 == 0) {
        printk(&_LC24,0x88);
        dump_stack();
        iVar4 = *(int *)(iVar1 + 0xa1d28);
      }
      iVar1 = HcGetBandByWdev(iVar4);
      if ((*(char *)(uVar3 * 0x14c0 + param_1 + 0xa2282) == '\x01') &&
         (*(char *)(param_1 + uVar3 * 0x620 + 0x2f762) != '\x01')) {
        if (-1 < DebugLevel) {
          printk("%s: PMF connection, Ignore AddBaReq Send DUE TO NOT IN PORTSECURED\n",
                 "MlmeADDBAAction");
        }
        os_free_mem(local_4c);
      }
      else {
        ActHeaderInit(param_1,auStack_41,param_2 + 1,iVar4 + 0x1b,iVar4 + 0x21);
        local_29 = 3;
        local_28 = 0;
        uVar2 = 0;
        if ((char)param_2[8] != '\0') {
          uVar2 = (uint)(*(short *)(uVar3 * 0x14c0 + param_1 + 0xa29e8) == 0);
        }
        uVar2 = local_26 & 0xfffffffe | uVar2;
        local_26 = (byte)uVar2;
        uVar3 = *(uint *)(param_1 + iVar1 * 0x24 + 0xa7d18c);
        bVar5 = (uVar3 & 0x800) != 0;
        local_27 = *(undefined1 *)((int)param_2 + 0xd);
        if (bVar5) {
          uVar3 = uVar2;
        }
        local_24 = param_2[5];
        if (bVar5) {
          local_26 = (byte)uVar3 & 0xfe;
        }
        local_26 = local_26 & 3 | 2 | ((byte)param_2[6] & 0xf) << 2 | (char)param_2[4] << 6;
        local_25 = (undefined1)(((uint)param_2[4] << 0x16) >> 0x18);
        local_22 = local_22 & 0xf0;
        uVar3 = chip_get_tid_sn(param_1,*param_2);
        local_22 = local_22 & 0xf | (byte)((uVar3 & 0xf) << 4);
        local_21 = (byte)((uVar3 << 0x14) >> 0x18);
        MakeOutgoingFrame(local_4c,&local_48,0x21,auStack_41,0xffffffff);
        MiniportMMRequest(param_1,*(byte *)((int)&WMM_UP2AC_MAP + (uint)(byte)param_2[6]) | 0x80,
                          local_4c,local_48);
        os_free_mem(local_4c);
        if (2 < DebugLevel) {
          printk("BA - Send ADDBA request. StartSeq = %x,  FrameLen = %ld. BufSize = %d\n",
                 (uint)local_21 << 4 | (uint)(local_22 >> 4),local_48,param_2[4]);
        }
      }
    }
    else if (2 < DebugLevel) {
      printk("BA - MlmeADDBAAction() allocate memory failed\n");
    }
  }
  return;
}

