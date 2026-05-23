// module: mt7915.ko
// function: BfSwitch @ 0x22f5b8
// size: 632 bytes
//

void BfSwitch(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  undefined1 *puVar7;
  int iVar8;
  void *pvVar9;
  void *local_ec;
  undefined1 auStack_e7 [11];
  byte local_dc;
  
  local_ec = (void *)0x0;
  iVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = iVar2 + -1;
  if (param_2 == 0) {
    os_alloc_mem(param_1,&local_ec,0xb8);
    if (local_ec != (void *)0x0) {
      pvVar9 = local_ec;
      if (0 < iVar2) {
        puVar7 = (undefined1 *)(param_1 + 0xa79634);
        uVar5 = 1;
        do {
          iVar8 = 0;
          uVar1 = *(ushort *)("Get_System_CapNode_Info" + param_1 + 0x10);
          iVar4 = *(int *)("Get_System_CenFreq_Info" + param_1);
          do {
            hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar8 + uVar5 * uVar1 + iVar4,
                         (int)pvVar9 + iVar8);
            pvVar9 = local_ec;
            iVar8 = iVar8 + 4;
          } while (iVar8 != 0xbc);
          memcpy(auStack_e7,local_ec,0xb8);
          if ((local_dc & 2) == 0) {
            if ((local_dc & 4) != 0) {
              *puVar7 = 2;
              goto LAB_0022f76c;
            }
            *puVar7 = 0;
          }
          else {
            *puVar7 = 1;
LAB_0022f76c:
            if (-1 < DebugLevel) {
              printk("%s():Disable wcid %d BF!\n","BfSwitch",uVar5);
            }
            CmdTxBfTxApplyCtrl(param_1,uVar5 & 0xffff,0,0,0,0);
            pvVar9 = local_ec;
          }
          uVar5 = uVar5 + 1;
          puVar7 = puVar7 + 1;
        } while ((int)uVar5 <= iVar2);
      }
      os_free_mem(pvVar9);
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s():AllocMem fail!\n","BfSwitch");
      return;
    }
  }
  else if (0 < iVar2) {
    pcVar6 = (char *)(param_1 + 0xa79633);
    uVar5 = 1;
    do {
      while( true ) {
        pcVar6 = pcVar6 + 1;
        if (*pcVar6 != '\x01') break;
        if (-1 < DebugLevel) {
          printk("%s():Enable wcid %d iBF!\n","BfSwitch",uVar5);
        }
        uVar3 = uVar5 & 0xffff;
        uVar5 = uVar5 + 1;
        CmdTxBfTxApplyCtrl(param_1,uVar3,0,1,0,0);
        if (iVar2 < (int)uVar5) {
          return;
        }
      }
      if (*pcVar6 == '\x02') {
        if (-1 < DebugLevel) {
          printk("%s():Enable wcid %d eBF!\n","BfSwitch",uVar5);
        }
        CmdTxBfTxApplyCtrl(param_1,uVar5 & 0xffff,1,0,0,0);
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 <= iVar2);
  }
  return;
}

