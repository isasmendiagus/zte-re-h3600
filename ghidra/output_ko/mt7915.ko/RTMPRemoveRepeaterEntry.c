// module: mt7915.ko
// function: RTMPRemoveRepeaterEntry @ 0x8206c
// size: 1072 bytes
//

void RTMPRemoveRepeaterEntry(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined1 auStack_29 [5];
  
  if (-1 < DebugLevel) {
    printk(" %s.CliIdx=%d\n","RTMPRemoveRepeaterEntry",param_2);
  }
  puVar8 = &DAT_00367914 + param_1;
  iVar7 = param_2 * 0x42f4;
  AsicRemoveRepeaterEntry(param_1,param_2);
  _raw_spin_lock_bh(puVar8);
  iVar9 = *(int *)(&DAT_003687a8 + param_1);
  iVar12 = iVar9 + iVar7;
  if (iVar12 == 0) {
    _raw_spin_unlock_bh(puVar8);
    if (-1 < DebugLevel) {
      printk("%s - pEntry is NULL !!!\n","RTMPRemoveRepeaterEntry");
    }
  }
  else {
    iVar11 = iVar12 + 0xe0;
    iVar5 = HcGetBandByWdev(iVar11);
    if (*(char *)(iVar9 + iVar7) != '\0') {
      if (*(int *)(iVar12 + 0x4144) != 0) {
        mac_entry_delete(param_1);
      }
      HcDelRepeaterEntry(iVar11);
      wdev_deinit(param_1,iVar11);
      iVar6 = param_1 + (uint)(byte)(*(byte *)(iVar12 + 0x84) ^ *(byte *)(iVar12 + 0x83) ^
                                     *(byte *)(iVar12 + 0x85) ^ *(byte *)(iVar12 + 0x86) ^
                                     *(byte *)(iVar12 + 0x87) ^ *(byte *)(iVar12 + 0x88)) * 4;
      iVar11 = *(int *)(&DAT_00367918 + iVar6);
      if (iVar11 == 0) {
        printk(&_LC57,0x464);
        dump_stack();
        bVar1 = false;
      }
      else if (iVar12 == iVar11) {
LAB_000823cc:
        *(undefined4 *)(&DAT_00367918 + iVar6) = *(undefined4 *)(iVar12 + 0x90);
LAB_000821a4:
        iVar6 = param_1 + (uint)(byte)(*(byte *)(iVar12 + 0x7e) ^ *(byte *)(iVar12 + 0x7d) ^
                                       *(byte *)(iVar12 + 0x7f) ^ *(byte *)(iVar12 + 0x80) ^
                                       *(byte *)(iVar12 + 0x81) ^ *(byte *)(iVar12 + 0x82)) * 4;
        iVar10 = *(int *)(&DAT_003687ac + param_1) + param_2 * 8;
        iVar11 = *(int *)(&DAT_00367d18 + iVar6);
        if (iVar11 == 0) {
          printk(&_LC58,0x488);
          dump_stack();
        }
        else {
          if (iVar10 == iVar11) {
LAB_000823dc:
            *(undefined4 *)(&DAT_00367d18 + iVar6) = *(undefined4 *)(iVar10 + 4);
LAB_00082238:
            bVar1 = true;
            goto LAB_00082288;
          }
          for (iVar2 = *(int *)(iVar11 + 4); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
            if (iVar10 == iVar2) {
              if (iVar11 == 0) goto LAB_000823dc;
              *(undefined4 *)(iVar11 + 4) = *(undefined4 *)(iVar10 + 4);
              goto LAB_00082238;
            }
            iVar11 = iVar2;
          }
        }
        bVar1 = true;
        printk(&_LC62,0x49c);
        dump_stack();
      }
      else {
        for (iVar10 = *(int *)(iVar11 + 0x90); iVar10 != 0; iVar10 = *(int *)(iVar10 + 0x90)) {
          if (iVar12 == iVar10) {
            if (iVar11 == 0) goto LAB_000823cc;
            *(undefined4 *)(iVar11 + 0x90) = *(undefined4 *)(iVar12 + 0x90);
            goto LAB_000821a4;
          }
          iVar11 = iVar10;
        }
        bVar1 = false;
        printk(&_LC61,0x47d);
        dump_stack();
      }
LAB_00082288:
      RTMPReleaseTimer(iVar12 + 0x3c,auStack_29);
      RTMPReleaseTimer(iVar12 + 8,auStack_29);
      if (0 < DebugLevel) {
        printk("%s:real=%02x:%02x:%02x:%02x:%02x:%02x,fake=%02x:%02x:%02x:%02x:%02x:%02x\n",
               "RTMPRemoveRepeaterEntry",*(undefined1 *)(iVar12 + 0x7d),
               *(undefined1 *)(iVar12 + 0x7e),*(undefined1 *)(iVar12 + 0x7f),
               *(undefined1 *)(iVar12 + 0x80),*(undefined1 *)(iVar12 + 0x81),
               *(undefined1 *)(iVar12 + 0x82),*(undefined1 *)(iVar12 + 0x83),
               *(undefined1 *)(iVar12 + 0x84),*(undefined1 *)(iVar12 + 0x85),
               *(undefined1 *)(iVar12 + 0x86),*(undefined1 *)(iVar12 + 0x87),
               *(undefined1 *)(iVar12 + 0x88));
      }
      *(undefined1 *)(iVar12 + 5) = 0;
      *(undefined1 *)(iVar12 + 1) = 0;
      *(undefined1 *)(iVar12 + 6) = 0;
      *(undefined1 *)(iVar9 + iVar7) = 0;
      *(undefined1 *)(iVar12 + 2) = 0;
      *(undefined4 *)(iVar12 + 0x4144) = 0;
      *(undefined4 *)(iVar12 + 0x4148) = 0;
      *(undefined1 *)(iVar12 + 3) = 0;
      uVar4 = ZERO_MAC_ADDR._4_2_;
      uVar3 = (undefined4)ZERO_MAC_ADDR;
      *(undefined1 *)(iVar12 + 0x7c) = 0;
      *(undefined4 *)(iVar12 + 0x7d) = uVar3;
      *(undefined4 *)(iVar12 + 0x83) = uVar3;
      *(undefined2 *)(iVar12 + 0x81) = uVar4;
      *(undefined2 *)(iVar12 + 0x87) = uVar4;
      if (bVar1) {
        (&DAT_00367912)[param_1 + iVar5] = (&DAT_00367912)[param_1 + iVar5] + -1;
      }
      complete(iVar12 + 0x9c);
      _raw_spin_unlock_bh(puVar8);
      if (0 < DebugLevel) {
        printk("Remove MacRep Sta:%pM\n",iVar12 + 0x83);
      }
      RtmpOSWrielessEventSend(*(undefined4 *)(iVar12 + 0xe0),1,4,0,iVar12 + 0x83,6);
      return;
    }
    _raw_spin_unlock_bh(puVar8);
    if (-1 < DebugLevel) {
      printk("%s - CliIdx:%d Enable is FALSE already\n","RTMPRemoveRepeaterEntry",param_2);
    }
  }
  return;
}

