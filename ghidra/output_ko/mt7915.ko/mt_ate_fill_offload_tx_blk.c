// module: mt7915.ko
// function: mt_ate_fill_offload_tx_blk @ 0x27cbc4
// size: 296 bytes
//

void mt_ate_fill_offload_tx_blk(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined1 auStack_30 [20];
  
  pbVar5 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar6 = net_ad_wrap_service(param_1);
  iVar7 = HcGetBandByWdev(param_2);
  iVar9 = *(int *)(param_3 + 0xc);
  cVar1 = *(char *)(iVar7 * 0xd18 + iVar6 + 0x1135);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar9 + 0x42);
  RTMP_QueryPacketInfo(iVar9,auStack_30,param_3 + 0x24,param_3 + 0x28);
  iVar6 = *(int *)(param_3 + 0x24) + (uint)*pbVar5;
  uVar8 = *(uint *)(param_3 + 0x18);
  *(int *)(param_3 + 0x24) = iVar6;
  bVar2 = *pbVar5;
  *(uint *)(param_3 + 0x18) = uVar8 | 0x100000;
  *(uint *)(param_3 + 0x28) = *(int *)(param_3 + 0x28) - (uint)bVar2;
  cVar3 = *(char *)(iVar9 + 0x2e);
  *(int *)(param_3 + 0x30) = iVar6;
  if (cVar3 != '\0') {
    *(uint *)(param_3 + 0x18) = uVar8 | 0x100100;
  }
  uVar4 = HcGetWmmIdx(param_1,param_2);
  *(undefined1 *)(param_3 + 0x20) = uVar4;
  iVar6 = net_ad_wrap_service(param_1);
  iVar7 = HcGetBandByWdev(param_2);
  cVar3 = *(char *)(iVar7 * 0xd18 + iVar6 + 0x1104);
  *(undefined1 *)(param_3 + 0x1c) = 0;
  *(undefined1 *)(param_3 + 0x2f) = 0;
  if (cVar1 == '\v' && cVar3 != '\0') {
    uVar8 = *(uint *)(param_3 + 0x18) | 0x80;
  }
  else {
    uVar8 = *(uint *)(param_3 + 0x18) | 0x20000000;
  }
  *(uint *)(param_3 + 0x18) = uVar8;
  *(uint *)(param_3 + 100) = *(uint *)(param_3 + 100) | 1;
  return;
}

