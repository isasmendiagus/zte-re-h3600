// module: mt7915.ko
// function: net_ad_get_rxv_stat @ 0x25e28c
// size: 272 bytes
//

undefined4 net_ad_get_rxv_stat(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    param_2 = param_2 * 0x168;
    puVar5 = (undefined4 *)(iVar1 + param_2 + 0xa7bfe0);
    puVar7 = (undefined4 *)(iVar1 + param_2 + 0xa7bfd0);
    puVar2 = (undefined4 *)(iVar1 + param_2 + 0xa7bf80);
    puVar4 = (undefined4 *)(iVar1 + param_2 + 0xa7bff0);
    iVar6 = 0;
    iVar3 = param_3;
    do {
      puVar5 = puVar5 + 1;
      iVar6 = iVar6 + 1;
      *(undefined4 *)(iVar3 + 0x78) = *puVar5;
      puVar4 = puVar4 + 1;
      *(undefined4 *)(iVar3 + 0x7c) = *puVar4;
      puVar7 = puVar7 + 1;
      *(undefined4 *)(iVar3 + 0x70) = *puVar7;
      puVar2 = puVar2 + 1;
      *(undefined4 *)(iVar3 + 0x74) = *puVar2;
      iVar3 = iVar3 + 0x18;
    } while (iVar6 != 4);
    puVar5 = (undefined4 *)(iVar1 + param_2 + 0xa7bf40);
    puVar4 = (undefined4 *)(iVar1 + param_2 + 0xa7bf90);
    puVar2 = (undefined4 *)(iVar1 + param_2 + 0xa7c010);
    iVar1 = 0;
    do {
      puVar5 = puVar5 + 1;
      iVar1 = iVar1 + 1;
      *(undefined4 *)(param_3 + 0xd0) = *puVar5;
      puVar4 = puVar4 + 1;
      *(undefined4 *)(param_3 + 0xd4) = *puVar4;
      puVar2 = puVar2 + 1;
      *(undefined4 *)(param_3 + 0xd8) = *puVar2;
      param_3 = param_3 + 0xc;
    } while (iVar1 != 0x10);
    return 0;
  }
  return 0x606;
}

