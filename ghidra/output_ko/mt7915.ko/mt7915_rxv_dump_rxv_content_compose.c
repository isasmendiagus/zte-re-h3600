// module: mt7915.ko
// function: mt7915_rxv_dump_rxv_content_compose @ 0x17aa44
// size: 1052 bytes
//

undefined4 mt7915_rxv_dump_rxv_content_compose(int param_1,uint param_2,void *param_3,int *param_4)

{
  byte bVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  void *__dest;
  void *__dest_00;
  uint local_44;
  uint local_40;
  int local_3c;
  uint local_38;
  int local_34;
  uint local_30;
  size_t local_2c [2];
  
  local_44 = 0;
  if (param_3 == (void *)0x0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s(): null pointer for rxv content.\n","mt7915_rxv_dump_rxv_content_compose");
    uVar6 = 1;
  }
  else if (param_4 == (int *)0x0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s(): null pointer for buffer of length.\n","mt7915_rxv_dump_rxv_content_compose");
    uVar6 = 1;
  }
  else {
    piVar8 = *(int **)(param_1 + 0xa7c220);
    if (piVar8 == (int *)0x0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s(): null pointer for entry list.\n","mt7915_rxv_dump_rxv_content_compose");
      uVar6 = 1;
    }
    else {
      piVar4 = (int *)*piVar8;
      if (piVar4 == piVar8) {
        piVar4 = (int *)0x0;
      }
      else {
        bVar1 = *(byte *)(piVar4 + 2);
        piVar11 = (int *)*piVar4;
        while (bVar1 != param_2) {
          if (piVar11 == piVar8) {
            piVar4 = (int *)0x0;
            break;
          }
          bVar1 = *(byte *)(piVar11 + 2);
          piVar4 = piVar11;
          piVar11 = (int *)*piVar11;
        }
      }
      local_44 = (uint)*(byte *)((int)piVar4 + 9);
      piVar11 = (int *)piVar4[3];
      iVar9 = 0;
      *param_4 = 0;
      __dest = (void *)((int)param_3 + 4);
      os_move_mem(param_3,&local_44,4);
      iVar7 = *param_4 + 4;
      *param_4 = iVar7;
      piVar4 = *(int **)*piVar11;
      piVar8 = (undefined4 *)*piVar11;
      while (piVar2 = piVar4, piVar8 != piVar11) {
        local_40 = 0;
        local_3c = 0;
        if (piVar11 == (int *)0x0) {
          if (-1 < DebugLevel) {
            printk("%s(): null pointer for badic entry list.\n",
                   "mt7915_rxv_dump_type_content_compose");
            iVar7 = *param_4;
          }
        }
        else if (__dest == (void *)0x0) {
          if (-1 < DebugLevel) {
            printk("%s(): null pointer for type content.\n","mt7915_rxv_dump_type_content_compose");
            iVar7 = *param_4;
          }
        }
        else {
          piVar4 = (int *)*piVar11;
          if (piVar11 == piVar4) {
LAB_0017ab68:
            piVar4 = (int *)0x0;
            local_40 = (uint)DAT_00000008;
          }
          else {
            bVar1 = *(byte *)(piVar4 + 2);
            piVar3 = (int *)*piVar4;
            while (local_40 = (uint)bVar1, *(byte *)(piVar8 + 2) != local_40) {
              if (piVar11 == piVar3) goto LAB_0017ab68;
              bVar1 = *(byte *)(piVar3 + 2);
              piVar4 = piVar3;
              piVar3 = (int *)*piVar3;
            }
          }
          bVar1 = *(byte *)(piVar4 + 3);
          __dest_00 = (void *)((int)__dest + 0x10);
          piVar8 = (int *)piVar4[4];
          os_move_mem(__dest,&local_40,4);
          iVar9 = 0;
          local_34 = 0;
          local_3c = 0;
          local_38 = (uint)bVar1;
          os_move_mem((void *)((int)__dest + 8),&local_38,4);
          local_3c = local_3c + 8;
          if (local_38 != 0) {
            uVar10 = 0;
            uVar5 = local_38;
            do {
              local_30 = 0;
              local_2c[0] = 0;
              if (piVar8 == (int *)0x0) {
                if (-1 < DebugLevel) {
                  printk("%s(): null pointer for data list.\n",
                         "mt7915_rxv_dump_user_content_compose");
                  uVar5 = local_38;
                }
              }
              else if (__dest_00 == (void *)0x0) {
                if (-1 < DebugLevel) {
                  printk("%s(): null pointer for user content.\n",
                         "mt7915_rxv_dump_user_content_compose");
                  uVar5 = local_38;
                }
              }
              else {
                piVar4 = (int *)*piVar8;
                if (piVar8 == piVar4) {
                  local_30 = (uint)*(byte *)(piVar8 + 2);
                  piVar4 = piVar8;
                }
                else {
                  bVar1 = *(byte *)(piVar4 + 2);
                  piVar3 = (int *)*piVar4;
                  while (local_30 = (uint)bVar1, uVar10 != local_30) {
                    piVar4 = piVar3;
                    if (piVar8 == piVar3) {
                      local_30 = (uint)*(byte *)(piVar8 + 2);
                      break;
                    }
                    bVar1 = *(byte *)(piVar3 + 2);
                    piVar3 = (int *)*piVar3;
                  }
                }
                local_2c[0] = (size_t)*(ushort *)((int)piVar4 + 10);
                os_move_mem(__dest_00,&local_30,4);
                os_move_mem((void *)((int)__dest_00 + 4),local_2c,4);
                os_move_mem((void *)((int)__dest_00 + 8),(void *)piVar4[3],local_2c[0]);
                iVar9 = local_2c[0] + 8;
                uVar5 = local_38;
              }
              local_3c = local_3c + iVar9;
              __dest_00 = (void *)((int)__dest_00 + iVar9);
              uVar10 = uVar10 + 1 & 0xff;
              local_34 = local_34 + iVar9;
            } while (uVar10 < uVar5);
          }
          os_move_mem((void *)((int)__dest + 0xc),&local_34,4);
          iVar9 = local_3c;
          os_move_mem((void *)((int)__dest + 4),&local_3c,4);
          iVar9 = iVar9 + 8;
          iVar7 = *param_4;
        }
        iVar7 = iVar7 + iVar9;
        __dest = (void *)((int)__dest + iVar9);
        *param_4 = iVar7;
        piVar4 = (int *)*piVar2;
        piVar8 = piVar2;
      }
      uVar6 = 0;
    }
  }
  return uVar6;
}

