// module: mt7915.ko
// function: RTMPInsertRepeaterEntry @ 0x81b90
// size: 1240 bytes
//

void RTMPInsertRepeaterEntry(int param_1,int param_2,undefined4 *param_3)

{
  undefined1 uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined *puVar10;
  uint uVar11;
  void *__s1;
  int iVar12;
  int iVar13;
  bool bVar14;
  undefined1 local_34;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar4 = HcGetBandByWdev(param_2);
  if (2 < DebugLevel) {
    printk(&_LC48,"RTMPInsertRepeaterEntry");
  }
  iVar6 = param_1 + iVar4;
  puVar10 = &DAT_00367914 + param_1;
  _raw_spin_lock_bh(puVar10);
  uVar7 = (uint)*(byte *)(iVar3 + 0x14a);
  bVar2 = __aeabi_uidiv(uVar7,*(undefined1 *)(iVar3 + 0x1c4));
  if ((byte)(&DAT_00367912)[iVar6] < bVar2) {
    if (uVar7 != 0) {
      iVar3 = *(int *)(&DAT_003687a8 + param_1);
      uVar11 = 0;
      __s1 = (void *)(iVar3 + 0x83);
      uVar9 = uVar7;
      do {
        if (*(char *)((int)__s1 + -0x83) == '\0') {
          if (uVar9 == uVar7) {
            uVar9 = uVar11;
          }
        }
        else {
          iVar4 = memcmp((void *)((int)__s1 + -6),param_3,6);
          if ((iVar4 == 0) ||
             (((&DAT_00367910)[param_1] != '\x02' && (iVar4 = memcmp(__s1,param_3,6), iVar4 == 0))))
          {
            _raw_spin_unlock_bh(puVar10);
            if (DebugLevel < 4) {
              return;
            }
            printk("\n  receive mac :%02x:%02x:%02x:%02x:%02x:%02x !!!\n",*(undefined1 *)param_3,
                   *(undefined1 *)((int)param_3 + 1),*(undefined1 *)((int)param_3 + 2),
                   *(undefined1 *)((int)param_3 + 3),*(undefined1 *)(param_3 + 1),
                   *(undefined1 *)((int)param_3 + 5));
            if (DebugLevel < 4) {
              return;
            }
            pcVar5 = " duplicate Insert !!!\n";
            goto LAB_00081fe4;
          }
        }
        uVar11 = uVar11 + 1;
        __s1 = (void *)((int)__s1 + 0x42f4);
      } while (uVar7 != uVar11);
      if ((int)uVar9 < (int)uVar7) {
        iVar8 = iVar3 + uVar9 * 0x42f4;
        iVar4 = *(int *)(&DAT_003687ac + param_1);
        RTMPInitTimer(param_1,iVar8 + 8,rtmp_timer_ApCliAssocTimeoutExt,iVar8,0);
        iVar13 = iVar4 + uVar9 * 8;
        iVar12 = iVar8 + 0x83;
        RTMPInitTimer(param_1,iVar8 + 0x3c,rtmp_timer_ApCliAuthTimeoutExt,iVar8,0);
        *(undefined1 *)(iVar8 + 5) = 0;
        *(undefined1 *)(iVar8 + 6) = 0;
        *(undefined4 *)(iVar8 + 0x98) = 0;
        *(undefined4 *)(iVar8 + 0x94) = 0;
        *(undefined1 *)(iVar8 + 1) = 0;
        local_34 = (undefined1)uVar9;
        *(undefined1 *)(iVar8 + 2) = local_34;
        *(undefined4 *)(iVar8 + 0x4144) = 0;
        *(undefined4 *)(iVar8 + 0x4148) = 0;
        *(undefined1 *)(iVar8 + 3) = 0;
        *(undefined2 *)(iVar8 + 0x70) = 0;
        *(undefined2 *)(iVar8 + 0x72) = 0;
        *(undefined4 *)(iVar8 + 0x74) = 0;
        *(undefined4 *)(iVar8 + 0x90) = 0;
        *(int *)(iVar8 + 0x4140) = param_2;
        *(int *)(iVar4 + uVar9 * 8) = iVar8;
        uVar1 = (&DAT_00580eeb)[param_1 + (uint)*(byte *)(param_2 + 0xe) * 0x2137b0];
        *(undefined4 *)(iVar8 + 0x42ac) = 0;
        *(undefined1 *)(iVar8 + 0x42b0) = uVar1;
        *(undefined4 *)(iVar13 + 4) = 0;
        *(undefined4 *)(iVar8 + 0x7d) = *param_3;
        *(undefined2 *)(iVar8 + 0x81) = *(undefined2 *)(param_3 + 1);
        iVar4 = RepeaterAssignMacAddress(param_1,(&DAT_00367910)[param_1],param_3,iVar12);
        if (iVar4 == 0) {
          return;
        }
        *(undefined1 *)(iVar3 + uVar9 * 0x42f4) = 1;
        *(undefined1 *)(iVar8 + 5) = 1;
        *(undefined4 *)(iVar8 + 0x90) = 0;
        bVar14 = -1 < DebugLevel;
        *(undefined4 *)(iVar8 + 0x74) = jiffies;
        if (bVar14) {
          printk("%s:repeater_entry_time(%ld)\n","RTMPInsertRepeaterEntry");
        }
        (&DAT_00367912)[iVar6] = (&DAT_00367912)[iVar6] + '\x01';
        _raw_spin_unlock_bh(puVar10);
        RepeaterInitWdev(param_1,iVar8,param_2,iVar8 + 0xe0);
        AsicInsertRepeaterEntry(param_1,uVar9 & 0xff,iVar12);
        _raw_spin_lock_bh(puVar10);
        iVar4 = param_1 + (uint)(byte)(*(byte *)(iVar8 + 0x88) ^
                                      *(byte *)(iVar8 + 0x87) ^
                                      *(byte *)(iVar8 + 0x84) ^ *(byte *)(iVar8 + 0x83) ^
                                      *(byte *)(iVar8 + 0x85) ^ *(byte *)(iVar8 + 0x86)) * 4;
        iVar3 = *(int *)(&DAT_00367918 + iVar4);
        if (*(int *)(&DAT_00367918 + iVar4) == 0) {
          *(int *)(&DAT_00367918 + iVar4) = iVar8;
        }
        else {
          do {
            iVar4 = iVar3;
            iVar3 = *(int *)(iVar4 + 0x90);
          } while (iVar3 != 0);
          *(int *)(iVar4 + 0x90) = iVar8;
        }
        iVar4 = param_1 + (uint)(byte)(*(byte *)(iVar8 + 0x82) ^
                                      *(byte *)(iVar8 + 0x81) ^
                                      *(byte *)(iVar8 + 0x7e) ^ *(byte *)(iVar8 + 0x7d) ^
                                      *(byte *)(iVar8 + 0x7f) ^ *(byte *)(iVar8 + 0x80)) * 4;
        iVar3 = *(int *)(&DAT_00367d18 + iVar4);
        if (*(int *)(&DAT_00367d18 + iVar4) == 0) {
          *(int *)(&DAT_00367d18 + iVar4) = iVar13;
        }
        else {
          do {
            iVar4 = iVar3;
            iVar3 = *(int *)(iVar4 + 4);
          } while (iVar3 != 0);
          *(int *)(iVar4 + 4) = iVar13;
        }
        _raw_spin_unlock_bh(puVar10);
        cntl_join_start_conf(iVar8 + 0xe0,0);
        RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,3,0,iVar12,6);
        return;
      }
    }
    _raw_spin_unlock_bh(puVar10);
    if (-1 < DebugLevel) {
      pcVar5 = "Repeater Pool Full !!!\n";
LAB_00081fe4:
      printk(pcVar5);
      return;
    }
  }
  else {
    _raw_spin_unlock_bh(puVar10);
    if (-1 < DebugLevel) {
      printk("band(%d) Repeater Client Full !!!\n",iVar4);
      return;
    }
  }
  return;
}

