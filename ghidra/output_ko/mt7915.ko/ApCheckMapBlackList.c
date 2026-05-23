// module: mt7915.ko
// function: ApCheckMapBlackList @ 0x1612f0
// size: 204 bytes
//

undefined4 ApCheckMapBlackList(int param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  char *__s2;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" +
                  param_1 + param_3 * 0x5834 + 0x2a);
  if (iVar3 != 0) {
    iVar2 = 0;
    __s2 = "Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1 + param_3 * 0x5834 + 0x2e;
    do {
      iVar2 = iVar2 + 1;
      iVar1 = memcmp(param_2,__s2,6);
      __s2 = __s2 + 8;
      if (iVar1 == 0) {
        if (2 < DebugLevel) {
          printk("%02x:%02x:%02x:%02x:%02x:%02x failed in Map Blacklist checking\n",*param_2,
                 param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
          return 0;
        }
        return 0;
      }
    } while (iVar2 != iVar3);
  }
  return 1;
}

