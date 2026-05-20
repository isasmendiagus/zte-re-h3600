// module: mt7915.ko
// function: SetATESa @ 0x260f60
// size: 672 bytes
//

undefined4 SetATESa(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  byte *__s;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  char cVar7;
  undefined1 *__src;
  undefined4 uVar8;
  
  iVar1 = net_ad_wrap_service();
  iVar2 = net_ad_wrap_service(param_1);
  uVar8 = *(undefined4 *)((uint)*(byte *)(iVar2 + 0x4cc) * 0xd18 + iVar1 + 0x504);
  sVar3 = strlen(param_2);
  if (sVar3 != 0x11) {
    return 0;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar1 = net_ad_wrap_service(param_1);
    iVar2 = net_ad_wrap_service(param_1);
    if (*(char *)(param_1 + 0x286285) != '\0') {
      __src = (undefined1 *)((uint)*(byte *)(iVar2 + 0x4cc) * 0xd18 + iVar1 + 0x5f1);
      goto LAB_00260ff0;
    }
  }
  else if (*(char *)(param_1 + 0x286285) != '\0') {
    return 0;
  }
  iVar1 = net_ad_wrap_service(param_1);
  iVar2 = net_ad_wrap_service(param_1);
  __src = (undefined1 *)((uint)*(byte *)(iVar2 + 0x4cc) * 0xd18 + iVar1 + 0x591);
LAB_00260ff0:
  if ((__src != (undefined1 *)0x0) && (__s = (byte *)rstrtok(param_2,&_LC2), __s != (byte *)0x0)) {
    iVar1 = 0;
    do {
      iVar2 = iVar1 + 1;
      sVar3 = strlen((char *)__s);
      if (sVar3 != 2) {
        return 0;
      }
      if (((&_ctype)[*__s] & 0x44) == 0) {
        return 0;
      }
      if (((&_ctype)[__s[1]] & 0x44) == 0) {
        return 0;
      }
      AtoH(__s,__src + iVar1,1);
      __s = (byte *)rstrtok(0,&_LC2);
      iVar1 = iVar2;
    } while (__s != (byte *)0x0);
    if (iVar2 == 6) {
      cVar7 = *(char *)(param_1 + 0x286285);
      if (cVar7 == '\x01') {
        iVar1 = 1;
        do {
          iVar2 = net_ad_wrap_service(param_1);
          iVar4 = net_ad_wrap_service(param_1);
          iVar6 = iVar1 + 1;
          os_move_mem((void *)(iVar2 + (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar1 * 6 + 0x5f1),
                      __src,6);
          iVar1 = iVar6;
        } while (iVar6 != 0x10);
        cVar7 = *(char *)(param_1 + 0x286285);
      }
      if (cVar7 == '\0') {
        iVar1 = 1;
        do {
          iVar2 = net_ad_wrap_service(param_1);
          iVar4 = net_ad_wrap_service(param_1);
          iVar6 = iVar1 + 1;
          os_move_mem((void *)(iVar2 + (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar1 * 6 + 0x591),
                      __src,6);
          iVar1 = iVar6;
        } while (iVar6 != 0x10);
      }
      uVar5 = HcGetBandByWdev(uVar8);
      uVar8 = HcGetOmacIdx(param_1,uVar8);
      AsicDevInfoUpdate(param_1,uVar8,__src,uVar5,1,1);
      if (2 < DebugLevel) {
        printk("%s: (SA = %02x:%02x:%02x:%02x:%02x:%02x)\n","SetATESa",*__src,__src[1],__src[2],
               __src[3],__src[4],__src[5]);
        return 1;
      }
      return 1;
    }
  }
  return 0;
}

