// module: mt7915.ko
// function: wifi_sys_conn_act @ 0x105258
// size: 504 bytes
//

undefined4 wifi_sys_conn_act(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_245;
  int local_244;
  uint local_240;
  int local_23c [8];
  undefined1 local_21c [2];
  undefined2 local_21a;
  undefined4 local_218;
  undefined1 local_214;
  uint local_210;
  undefined1 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined2 local_1fc;
  undefined1 local_1fa;
  byte local_1f9;
  undefined1 auStack_1f8 [114];
  undefined1 auStack_186 [54];
  int local_150;
  int local_30;
  undefined1 local_2c;
  
  iVar2 = *(int *)(param_1 + 8);
  *(undefined4 *)(param_2 + 4) = 1;
  local_244 = 0;
  iVar1 = (uint)*(ushort *)(param_2 + 0xe2) * 0x620;
  local_240 = 0;
  local_245 = 0;
  iVar3 = iVar2 + iVar1 + 0x2f6a0;
  os_zero_mem(local_23c,0x214);
  FUN_00104ea8(param_1,*(undefined4 *)(param_2 + 0x1424),param_2,&local_240);
  FUN_0010412c(param_1,param_2,&local_245);
  os_move_mem(local_21c,(void *)(iVar2 + iVar1 + 0x2fa80),0xd8);
  fill_starec_he(param_1,param_2,local_21c);
  local_218 = *(undefined4 *)(param_2 + 0x1424);
  local_21a = *(undefined2 *)(param_2 + 0xe0);
  local_21c[0] = *(undefined1 *)(param_1 + 0x999);
  local_20c = 1;
  local_210 = local_240;
  local_214 = local_245;
  local_150 = iVar3;
  if ((local_240 & 0x1000) == 0) {
    iVar1 = *(int *)(param_1 + 0x14);
  }
  else {
    os_zero_mem(&local_208,0x88);
    local_1f9 = *(byte *)(param_2 + 0x2c8);
    local_1fa = *(undefined1 *)(param_2 + 0xe4);
    local_200 = *(undefined4 *)(param_2 + 0x2c4);
    local_1fc = *(undefined2 *)(param_2 + 0xe0);
    local_204 = 2;
    local_208 = 0;
    os_move_mem(auStack_1f8,(void *)(param_2 + (uint)local_1f9 * 0x51 + 0x180),0x51);
    os_move_mem(auStack_186,(void *)(param_2 + 0xec),6);
    iVar1 = *(int *)(param_1 + 0x14);
  }
  if (iVar1 == 1) {
    local_2c = 1;
    os_alloc_mem(0,&local_244,0x318);
    if (local_244 != 0) {
      os_zero_mem(local_244,0x318);
      local_30 = local_244;
      if ((*(uint *)(param_2 + 0xb4) & 0x200) != 0) {
        *(undefined1 *)(local_244 + 0x314) = 1;
      }
    }
  }
  local_23c[0] = param_1;
  HW_WIFISYS_PEER_LINKUP(iVar2,local_23c);
  if (2 < DebugLevel) {
    printk("===> AsicStaRecUpdate called by (%s), wcid=%d, PortSecured=%d, AKMMap=%d\n",
           "wifi_sys_conn_act",*(undefined2 *)(param_2 + 0xe0),local_214,
           *(undefined4 *)(param_2 + 0x17c));
  }
  sta_set_wireless_sta_configs(iVar2,param_2);
  return 1;
}

