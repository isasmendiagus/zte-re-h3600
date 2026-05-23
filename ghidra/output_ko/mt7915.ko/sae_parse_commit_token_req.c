// module: mt7915.ko
// function: sae_parse_commit_token_req @ 0x209778
// size: 204 bytes
//

void sae_parse_commit_token_req
               (undefined4 param_1,int *param_2,int param_3,int *param_4,int *param_5)

{
  int iVar1;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_commit_token_req");
  }
  if (param_3 - *param_2 < 1) {
    if (param_4 != (int *)0x0) {
      *param_4 = 0;
    }
    if (param_5 != (int *)0x0) {
      *param_5 = 0;
    }
    return;
  }
  if (2 < DebugLevel) {
    printk("%s:add anti clogging token\n","sae_parse_commit_token_req");
  }
  if (param_4 != (int *)0x0) {
    *param_4 = *param_2;
  }
  if (param_5 != (int *)0x0) {
    iVar1 = *param_2;
    *param_5 = param_3 - iVar1;
    *param_2 = *param_2 + (param_3 - iVar1);
  }
  return;
}

