// module: mt7915.ko
// function: parse_patch_v1 @ 0x1c0444
// size: 484 bytes
//

int parse_patch_v1(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined1 *puVar6;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = FUN_001c00c0(param_1,*(undefined4 *)(iVar1 + 0x114),param_1 + param_2 * 0x38 + 0xa785a8);
  if (iVar2 == 0) {
    if (0 < DebugLevel) {
      printk("Parsing patch header\n");
    }
    iVar5 = param_1 + param_2 * 0x38 + 0xa785b8;
    puVar6 = (undefined1 *)(iVar5 + 7);
    iVar2 = *(int *)(param_1 + param_2 * 0x38 + 0xa785b8);
    puVar4 = (undefined1 *)(iVar2 + -1);
    puVar3 = (undefined1 *)(iVar2 + 0xf);
    do {
      puVar4 = puVar4 + 1;
      puVar6 = puVar6 + 1;
      *puVar6 = *puVar4;
    } while (puVar4 != puVar3);
    puVar4 = (undefined1 *)(param_1 + param_2 * 0x38 + 0xa785cf);
    do {
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
      *puVar4 = *puVar3;
    } while (puVar3 != (undefined1 *)(iVar2 + 0x13));
    puVar4 = (undefined1 *)(param_1 + param_2 * 0x38 + 0xa785d3);
    do {
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
      *puVar4 = *puVar3;
    } while (puVar3 != (undefined1 *)(iVar2 + 0x17));
    puVar4 = (undefined1 *)(param_1 + param_2 * 0x38 + 0xa785d7);
    do {
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
      *puVar4 = *puVar3;
    } while (puVar3 != (undefined1 *)(iVar2 + 0x1b));
    FUN_001bf504(iVar5 + 8);
    *(undefined1 *)(param_3 + 1) = 1;
    iVar2 = os_alloc_mem(param_1,param_3,0x10);
    if (iVar2 == 0) {
      param_3 = (int *)*param_3;
      param_1 = param_1 + param_2 * 0x38;
      param_3[1] = *(int *)(iVar1 + 0x11c);
      param_3[2] = *(int *)(param_1 + 0xa785bc) + -0x1e;
      *param_3 = *(int *)(param_1 + 0xa785b8) + 0x1e;
      if (0 < DebugLevel) {
        printk("\tTarget address: 0x%x, length: 0x%x\n");
      }
      return 0;
    }
  }
  if (DebugLevel < 1) {
    return iVar2;
  }
  printk("%s: parse patch fail\n","parse_patch_v1");
  return iVar2;
}

