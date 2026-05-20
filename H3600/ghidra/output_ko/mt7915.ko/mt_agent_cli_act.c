// module: mt7915.ko
// function: mt_agent_cli_act @ 0x24f970
// size: 120 bytes
//

bool mt_agent_cli_act(char *param_1,int param_2)

{
  int iVar1;
  char *__s2;
  int iVar2;
  undefined4 uVar3;
  
  __s2 = _LANCHOR2;
  uVar3 = *(undefined4 *)(param_2 + 4);
  if (_LANCHOR2[0] == '\0') {
    return true;
  }
  iVar2 = 0;
  do {
    while (iVar1 = strcmp(param_1,__s2), iVar1 == 0) {
      iVar2 = (**(code **)(__s2 + 100))(uVar3);
      __s2 = __s2 + 0x68;
      if (*__s2 == '\0') goto LAB_0024f9d4;
    }
    __s2 = __s2 + 0x68;
  } while (*__s2 != '\0');
LAB_0024f9d4:
  return iVar2 == 0;
}

