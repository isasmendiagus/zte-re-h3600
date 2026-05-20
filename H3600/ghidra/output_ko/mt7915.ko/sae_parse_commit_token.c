// module: mt7915.ko
// function: sae_parse_commit_token @ 0x209b18
// size: 224 bytes
//

void sae_parse_commit_token(int param_1,int *param_2,uint param_3,int *param_4,int *param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 == 0) {
    return;
  }
  switch(*(undefined2 *)(param_1 + 0x2c)) {
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
    iVar3 = 3;
    break;
  default:
    iVar3 = 2;
  }
  iVar3 = *(int *)(param_1 + 100) * iVar3;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_commit_token");
  }
  uVar1 = *param_2 + iVar3;
  if ((uVar1 < param_3) && (iVar2 = is_sae_pwd_id_element(uVar1,param_3,0), iVar2 == 0)) {
    if (param_4 != (int *)0x0) {
      *param_4 = *param_2;
    }
    if (param_5 != (int *)0x0) {
      iVar3 = (param_3 - *param_2) - iVar3;
      *param_5 = iVar3;
      *param_2 = *param_2 + iVar3;
      return;
    }
    return;
  }
  if (param_4 != (int *)0x0) {
    *param_4 = 0;
  }
  if (param_5 != (int *)0x0) {
    *param_5 = 0;
  }
  return;
}

