// module: mt7915.ko
// function: Set_APProxy_Status_Show_Proc @ 0x9ff54
// size: 824 bytes
//

undefined4 Set_APProxy_Status_Show_Proc(int *param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int local_70;
  int local_6c;
  undefined4 uStack_68;
  char *pcStack_64;
  
  local_6c = 0;
  local_70 = 0;
  os_alloc_mem(0,&local_6c,0x400);
  if (local_6c == 0) {
    if (-1 < DebugLevel) {
      printk("%s: routing_entry_list Allocate memory fail!!!\n","Set_APProxy_Status_Show_Proc");
    }
  }
  else {
    __memzero(local_6c,0x400);
    if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) {
      uVar5 = *(uint *)(*param_1 + 0x3c) & 0xff;
      iVar3 = a4_get_entry_count(param_1,uVar5);
      uVar2 = jiffies;
      if (iVar3 != 0) {
        for (piVar7 = (int *)param_1[uVar5 * 0x160d + 0xaf0a3];
            piVar7 != param_1 + uVar5 * 0x160d + 0xaf0a3; piVar7 = (int *)*piVar7) {
          if (((piVar7 != (int *)0x0) && (*(char *)(piVar7 + 2) != '\0')) &&
             (uVar1 = *(ushort *)((int)piVar7 + 10),
             uVar4 = hc_get_chip_wtbl_max_num(param_1[0x29e5e8]), uVar1 < uVar4)) {
            uVar4 = (uint)*(ushort *)((int)piVar7 + 10);
            local_70 = 0;
            if (0 < DebugLevel) {
              printk("Proxy Mac: %02x:%02x:%02x:%02x:%02x:%02x\n",
                     (char)param_1[uVar4 * 0x530 + 0x28783],
                     *(undefined1 *)((int)param_1 + uVar4 * 0x14c0 + 0xa1e0d),
                     *(undefined1 *)((int)param_1 + uVar4 * 0x14c0 + 0xa1e0e),
                     *(undefined1 *)((int)param_1 + uVar4 * 0x14c0 + 0xa1e0f),
                     (char)param_1[uVar4 * 0x530 + 0x28784],
                     *(undefined1 *)((int)param_1 + uVar4 * 0x14c0 + 0xa1e11));
              uVar4 = (uint)*(ushort *)((int)piVar7 + 10);
            }
            iVar3 = GetRoutingEntryAll(param_1,uVar5,uVar4,1,0x100,&local_6c,&local_70);
            if (iVar3 != 0) {
              if (0 < local_70) {
                iVar8 = 0;
                iVar3 = local_70;
                do {
                  iVar9 = *(int *)(local_6c + iVar8 * 4);
                  if (iVar9 != 0) {
                    if (*(uint *)(iVar9 + 8) < uVar2) {
                      uVar4 = 0;
                    }
                    else {
                      uVar4 = (*(uint *)(iVar9 + 8) - uVar2) / 100;
                    }
                    uVar6 = *(uint *)(iVar9 + 0x14);
                    if (uVar6 == 0) {
                      uStack_68 = 0x2e302e30;
                      pcStack_64 = "mand type = %x\n";
                    }
                    else {
                      sprintf((char *)&uStack_68,"%d.%d.%d.%d",uVar6 & 0xff,(uVar6 << 0x10) >> 0x18,
                              (uVar6 << 8) >> 0x18,uVar6 >> 0x18);
                    }
                    iVar3 = local_70;
                    if (0 < DebugLevel) {
                      printk("MAC:%02x:%02x:%02x:%02x:%02x:%02x, IP:%s, AgeOut:%lus, Retry:(%d,%d)\n"
                             ,*(undefined1 *)(iVar9 + 0x18),*(undefined1 *)(iVar9 + 0x19),
                             *(undefined1 *)(iVar9 + 0x1a),*(undefined1 *)(iVar9 + 0x1b),
                             *(undefined1 *)(iVar9 + 0x1c),*(undefined1 *)(iVar9 + 0x1d),&uStack_68,
                             uVar4,*(undefined1 *)(iVar9 + 0x10),5);
                      iVar3 = local_70;
                    }
                  }
                  iVar8 = iVar8 + 1;
                } while (iVar8 < iVar3);
              }
              if (0 < DebugLevel) {
                printk("Total Count = %d\n\n");
              }
            }
          }
        }
      }
      os_free_mem(local_6c);
      return 1;
    }
    os_free_mem(local_6c);
  }
  return 0;
}

