// module: mt7915.ko
// function: load_patch_v1 @ 0x1bfe38
// size: 644 bytes
//

int load_patch_v1(int param_1,undefined4 param_2,int *param_3)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  int local_34;
  int *local_30;
  int local_2c;
  
  iVar7 = param_1 + 0xa70000;
  bVar1 = *(byte *)(param_3 + 1);
  *(undefined4 *)(param_1 + 0xa7861c) = 1;
  local_34 = MtCmdPatchSemGet(param_1,1);
  if (local_34 != 0) {
    local_30 = &DebugLevel;
    local_2c = iVar7;
    goto LAB_001bff48;
  }
  iVar3 = *(int *)(param_1 + 0xa78618);
  if (iVar3 == 1) {
    if (0 < DebugLevel) {
      printk("patch is ready, continue to ILM/DLM DL\n");
    }
LAB_001bffb0:
    os_free_mem(*param_3);
    *param_3 = 0;
    *(undefined1 *)(param_3 + 1) = 0;
    return 0;
  }
  if (iVar3 == 0) {
    local_30 = &DebugLevel;
    if (0 < DebugLevel) {
      local_34 = 1;
      printk("patch is not ready && get semaphore fail\n");
      local_2c = iVar7;
      goto LAB_001bff48;
    }
  }
  else if (iVar3 == 2) {
    if (0 < DebugLevel) {
      printk("patch is not ready && get semaphore success\n");
    }
    bVar8 = bVar1 == 0;
    if (!bVar8) {
      local_30 = &DebugLevel;
      local_2c = iVar7;
    }
    uVar4 = (uint)bVar8;
    piVar2 = &DebugLevel;
    if (!bVar8) {
      do {
        iVar5 = *param_3;
        iVar7 = uVar4 * 0x10;
        iVar6 = iVar5 + iVar7;
        iVar3 = uVar4 * 0x10;
        uVar4 = uVar4 + 1;
        if (*(int *)(iVar5 + iVar3) != 0) {
          *(undefined4 *)(param_1 + 0xa7861c) = 1;
          local_34 = MtCmdAddressLenReq(param_1,*(undefined4 *)(iVar6 + 4),
                                        *(undefined4 *)(iVar6 + 8),0x80000000);
          if (local_34 != 0) goto LAB_001bff48;
          *(undefined4 *)(param_1 + 0xa7861c) = 2;
          local_34 = FUN_001bfba4(param_1,*(undefined4 *)(iVar5 + iVar7),*(undefined4 *)(iVar6 + 8))
          ;
          if (local_34 != 0) goto LAB_001bff48;
        }
        iVar7 = local_2c;
        piVar2 = local_30;
      } while (bVar1 != uVar4);
    }
    local_30 = piVar2;
    local_2c = iVar7;
    *(undefined4 *)(param_1 + 0xa7861c) = 1;
    local_34 = MtCmdPatchFinishReq(param_1);
    if ((local_34 != 0) || (local_34 = MtCmdPatchSemGet(param_1), local_34 != 0)) goto LAB_001bff48;
    if (*(int *)(param_1 + 0xa78618) == 3) {
      if (0 < *local_30) {
        printk("release patch semaphore\n");
      }
      goto LAB_001bffb0;
    }
    iVar7 = local_2c;
    if (0 < *local_30) {
      local_34 = 1;
      printk("release patch semaphore invalid status(%d)\n");
      goto LAB_001bff48;
    }
  }
  else {
    local_30 = &DebugLevel;
    if (0 < DebugLevel) {
      local_34 = 1;
      printk("get semaphore invalid status(%d)\n");
      local_2c = iVar7;
      goto LAB_001bff48;
    }
  }
  local_34 = 1;
  local_2c = iVar7;
LAB_001bff48:
  os_free_mem(*param_3);
  *param_3 = 0;
  iVar7 = *local_30;
  *(undefined1 *)(param_3 + 1) = 0;
  *(undefined4 *)(local_2c + 0x861c) = 0;
  if (0 < iVar7) {
    printk("%s: load patch fail\n","load_patch_v1");
  }
  return local_34;
}

