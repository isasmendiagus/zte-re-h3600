// module: mt7915.ko
// function: ShowProgTrace @ 0x193a08
// size: 916 bytes
//

void ShowProgTrace(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int local_30;
  int local_2c;
  uint local_28;
  undefined4 local_24;
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  os_alloc_mem(0,&local_30,0x480);
  if (local_30 == 0) {
    if (-1 < DebugLevel) {
      printk("%s : msg_trace Allocate memory fail!!!\n","ShowProgTrace");
    }
  }
  else {
    __memzero(local_30,0x480);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f0e0,&local_2c);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f0e8,&local_24);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),local_24,&local_28);
    local_28 = local_28 & 0xff;
    iVar8 = local_30 + 0x480;
    iVar7 = local_2c - local_30;
    iVar4 = local_30;
    if (0x1f < local_28) {
      local_28 = 0;
    }
    do {
      iVar5 = iVar4 + 4;
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar4 + iVar7,iVar4);
      iVar4 = iVar5;
    } while (iVar5 != iVar8);
    if ((0 < DebugLevel) && (printk(&_LC12), 0 < DebugLevel)) {
      printk("       prog trace:\n");
    }
    iVar7 = 0x20;
    iVar4 = local_30;
    do {
      uVar6 = local_28 + 0x1f & 0x1f;
      if (DebugLevel < 1) {
LAB_00193b40:
        piVar3 = (int *)(iVar4 + local_28 * 0x24);
        piVar9 = (int *)(iVar4 + uVar6 * 0x24);
        iVar5 = piVar3[4];
        iVar8 = piVar9[4];
        if (iVar8 == 0) goto LAB_00193ae8;
LAB_00193b64:
        if (((*piVar9 != *piVar3) || (piVar9[2] != piVar3[2])) || (iVar5 - iVar8 == -1))
        goto LAB_00193b74;
        if (0 < DebugLevel) {
          printk("diff4=%8d, ");
          goto LAB_00193c44;
        }
        iVar8 = piVar9[3];
        iVar5 = piVar3[3];
        if (iVar8 != 0) goto LAB_00193bc0;
      }
      else {
        iVar5 = iVar4 + local_28 * 0x24;
        iVar8 = iVar5 + 0x18;
        uVar10 = *(undefined4 *)(iVar5 + 4);
        uVar11 = *(undefined4 *)(iVar5 + 0x14);
        uVar12 = *(undefined4 *)(iVar5 + 0x10);
        printk("       (p_%d)t_id=%x/%d, m_id=%d, LP=0x%p, name=%s, ts4=%d, ",local_28,
               *(undefined4 *)(iVar4 + local_28 * 0x24),*(undefined4 *)(iVar5 + 8),uVar10,uVar11,
               iVar8,uVar12);
        iVar4 = local_30;
        if (DebugLevel < 1) goto LAB_00193b40;
        iVar4 = local_30 + local_28 * 0x24;
        printk("ts2=%d, ",*(undefined4 *)(iVar4 + 0xc),local_30,iVar4,uVar10,uVar11,iVar8,uVar12);
        piVar9 = (int *)(local_30 + uVar6 * 0x24);
        iVar8 = piVar9[4];
        piVar3 = (int *)(local_30 + local_28 * 0x24);
        iVar5 = piVar3[4];
        iVar4 = local_30;
        if (iVar8 != 0) goto LAB_00193b64;
LAB_00193b74:
        if (DebugLevel < 1) {
LAB_00193ae8:
          iVar8 = piVar9[3];
          iVar5 = piVar3[3];
          if (((iVar8 != 0) && (*piVar9 == *piVar3)) && (piVar9[2] == piVar3[2])) goto LAB_00193bc0;
        }
        else {
          printk("diff4=NA, ");
LAB_00193c44:
          iVar1 = local_30 + uVar6 * 0x24;
          iVar8 = *(int *)(iVar1 + 0xc);
          iVar2 = local_30 + local_28 * 0x24;
          iVar5 = *(int *)(iVar2 + 0xc);
          iVar4 = local_30;
          if (((iVar8 != 0) &&
              (*(int *)(local_30 + uVar6 * 0x24) == *(int *)(local_30 + local_28 * 0x24))) &&
             (*(int *)(iVar1 + 8) == *(int *)(iVar2 + 8))) {
LAB_00193bc0:
            if (iVar5 - iVar8 != -1) {
              if (0 < DebugLevel) {
                printk("diff2=%8d\n");
                iVar4 = local_30;
              }
              goto LAB_00193b0c;
            }
          }
          if (0 < DebugLevel) {
            printk("diff2=NA\n");
            iVar4 = local_30;
          }
        }
      }
LAB_00193b0c:
      local_28 = local_28 + 1;
      if (0x1f < local_28) {
        local_28 = 0;
      }
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    os_free_mem(iVar4);
  }
  return;
}

