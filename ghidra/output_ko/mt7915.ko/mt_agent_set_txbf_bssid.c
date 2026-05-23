// module: mt7915.ko
// function: mt_agent_set_txbf_bssid @ 0x24d3b8
// size: 284 bytes
//

undefined4 mt_agent_set_txbf_bssid(int param_1,char *param_2)

{
  byte bVar1;
  size_t sVar2;
  byte *__s;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined4 local_30 [6];
  
  bVar1 = *(byte *)(param_1 + 0x4cc);
  printk("%s: BSSID = %s\n","mt_agent_set_txbf_bssid",param_2);
  sVar2 = strlen(param_2);
  if (sVar2 == 0x11) {
    __s = (byte *)agent_trtok(param_2,&_LC90);
    puVar5 = (undefined1 *)((uint)bVar1 * 0xd18 + param_1 + 0x590);
    if (__s != (byte *)0x0) {
      iVar6 = 0;
      puVar4 = local_30;
      while( true ) {
        sVar2 = strlen((char *)__s);
        iVar6 = iVar6 + 1;
        if (((sVar2 != 2) || ((9 < *__s - 0x30 && (5 < (*__s & 0xffffffdf) - 0x41)))) ||
           ((9 < __s[1] - 0x30 && (5 < (__s[1] & 0xffffffdf) - 0x41)))) break;
        iVar3 = _kstrtol(__s,0x10,puVar4);
        if (iVar3 != 0) {
          return 0x104;
        }
        puVar5 = puVar5 + 1;
        *puVar5 = (char)*puVar4;
        __s = (byte *)agent_trtok(0,&_LC90);
        puVar4 = puVar4 + 1;
        if (__s == (byte *)0x0) {
          if (iVar6 != 6) {
            return 0x103;
          }
          return 0;
        }
      }
    }
  }
  return 0x103;
}

