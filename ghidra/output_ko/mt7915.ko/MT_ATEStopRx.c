// module: mt7915.ko
// function: MT_ATEStopRx @ 0x2803fc
// size: 312 bytes
//

undefined4 MT_ATEStopRx(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  code *pcVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  iVar7 = *(int *)(param_1 + 0xa39fd8);
  iVar2 = net_ad_wrap_service();
  uVar6 = (uint)*(byte *)(iVar2 + 0x4cc);
  iVar2 = net_ad_wrap_service(param_1);
  iVar5 = uVar6 * 0xd18;
  uVar8 = *(uint *)(iVar2 + iVar5 + 0x4e0);
  iVar2 = net_ad_wrap_service(param_1);
  cVar1 = *(char *)(iVar2 + iVar5 + 0x1135);
  uVar3 = MtATESetMacTxRx(param_1,6,0,uVar6);
  iVar2 = net_ad_wrap_service(param_1);
  *(uint *)(iVar2 + iVar5 + 0x4e0) = uVar8 & 0xfffffffb;
  pcVar4 = *(code **)(iVar7 + 4);
  if (pcVar4 != (code *)0x0) {
    (*pcVar4)(param_1);
  }
  iVar2 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (cVar1 == '\v') {
    iVar2 = net_ad_wrap_service(param_1);
    if (*(int *)(uVar6 * 0xd18 + iVar2 + 0x1110) != 0) {
      MtATESetRxMUAid(param_1,uVar6,0xf100);
    }
  }
  else if ((cVar1 == '\n') && (*(code **)(iVar2 + 0x9c) != (code *)0x0)) {
    (**(code **)(iVar2 + 0x9c))(param_1,uVar6,0,0,0,0,0xffffffff,0xffffffff,0,0);
    return uVar3;
  }
  return uVar3;
}

