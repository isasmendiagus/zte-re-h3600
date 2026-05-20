// module: mt7915.ko
// function: build_vht_ies @ 0x2033e4
// size: 580 bytes
//

uint build_vht_ies(undefined4 param_1,int *param_2)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  void *__dest;
  byte local_27 [4];
  undefined1 local_23;
  byte local_22;
  
  iVar4 = wlan_operate_get_vht_bw(param_2[4]);
  iVar5 = wlan_operate_get_ht_bw(param_2[4]);
  iVar6 = FUN_002019d0(param_1,param_2);
  if (iVar6 == 0) {
    if ((*(ushort *)(param_2 + 2) & 0x20) == 0) {
      return *(ushort *)(param_2 + 2) & 0x20;
    }
    if (*(byte *)((int)param_2 + 6) < 0xf) {
      return 0;
    }
  }
  __memzero(local_27 + 1,3);
  local_27[2] = 0xc;
  local_27[1] = 0xbf;
  memmove((void *)*param_2,local_27 + 1,2);
  iVar6 = build_vht_cap_ie(param_1,param_2[4],*param_2 + 2);
  bVar1 = *(byte *)(param_2 + 1);
  uVar7 = iVar6 + 2;
  if ((bVar1 & 0xfd) != 1 && (bVar1 != 8 && bVar1 != 5)) {
    if (((bVar1 & 0xfd) == 0) && (iVar4 == 0 && iVar5 == 1)) {
      iVar5 = param_2[4];
      __dest = (void *)(*param_2 + uVar7);
      iVar4 = wlan_operate_get_vht_bw(iVar5);
      __memzero(&local_23,3);
      __memzero(local_27,1);
      local_23 = 199;
      local_22 = 1;
      memmove(__dest,&local_23,2);
      local_27[0] = local_27[0] & 0x7f | bVar1 << 7;
      cVar3 = wlan_operate_get_rx_stream(iVar5);
      bVar1 = (cVar3 - 1U & 7) << 4;
      bVar2 = local_27[0] & 0x8f | bVar1;
      if (iVar4 == 0) {
        local_27[0] = bVar2;
        iVar4 = wlan_operate_get_ht_bw(iVar5);
        if (iVar4 == 1) {
          local_27[0] = local_27[0] & 0xfc | 1;
        }
        else {
          local_27[0] = local_27[0] & 0xfc;
        }
      }
      else if (iVar4 == 1) {
        local_27[0] = local_27[0] & 0x8c | bVar1 | 2;
      }
      else {
        local_27[0] = bVar2;
        if ((iVar4 - 2U & 0xff) < 2) {
          local_27[0] = bVar2 | 3;
        }
      }
      uVar7 = uVar7 + local_22 + 2;
      *(byte *)((int)__dest + 2) = local_27[0];
    }
    return uVar7;
  }
  local_27[1] = 0xc0;
  local_27[2] = 5;
  memmove((void *)(*param_2 + uVar7),local_27 + 1,2);
  iVar5 = FUN_002019d0(param_1,param_2);
  if (iVar5 != 0) {
    iVar4 = 0;
  }
  iVar4 = build_vht_oper_ie(param_1,iVar4,*(undefined1 *)((int)param_2 + 6),param_2[4],
                            *param_2 + iVar6 + 4);
  return iVar4 + iVar6 + 4;
}

