// module: mt7915.ko
// function: repeater_disconnect_by_band @ 0x83820
// size: 180 bytes
//

void repeater_disconnect_by_band(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (((&DAT_0036790d)[param_1] != '\0') && (uVar3 = (uint)*(byte *)(iVar1 + 0x14a), uVar3 != 0)) {
    uVar4 = 0;
    do {
      iVar6 = *(int *)(&DAT_003687a8 + param_1);
      iVar5 = iVar6 + uVar4 * 0x42f4;
      if (iVar5 != -0xe0) {
        iVar2 = HcGetBandByWdev();
        if ((iVar2 == param_2) && (*(char *)(iVar6 + uVar4 * 0x42f4) != '\0')) {
          RepeaterDisconnectRootAP(param_1,iVar5,0xc);
        }
        uVar3 = (uint)*(byte *)(iVar1 + 0x14a);
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < uVar3);
  }
  return;
}

