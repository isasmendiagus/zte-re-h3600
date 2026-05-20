// module: mt7915.ko
// function: HQA_MPSSetPerpacketBW @ 0x2713dc
// size: 440 bytes
//

uint HQA_MPSSetPerpacketBW(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  bool bVar8;
  int local_30;
  uint local_2c;
  
  uVar2 = (((*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8)) << 0x10)
          >> 0x12;
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  iVar4 = uVar2 - 1;
  local_30 = 0;
  local_2c = 0;
  if (2 < DebugLevel) {
    printk("%s: len:%u\n","HQA_MPSSetPerpacketBW",iVar4);
  }
  if (uVar2 - 2 < 0x200) {
    uVar3 = os_alloc_mem(param_1,&local_30,iVar4 * 4);
    if (uVar3 == 1) {
      uVar2 = 0;
    }
    else {
      uVar1 = *(uint *)(param_3 + 0xc);
      iVar6 = 0;
      uVar2 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
              uVar1 >> 0x18;
      *(char *)(param_1 + 0xa3ae36) = (char)(uVar1 >> 0x18);
      do {
        uVar7 = 0;
        uVar1 = *(uint *)(param_3 + iVar6 + 0x10);
        uVar1 = (uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                uVar1 >> 0x18) - 1;
        if (uVar1 < 6) {
          uVar7 = *(undefined4 *)(&DAT_002a621c + uVar1 * 4);
        }
        bVar8 = iVar6 != iVar4 * 4 + -4;
        *(undefined4 *)(local_30 + iVar6) = uVar7;
        iVar6 = iVar6 + 4;
      } while ((bVar8) && (iVar6 != 0x7fc));
      local_2c = uVar2;
      (**(code **)(iVar5 + 0xcc))(param_1,9,iVar4,local_30);
      os_free_mem(local_30);
    }
  }
  else {
    uVar3 = 0;
    uVar2 = uVar3;
  }
  iVar5 = net_ad_wrap_service(param_1);
  if (2 < DebugLevel) {
    printk("%s: len:%u, MPS_CNT:%u\n","HQA_MPSSetPerpacketBW",iVar4,
           *(undefined4 *)(uVar2 * 0xd18 + iVar5 + 0x11b8));
  }
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  return uVar3;
}

