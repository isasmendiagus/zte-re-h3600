// module: mt7915.ko
// function: bufferModeEfuseFill @ 0x179658
// size: 140 bytes
//

void bufferModeEfuseFill(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *(undefined2 *)(param_2 + 2) = 0;
  uVar2 = ((uint)*(byte *)(param_2 + 1) << 0x1b) >> 0x1d;
  if (uVar2 == *(byte *)(param_2 + 1) >> 5) {
    uVar5 = *(ushort *)(iVar1 + 0xf6) & 0x3ff;
    if ((*(ushort *)(iVar1 + 0xf6) & 0x3ff) == 0) {
      uVar5 = 0x400;
    }
  }
  else {
    uVar5 = 0x400;
  }
  puVar6 = (undefined1 *)(param_2 + 3);
  uVar4 = 0;
  do {
    uVar3 = uVar2 * 0x400 + uVar4;
    uVar4 = uVar4 + 1;
    puVar6 = puVar6 + 1;
    *puVar6 = *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + (uVar3 & 0xffff));
    *(short *)(param_2 + 2) = (short)uVar4;
  } while ((uVar4 & 0xffff) < uVar5);
  return;
}

