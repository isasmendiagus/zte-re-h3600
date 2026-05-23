// module: mt7915.ko
// function: SetATEBssid @ 0x261204
// size: 588 bytes
//

undefined4 SetATEBssid(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  byte *__s;
  int iVar4;
  char cVar5;
  int iVar6;
  undefined1 *__src;
  
  sVar1 = strlen(param_2);
  if (sVar1 != 0x11) {
    return 0;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar2 = net_ad_wrap_service(param_1);
    iVar3 = net_ad_wrap_service(param_1);
    if (*(char *)(param_1 + 0x286285) != '\0') {
      __src = (undefined1 *)((uint)*(byte *)(iVar3 + 0x4cc) * 0xd18 + iVar2 + 0x591);
      goto LAB_00261274;
    }
  }
  else if (*(char *)(param_1 + 0x286285) != '\0') {
    return 0;
  }
  iVar2 = net_ad_wrap_service(param_1);
  iVar3 = net_ad_wrap_service(param_1);
  __src = (undefined1 *)((uint)*(byte *)(iVar3 + 0x4cc) * 0xd18 + iVar2 + 0x531);
LAB_00261274:
  if ((__src != (undefined1 *)0x0) && (__s = (byte *)rstrtok(param_2,&_LC2), __s != (byte *)0x0)) {
    iVar2 = 0;
    do {
      iVar3 = iVar2 + 1;
      sVar1 = strlen((char *)__s);
      if (sVar1 != 2) {
        return 0;
      }
      if (((&_ctype)[*__s] & 0x44) == 0) {
        return 0;
      }
      if (((&_ctype)[__s[1]] & 0x44) == 0) {
        return 0;
      }
      AtoH(__s,__src + iVar2,1);
      __s = (byte *)rstrtok(0,&_LC2);
      iVar2 = iVar3;
    } while (__s != (byte *)0x0);
    if (iVar3 == 6) {
      cVar5 = *(char *)(param_1 + 0x286285);
      if (cVar5 == '\x01') {
        iVar2 = 1;
        do {
          iVar3 = net_ad_wrap_service(param_1);
          iVar4 = net_ad_wrap_service(param_1);
          iVar6 = iVar2 + 1;
          os_move_mem((void *)(iVar3 + (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar2 * 6 + 0x591),
                      __src,6);
          iVar2 = iVar6;
        } while (iVar6 != 0x10);
        cVar5 = *(char *)(param_1 + 0x286285);
      }
      if (cVar5 == '\0') {
        iVar2 = 1;
        do {
          iVar3 = net_ad_wrap_service(param_1);
          iVar4 = net_ad_wrap_service(param_1);
          iVar6 = iVar2 + 1;
          os_move_mem((void *)(iVar3 + (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar2 * 6 + 0x531),
                      __src,6);
          iVar2 = iVar6;
        } while (iVar6 != 0x10);
      }
      if (2 < DebugLevel) {
        printk("%s: (BSSID = %02x:%02x:%02x:%02x:%02x:%02x)\n","SetATEBssid",*__src,__src[1],
               __src[2],__src[3],__src[4],__src[5]);
      }
      return 1;
    }
  }
  return 0;
}

