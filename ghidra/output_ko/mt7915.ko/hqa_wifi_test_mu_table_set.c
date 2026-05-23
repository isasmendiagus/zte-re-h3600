// module: mt7915.ko
// function: hqa_wifi_test_mu_table_set @ 0x90684
// size: 1160 bytes
//

undefined4 hqa_wifi_test_mu_table_set(undefined4 param_1,short *param_2)

{
  int iVar1;
  void *pvVar2;
  size_t __n;
  uint uVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined4 local_40;
  void *local_3c;
  void *local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_40 = 0;
  local_3c = (void *)0x0;
  local_38 = (void *)0x0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (param_2 == (short *)0x0) {
    if (DebugLevel < 0) {
LAB_000907ec:
      uVar6 = 0xffffffff;
      goto LAB_0009070c;
    }
    uVar6 = 0xffffffff;
    printk("%s: ptr is NULL\n","hqa_wifi_test_mu_table_set");
LAB_00090700:
    if (local_38 == (void *)0x0) goto LAB_0009070c;
  }
  else {
    if (0 < DebugLevel) {
      printk("%s: type = %u, length = %u\n","hqa_wifi_test_mu_table_set",*param_2,
             *(undefined4 *)(param_2 + 2));
    }
    if (*param_2 == 0) {
      local_40 = 0x4c;
      os_alloc_mem(param_1,&local_38,0x3c);
      if (local_38 == (void *)0x0) {
        if (DebugLevel < 0) goto LAB_000907ec;
        uVar6 = 0xffffffff;
        printk("%s: pSuParam memory allocation failed\n","hqa_wifi_test_mu_table_set");
      }
      else {
        __memzero(local_38,0x3c);
LAB_00090760:
        __n = *(size_t *)(param_2 + 2);
        if (*param_2 == 0) {
          if (__n < 0x3d) {
            memcpy(local_38,*(void **)(param_2 + 4),__n);
LAB_00090850:
            if (0 < DebugLevel) {
              pcVar5 = "su_metric_table:";
              if (*param_2 != 0) {
                pcVar5 = "mu_metric_table:";
              }
              printk(&_LC0,pcVar5);
            }
            uVar3 = *(uint *)(param_2 + 2);
            if (*param_2 == 1) {
              if (uVar3 != 0) {
                uVar7 = 0;
                do {
                  if (0 < DebugLevel) {
                    puVar8 = (undefined1 *)((int)local_3c + uVar7);
                    printk("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",*puVar8,puVar8[1],puVar8[2],
                           puVar8[3],puVar8[4],puVar8[5],puVar8[6],
                           *(undefined1 *)((int)local_3c + uVar7 + 7));
                    uVar3 = *(uint *)(param_2 + 2);
                  }
                  uVar7 = uVar7 + 8;
                } while ((uVar7 < uVar3) && (uVar7 != 0x1e0));
              }
            }
            else if (uVar3 != 0) {
              uVar7 = 0;
              do {
                if (0 < DebugLevel) {
                  printk("0x%x 0x%x 0x%x\n",*(undefined1 *)((int)local_38 + uVar7),
                         ((undefined1 *)((int)local_38 + uVar7))[1],
                         *(undefined1 *)((int)local_38 + uVar7 + 2));
                  uVar3 = *(uint *)(param_2 + 2);
                }
                uVar7 = uVar7 + 3;
              } while ((uVar7 < uVar3) && (uVar7 != 0x3c));
            }
            iVar1 = AndesAllocCmdMsg(param_1);
            if (iVar1 == 0) {
              if (DebugLevel < 0) goto LAB_000906f8;
              uVar6 = 0xffffffff;
              printk("%s: msg is NULL\n","hqa_wifi_test_mu_table_set");
            }
            else {
              local_28 = 0;
              local_24 = 0;
              local_30 = CONCAT31(local_30._1_3_,10);
              local_2c = local_2c & 0xffff0000;
              local_30 = local_30 & 0xffff;
              local_34 = 0x40ed0000;
              AndesInitCmdMsg(iVar1,0x40ed0000,local_30,local_2c,0,0);
              AndesAppendCmdMsg(iVar1,&local_40,4);
              uVar6 = 0;
              if (*param_2 == 0) {
                uVar4 = 0x3c;
                pvVar2 = local_38;
              }
              else {
                uVar4 = 0x1e0;
                pvVar2 = local_3c;
              }
              AndesAppendCmdMsg(iVar1,pvVar2,uVar4);
              AndesSendCmdMsg(param_1,iVar1);
            }
          }
          else {
            if (-1 < DebugLevel) {
              printk("length(%u) error!!should < su_metric_tbl(%zu)\n",__n,0x3c);
              uVar6 = 0xffffffff;
              goto LAB_00090700;
            }
LAB_000906f8:
            uVar6 = 0xffffffff;
          }
        }
        else {
          if (__n < 0x1e1) {
            memcpy(local_3c,*(void **)(param_2 + 4),__n);
            goto LAB_00090850;
          }
          if (DebugLevel < 0) goto LAB_000906f8;
          printk("length(%u) error!!should < mu_metric_tbl(%zu)\n",__n,0x3c);
          uVar6 = 0xffffffff;
        }
      }
      goto LAB_00090700;
    }
    local_40 = 0x4b;
    if (*param_2 != 1) {
      if (DebugLevel < 0) goto LAB_000906f8;
      uVar6 = 0xffffffff;
      printk("Error type!\n");
      goto LAB_00090700;
    }
    os_alloc_mem(param_1,&local_3c,0x1e0);
    if (local_3c != (void *)0x0) {
      __memzero(local_3c,0x1e0);
      goto LAB_00090760;
    }
    if (-1 < DebugLevel) {
      uVar6 = 0xffffffff;
      printk("%s: pMuParam memory allocation failed\n","hqa_wifi_test_mu_table_set");
      goto LAB_00090700;
    }
    uVar6 = 0xffffffff;
    if (local_38 == (void *)0x0) {
      return 0xffffffff;
    }
  }
  os_free_mem();
LAB_0009070c:
  if (local_3c != (void *)0x0) {
    os_free_mem();
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_mu_table_set",uVar6);
  }
  return uVar6;
}

