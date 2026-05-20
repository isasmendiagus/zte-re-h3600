// module: mt7915.ko
// function: MT_ATEStartContinousTx @ 0x27e15c
// size: 240 bytes
//

undefined4 MT_ATEStartContinousTx(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  char cVar8;
  bool bVar9;
  
  bVar1 = *(byte *)(param_1 + 0xa3ae36);
  iVar6 = net_ad_wrap_service();
  iVar7 = (uint)bVar1 * 0xd18;
  uVar2 = *(undefined1 *)(iVar6 + iVar7 + 0x1135);
  iVar6 = net_ad_wrap_service(param_1);
  cVar8 = *(char *)(iVar6 + iVar7 + 0x1136);
  iVar6 = net_ad_wrap_service(param_1);
  uVar3 = *(undefined1 *)(iVar6 + iVar7 + 0x1132);
  iVar6 = net_ad_wrap_service(param_1);
  uVar4 = *(undefined1 *)(iVar6 + iVar7 + 0x1130);
  iVar6 = net_ad_wrap_service(param_1);
  uVar5 = *(undefined1 *)(iVar6 + iVar7 + 0x1138);
  iVar6 = net_ad_wrap_service(param_1);
  bVar9 = cVar8 == '\x06';
  if (bVar9) {
    cVar8 = '\x03';
  }
  if ((!bVar9) && (cVar8 == '\x05')) {
    cVar8 = '\x04';
  }
  MtCmdTxContinous(param_1,uVar2,cVar8,uVar3,uVar4,uVar5,*(undefined4 *)(iVar6 + iVar7 + 0x1128),
                   param_3,(uint)bVar1,1);
  return 0;
}

