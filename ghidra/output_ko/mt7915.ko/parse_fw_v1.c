// module: mt7915.ko
// function: parse_fw_v1 @ 0x1c0a48
// size: 464 bytes
//

int parse_fw_v1(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int local_28;
  int local_24 [2];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = FUN_001c00c0(param_1,*(undefined4 *)(iVar1 + 0x118),param_1 + param_2 * 0x3c + 0xa78530);
  if (iVar1 == 0) {
    if (0 < DebugLevel) {
      printk("Parsing CPU %d fw tailer\n",param_2);
    }
    iVar1 = param_1 + param_2 * 0x3c;
    puVar5 = (undefined1 *)(iVar1 + 0xa7854c);
    local_28 = *(int *)(iVar1 + 0xa78540) + *(int *)(iVar1 + 0xa78544) + -0x1d;
    puVar4 = (undefined1 *)(local_28 + -1);
    puVar3 = (undefined1 *)(local_28 + 9);
    do {
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
      *puVar5 = *puVar4;
    } while (puVar4 != puVar3);
    puVar4 = (undefined1 *)(param_1 + param_2 * 0x3c + 0xa78556);
    do {
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
      *puVar4 = *puVar3;
    } while (puVar3 != (undefined1 *)(local_28 + 0x18));
    local_28 = local_28 + 0x19;
    FUN_001bf6f4(param_1 + param_2 * 0x3c + 0xa78548);
    *(undefined1 *)(param_3 + 1) = 1;
    iVar1 = os_alloc_mem(param_1,param_3,0x1c);
    if (iVar1 == 0) {
      param_1 = param_1 + param_2 * 0x3c;
      local_28 = *(int *)(param_1 + 0xa78540) + *(int *)(param_1 + 0xa78544) + -4;
      FUN_001c062c(local_24,&local_28);
      param_3 = (undefined4 *)*param_3;
      param_3[1] = 0x100000;
      param_3[2] = local_24[0] + 4;
      uVar2 = *(undefined4 *)(param_1 + 0xa78540);
      *(undefined1 *)(param_3 + 3) = 0x20;
      *param_3 = uVar2;
      return 0;
    }
  }
  if (0 < DebugLevel) {
    printk("%s: parse fw fail\n","parse_fw_v1");
  }
  return iVar1;
}

