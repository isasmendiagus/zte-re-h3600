// module: mt7915.ko
// function: HQA_GetHETBParams @ 0x270710
// size: 240 bytes
//

undefined4 HQA_GetHETBParams(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  iVar3 = net_ad_wrap_service();
  iVar4 = net_ad_wrap_service(param_1);
  bVar1 = *(byte *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0x10dc);
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  iVar3 = (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0xa1c + (uint)bVar1 * 0x6c;
  uVar5 = *(uint *)(iVar3 + 0x30);
  bVar1 = *(byte *)(iVar3 + 0x5c);
  bVar2 = *(byte *)(iVar3 + 100);
  uVar7 = *(uint *)(iVar3 + 0x2c);
  uVar6 = *(uint *)(iVar3 + 0x68);
  *(uint *)(param_3 + 0xe) =
       uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 | uVar5 >> 0x18;
  *(uint *)(param_3 + 0x12) = (uint)bVar1 << 0x18;
  *(uint *)(param_3 + 0x16) = (uint)bVar2 << 0x18;
  *(uint *)(param_3 + 0x1a) =
       uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 | uVar7 >> 0x18;
  *(uint *)(param_3 + 0x1e) =
       uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 | uVar6 >> 0x18;
  FUN_0026cdd0(param_3,param_2,0x16,0);
  return 0;
}

