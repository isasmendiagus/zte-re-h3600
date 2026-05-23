// module: mt7915.ko
// function: wifi_sys_disconn_act @ 0x10512c
// size: 236 bytes
//

undefined4 wifi_sys_disconn_act(int param_1,int *param_2)

{
  ushort uVar1;
  int iVar2;
  int local_234;
  int local_230;
  int local_22c [8];
  undefined1 local_20c;
  undefined2 local_20a;
  int local_208;
  undefined1 local_204;
  int local_200;
  int local_140;
  undefined1 local_1c;
  
  iVar2 = *(int *)(param_1 + 8);
  uVar1 = *(ushort *)((int)param_2 + 0xe2);
  os_zero_mem(local_22c,0x214);
  local_200 = param_2[1];
  if (local_200 == 1) {
    param_2[1] = 0;
    *(undefined1 *)((int)param_2 + 0x1466) = 0;
    local_208 = param_2[0x509];
    local_20c = *(undefined1 *)(param_1 + 0x999);
    local_20a = (undefined2)param_2[0x38];
    if ((*param_2 - 0x20001U & 0xfffdffff) == 0) {
      local_1c = 1;
    }
    local_204 = 0;
    local_230 = iVar2 + (uint)uVar1 * 0x620 + 0x2f6a0;
    local_234 = param_1;
    local_22c[0] = param_1;
    local_140 = local_230;
    mt_notify_call_chain(*(int *)(param_1 + 8) + 0xa7bef8,3,&local_234);
    HW_WIFISYS_PEER_LINKDOWN(iVar2,local_22c);
    if (*(int *)(param_1 + 0x14) == 1) {
      CheckBMCPortSecured(iVar2,param_2,0);
    }
  }
  return 1;
}

