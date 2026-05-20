// module: mt7915.ko
// function: fp_qm_exit @ 0xd4120
// size: 876 bytes
//

undefined4 fp_qm_exit(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = *(undefined4 *)(param_1 + 0x285ae8);
  iVar5 = param_1 + 0x285b3c;
  puVar7 = (undefined4 *)(param_1 + 0x285b50);
  do {
    OS_SPIN_LOCK_BH(iVar5);
    piVar4 = (int *)puVar7[-1];
    while (piVar4 != (int *)0x0) {
      iVar2 = *piVar4;
      *piVar4 = 0;
      puVar7[-1] = iVar2;
      if (iVar2 == 0) {
        *puVar7 = 0;
      }
      puVar7[1] = puVar7[1] + -1;
      RTMPFreeNdisPacket(param_1,piVar4);
      piVar4 = (int *)puVar7[-1];
    }
    OS_SPIN_LOCK_BH(iVar5 + 8);
    piVar4 = (int *)puVar7[7];
    while (piVar4 != (int *)0x0) {
      iVar2 = *piVar4;
      *piVar4 = 0;
      puVar7[7] = iVar2;
      if (iVar2 == 0) {
        puVar7[8] = 0;
      }
      puVar7[9] = puVar7[9] + -1;
      RTMPFreeNdisPacket(param_1,piVar4);
      piVar4 = (int *)puVar7[7];
    }
    OS_SPIN_UNLOCK_BH(iVar5 + 8);
    OS_SPIN_UNLOCK_BH(iVar5);
    OS_SPIN_LOCK_BH(iVar5 + -0x10);
    piVar4 = (int *)puVar7[-0x19];
    while (piVar4 != (int *)0x0) {
      iVar2 = *piVar4;
      *piVar4 = 0;
      puVar7[-0x19] = iVar2;
      if (iVar2 == 0) {
        puVar7[-0x18] = 0;
      }
      puVar7[-0x17] = puVar7[-0x17] + -1;
      RTMPFreeNdisPacket(param_1,piVar4);
      piVar4 = (int *)puVar7[-0x19];
    }
    OS_SPIN_LOCK_BH(iVar5 + -8);
    piVar4 = (int *)puVar7[-0x11];
    while (piVar4 != (int *)0x0) {
      iVar2 = *piVar4;
      *piVar4 = 0;
      puVar7[-0x11] = iVar2;
      if (iVar2 == 0) {
        puVar7[-0x10] = 0;
      }
      puVar7[-0xf] = puVar7[-0xf] + -1;
      RTMPFreeNdisPacket(param_1,piVar4);
      piVar4 = (int *)puVar7[-0x11];
    }
    puVar7 = puVar7 + 4;
    OS_SPIN_UNLOCK_BH(iVar5 + -8);
    OS_SPIN_UNLOCK_BH(iVar5 + -0x10);
    iVar5 = iVar5 + 4;
  } while (puVar7 != (undefined4 *)(param_1 + 0x285b70));
  if (*(char *)(iVar1 + 0x15b) == '\0') {
    OS_SPIN_LOCK_BH(param_1 + 0x285bf0);
    piVar4 = *(int **)(param_1 + 0x285bf4);
    while (piVar4 != (int *)0x0) {
      iVar1 = *piVar4;
      *piVar4 = 0;
      *(int *)(param_1 + 0x285bf4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0x285bf8) = 0;
      }
      *(int *)(param_1 + 0x285bfc) = *(int *)(param_1 + 0x285bfc) + -1;
      RTMPFreeNdisPacket(param_1,piVar4);
      piVar4 = *(int **)(param_1 + 0x285bf4);
    }
    piVar4 = *(int **)(param_1 + 0x285c04);
    while (piVar4 != (int *)0x0) {
      iVar1 = *piVar4;
      *piVar4 = 0;
      *(int *)(param_1 + 0x285c04) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0x285c08) = 0;
      }
      *(int *)(param_1 + 0x285c0c) = *(int *)(param_1 + 0x285c0c) + -1;
      RTMPFreeNdisPacket(param_1,piVar4);
      piVar4 = *(int **)(param_1 + 0x285c04);
    }
    OS_SPIN_UNLOCK_BH(param_1 + 0x285bf0);
  }
  iVar1 = 0;
  os_free_mem(uVar3);
  do {
    iVar5 = iVar1 * 2;
    iVar6 = param_1 + iVar1 + 0x285b2c;
    OS_SPIN_LOCK_BH(iVar6);
    iVar2 = *(int *)(*(int *)(param_1 + 0x285b94) + iVar1 * 2);
    if (*(int *)(param_1 + 0x285b94) + iVar5 != iVar2) {
      do {
        piVar4 = (int *)(iVar2 + -0x4050);
        if (piVar4 == (int *)0x0) break;
        if (piVar4[0x1014] != 0) {
          *(int *)(piVar4[0x1014] + 4) = piVar4[0x1015];
        }
        if ((int *)piVar4[0x1015] != (int *)0x0) {
          *(int *)piVar4[0x1015] = piVar4[0x1014];
        }
        piVar4[0x1014] = 0;
        piVar4[0x1015] = 0;
        netif_tx_wake_queue(*(undefined4 *)(*piVar4 + 0x240));
        iVar2 = *(int *)(*(int *)(param_1 + 0x285b94) + iVar5);
      } while (*(int *)(param_1 + 0x285b94) + iVar5 != iVar2);
    }
    iVar1 = iVar1 + 4;
    OS_SPIN_UNLOCK_BH(iVar6);
    if (iVar1 == 8) {
      os_free_mem(*(undefined4 *)(param_1 + 0x285b90));
      os_free_mem(*(undefined4 *)(param_1 + 0x285b94));
      return 0;
    }
  } while( true );
}

