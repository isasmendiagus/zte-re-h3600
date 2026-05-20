// module: mt7915.ko
// function: mt_agent_set_txbf_da @ 0x24d108
// size: 388 bytes
//

undefined4 mt_agent_set_txbf_da(int param_1,char *param_2)

{
  byte bVar1;
  char *pcVar2;
  size_t sVar3;
  undefined4 uVar4;
  byte *__s;
  int iVar5;
  uint uVar6;
  uint local_34;
  undefined4 auStack_30 [6];
  
  bVar1 = *(byte *)(param_1 + 0x4cc);
  printk("%s: Da = %s\n","mt_agent_set_txbf_da",param_2);
  pcVar2 = strchr(param_2,0x2d);
  if (pcVar2 == (char *)0x0) {
    uVar6 = 1;
    pcVar2 = param_2;
  }
  else {
    *pcVar2 = '\0';
    kstrtouint(param_2,10,&local_34);
    uVar6 = local_34 & 0xffff;
    pcVar2 = pcVar2 + 1;
  }
  sVar3 = strlen(pcVar2);
  if (sVar3 == 0x11) {
    local_34 = 0;
    __s = (byte *)agent_trtok(param_2,&_LC90);
    while (__s != (byte *)0x0) {
      sVar3 = strlen((char *)__s);
      if (((sVar3 != 2) || ((9 < *__s - 0x30 && (5 < (*__s & 0xffffffdf) - 0x41)))) ||
         ((9 < __s[1] - 0x30 && (5 < (__s[1] & 0xffffffdf) - 0x41)))) goto LAB_0024d174;
      iVar5 = _kstrtol(__s,0x10,auStack_30 + local_34);
      if (iVar5 != 0) {
        return 0x104;
      }
      *(char *)(param_1 + (uint)bVar1 * 0xd18 + (uVar6 - 1) * 6 + 0x531 + local_34) =
           (char)auStack_30[local_34];
      local_34 = local_34 + 1;
      __s = (byte *)agent_trtok(0,&_LC90);
    }
    uVar4 = 0x103;
    if (local_34 == 6) {
      uVar4 = 0;
    }
  }
  else {
LAB_0024d174:
    uVar4 = 0x103;
  }
  return uVar4;
}

