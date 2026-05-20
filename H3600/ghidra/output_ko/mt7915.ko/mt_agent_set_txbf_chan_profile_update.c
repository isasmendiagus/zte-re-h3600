// module: mt7915.ko
// function: mt_agent_set_txbf_chan_profile_update @ 0x24e560
// size: 344 bytes
//

undefined4 mt_agent_set_txbf_chan_profile_update(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  byte *__s;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined2 local_5a [11];
  undefined4 local_44 [11];
  
  uVar4 = 0;
  local_44[0] = 0;
  local_44[1] = 0;
  local_44[2] = 0;
  local_44[3] = 0;
  local_44[4] = 0;
  local_44[5] = 0;
  local_44[6] = 0;
  local_44[7] = 0;
  local_44[8] = 0;
  local_44[9] = 0;
  local_44[10] = 0;
  local_5a[0] = 0;
  local_5a[1] = 0;
  local_5a[2] = 0;
  local_5a[3] = 0;
  local_5a[4] = 0;
  local_5a[5] = 0;
  local_5a[6] = 0;
  local_5a[7] = 0;
  local_5a[8] = 0;
  local_5a[9] = 0;
  local_5a[10] = 0;
  if ((param_2 == (char *)0x0) || (sVar1 = strlen(param_2), sVar1 != 0x2b)) {
LAB_0024e5e4:
    uVar2 = 0x104;
  }
  else {
    __s = (byte *)agent_trtok(param_2,&_LC90);
    while (__s != (byte *)0x0) {
      uVar5 = uVar4 & 0xff;
      sVar1 = strlen((char *)__s);
      uVar4 = uVar4 + 1;
      if (((3 < sVar1) || ((9 < *__s - 0x30 && (5 < (*__s & 0xffffffdf) - 0x41)))) ||
         ((9 < __s[1] - 0x30 && (5 < (__s[1] & 0xffffffdf) - 0x41)))) goto LAB_0024e5e4;
      iVar3 = _kstrtol(__s,0x10,local_44 + uVar5);
      if (iVar3 != 0) goto LAB_0024e5e4;
      local_5a[uVar5] = (short)local_44[uVar5];
      __s = (byte *)agent_trtok(0,&_LC90);
    }
    uVar2 = mt_serv_set_txbf_chan_profile_update(param_1,local_5a);
  }
  return uVar2;
}

