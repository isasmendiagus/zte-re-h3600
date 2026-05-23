// module: mt7915.ko
// function: mt_agent_set_txbf_tx_apply @ 0x24d5d0
// size: 260 bytes
//

undefined4 mt_agent_set_txbf_tx_apply(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  byte *__s;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined1 local_39 [5];
  undefined4 local_34 [6];
  
  local_39[0] = 0;
  local_39[1] = 0;
  local_39[2] = 0;
  local_39[3] = 0;
  local_39[4] = 0;
  sVar1 = strlen(param_2);
  if (sVar1 == 0xe) {
    __s = (byte *)agent_trtok(param_2,&_LC90);
    if (__s != (byte *)0x0) {
      puVar4 = local_34;
      puVar5 = local_39;
      do {
        sVar1 = strlen((char *)__s);
        if ((((sVar1 != 2) || ((9 < *__s - 0x30 && (5 < (*__s & 0xffffffdf) - 0x41)))) ||
            ((9 < __s[1] - 0x30 && (5 < (__s[1] & 0xffffffdf) - 0x41)))) ||
           (iVar3 = _kstrtol(__s,0x10,puVar4), iVar3 != 0)) goto LAB_0024d608;
        *puVar5 = (char)*puVar4;
        __s = (byte *)agent_trtok(0,&_LC90);
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      } while (__s != (byte *)0x0);
    }
    uVar2 = mt_serv_set_txbf_tx_apply(param_1,local_39);
  }
  else {
LAB_0024d608:
    uVar2 = 0x104;
  }
  return uVar2;
}

