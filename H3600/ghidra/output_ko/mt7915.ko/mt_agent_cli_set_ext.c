// module: mt7915.ko
// function: mt_agent_cli_set_ext @ 0x24fbb0
// size: 124 bytes
//

bool mt_agent_cli_set_ext(char *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  char *__s2;
  int iVar2;
  
  __s2 = s_ATECTRLBANDIDX_005e1030;
  if (s_ATECTRLBANDIDX_005e1030[0] == '\0') {
    return true;
  }
  iVar2 = 0;
  do {
    while (iVar1 = strcmp(param_1,__s2), iVar1 == 0) {
      iVar2 = (**(code **)(__s2 + 100))(*(undefined4 *)(param_2 + 4),param_3);
      __s2 = __s2 + 0x68;
      if (*__s2 == '\0') goto LAB_0024fc18;
    }
    __s2 = __s2 + 0x68;
  } while (*__s2 != '\0');
LAB_0024fc18:
  return iVar2 == 0;
}

