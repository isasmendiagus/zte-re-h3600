// module: mt7915.ko
// function: HQA_MPSSetPacketCount @ 0x2718b8
// size: 392 bytes
//

uint HQA_MPSSetPacketCount(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  int local_30;
  uint local_2c;
  
  uVar3 = (((*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8)) << 0x10)
          >> 0x12;
  iVar6 = *(int *)(param_1 + 0xa39fd4);
  iVar4 = uVar3 - 1;
  local_30 = 0;
  local_2c = 0;
  if (2 < DebugLevel) {
    printk("%s: len:%u\n","HQA_MPSSetPacketCount",iVar4);
  }
  if (uVar3 - 2 < 0x400) {
    uVar5 = os_alloc_mem(param_1,&local_30,iVar4 * 4);
    if (uVar5 == 1) {
      uVar3 = 0;
    }
    else {
      uVar1 = *(uint *)(param_3 + 0xc);
      iVar7 = 0;
      iVar2 = 1;
      uVar3 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
              uVar1 >> 0x18;
      *(char *)(param_1 + 0xa3ae36) = (char)(uVar1 >> 0x18);
      do {
        bVar8 = iVar2 == iVar4;
        iVar2 = iVar2 + 1;
        uVar1 = *(uint *)(param_3 + iVar7 + 0x10);
        *(uint *)(local_30 + iVar7) =
             uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
             uVar1 >> 0x18;
        iVar7 = iVar7 + 4;
        if (bVar8) break;
      } while (iVar7 != 0x7fc);
      local_2c = uVar3;
      (**(code **)(iVar6 + 0xcc))(param_1,5,iVar4,local_30);
      os_free_mem(local_30);
    }
  }
  else {
    uVar5 = 0;
    uVar3 = uVar5;
  }
  iVar6 = net_ad_wrap_service(param_1);
  if (2 < DebugLevel) {
    printk("%s: len:%u, MPS_CNT:%u\n","HQA_MPSSetPacketCount",iVar4,
           *(undefined4 *)(uVar3 * 0xd18 + iVar6 + 0x11b8));
  }
  FUN_0026cdd0(param_3,param_2,2,uVar5);
  return uVar5;
}

