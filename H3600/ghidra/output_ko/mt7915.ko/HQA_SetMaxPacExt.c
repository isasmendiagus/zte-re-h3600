// module: mt7915.ko
// function: HQA_SetMaxPacExt @ 0x270800
// size: 224 bytes
//

undefined4 HQA_SetMaxPacExt(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = *(undefined4 *)(param_3 + 0xc);
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  iVar5 = DebugLevel;
  *(char *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0x1150) = (char)((uint)uVar2 >> 0x18);
  if (2 < iVar5) {
    iVar5 = net_ad_wrap_service(param_1);
    iVar3 = net_ad_wrap_service(param_1);
    uVar1 = *(undefined1 *)((uint)*(byte *)(iVar3 + 0x4cc) * 0xd18 + iVar5 + 0x1150);
    iVar5 = net_ad_wrap_service(param_1);
    iVar3 = net_ad_wrap_service(param_1);
    printk("%s: Max Packet Extension:%d (%d us)\n","HQA_SetMaxPacExt",uVar1,
           (2 - (uint)*(byte *)((uint)*(byte *)(iVar3 + 0x4cc) * 0xd18 + iVar5 + 0x1150)) * 8);
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

