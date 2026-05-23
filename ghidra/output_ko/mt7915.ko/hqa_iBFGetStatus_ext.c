// module: mt7915.ko
// function: hqa_iBFGetStatus_ext @ 0x277f40
// size: 256 bytes
//

undefined4 hqa_iBFGetStatus_ext(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int local_2c;
  uint local_28;
  int local_24;
  
  local_2c = param_3 + 0xc;
  iVar2 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar2 + 0x4cc);
  iVar2 = net_ad_wrap_service(param_1);
  iVar4 = (uint)bVar1 * 0xd18;
  local_28 = 0;
  local_24 = 0;
  uVar6 = *(undefined4 *)(iVar2 + iVar4 + 0x11d0);
  FUN_00276034(1,4,&local_2c,&local_28);
  iVar2 = net_ad_wrap_service(param_1);
  if (*(int *)(iVar2 + iVar4 + 0x11d0) != 0) {
    iVar2 = net_ad_wrap_service(param_1);
    bVar1 = *(byte *)(iVar2 + iVar4 + 0x11d8);
    iVar3 = net_ad_wrap_service(param_1);
    iVar2 = (uint)bVar1 << 0x18;
    uVar5 = *(uint *)(iVar3 + iVar4 + 0x4e0);
    iVar3 = net_ad_wrap_service(param_1);
    *(uint *)(iVar3 + iVar4 + 0x4e0) = uVar5 & 0xfffffbff;
    os_free_mem(uVar6);
    local_28 = local_28 << 0x18 | (local_28 >> 8 & 0xff) << 0x10 | (local_28 >> 0x10 & 0xff) << 8 |
               local_28 >> 0x18;
    *(uint *)(param_3 + 0xe) = local_28;
    *(int *)(param_3 + 0x12) = iVar2;
    local_24 = iVar2;
  }
  FUN_0026cdd0(param_3,param_2,10,0);
  return 0;
}

