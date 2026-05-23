// module: mt7915.ko
// function: RTMPUpdateMlmeRate @ 0x12f650
// size: 600 bytes
//

void RTMPUpdateMlmeRate(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  byte bVar7;
  byte *pbVar8;
  byte bVar9;
  ushort *puVar10;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 == 0) {
    printk(&_LC14,0x18ea);
    dump_stack();
    return;
  }
  if (*(ushort *)(param_2 + 0x18) == 2) {
    uVar6 = 3;
    cVar2 = '\0';
    bVar9 = *(byte *)(iVar1 + 0x4176);
LAB_0012f68c:
    if (bVar9 == 0) goto LAB_0012f6e0;
  }
  else {
    if ((*(ushort *)(param_2 + 0x18) & 2) == 0) {
      bVar9 = *(byte *)(iVar1 + 0x4176);
      uVar6 = 8;
      cVar2 = '\x04';
      goto LAB_0012f68c;
    }
    bVar9 = *(byte *)(iVar1 + 0x4176);
    if (bVar9 != 4) {
      uVar6 = 8;
      if (0xe < *(byte *)(iVar1 + 0x4165)) goto LAB_0012f804;
      cVar2 = '\0';
      goto LAB_0012f68c;
    }
    if (*(char *)(iVar1 + 0x4183) == '\0') {
      uVar6 = 3;
      cVar2 = '\0';
      if (0xe < *(byte *)(iVar1 + 0x4165)) {
LAB_0012f804:
        cVar2 = '\x04';
        goto LAB_0012f68c;
      }
    }
    else {
      uVar6 = 8;
      if (0xe < *(byte *)(iVar1 + 0x4165)) goto LAB_0012f804;
      cVar2 = '\0';
    }
  }
  bVar7 = 0;
  pbVar8 = (byte *)(iVar1 + 0x4176);
  do {
    pbVar8 = pbVar8 + 1;
    uVar4 = 0;
    puVar10 = (ushort *)RateIdTo500Kbps;
    do {
      uVar3 = uVar4 & 0xff;
      uVar4 = uVar4 + 1;
      cVar5 = (char)uVar6;
      if (*puVar10 == (*pbVar8 & 0x7f) && uVar6 == uVar3) goto LAB_0012f744;
      puVar10 = puVar10 + 1;
    } while (uVar4 != 0xc);
    bVar7 = bVar7 + 1;
  } while (bVar7 < bVar9);
LAB_0012f6e0:
  cVar5 = cVar2;
  if (*(char *)(iVar1 + 0x4183) != '\0') {
    pbVar8 = (byte *)(iVar1 + 0x4183);
    do {
      pbVar8 = pbVar8 + 1;
      uVar4 = 0;
      puVar10 = (ushort *)RateIdTo500Kbps;
      do {
        uVar3 = uVar4 & 0xff;
        uVar4 = uVar4 + 1;
        cVar5 = (char)uVar6;
        if (*puVar10 == (*pbVar8 & 0x7f) && uVar6 == uVar3) goto LAB_0012f744;
        puVar10 = puVar10 + 1;
      } while (uVar4 != 0xc);
      cVar5 = cVar2;
    } while (pbVar8 != (byte *)(iVar1 + (byte)(*(char *)(iVar1 + 0x4183) - 1) + 0x4184));
  }
LAB_0012f744:
  *(char *)(param_1 + 0x794cd5) = cVar2;
  *(char *)(param_1 + 0x794cd4) = cVar5;
  if (cVar2 == '\x04') {
    *(byte *)(param_2 + 0xb0b) = *(byte *)(param_2 + 0xb0b) & 0x1f | 0x20;
    *(byte *)(param_2 + 0xb0a) =
         *(byte *)(param_2 + 0xb0a) & 0xc0 | OfdmRateToRxwiMCS[*(byte *)(param_1 + 0x794cd5)] & 0x3f
    ;
    *(byte *)(param_1 + 0xa1ddd) = *(byte *)(param_1 + 0xa1ddd) & 0x1f | 0x20;
    *(byte *)(param_1 + 0xa1ddc) =
         *(byte *)(param_1 + 0xa1ddc) & 0xc0 |
         OfdmRateToRxwiMCS[*(byte *)(param_1 + 0x794cd5)] & 0x3f;
  }
  else {
    *(byte *)(param_2 + 0xb0b) = *(byte *)(param_2 + 0xb0b) & 0x1f;
    *(byte *)(param_2 + 0xb0a) =
         *(byte *)(param_2 + 0xb0a) & 0xc0 | *(byte *)(param_1 + 0x794cd5) & 0x3f;
    *(byte *)(param_1 + 0xa1ddd) = *(byte *)(param_1 + 0xa1ddd) & 0x1f;
    *(byte *)(param_1 + 0xa1ddc) =
         *(byte *)(param_1 + 0xa1ddc) & 0xc0 | *(byte *)(param_1 + 0x794cd5) & 0x3f;
  }
  if (2 < DebugLevel) {
    printk("%s():=>MlmeTransmit=0x%x\n","RTMPUpdateMlmeRate",*(undefined2 *)(param_2 + 0xb0a),
           param_4);
    return;
  }
  return;
}

