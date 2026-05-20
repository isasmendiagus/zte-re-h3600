// module: mt7915.ko
// function: mt_agent_set_ibf_phase_cal_e2p_update @ 0x24cfcc
// size: 248 bytes
//

undefined4 mt_agent_set_ibf_phase_cal_e2p_update(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  byte *__s;
  int iVar3;
  uint *puVar4;
  uint local_1c;
  uint local_18;
  uint local_14;
  
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if ((param_2 == (char *)0x0) || (sVar1 = strlen(param_2), sVar1 != 8)) {
LAB_0024d004:
    uVar2 = 0x104;
  }
  else {
    __s = (byte *)agent_trtok(param_2,&_LC90);
    if (__s != (byte *)0x0) {
      puVar4 = &local_1c;
      do {
        sVar1 = strlen((char *)__s);
        if ((((sVar1 != 2) || ((9 < *__s - 0x30 && (5 < (*__s & 0xffffffdf) - 0x41)))) ||
            ((9 < __s[1] - 0x30 && (5 < (__s[1] & 0xffffffdf) - 0x41)))) ||
           (iVar3 = _kstrtol(__s,0x10,puVar4), iVar3 != 0)) goto LAB_0024d004;
        __s = (byte *)agent_trtok(0,&_LC90);
        puVar4 = puVar4 + 1;
      } while (__s != (byte *)0x0);
    }
    uVar2 = mt_serv_set_ibf_phase_cal_e2p_update
                      (param_1,local_1c & 0xff,local_18 & 0xff,local_14 & 0xff);
  }
  return uVar2;
}

