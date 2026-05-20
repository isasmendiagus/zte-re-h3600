// module: mt7915.ko
// function: SetATEDaByWtblTlv @ 0x260664
// size: 620 bytes
//

undefined4 SetATEDaByWtblTlv(int param_1,char *param_2)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  byte *__s;
  undefined1 *puVar5;
  undefined1 *__src;
  uint uVar6;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (2 < DebugLevel) {
    printk("%s: Da = %s\n","SetATEDaByWtblTlv",param_2);
  }
  pcVar1 = strchr(param_2,0x2d);
  if (pcVar1 == (char *)0x0) {
    uVar6 = 1;
    pcVar1 = param_2;
  }
  else {
    *pcVar1 = '\0';
    pcVar1 = pcVar1 + 1;
    sscanf(param_2,"%d",&local_38);
    uVar6 = local_38 & 0xffff;
  }
  sVar2 = strlen(pcVar1);
  if (sVar2 != 0x11) {
    return 0;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar3 = net_ad_wrap_service(param_1);
    iVar4 = net_ad_wrap_service(param_1);
    if (*(char *)(param_1 + 0x286285) != '\0') {
      __src = (undefined1 *)
              (iVar3 + (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + (uVar6 - 1) * 6 + 0x531);
      goto LAB_0026074c;
    }
  }
  else if (*(char *)(param_1 + 0x286285) != '\0') {
    return 0;
  }
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  __src = (undefined1 *)(iVar3 + (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + (uVar6 - 1) * 6 + 0x5f1);
LAB_0026074c:
  if (__src != (undefined1 *)0x0) {
    local_38 = 0;
    __s = (byte *)rstrtok(pcVar1,&_LC2);
    while (__s != (byte *)0x0) {
      sVar2 = strlen((char *)__s);
      if (sVar2 != 2) {
        return 0;
      }
      if (((&_ctype)[*__s] & 0x44) == 0) {
        return 0;
      }
      if (((&_ctype)[__s[1]] & 0x44) == 0) {
        return 0;
      }
      puVar5 = __src + local_38;
      local_38 = local_38 + 1;
      AtoH(__s,puVar5);
      __s = (byte *)rstrtok(0,&_LC2);
    }
    if (local_38 == 6) {
      local_34 = 0x140000;
      memmove(&local_30,__src,6);
      CmdExtWtblUpdate(param_1,uVar6,2,&local_34,0x14);
      if (DebugLevel < 3) {
        return 1;
      }
      printk("%s: (DA = %02x:%02x:%02x:%02x:%02x:%02x)\n","SetATEDaByWtblTlv",*__src,__src[1],
             __src[2],__src[3],__src[4],__src[5]);
      return 1;
    }
  }
  return 0;
}

