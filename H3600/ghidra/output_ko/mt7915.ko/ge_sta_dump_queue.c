// module: mt7915.ko
// function: ge_sta_dump_queue @ 0xd0564
// size: 1700 bytes
//

void ge_sta_dump_queue(int param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  
  iVar6 = param_1 + 0x1c0;
  if (iVar6 + param_2 * 0x620 == -0x2f4e0) {
    if (DebugLevel < 1) {
      return;
    }
    printk("%s():Invalid entry(%p) or qidx(%d)\n","ge_sta_dump_queue",0);
    return;
  }
  if (0 < DebugLevel) {
    iVar3 = param_1 + param_2 * 0x620;
    pcVar2 = "PWR_ACTIVE";
    if (*(char *)(iVar3 + 0x2f72c) != '\0') {
      pcVar2 = "PWR_SAVE";
    }
    printk("\nDump TxQ[%d] of TR_ENTRY(ID:%d,\t\t\t\tMAC:%02x:%02x:%02x:%02x:%02x:%02x),\t\t\t\tenq_cap = %d, ps_state = %s\n"
           ,param_4,*(undefined2 *)(iVar6 + param_2 * 0x620 + 0x2f4e8),
           *(undefined1 *)(iVar3 + 0x2f6ab),*(undefined1 *)(iVar3 + 0x2f6ac),
           *(undefined1 *)(iVar3 + 0x2f6ad),*(undefined1 *)(iVar3 + 0x2f6ae),
           *(undefined1 *)(iVar3 + 0x2f6af),*(undefined1 *)(iVar3 + 0x2f6b0),
           *(undefined1 *)(iVar3 + 0x2f758),pcVar2);
  }
  if (param_3 == 0) {
    if (3 < param_4) {
      if (DebugLevel < 1) {
        return;
      }
      printk("unknown q_idx = %d\n",param_4);
      return;
    }
    iVar6 = iVar6 + (param_4 + param_2 * 0x188) * 4 + 0x2f574;
    _raw_spin_lock_bh(iVar6);
    piVar4 = *(int **)(param_1 + (param_4 + param_2 * 0x62 + 0x2f50) * 0x10 + 0x1c4);
    if (0 < DebugLevel) {
      pcVar2 = "Empty";
      if (piVar4 != (int *)0x0) {
        pcVar2 = "HasEntry";
      }
      printk("\nDump Entry %s\n",pcVar2);
    }
    if (piVar4 != (int *)0x0) {
      iVar3 = DebugLevel;
      uVar1 = 0;
LAB_000d06c4:
      do {
        uVar5 = uVar1;
        if (iVar3 < 1) {
          piVar4 = (int *)*piVar4;
          if (piVar4 == (int *)0x0) break;
LAB_000d0694:
          uVar1 = uVar5 + 1;
          if (uVar5 + 1 <= *(uint *)(param_1 + (param_4 + param_2 * 0x62) * 0x10 + 0x2f6cc))
          goto LAB_000d06c4;
        }
        else {
          printk(" 0x%p ",piVar4);
          piVar4 = (int *)*piVar4;
          iVar3 = DebugLevel;
          if (piVar4 != (int *)0x0) goto LAB_000d0694;
          if ((DebugLevel < 1) ||
             (printk(&_LC7), iVar3 = DebugLevel,
             uVar5 + 1 <= *(uint *)(param_1 + (param_2 * 0x62 + param_4) * 0x10 + 0x2f6cc))) break;
        }
        if (0 < iVar3) {
          printk("%s():Buggy here? Queue[%d] entry number(%d) not equal!\n","ge_sta_dump_queue",
                 param_4);
        }
        iVar3 = DebugLevel;
        uVar1 = uVar5 + 1;
      } while (piVar4 != (int *)0x0);
    }
  }
  else {
    if (param_3 != 6) {
      if (param_3 == 1) {
        iVar6 = param_1 + 0x285b98;
        _raw_spin_lock_bh(iVar6);
        piVar4 = *(int **)(param_1 + 0x285b9c);
        if (0 < DebugLevel) {
          pcVar2 = "Empty";
          if (piVar4 != (int *)0x0) {
            pcVar2 = "HasEntry";
          }
          printk("\nDump Entry %s\n",pcVar2);
        }
        if (piVar4 != (int *)0x0) {
          iVar3 = DebugLevel;
          uVar1 = 0;
LAB_000d0870:
          do {
            uVar5 = uVar1;
            if (iVar3 < 1) {
              piVar4 = (int *)*piVar4;
              if (piVar4 == (int *)0x0) break;
LAB_000d0850:
              uVar1 = uVar5 + 1;
              if (uVar5 + 1 <= *(uint *)(param_1 + 0x285ba4)) goto LAB_000d0870;
            }
            else {
              printk(" 0x%p ",piVar4);
              piVar4 = (int *)*piVar4;
              iVar3 = DebugLevel;
              if (piVar4 != (int *)0x0) goto LAB_000d0850;
              if ((DebugLevel < 1) ||
                 (printk(&_LC7), iVar3 = DebugLevel, uVar5 + 1 <= *(uint *)(param_1 + 0x285ba4)))
              break;
            }
            if (0 < iVar3) {
              printk("%s():Buggy here? Queue[%d] entry number(%d) not equal!\n","ge_sta_dump_queue",
                     param_4);
            }
            iVar3 = DebugLevel;
            uVar1 = uVar5 + 1;
          } while (piVar4 != (int *)0x0);
        }
      }
      else {
        if (param_3 != 2) {
          return;
        }
        iVar6 = param_1 + 0x285b3c;
        _raw_spin_lock_bh(iVar6);
        piVar4 = *(int **)(param_1 + 0x285b4c);
        if (0 < DebugLevel) {
          pcVar2 = "Empty";
          if (piVar4 != (int *)0x0) {
            pcVar2 = "HasEntry";
          }
          printk("\nDump Entry %s\n",pcVar2);
        }
        if (piVar4 != (int *)0x0) {
          iVar3 = DebugLevel;
          uVar1 = 0;
LAB_000d074c:
          do {
            uVar5 = uVar1;
            if (iVar3 < 1) {
              piVar4 = (int *)*piVar4;
              if (piVar4 == (int *)0x0) break;
LAB_000d072c:
              uVar1 = uVar5 + 1;
              if (uVar5 + 1 <= *(uint *)(param_1 + 0x285b54)) goto LAB_000d074c;
            }
            else {
              printk(" 0x%p ",piVar4);
              piVar4 = (int *)*piVar4;
              iVar3 = DebugLevel;
              if (piVar4 != (int *)0x0) goto LAB_000d072c;
              if ((DebugLevel < 1) ||
                 (printk(&_LC7), iVar3 = DebugLevel, uVar5 + 1 <= *(uint *)(param_1 + 0x285b54)))
              break;
            }
            if (0 < iVar3) {
              printk("%s():Buggy here? Queue[%d] entry number(%d) not equal!\n","ge_sta_dump_queue",
                     param_4);
            }
            iVar3 = DebugLevel;
            uVar1 = uVar5 + 1;
          } while (piVar4 != (int *)0x0);
        }
      }
      _raw_spin_unlock_bh(iVar6);
      return;
    }
    iVar6 = iVar6 + param_2 * 0x620 + 0x2f584;
    _raw_spin_lock_bh(iVar6);
    piVar4 = *(int **)(param_1 + param_2 * 0x620 + 0x2f704);
    if (0 < DebugLevel) {
      pcVar2 = "Empty";
      if (piVar4 != (int *)0x0) {
        pcVar2 = "HasEntry";
      }
      printk("\nDump Entry %s\n",pcVar2);
    }
    if (piVar4 != (int *)0x0) {
      iVar3 = DebugLevel;
      uVar1 = 0;
LAB_000d07f4:
      do {
        uVar5 = uVar1;
        if (iVar3 < 1) {
          piVar4 = (int *)*piVar4;
          if (piVar4 == (int *)0x0) break;
LAB_000d07c8:
          uVar1 = uVar5 + 1;
          if (uVar5 + 1 <= *(uint *)(param_1 + param_2 * 0x620 + 0x2f70c)) goto LAB_000d07f4;
        }
        else {
          printk(" 0x%p ",piVar4);
          piVar4 = (int *)*piVar4;
          iVar3 = DebugLevel;
          if (piVar4 != (int *)0x0) goto LAB_000d07c8;
          if ((DebugLevel < 1) ||
             (printk(&_LC7), iVar3 = DebugLevel,
             uVar5 + 1 <= *(uint *)(param_2 * 0x620 + param_1 + 0x2f70c))) break;
        }
        if (0 < iVar3) {
          printk("%s():Buggy here? Queue[%d] entry number(%d) not equal!\n","ge_sta_dump_queue",
                 param_4);
        }
        iVar3 = DebugLevel;
        uVar1 = uVar5 + 1;
      } while (piVar4 != (int *)0x0);
    }
  }
  _raw_spin_unlock_bh(iVar6);
  return;
}

