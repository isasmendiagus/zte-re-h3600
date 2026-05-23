// module: mt7915.ko
// function: MT_ATEInsertLog @ 0x281464
// size: 612 bytes
//

undefined4 MT_ATEInsertLog(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  code *pcVar8;
  
  if (param_3 == 4) {
    iVar7 = 1;
    pcVar8 = MT_ATEInsertRDD;
  }
  else if (param_3 == 8) {
    iVar7 = 2;
    pcVar8 = MT_ATEInsertReCal;
  }
  else {
    if (param_3 != 2) {
      if (-1 < DebugLevel) {
        printk("%s: Unknown log type %08x\n","MT_ATEInsertLog");
      }
      goto LAB_002814a4;
    }
    iVar7 = 0;
    pcVar8 = MT_ATEInsertRXV;
  }
  iVar5 = param_1 + 0xa39000 + iVar7 * 0x18;
  iVar6 = param_1 + iVar7 * 0x18 + 0xa3b854;
  iVar4 = *(int *)(iVar5 + 0x285c);
  OS_SPIN_LOCK(iVar6);
  cVar1 = *(char *)(iVar5 + 0x2859);
  OS_SPIN_UNLOCK(iVar6);
  if (cVar1 != '\0') goto LAB_002814a4;
  if (*(int *)(iVar5 + 0x285c) + 1 == *(int *)(iVar5 + 0x2860)) {
    if (*(char *)(iVar5 + 0x2858) != '\0') {
      *(undefined1 *)(iVar5 + 0x285a) = 1;
      goto LAB_0028154c;
    }
  }
  else {
LAB_0028154c:
    OS_SPIN_LOCK(iVar6);
    iVar5 = param_1 + 0xa39000 + iVar7 * 0x18;
    if (*(int *)(iVar5 + 0x2868) == 0) {
      OS_SPIN_UNLOCK(iVar6);
    }
    else {
      iVar2 = (*pcVar8)(*(int *)(iVar5 + 0x2868) + iVar4 * 0x2c,param_2,param_4);
      OS_SPIN_UNLOCK(iVar6);
      if (iVar2 == 0) {
        iVar6 = *(int *)(iVar5 + 0x285c) + 1;
        *(int *)(iVar5 + 0x285c) = iVar6;
        if (*(int *)(iVar5 + 0x2860) <= iVar6) {
          *(undefined4 *)(iVar5 + 0x285c) = 0;
        }
        if (DebugLevel < 5) {
          return 0;
        }
        printk("%s: idx:%d, log_cb->idx:%d, log_type:%08x\n","MT_ATEInsertLog",iVar4,
               *(undefined4 *)(iVar7 * 0x18 + param_1 + 0xa30000 + 0xb85c),param_3);
        return 0;
      }
    }
  }
  if (DebugLevel < 2) {
    return 0xfffffffd;
  }
  if (iVar6 == 0) {
    uVar3 = 0xff;
  }
  else {
    uVar3 = *(undefined1 *)(iVar7 * 0x18 + param_1 + 0xa30000 + 0xb858);
  }
  printk("[WARN]%s: idx:%x, overwritable:%x, log_type:%08x\n","MT_ATEInsertLog",iVar4,uVar3,param_3)
  ;
LAB_002814a4:
  if (1 < DebugLevel) {
    printk("%s: Log dumping\n","MT_ATEInsertLog");
  }
  return 0xfffffffd;
}

