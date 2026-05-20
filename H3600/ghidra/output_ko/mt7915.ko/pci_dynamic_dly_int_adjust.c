// module: mt7915.ko
// function: pci_dynamic_dly_int_adjust @ 0x1d0708
// size: 328 bytes
//

undefined4 pci_dynamic_dly_int_adjust(undefined4 param_1,uint param_2,uint param_3)

{
  byte bVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint *puVar10;
  
  iVar3 = hc_get_hif_ctrl();
  iVar7 = param_2 + param_3;
  bVar1 = *(byte *)(iVar3 + 1);
  uVar8 = 0;
  if (iVar7 != 0) {
    if (bVar1 != 0) {
      uVar6 = 0;
      do {
        iVar9 = *(int *)(*(int *)(iVar3 + 4) + uVar6 * 4);
        if (*(char *)(iVar9 + 0x6c) != '\0') {
          uVar4 = __aeabi_uidiv(param_2 * 100,iVar7);
          if (uVar4 < 0x47) {
            uVar4 = __aeabi_uidiv(param_3 * 100,iVar7);
            if (((0x46 < uVar4) && (*(int *)(iVar9 + 0x7c) != 0)) &&
               (**(uint **)(iVar9 + 0x78) < param_3)) {
              iVar5 = 0;
              puVar2 = *(uint **)(iVar9 + 0x78);
              do {
                puVar10 = puVar2;
                iVar5 = iVar5 + 1;
                if (iVar5 == *(int *)(iVar9 + 0x7c)) break;
                puVar2 = puVar10 + 2;
              } while (puVar10[2] < param_3);
              goto LAB_001d07c0;
            }
          }
          else if ((*(int *)(iVar9 + 0x74) != 0) && (**(uint **)(iVar9 + 0x70) < param_2)) {
            iVar5 = 0;
            puVar2 = *(uint **)(iVar9 + 0x70);
            do {
              puVar10 = puVar2;
              iVar5 = iVar5 + 1;
              if (iVar5 == *(int *)(iVar9 + 0x74)) break;
              puVar2 = puVar10 + 2;
            } while (puVar10[2] < param_2);
LAB_001d07c0:
            if (puVar10 != (uint *)0x0) {
              chip_cfg_dly_int(param_1,*(undefined4 *)(iVar9 + 0x4c),(short)puVar10[1],
                               *(undefined2 *)((int)puVar10 + 6));
            }
          }
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 != bVar1);
    }
    uVar8 = 3;
  }
  return uVar8;
}

