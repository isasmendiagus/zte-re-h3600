// module: mt7915.ko
// function: mt_agent_set_txbf_sa @ 0x24d290
// size: 292 bytes
//

undefined4 mt_agent_set_txbf_sa(int param_1,undefined4 param_2,char *param_3)

{
  byte bVar1;
  size_t sVar2;
  byte *__s;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined1 *puVar7;
  int iVar8;
  undefined4 local_38 [6];
  
  bVar1 = *(byte *)(param_1 + 0x4cc);
  printk("%s: Sa = %s\n","mt_agent_set_txbf_sa");
  sVar2 = strlen(param_3);
  if (sVar2 == 0x11) {
    __s = (byte *)agent_trtok(param_3,&_LC90);
    iVar6 = (uint)bVar1 * 0xd18 + param_1;
    puVar7 = (undefined1 *)(iVar6 + 0x5f0);
    if (__s != (byte *)0x0) {
      iVar8 = 0;
      puVar5 = local_38;
      do {
        sVar2 = strlen((char *)__s);
        iVar8 = iVar8 + 1;
        if ((((sVar2 != 2) || ((9 < *__s - 0x30 && (5 < (*__s & 0xffffffdf) - 0x41)))) ||
            ((9 < __s[1] - 0x30 && (5 < (__s[1] & 0xffffffdf) - 0x41)))) ||
           (iVar3 = _kstrtol(__s,0x10,puVar5), iVar3 != 0)) {
          return 0x104;
        }
        puVar7 = puVar7 + 1;
        *puVar7 = (char)*puVar5;
        __s = (byte *)agent_trtok(0,&_LC90);
        puVar5 = puVar5 + 1;
      } while (__s != (byte *)0x0);
      if (iVar8 == 6) {
        uVar4 = mt_serv_set_txbf_sa(param_1,iVar6 + 0x5f1);
        return uVar4;
      }
    }
  }
  return 0x103;
}

