// module: mt7915.ko
// function: MT_ATEDumpLog @ 0x281ba8
// size: 632 bytes
//

undefined4 MT_ATEDumpLog(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  undefined4 *puVar5;
  char *local_68;
  undefined2 local_64;
  
  iVar1 = DebugLevel;
  if (*(int *)(param_2 + 0x14) == 0) {
    return 0xffffffff;
  }
  uVar2 = 0;
  if (*(char *)(param_1 + 0xa7cbdb) != '\0') {
    uVar2 = (uint)*(ushort *)(param_1 + 0xa7cbd8);
  }
  if (*(char *)(param_2 + 6) != '\0') {
    uVar2 = *(uint *)(param_2 + 8);
  }
  if (2 < DebugLevel) {
    printk("%s: idx:%d, log_type:%08x, log_cb->idx:%d\n","MT_ATEDumpLog",uVar2,param_3,
           *(undefined4 *)(param_2 + 8));
  }
  if (param_3 == 2) {
    pcVar4 = MT_ATERDDParseResult;
    local_68 = s_muruTxCMuTrigTx_0044444c + 6;
  }
  else if (param_3 == 3) {
    pcVar4 = MT_ATEDumpReCal;
    local_68 = (char *)0x41434552;
    local_64 = 0x4c;
  }
  else {
    if (param_3 != 1) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      printk("%s: Unknown log type %08x\n","MT_ATEDumpLog",param_3);
      return 0xffffffff;
    }
    pcVar4 = MT_ATEDumpRXV;
    local_68 = &DAT_00474f4c;
  }
  DebugLevel = 1;
  OS_SPIN_LOCK(param_2);
  *(undefined1 *)(param_2 + 5) = 1;
  OS_SPIN_UNLOCK(param_2);
  if (0 < DebugLevel) {
    printk("[%s DUMP START]\n",&local_68);
  }
  uVar3 = 0;
  *(undefined1 *)(param_1 + 0xa7cbda) = 1;
  do {
    puVar5 = (undefined4 *)(*(int *)(param_2 + 0x14) + uVar2 * 0x2c);
    if (*(char *)(puVar5 + 1) == '\0') {
      if (*(char *)(param_1 + 0xa7cbdb) != '\0' && 0xd6 < uVar3) goto LAB_00281d20;
    }
    else {
      uVar3 = uVar3 + 1;
      (*pcVar4)(*puVar5,puVar5[1],puVar5[2],puVar5[3],puVar5[4],puVar5[5],puVar5[6],puVar5[7],
                puVar5[8],puVar5[9],puVar5[10],uVar2);
      *(undefined1 *)(*(int *)(param_2 + 0x14) + uVar2 * 0x2c + 4) = 0;
      if (*(char *)(param_1 + 0xa7cbdb) != '\0' && 0xd6 < uVar3) {
LAB_00281d20:
        *(short *)(param_1 + 0xa7cbd8) = (short)uVar2;
        if (uVar2 != *(uint *)(param_2 + 8)) goto LAB_00281d34;
        break;
      }
    }
    uVar2 = uVar2 + 1;
    if (*(int *)(param_2 + 0xc) <= (int)uVar2) {
      uVar2 = 0;
    }
  } while (*(uint *)(param_2 + 8) != uVar2);
  if (*(char *)(param_1 + 0xa7cbda) != '\0') {
    if (0 < DebugLevel) {
      printk("[%s DUMP END]\n",&local_68);
    }
    *(undefined1 *)(param_1 + 0xa7cbda) = 0;
  }
LAB_00281d34:
  OS_SPIN_LOCK(param_2);
  *(undefined1 *)(param_2 + 5) = 0;
  OS_SPIN_UNLOCK(param_2);
  DebugLevel = iVar1;
  return 0;
}

