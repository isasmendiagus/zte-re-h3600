// module: mt7915.ko
// function: pci_reset_task_group @ 0x1cb4f4
// size: 204 bytes
//

undefined4 pci_reset_task_group(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar1 = hc_get_chip_cap();
  iVar2 = hc_get_hif_ctrl(param_1);
  uVar3 = (uint)*(byte *)(iVar2 + 0xa8);
  if (uVar3 != 0) {
    uVar4 = 0;
    do {
      while( true ) {
        iVar5 = *(int *)(*(int *)(iVar2 + 0xac) + uVar4 * 4);
        if (*(char *)(iVar1 + 0x15d) != '\0') break;
        tasklet_kill(iVar5 + 0xe0);
        tasklet_kill(iVar5 + 0xf4);
LAB_001cb560:
        tasklet_kill(iVar5 + 0x108);
        tasklet_kill(iVar5 + 0x11c);
        tasklet_kill(iVar5 + 0x130);
        tasklet_kill(iVar5 + 0x144);
        tasklet_kill(iVar5 + 0x158);
        tasklet_kill(iVar5 + 0x16c);
        uVar3 = (uint)*(byte *)(iVar2 + 0xa8);
        uVar4 = uVar4 + 1 & 0xff;
        if (uVar3 <= uVar4) {
          return 0;
        }
      }
      if (*(char *)(iVar1 + 0x15d) == '\x01') {
        tasklet_kill(iVar5 + 0xe0);
        netif_napi_del(iVar5 + 0x640);
        goto LAB_001cb560;
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < uVar3);
  }
  return 0;
}

