// module: mt7915.ko
// function: HQA_GetDumpRecal @ 0x26fdb8
// size: 1200 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void HQA_GetDumpRecal(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int extraout_r1;
  int extraout_r1_00;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint local_3c;
  
  iVar2 = param_1 + 0xa3b884;
  local_3c = 0;
  OS_SPIN_LOCK(iVar2);
  *(undefined1 *)(param_1 + 0xa3b889) = 1;
  OS_SPIN_UNLOCK(iVar2);
  iVar7 = DebugLevel;
  if (DebugLevel < 1) {
    *(undefined1 *)(param_1 + 0xa7cbda) = 1;
  }
  else {
    printk("[RECAL DUMP START][HQA_GetDumpRecal]\n");
    iVar7 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7cbda) = 1;
    if (0 < iVar7) {
      printk("log_cb->idx is %d, log_cb->len is %d\n",*(undefined4 *)(param_1 + 0xa3b88c),
             *(undefined4 *)(param_1 + 0xa3b890));
      iVar7 = DebugLevel;
    }
  }
  if ((*(char *)(param_1 + 0xa3ba94) == '\x01') || (*(char *)(param_1 + 0xa3ba96) == '\x01')) {
    _LANCHOR1 = 0;
  }
  if (0 < iVar7) {
    printk("idx: %d\n",_LANCHOR1);
    iVar7 = DebugLevel;
  }
  iVar3 = _LANCHOR1;
  iVar4 = *(int *)(param_1 + 0xa3b88c);
  iVar8 = *(int *)(param_1 + 0xa3b890);
  if (iVar4 < _LANCHOR1) {
    iVar4 = iVar4 + iVar8;
  }
  iVar4 = iVar4 - _LANCHOR1;
  if (iVar4 < 0x65) {
    iVar1 = iVar4 + _LANCHOR1;
  }
  else {
    iVar1 = _LANCHOR1 + 100;
  }
  __aeabi_idivmod(iVar1,iVar8);
  if (0 < iVar7) {
    printk("remindIdx: %d, end: %d\n",iVar4,extraout_r1);
    iVar8 = *(int *)(param_1 + 0xa3b890);
    iVar3 = _LANCHOR1;
  }
  uVar5 = 0;
  while( true ) {
    __aeabi_idivmod(iVar3,iVar8);
    iVar3 = *(int *)(param_1 + 0xa3b898) + extraout_r1_00 * 0x2c;
    iVar7 = extraout_r1_00;
    _LANCHOR1 = extraout_r1_00;
    if (*(char *)(iVar3 + 4) != '\0') {
      uVar10 = *(uint *)(iVar3 + 0xc);
      uVar6 = *(uint *)(iVar3 + 0x10);
      uVar9 = *(uint *)(iVar3 + 0x14);
      if (DebugLevel < 1) {
        *(undefined1 *)(iVar3 + 4) = 0;
      }
      else {
        printk("[Recal][%08x][%08x]%08x\n",uVar10,uVar6,uVar9);
        iVar7 = _LANCHOR1;
        *(undefined1 *)(*(int *)(param_1 + 0xa3b898) + _LANCHOR1 * 0x2c + 4) = 0;
      }
      uVar5 = uVar5 + 1;
      iVar3 = param_3 + local_3c * 4;
      local_3c = local_3c + 3;
      *(uint *)(iVar3 + 0x12) =
           uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
           uVar10 >> 0x18;
      *(uint *)(iVar3 + 0x16) =
           uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 | uVar6 >> 0x18
      ;
      *(uint *)(iVar3 + 0x1a) =
           uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 | uVar9 >> 0x18
      ;
    }
    if (*(char *)(param_1 + 0xa7cbdb) != '\0' && 0xd6 < uVar5) break;
    iVar8 = *(int *)(param_1 + 0xa3b890);
    _LANCHOR1 = iVar7 + 1;
    if (iVar8 <= iVar7 + 1) {
      _LANCHOR1 = 0;
    }
    iVar3 = _LANCHOR1;
    if (extraout_r1 == _LANCHOR1) {
LAB_0026ffb8:
      if (0 < DebugLevel) {
        printk("[After dumping] idx: %d, end: %d\n",_LANCHOR1,extraout_r1);
        if (2 < DebugLevel) {
          printk("[HQA_GetDumpRecal]: Total Count As a Group of three = %d\n",local_3c / 3,
                 local_3c * -0x55555555);
        }
      }
      local_3c = local_3c / 3;
      if ((*(int *)(param_1 + 0xa3b88c) == _LANCHOR1) && (*(char *)(param_1 + 0xa7cbda) != '\0')) {
        if (0 < DebugLevel) {
          printk("[RECAL DUMP END]\n");
        }
        *(undefined1 *)(param_1 + 0xa7cbda) = 0;
      }
      if (local_3c == 0) {
        *(undefined4 *)(param_3 + 0xe) = 0;
        FUN_0026cdd0(param_3,param_2,6,0);
        OS_SPIN_LOCK(iVar2);
        *(undefined1 *)(param_1 + 0xa3b889) = 0;
        OS_SPIN_UNLOCK(iVar2);
        if (*(int *)(param_1 + 0xa3ba98) == 0) {
          iVar7 = *(int *)(param_1 + 0xa39fd4);
          if (0 < DebugLevel) {
            printk("%s:LogOnOff, log_type:%d, log_ctrl:%d, log_size:%d\n","HQA_GetDumpRecal",
                   *(undefined4 *)(param_1 + 0xa3ba9c),*(undefined4 *)(param_1 + 0xa3baa0),
                   *(undefined4 *)(param_1 + 0xa3baa4));
          }
          (**(code **)(iVar7 + 0x100))
                    (param_1,*(undefined4 *)(param_1 + 0xa3ba9c),*(undefined4 *)(param_1 + 0xa3baa0)
                     ,*(undefined4 *)(param_1 + 0xa3baa4));
          *(undefined4 *)(param_1 + 0xa3ba9c) = 0;
          *(undefined4 *)(param_1 + 0xa3ba98) = 2;
          *(undefined4 *)(param_1 + 0xa3baa0) = 0;
          *(undefined4 *)(param_1 + 0xa3baa4) = 0;
          _LANCHOR1 = 0;
        }
      }
      else {
        uVar5 = local_3c >> 8 & 0xff;
        uVar6 = local_3c >> 0x10 & 0xff;
        *(uint *)(param_3 + 0xe) = local_3c << 0x18 | uVar5 << 0x10 | uVar6 << 8 | local_3c >> 0x18;
        FUN_0026cdd0(param_3,param_2,
                     ((local_3c >> 0x18) << 0x18 | uVar6 << 0x10 | uVar5 << 8 | local_3c & 0xff) *
                     0xc + 6,0);
      }
      *(undefined1 *)(param_1 + 0xa3ba94) = 0;
      *(undefined1 *)(param_1 + 0xa3ba96) = 0;
      return;
    }
  }
  *(short *)(param_1 + 0xa7cbd8) = (short)iVar7;
  goto LAB_0026ffb8;
}

