// module: mt7915.ko
// function: mt7915_hif_pci_data_ring_assign @ 0x17f434
// size: 204 bytes
//

void mt7915_hif_pci_data_ring_assign(undefined4 param_1,undefined1 *param_2)

{
  char cVar1;
  char *pcVar2;
  undefined1 uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  undefined1 uVar7;
  
  pcVar2 = (char *)hc_get_hif_ctrl();
  cVar1 = *pcVar2;
  if (cVar1 == '\0') {
    return;
  }
  piVar6 = *(int **)(pcVar2 + 8);
  iVar5 = *piVar6;
  if (*(int *)(iVar5 + 0x2c) == 0xd9330) {
    uVar7 = *(undefined1 *)(iVar5 + 0x58);
  }
  else {
    piVar4 = piVar6;
    do {
      if (piVar4 == piVar6 + (byte)(cVar1 - 1)) {
        return;
      }
      piVar4 = piVar4 + 1;
    } while (*(int *)(*piVar4 + 0x2c) != 0xd9330);
    uVar7 = *(undefined1 *)(*piVar4 + 0x58);
    if (*(int *)(iVar5 + 0x2c) == 0xd5420) goto LAB_0017f4ec;
  }
  piVar4 = piVar6 + (byte)(cVar1 - 1);
  do {
    if (piVar6 == piVar4) {
      uVar3 = 0;
      goto LAB_0017f4e0;
    }
    piVar6 = piVar6 + 1;
    iVar5 = *piVar6;
  } while (*(int *)(iVar5 + 0x2c) != 0xd5420);
LAB_0017f4ec:
  uVar3 = *(undefined1 *)(iVar5 + 0x58);
LAB_0017f4e0:
  *param_2 = uVar3;
  param_2[1] = uVar7;
  return;
}

