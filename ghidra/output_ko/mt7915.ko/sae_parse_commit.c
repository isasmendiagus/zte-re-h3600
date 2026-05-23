// module: mt7915.ko
// function: sae_parse_commit @ 0x20b2b8
// size: 400 bytes
//

int sae_parse_commit(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                    undefined4 param_6,char param_7)

{
  int iVar1;
  undefined2 *local_24 [2];
  
  local_24[0] = (undefined2 *)(param_3 + 0x1e);
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_commit");
  }
  iVar1 = sae_group_allowed(param_2,param_1 + 0x1b900,*local_24[0]);
  if (iVar1 == 0) {
    param_3 = param_3 + param_4;
    local_24[0] = local_24[0] + 1;
    if (param_7 == '\x01') {
      if (-1 < DebugLevel) {
        printk("%s:Parsing AntiClogging Request token\n","sae_parse_commit");
      }
      sae_parse_commit_token_req(param_2,local_24,param_3,param_5,param_6);
      return 0;
    }
    sae_parse_commit_token(param_2,local_24,param_3,param_5,param_6);
    log_time_begin(0,param_2 + 0xb0);
    iVar1 = sae_parse_commit_scalar(param_2,local_24,param_3);
    if (iVar1 == 0) {
      log_time_end(1,"parse_commit_scalar_time",3,param_2 + 0xb0);
      iVar1 = sae_parse_commit_element(param_2,local_24,param_3);
      if (iVar1 == 0) {
        if (*(int *)(param_2 + 0x98) == 0) {
          iVar1 = 1;
        }
        else {
          iVar1 = (**(code **)(*(int *)(param_2 + 0x98) + 0x1c))(param_2);
          if (iVar1 == 0) {
            iVar1 = sae_parse_password_identifier
                              (param_2,local_24[0],param_3,*(undefined1 *)(param_2 + 0x8c));
          }
        }
      }
    }
  }
  return iVar1;
}

