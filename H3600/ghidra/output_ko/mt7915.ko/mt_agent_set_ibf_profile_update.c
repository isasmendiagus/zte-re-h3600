// module: mt7915.ko
// function: mt_agent_set_ibf_profile_update @ 0x24e274
// size: 240 bytes
//

undefined4 mt_agent_set_ibf_profile_update(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  byte *__s;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint local_1c [3];
  
  uVar5 = 0;
  local_1c[0] = 0;
  local_1c[1] = 0;
  local_1c[2] = 0;
  if ((param_2 != (char *)0x0) && (sVar1 = strlen(param_2), sVar1 == 8)) {
    do {
      __s = (byte *)agent_trtok(param_2,&_LC90);
      if (__s == (byte *)0x0) {
        uVar3 = mt_serv_set_ibf_profile_update(param_1,local_1c[0] & 0xff,local_1c[2] & 0xff);
        return uVar3;
      }
      sVar1 = strlen((char *)__s);
      uVar4 = uVar5 & 0xff;
      uVar5 = uVar5 + 1;
      if (sVar1 != 2) {
        return 0x104;
      }
      if ((9 < *__s - 0x30) && (5 < (*__s & 0xffffffdf) - 0x41)) {
        return 0x104;
      }
      if ((9 < __s[1] - 0x30) && (5 < (__s[1] & 0xffffffdf) - 0x41)) {
        return 0x104;
      }
      iVar2 = _kstrtol(__s,0x10,local_1c + uVar4);
      param_2 = (char *)0x0;
    } while (iVar2 == 0);
  }
  return 0x104;
}

