// module: mt7915.ko
// function: mt_agent_set_ibf_phase_comp @ 0x24d6d4
// size: 296 bytes
//

undefined4 mt_agent_set_ibf_phase_comp(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  byte *__s;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint local_28 [6];
  
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  local_28[4] = 0;
  local_28[5] = 0;
  if ((param_2 != (char *)0x0) && (sVar1 = strlen(param_2), sVar1 == 0xe || sVar1 == 0x11)) {
    uVar5 = 0;
    do {
      __s = (byte *)agent_trtok(param_2,&_LC90);
      if (__s == (byte *)0x0) {
        uVar3 = mt_serv_set_ibf_phase_comp
                          (param_1,local_28[0] & 0xff,(local_28[2] & 0xff) == 1,local_28[1] & 0xff,
                           local_28[2] & 0xff,local_28[3] & 0xff,local_28[4] & 0xff);
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
      iVar2 = _kstrtol(__s,0x10,local_28 + uVar4);
      param_2 = (char *)0x0;
    } while (iVar2 == 0);
  }
  return 0x104;
}

