// module: mt7915.ko
// function: HQA_SetFAGCRssiPath @ 0x275c94
// size: 200 bytes
//

undefined4 HQA_SetFAGCRssiPath(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar4 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar5 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  uVar6 = uVar4;
  uVar7 = uVar5;
  iVar3 = net_ad_wrap_service(param_1);
  *(char *)(uVar4 * 0xd18 + iVar3 + 0x113e) = (char)(uVar2 >> 0x18);
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar1 >> 0x18);
  MtCmdSetFAGCPath(param_1,uVar2 >> 0x18,uVar1 >> 0x18,param_1 + 0xa3a000,uVar6,uVar7);
  if (2 < DebugLevel) {
    printk("%s: band_idx:%d, FAGC_Path%d\n","HQA_SetFAGCRssiPath",uVar4,uVar5);
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

