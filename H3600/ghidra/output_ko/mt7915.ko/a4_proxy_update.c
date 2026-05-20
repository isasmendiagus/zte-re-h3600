// module: mt7915.ko
// function: a4_proxy_update @ 0x9f4bc
// size: 260 bytes
//

void a4_proxy_update(int param_1,undefined4 param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  ushort local_1a;
  
  local_1a = 0;
  iVar1 = a4_get_entry_count();
  if (iVar1 == 0) {
    return;
  }
  uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_4 == 0 || uVar2 <= param_3) {
    return;
  }
  iVar1 = RoutingTabLookup(param_1,param_2,param_4,1,&local_1a);
  if (iVar1 != 0) {
    if ((*(uint *)(iVar1 + 4) & 1) == 0) {
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
      goto LAB_0009f594;
    }
    if (local_1a == param_3) goto LAB_0009f594;
    RoutingTabSetOneFree(param_1,param_2,param_4,1);
  }
  iVar1 = RoutingTabGetFree(param_1,param_2);
  if (iVar1 == 0) {
    return;
  }
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
  RoutingEntrySet(param_1,param_2,param_3,param_4,iVar1);
LAB_0009f594:
  if (param_5 != 0) {
    RoutingTabARPLookupUpdate(param_1,param_2,iVar1);
  }
  return;
}

