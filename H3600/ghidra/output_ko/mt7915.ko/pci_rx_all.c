// module: mt7915.ko
// function: pci_rx_all @ 0x1cee28
// size: 88 bytes
//

void pci_rx_all(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 0xb0));
  if (*(char *)(param_1 + 1) == '\0') {
    return;
  }
  uVar3 = 0;
  do {
    piVar2 = *(int **)(*(int *)(param_1 + 4) + uVar3 * 4);
    uVar3 = uVar3 + 1;
    (**(code **)(param_1 + *piVar2 * 4 + 0xc))(uVar1,(char)piVar2[7]);
  } while (uVar3 < *(byte *)(param_1 + 1));
  return;
}

