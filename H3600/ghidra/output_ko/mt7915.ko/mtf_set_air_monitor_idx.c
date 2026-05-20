// module: mt7915.ko
// function: mtf_set_air_monitor_idx @ 0x197990
// size: 1532 bytes
//

undefined4 mtf_set_air_monitor_idx(int param_1,undefined4 param_2,uint param_3,uint param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  undefined6 *puVar10;
  void *local_44;
  char local_3d;
  undefined1 uStack_3c;
  undefined2 uStack_3b;
  undefined2 uStack_39;
  undefined2 uStack_37;
  undefined1 local_35 [10];
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  local_44 = (void *)0x0;
  __memzero(local_35,0xd);
  __memzero(&local_3d,8);
  os_alloc_mem(param_1,&local_44,0x15);
  if (local_44 == (void *)0x0) {
    return 0;
  }
  if (2 < DebugLevel) {
    printk("--> %s()\n","mtf_set_air_monitor_idx");
  }
  if (param_3 < 0x10) {
    *(char *)(param_1 + 0xa37694) = (char)param_3;
    iVar2 = memcmp(&ZERO_MAC_ADDR,(undefined4 *)(param_1 + 0xa37695),6);
    uVar1 = (undefined1)param_4;
    if (iVar2 == 0) {
      iVar2 = param_1 + param_3 * 0x44;
      if (*(char *)(iVar2 + 0xa37234) != '\0') {
        iVar2 = *(int *)(iVar2 + 0xa37274);
        if (iVar2 != 0) {
          if (param_4 == 1) {
            bVar6 = *(byte *)(iVar2 + 0x17a) & 0xfd;
          }
          else {
            bVar6 = *(byte *)(iVar2 + 0x17a) & 0xfe;
          }
          *(byte *)(iVar2 + 0x17a) = bVar6;
          if (bVar6 == 0) {
            MacTableDeleteEntry(param_1,*(undefined2 *)(iVar2 + 0xe0),iVar2 + 0xec);
          }
        }
        uVar7 = (uint)*(byte *)(param_1 + param_3 * 0x44 + 0xa37237);
        if (((uVar7 < 8) && (iVar2 = param_1 + uVar7 * 4, iVar2 != -0xa37674)) &&
           (cVar4 = *(char *)(iVar2 + 0xa37675) + -1, *(char *)(iVar2 + 0xa37675) = cVar4,
           cVar4 == '\0')) {
          *(undefined1 *)(iVar2 + 0xa37674) = 0;
        }
        iVar8 = param_1 + param_4 * 4;
        *(undefined1 *)(param_1 + param_3 * 0x44 + 0xa37234) = 0;
        iVar2 = *(int *)(iVar8 + 0xa3769c);
        puVar10 = &ZERO_MAC_ADDR;
        if (iVar2 != 0) {
          *(int *)(iVar8 + 0xa3769c) = iVar2 + -1;
        }
        cVar4 = *(char *)(param_1 + param_3 * 0x44 + 0xa37236);
LAB_00197b3c:
        if ((0 < DebugLevel) && (printk("index: %d\n",param_3), 0 < DebugLevel)) {
          printk("entry: %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)puVar10,
                 *(undefined1 *)((int)puVar10 + 1),*(undefined1 *)((int)puVar10 + 2),
                 *(undefined1 *)((int)puVar10 + 3),*(undefined1 *)((int)puVar10 + 4),
                 *(undefined1 *)((int)puVar10 + 5));
        }
        uStack_37 = *(undefined2 *)((int)puVar10 + 4);
        local_2a = 1;
        local_2b = 1;
        local_35[0] = 0;
        uStack_3b = (undefined2)*(undefined4 *)puVar10;
        uStack_39 = (undefined2)((uint)*(undefined4 *)puVar10 >> 0x10);
        local_3d = cVar4;
        local_29 = uVar1;
        memmove(local_44,local_35,0xd);
        *(uint *)((int)local_44 + 0xd) = CONCAT22(uStack_3b,CONCAT11(uStack_3c,local_3d));
        *(uint *)((int)local_44 + 0x11) = CONCAT22(uStack_37,uStack_39);
        MtCmdMuarConfigSet(param_1,local_44);
        uVar3 = mtf_set_air_monitor_enable
                          (param_1,*(int *)(param_1 + (param_4 + 0x28dda6) * 4 + 4) != 0,param_4);
        if (2 < DebugLevel) {
          printk("<-- %s()\n","mtf_set_air_monitor_idx");
        }
        os_free_mem(local_44);
        return uVar3;
      }
    }
    else {
      if (*(char *)(param_1 + param_3 * 0x44 + 0xa37234) == '\0') {
        if ((uint)(*(int *)(param_1 + 0xa376a0) + *(int *)(param_1 + 0xa3769c)) < 0x10) {
          iVar8 = param_1 + param_3 * 0x44 + 0xa37234;
          pcVar9 = (char *)(param_1 + 0xa37674);
          iVar2 = 0;
          do {
            if (*pcVar9 == '\0') {
              __memzero(iVar8,0x44);
              iVar8 = param_1 + iVar2 * 4;
              *(undefined1 *)(iVar8 + 0xa37676) = uVar1;
              *(char *)(iVar8 + 0xa37677) = ((char)iVar2 + '\x10') * '\x02';
              *(undefined1 *)(iVar8 + 0xa37674) = 1;
LAB_00197d14:
              iVar5 = param_1 + param_3 * 0x44;
              *(char *)(iVar5 + 0xa37237) = (char)iVar2;
              cVar4 = *(char *)(iVar8 + 0xa37675);
              *(char *)(iVar8 + 0xa37675) = cVar4 + '\x01';
              cVar4 = cVar4 + *(char *)(iVar8 + 0xa37677);
              *(char *)(iVar5 + 0xa37236) = cVar4;
              iVar2 = param_1 + param_3 * 0x44;
              puVar10 = (undefined6 *)(iVar2 + 0xa37248);
              *(undefined4 *)(iVar2 + 0xa37248) = *(undefined4 *)(param_1 + 0xa37695);
              *(undefined2 *)(iVar2 + 0xa3724c) = *(undefined2 *)(param_1 + 0xa37699);
              iVar2 = MacTableLookup(param_1,puVar10);
              if (iVar2 == 0) {
                iVar2 = MacTableInsertEntry(param_1,puVar10,param_2,0x10,0,1);
                if (iVar2 == 0) {
                  if (-1 < DebugLevel) {
                    printk("%s(): MacTableInsertEntry fail!!\n","mtf_set_air_monitor_idx");
                  }
                  goto LAB_00197c04;
                }
                iVar8 = wdev_do_conn_act(param_2,iVar2);
                if (iVar8 != 1) {
                  if (-1 < DebugLevel) {
                    printk("%s(): connect fail!!\n","mtf_set_air_monitor_idx");
                  }
                  goto LAB_00197c04;
                }
              }
              iVar5 = param_1 + param_4 * 4;
              iVar8 = param_1 + param_3 * 0x44;
              *(int *)(iVar5 + 0xa3769c) = *(int *)(iVar5 + 0xa3769c) + 1;
              *(undefined1 *)(iVar8 + 0xa37235) = uVar1;
              *(undefined1 *)(iVar8 + 0xa37234) = 1;
              *(char *)(iVar2 + param_4 + 0x178) = (char)param_3;
              if (param_4 == 1) {
                bVar6 = *(byte *)(iVar2 + 0x17a) | 2;
              }
              else {
                bVar6 = *(byte *)(iVar2 + 0x17a) | 1;
              }
              *(byte *)(iVar2 + 0x17a) = bVar6;
              *(int *)(param_1 + param_3 * 0x44 + 0xa37274) = iVar2;
              goto LAB_00197b3c;
            }
            if (((byte)pcVar9[1] < 2) && ((byte)pcVar9[2] == param_4)) {
              __memzero(iVar8,0x44);
              iVar8 = param_1 + iVar2 * 4;
              goto LAB_00197d14;
            }
            iVar2 = iVar2 + 1;
            pcVar9 = pcVar9 + 4;
          } while (iVar2 != 8);
          if (-1 < DebugLevel) {
            printk("Can\'t create a monitor entry!\n");
          }
        }
        else if (-1 < DebugLevel) {
          printk("The monitor number extends to maximum limit(%d).\n",0x10);
        }
        goto LAB_00197c04;
      }
      if (-1 < DebugLevel) {
        printk("The index of existed monitor entry.\n");
      }
    }
    os_free_mem(local_44);
    return 1;
  }
  if (-1 < DebugLevel) {
    printk("The index is over the maximum limit.\n");
  }
LAB_00197c04:
  os_free_mem(local_44);
  return 0;
}

