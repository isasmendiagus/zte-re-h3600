// module: idmfdb.ko
// function: register_idm_fdb_node_bydev @ 0x10748
// size: 196 bytes
//

undefined1 * register_idm_fdb_node_bydev(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  char local_20 [16];
  
  local_20[0] = '\0';
  local_20[1] = '\0';
  local_20[2] = '\0';
  local_20[3] = '\0';
  local_20[4] = '\0';
  local_20[5] = '\0';
  local_20[6] = '\0';
  local_20[7] = '\0';
  local_20[8] = '\0';
  local_20[9] = '\0';
  local_20[10] = '\0';
  local_20[0xb] = '\0';
  local_20[0xc] = '\0';
  local_20[0xd] = '\0';
  local_20[0xe] = '\0';
  local_20[0xf] = '\0';
  if (((param_1 != 0) && (iVar2 = IfName2WlanIdmMap(), iVar2 != 0)) &&
     (uVar4 = (uint)*(byte *)(iVar2 + 0x26) + (uint)*(byte *)(iVar2 + 0x25) * 8, uVar4 < 0x10)) {
    iVar1 = uVar4 * 0x128;
    (&fdb_list)[iVar1] = 1;
    snprintf(local_20,0xf,"idm%d",(uint)(byte)(&DAT_000135a9)[iVar1]);
    uVar3 = __dev_get_by_name(&init_net,local_20);
    (&DAT_000135bc)[uVar4 * 0x4a] = param_1;
    *(undefined4 *)(&DAT_000135b8 + iVar1) = uVar3;
    (&DAT_000135ac)[iVar1] = *(undefined1 *)(iVar2 + 0x22);
    create_idm_proc_file(&fdb_list + iVar1);
    idm_fdb_idm_isolate_handle();
    return &fdb_list + iVar1;
  }
  return (undefined1 *)0x0;
}

