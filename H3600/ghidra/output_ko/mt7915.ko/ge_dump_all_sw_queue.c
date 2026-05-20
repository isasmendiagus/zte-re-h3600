// module: mt7915.ko
// function: ge_dump_all_sw_queue @ 0xcfef8
// size: 1640 bytes
//

undefined4 ge_dump_all_sw_queue(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  int *piVar12;
  char *local_34;
  
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  _raw_spin_lock_bh(param_1 + 0x285b3c);
  piVar7 = *(int **)(param_1 + 0x285b4c);
  if (0 < DebugLevel) {
    pcVar2 = "Empty";
    if (piVar7 != (int *)0x0) {
      pcVar2 = "HasEntry";
    }
    printk("\nDump management queue Entry %s\n",pcVar2);
  }
  if (piVar7 == (int *)0x0) {
    uVar9 = 0;
  }
  else {
    uVar9 = 0;
    iVar10 = DebugLevel;
LAB_000cff78:
    if (iVar10 < 3) {
      piVar7 = (int *)*piVar7;
      iVar3 = iVar10;
      if (piVar7 == (int *)0x0) goto LAB_000cff90;
LAB_000cff60:
      uVar9 = uVar9 + 1;
      iVar10 = iVar3;
      if ((*(uint *)(param_1 + 0x285b54) < uVar9) && (iVar10 = DebugLevel, -1 < iVar3)) {
        printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
        iVar10 = DebugLevel;
      }
      goto LAB_000cff78;
    }
    printk(" 0x%p ",piVar7);
    piVar7 = (int *)*piVar7;
    iVar3 = DebugLevel;
    if (piVar7 != (int *)0x0) goto LAB_000cff60;
    if (2 < DebugLevel) {
      printk(&_LC7);
    }
LAB_000cff90:
    uVar9 = uVar9 + 1;
    if ((*(uint *)(param_1 + 0x285b54) < uVar9) && (-1 < DebugLevel)) {
      printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
    }
  }
  _raw_spin_unlock_bh(param_1 + 0x285b3c);
  if (0 < DebugLevel) {
    printk("Count of management Entry = %d\n",uVar9);
  }
  _raw_spin_lock_bh(param_1 + 0x285b98);
  piVar7 = *(int **)(param_1 + 0x285b9c);
  if (0 < DebugLevel) {
    pcVar2 = "Empty";
    if (piVar7 != (int *)0x0) {
      pcVar2 = "HasEntry";
    }
    printk("\nDump high prority queue Entry %s\n",pcVar2);
  }
  if (piVar7 != (int *)0x0) {
    uVar9 = 0;
    iVar10 = DebugLevel;
LAB_000d000c:
    if (iVar10 < 3) {
      piVar7 = (int *)*piVar7;
      iVar3 = iVar10;
      if (piVar7 == (int *)0x0) goto LAB_000d0024;
    }
    else {
      printk(" 0x%p ",piVar7);
      piVar7 = (int *)*piVar7;
      iVar3 = DebugLevel;
      if (piVar7 == (int *)0x0) {
        if (2 < DebugLevel) {
          printk(&_LC7);
        }
LAB_000d0024:
        uVar9 = uVar9 + 1;
        if ((*(uint *)(param_1 + 0x285ba4) < uVar9) && (-1 < DebugLevel)) {
          printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
        }
        goto LAB_000d003c;
      }
    }
    uVar9 = uVar9 + 1;
    iVar10 = iVar3;
    if ((*(uint *)(param_1 + 0x285ba4) < uVar9) && (iVar10 = DebugLevel, -1 < iVar3)) {
      printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
      iVar10 = DebugLevel;
    }
    goto LAB_000d000c;
  }
  uVar9 = 0;
LAB_000d003c:
  _raw_spin_unlock_bh(param_1 + 0x285b98);
  if (0 < DebugLevel) {
    printk("Count of high prority queue Entry = %d\n",uVar9);
  }
  if (iVar1 != 0) {
    piVar8 = (int *)(param_1 + 0xa1d20);
    piVar7 = (int *)(param_1 + 0x2f6c4);
    iVar10 = 0;
    local_34 = "Empty";
    do {
      iVar3 = *piVar8;
      if ((iVar3 != 0) &&
         ((iVar3 != 2 && (iVar3 - 0x20001U & 0xfffdffff) != 0 || (piVar8[0x3f] == 2)))) {
        if (0 < DebugLevel) {
          pcVar2 = "PWR_ACTIVE";
          if ((char)piVar7[0x1a] != '\0') {
            pcVar2 = "PWR_SAVE";
          }
          printk("\nDump TR_ENTRY(ID:%d,\t\t\t\tMAC:%02x:%02x:%02x:%02x:%02x:%02x),\t\t\t\tenq_cap = %d, ps_state = %s\n"
                 ,(short)piVar7[-7],*(undefined1 *)((int)piVar7 + -0x19),(char)piVar7[-6],
                 *(undefined1 *)((int)piVar7 + -0x17),*(undefined1 *)((int)piVar7 + -0x16),
                 *(undefined1 *)((int)piVar7 + -0x15),(char)piVar7[-5],(char)piVar7[0x25],pcVar2);
        }
        _raw_spin_lock_bh(piVar7 + 0x20);
        piVar11 = (int *)piVar7[0x10];
        if (0 < DebugLevel) {
          pcVar2 = local_34;
          if (piVar11 != (int *)0x0) {
            pcVar2 = "HasEntry";
          }
          printk("\nDump wcid(%d) power saving queue Entry %s\n",iVar10,pcVar2);
        }
        if (piVar11 == (int *)0x0) {
          uVar9 = 0;
        }
        else {
          uVar9 = 0;
          iVar3 = DebugLevel;
LAB_000d0110:
          if (iVar3 < 3) {
            piVar11 = (int *)*piVar11;
            iVar5 = iVar3;
            if (piVar11 == (int *)0x0) goto LAB_000d0128;
LAB_000d00f8:
            uVar9 = uVar9 + 1;
            iVar3 = iVar5;
            if (((uint)piVar7[0x12] < uVar9) && (iVar3 = DebugLevel, -1 < iVar5)) {
              printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
              iVar3 = DebugLevel;
            }
            goto LAB_000d0110;
          }
          printk(" 0x%p ",piVar11);
          piVar11 = (int *)*piVar11;
          iVar5 = DebugLevel;
          if (piVar11 != (int *)0x0) goto LAB_000d00f8;
          if (2 < DebugLevel) {
            printk(&_LC7);
          }
LAB_000d0128:
          uVar9 = uVar9 + 1;
          if (((uint)piVar7[0x12] < uVar9) && (-1 < DebugLevel)) {
            printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
          }
        }
        _raw_spin_unlock_bh(piVar7 + 0x20);
        if (0 < DebugLevel) {
          printk("Count of wcid(%d) power saving Entry = %d\n",iVar10,uVar9);
        }
        piVar6 = piVar7 + 0x1c;
        iVar3 = 0;
        piVar11 = piVar7;
        do {
          _raw_spin_lock_bh(piVar6);
          piVar12 = (int *)*piVar11;
          if (0 < DebugLevel) {
            pcVar2 = local_34;
            if (piVar12 != (int *)0x0) {
              pcVar2 = "HasEntry";
            }
            printk("\nDump wcid(%d), qidx(%d) data queue Entry %s\n",iVar10,iVar3,pcVar2);
          }
          if (piVar12 == (int *)0x0) {
            uVar9 = 0;
          }
          else {
            uVar9 = 0;
            iVar5 = DebugLevel;
LAB_000d01ac:
            if (iVar5 < 3) {
              piVar12 = (int *)*piVar12;
              iVar4 = iVar5;
              if (piVar12 == (int *)0x0) goto LAB_000d01c4;
LAB_000d0194:
              uVar9 = uVar9 + 1;
              iVar5 = iVar4;
              if (((uint)piVar11[2] < uVar9) && (iVar5 = DebugLevel, -1 < iVar4)) {
                printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
                iVar5 = DebugLevel;
              }
              goto LAB_000d01ac;
            }
            printk(" 0x%p ",piVar12);
            piVar12 = (int *)*piVar12;
            iVar4 = DebugLevel;
            if (piVar12 != (int *)0x0) goto LAB_000d0194;
            if (2 < DebugLevel) {
              printk(&_LC7);
            }
LAB_000d01c4:
            uVar9 = uVar9 + 1;
            if (((uint)piVar11[2] < uVar9) && (-1 < DebugLevel)) {
              printk("%s():Buggy here? entry number(%d) not equal!\n","ge_dump_all_sw_queue");
            }
          }
          _raw_spin_unlock_bh(piVar6);
          if (0 < DebugLevel) {
            printk("Count of wcid(%d), qidx(%d) data Entry = %d\n",iVar10,iVar3,uVar9);
          }
          iVar3 = iVar3 + 1;
          piVar6 = piVar6 + 1;
          piVar11 = piVar11 + 4;
        } while (iVar3 != 4);
      }
      iVar10 = iVar10 + 1;
      piVar8 = piVar8 + 0x530;
      piVar7 = piVar7 + 0x188;
    } while (iVar1 != iVar10);
  }
  return 0;
}

