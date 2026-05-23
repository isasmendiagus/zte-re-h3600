// module: mt7915.ko
// function: parse_fw_v2 @ 0x1c0c1c
// size: 896 bytes
//

int parse_fw_v2(int param_1,int param_2,int *param_3)

{
  byte bVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_44;
  int local_34;
  undefined4 local_30;
  int local_2c [2];
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = FUN_001c00c0(param_1,*(undefined4 *)(iVar2 + 0x118),param_1 + param_2 * 0x3c + 0xa78530);
  if (iVar2 == 0) {
    if (0 < DebugLevel) {
      printk("Parsing CPU %d fw tailer\n",param_2);
    }
    iVar10 = param_1 + param_2 * 0x3c;
    iVar2 = param_1 + param_2 * 0x3c + 0xa78540;
    puVar3 = (undefined1 *)(iVar2 + 0xc);
    local_34 = *(int *)(iVar10 + 0xa78540) + *(int *)(iVar10 + 0xa78544) + -0x24;
    puVar5 = (undefined1 *)(local_34 + 6);
    *(undefined1 *)(iVar2 + 8) = *(undefined1 *)(local_34 + 4);
    *(undefined1 *)(iVar10 + 0xa78549) = *(undefined1 *)(local_34 + 6);
    do {
      puVar5 = puVar5 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar5;
    } while (puVar5 != (undefined1 *)(local_34 + 0x10));
    puVar3 = (undefined1 *)(param_1 + param_2 * 0x3c + 0xa78556);
    do {
      puVar5 = puVar5 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar5;
    } while (puVar5 != (undefined1 *)(local_34 + 0x1f));
    local_34 = local_34 + 0x20;
    FUN_001bf6f4(iVar2 + 8);
    if (param_2 != 1) {
      uVar4 = 0x38;
      local_44 = 2;
    }
    else {
      uVar4 = 0x1c;
      local_44 = param_2;
    }
    *(char *)(param_3 + 1) = (char)local_44;
    if (param_2 == 1) {
      local_44 = param_2;
    }
    iVar2 = os_alloc_mem(param_1,param_3,uVar4);
    if (iVar2 == 0) {
      iVar8 = param_1 + param_2 * 0x3c;
      iVar2 = local_44 * 0x24;
      iVar10 = 0;
      iVar9 = 0;
      do {
        if (0 < DebugLevel) {
          printk("Parsing tailer region %d\n",iVar10);
        }
        local_34 = *(int *)(iVar8 + 0xa78540) + (*(int *)(iVar8 + 0xa78544) - iVar2);
        FUN_001c062c(&local_30,&local_34);
        if (0 < DebugLevel) {
          printk("\tTarget address: 0x%x\n",local_30);
        }
        iVar6 = local_34 + 2;
        bVar1 = *(byte *)(local_34 + 1);
        local_34 = iVar6;
        if ((((-1 < DebugLevel) && (printk("\tFeature set: "), -1 < DebugLevel)) &&
            (printk(&_LC5), -1 < DebugLevel)) && (printk(&_LC6,bVar1), -1 < DebugLevel)) {
          printk(&_LC2);
        }
        local_34 = local_34 + 0x1a;
        FUN_001c062c(local_2c,&local_34);
        local_2c[0] = local_2c[0] + 4;
        if (0 < DebugLevel) {
          printk("\tDownload size: %d\n");
        }
        iVar6 = *param_3;
        iVar7 = iVar6 + iVar10 * 0x1c;
        *(int *)(iVar7 + 8) = local_2c[0];
        *(undefined4 *)(iVar7 + 4) = local_30;
        *(int *)(iVar6 + iVar10 * 0x1c) = *(int *)(iVar8 + 0xa78540) + iVar9;
        *(byte *)(iVar7 + 0xc) = bVar1;
        iVar9 = iVar9 + local_2c[0];
        if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) &&
           (param_2 == 0 && iVar10 == 0)) {
          *(byte *)(iVar7 + 0xc) = bVar1 | 0x20;
        }
        iVar10 = iVar10 + 1;
        iVar2 = iVar2 + -0x24;
      } while (iVar10 != local_44);
      return 0;
    }
  }
  if (0 < DebugLevel) {
    printk("%s: parse fw fail\n","parse_fw_v2");
  }
  return iVar2;
}

