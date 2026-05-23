// module: mt7915.ko
// function: mt_agent_cli_set_w @ 0x24f9e8
// size: 216 bytes
//

bool mt_agent_cli_set_w(char *param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  char *__s2;
  ushort local_1e;
  uint local_1c [2];
  
  local_1c[0] = 0;
  local_1e = 0;
  sys_ad_zero_mem(&_LANCHOR1,0x80c);
  iVar2 = _kstrtol(param_3,10,local_1c);
  if (iVar2 == 0) {
    __s2 = &DAT_005f635c;
    local_1e = (ushort)((local_1c[0] & 0xff) << 8) | (ushort)(local_1c[0] >> 8) & 0xff;
    sys_ad_move_mem(&DAT_005f5b58,&local_1e,2);
    iVar2 = 0;
    if (DAT_005f635c != '\0') {
      do {
        while (iVar3 = strcmp(param_1,__s2), iVar3 == 0) {
          iVar2 = (**(code **)(__s2 + 100))(*(undefined4 *)(param_2 + 4),&_LANCHOR1);
          __s2 = __s2 + 0x68;
          if (*__s2 == '\0') goto LAB_0024fab0;
        }
        __s2 = __s2 + 0x68;
      } while (*__s2 != '\0');
LAB_0024fab0:
      return iVar2 == 0;
    }
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

