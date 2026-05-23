// module: mt7915.ko
// function: MT_ATEStopContinousTx @ 0x27e054
// size: 260 bytes
//

void MT_ATEStopContinousTx(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  
  bVar1 = *(byte *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATEStopContinousTx");
  }
  iVar7 = net_ad_wrap_service(param_1);
  iVar8 = (uint)bVar1 * 0xd18;
  uVar2 = *(undefined1 *)(iVar7 + iVar8 + 0x1135);
  iVar7 = net_ad_wrap_service(param_1);
  uVar3 = *(undefined1 *)(iVar7 + iVar8 + 0x1136);
  iVar7 = net_ad_wrap_service(param_1);
  uVar4 = *(undefined1 *)(iVar7 + iVar8 + 0x1132);
  iVar7 = net_ad_wrap_service(param_1);
  uVar5 = *(undefined1 *)(iVar7 + iVar8 + 0x1130);
  iVar7 = net_ad_wrap_service(param_1);
  uVar6 = *(undefined1 *)(iVar7 + iVar8 + 0x1138);
  iVar7 = net_ad_wrap_service(param_1);
  MtCmdTxContinous(param_1,uVar2,uVar3,uVar4,uVar5,uVar6,*(undefined4 *)(iVar7 + iVar8 + 0x1128),
                   param_2,(uint)bVar1,0);
  return;
}

