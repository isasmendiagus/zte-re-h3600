// module: mt7915.ko
// function: parse_patch_v2 @ 0x1c0178
// size: 712 bytes
//

int parse_patch_v2(int param_1,int param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  uint uVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  undefined1 *puVar12;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = FUN_001c00c0(param_1,*(undefined4 *)(iVar1 + 0x114),param_1 + param_2 * 0x38 + 0xa785a8);
  if (iVar1 == 0) {
    if (0 < DebugLevel) {
      printk("Parsing patch header\n");
    }
    iVar1 = param_1 + param_2 * 0x38 + 0xa785b8;
    puVar3 = (undefined1 *)(iVar1 + 7);
    iVar8 = *(int *)(param_1 + param_2 * 0x38 + 0xa785b8);
    puVar5 = (undefined1 *)(iVar8 + -1);
    puVar12 = (undefined1 *)(iVar8 + 0xf);
    do {
      puVar5 = puVar5 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar5;
    } while (puVar5 != puVar12);
    puVar3 = (undefined1 *)(param_1 + param_2 * 0x38 + 0xa785cf);
    do {
      puVar12 = puVar12 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar12;
    } while (puVar12 != (undefined1 *)(iVar8 + 0x13));
    puVar3 = (undefined1 *)(param_1 + param_2 * 0x38 + 0xa785d3);
    do {
      puVar12 = puVar12 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar12;
    } while (puVar12 != (undefined1 *)(iVar8 + 0x17));
    puVar3 = (undefined1 *)(param_1 + param_2 * 0x38 + 0xa785d7);
    do {
      puVar12 = puVar12 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar12;
    } while (puVar12 != (undefined1 *)(iVar8 + 0x1b));
    FUN_001bf504(iVar1 + 8);
    uVar10 = *(uint *)(iVar8 + 0x2c);
    uVar11 = uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
             uVar10 >> 0x18;
    if (0 < DebugLevel) {
      uVar2 = *(uint *)(iVar8 + 0x24);
      printk("\tSection num: 0x%x, subsys: 0x%x\n",uVar11,
             uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18);
    }
    *(char *)(param_3 + 1) = (char)(uVar10 >> 0x18);
    iVar1 = os_alloc_mem(param_1,param_3,uVar11 << 4);
    if (iVar1 == 0) {
      if (uVar11 != 0) {
        uVar10 = 0;
        puVar9 = (uint *)(iVar8 + 0x60);
        do {
          iVar1 = uVar10 * 0x10;
          iVar8 = *param_3;
          uVar7 = *puVar9;
          uVar2 = (uVar7 >> 0x10 & 0xff) << 8;
          if (0 < DebugLevel) {
            uVar4 = puVar9[2];
            uVar6 = puVar9[1];
            printk("\tSection %d: type = 0x%x, offset = 0x%x, size = 0x%x\n",uVar10,
                   uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | uVar2 | uVar7 >> 0x18,
                   uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                   uVar6 >> 0x18,
                   uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                   uVar4 >> 0x18);
          }
          if ((uVar2 | uVar7 >> 0x18) == 2) {
            uVar2 = puVar9[3];
            *(uint *)(iVar8 + iVar1 + 4) =
                 uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                 uVar2 >> 0x18;
            uVar2 = puVar9[4];
            *(uint *)(iVar8 + iVar1 + 8) =
                 uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                 uVar2 >> 0x18;
            uVar2 = puVar9[1];
            *(uint *)(iVar8 + iVar1) =
                 *(int *)(param_1 + param_2 * 0x38 + 0xa785b8) +
                 (uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                 uVar2 >> 0x18);
            if (0 < DebugLevel) {
              printk("\tTarget address: 0x%x, length: 0x%x\n");
            }
          }
          else {
            *(undefined4 *)(iVar8 + iVar1) = 0;
            if (0 < DebugLevel) {
              printk("\tNot binary\n");
            }
          }
          uVar10 = uVar10 + 1;
          puVar9 = puVar9 + 0x10;
        } while (uVar10 != uVar11);
      }
      return 0;
    }
  }
  if (0 < DebugLevel) {
    printk("%s: parse patch fail\n","parse_patch_v2");
  }
  return iVar1;
}

