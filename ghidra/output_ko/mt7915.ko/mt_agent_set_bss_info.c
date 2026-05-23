// module: mt7915.ko
// function: mt_agent_set_bss_info @ 0x24d4d8
// size: 248 bytes
//

undefined4 mt_agent_set_bss_info(undefined4 param_1,undefined4 param_2)

{
  byte *__s;
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined4 local_30 [6];
  
  uVar5 = 0;
  local_36 = 0;
  local_34 = 0;
  local_32 = 0;
  __s = (byte *)agent_trtok(param_2,&_LC90);
  while( true ) {
    if (__s == (byte *)0x0) {
      uVar3 = mt_serv_set_bss_info(param_1,&local_36);
      return uVar3;
    }
    uVar4 = uVar5 & 0xff;
    sVar2 = strlen((char *)__s);
    uVar5 = uVar5 + 1;
    if ((((sVar2 != 2) || ((9 < *__s - 0x30 && (5 < (*__s & 0xffffffdf) - 0x41)))) ||
        ((9 < __s[1] - 0x30 && (5 < (__s[1] & 0xffffffdf) - 0x41)))) ||
       (iVar1 = _kstrtol(__s,0x10,local_30 + uVar4), iVar1 != 0)) break;
    *(char *)((int)&local_36 + uVar4) = (char)local_30[uVar4];
    __s = (byte *)agent_trtok(0,&_LC90);
  }
  return 0x104;
}

