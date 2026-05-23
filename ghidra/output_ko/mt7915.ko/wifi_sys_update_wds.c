// module: mt7915.ko
// function: wifi_sys_update_wds @ 0x1059f8
// size: 184 bytes
//

void wifi_sys_update_wds(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_238;
  int local_234 [8];
  undefined1 local_214;
  undefined2 local_212;
  undefined4 local_210;
  undefined1 local_20c;
  undefined4 local_208;
  undefined1 local_204;
  int local_148;
  
  iVar2 = *(int *)(param_2 + 8);
  local_238 = 0;
  iVar1 = (uint)*(ushort *)(param_2 + 0xe2) * 0x620;
  iVar3 = param_1 + iVar1;
  if (*(char *)(iVar3 + 0x2fa88) != '\0') {
    os_zero_mem(local_234,0x214);
    FUN_00104ea8(iVar2,*(undefined4 *)(param_2 + 0x1424),param_2,&local_238);
    local_212 = *(undefined2 *)(param_2 + 0xe0);
    local_210 = *(undefined4 *)(param_2 + 0x1424);
    local_20c = *(undefined1 *)(iVar3 + 0x2fa88);
    local_214 = *(undefined1 *)(iVar2 + 0x999);
    local_204 = 0;
    local_208 = local_238;
    local_234[0] = iVar2;
    local_148 = param_1 + iVar1 + 0x2f6a0;
    HW_WIFISYS_PEER_UPDATE(param_1,local_234);
  }
  return;
}

