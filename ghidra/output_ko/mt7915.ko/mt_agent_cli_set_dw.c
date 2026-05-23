// module: mt7915.ko
// function: mt_agent_cli_set_dw @ 0x24fac8
// size: 224 bytes
//

bool mt_agent_cli_set_dw(char *param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  char *__s2;
  uint local_20;
  uint local_1c [2];
  
  local_20 = 0;
  local_1c[0] = 0;
  sys_ad_zero_mem(&_LANCHOR1,0x80c);
  iVar2 = _kstrtol(param_3,10,&local_20);
  if (iVar2 == 0) {
    local_1c[0] = local_20 << 0x18 | (local_20 >> 8 & 0xff) << 0x10 | (local_20 >> 0x10 & 0xff) << 8
                  | local_20 >> 0x18;
    sys_ad_move_mem(&DAT_005f5b58,local_1c,4);
    if (s_ATETXMCS_005e0d58[0] == '\0') {
      bVar1 = true;
    }
    else {
      __s2 = s_ATETXMCS_005e0d58;
      iVar2 = 0;
      do {
        while (iVar3 = strcmp(param_1,__s2), iVar3 != 0) {
          __s2 = __s2 + 0x68;
          if (*__s2 == '\0') goto LAB_0024fb90;
        }
        iVar2 = (**(code **)(__s2 + 100))(*(undefined4 *)(param_2 + 4),&_LANCHOR1);
        __s2 = __s2 + 0x68;
      } while (*__s2 != '\0');
LAB_0024fb90:
      bVar1 = iVar2 == 0;
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

