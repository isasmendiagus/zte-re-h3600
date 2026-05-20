// module: plat-zxylzb_9128S.ko
// function: idm_net_int @ 0x14d48
// size: 176 bytes
//

undefined4 idm_net_int(void)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  
  iVar1 = (int)idm_netdev;
  puVar3 = (uint *)(npp_base + 0x8020);
  *(int *)((int)idm_netdev + 0x598) = *(int *)((int)idm_netdev + 0x598) + 1;
  puVar4 = (uint *)(npp_base + 0x8024);
  *(uint *)(iVar1 + 0x4c8) = *puVar3 & ~idm_int_mask;
  idm_int_mask = *puVar4 | 0x14;
  *(uint *)(npp_base + 0x8024) = idm_int_mask;
  if ((-1 < *(int *)(iVar1 + 0x530) << 0x1e) &&
     (iVar2 = _test_and_set_bit(0,iVar1 + 0x530), iVar2 == 0)) {
    __napi_schedule(iVar1 + 0x528);
    return 1;
  }
  *(int *)(iVar1 + 0x59c) = *(int *)(iVar1 + 0x59c) + 1;
  return 1;
}

