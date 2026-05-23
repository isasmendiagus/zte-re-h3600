// module: idmfdb.ko
// function: create_idm_proc_file @ 0x11dbc
// size: 228 bytes
//

undefined4 create_idm_proc_file(int param_1)

{
  int iVar1;
  char *__src;
  char local_20 [16];
  
  __src = *(char **)(param_1 + 0x14);
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
  if ((__src == (char *)0x0) || (*__src == '\0')) {
    snprintf(local_20,0xf,"idm%d_ssid%d",(uint)*(byte *)(param_1 + 1),(uint)*(byte *)(param_1 + 3));
  }
  else {
    strncpy(local_20,__src,0xf);
  }
  remove_proc_subtree(local_20,proc_parent);
  iVar1 = proc_mkdir(local_20,proc_parent);
  *(int *)(param_1 + 0x120) = iVar1;
  if (iVar1 != 0) {
    proc_create_data(&_LC3,0x1b6,iVar1,&idm_proc_stat_file_ops,param_1);
    proc_create_data("forbidIdm",0x1b6,*(undefined4 *)(param_1 + 0x120),idm_proc_forbidIdm_file_ops,
                     param_1);
  }
  return 0;
}

