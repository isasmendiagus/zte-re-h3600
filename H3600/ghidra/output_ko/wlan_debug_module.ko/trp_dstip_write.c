// module: wlan_debug_module.ko
// function: trp_dstip_write @ 0x102cc
// size: 308 bytes
//

uint trp_dstip_write(int param_1,uint param_2,uint param_3)

{
  char *__s;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint local_28;
  int local_24;
  undefined4 local_1c;
  
  __s = (char *)__kmalloc(param_3 + 1,0x80d0);
  if (__s == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar4 = *(uint *)(((uint)&local_28 & 0xffffe000) + 8);
  uVar2 = param_2 + param_3;
  uVar3 = uVar2;
  if (!CARRY4(param_2,param_3)) {
    uVar3 = uVar2 - (uVar4 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar2 <= uVar4) {
    uVar4 = 0;
  }
  if (uVar4 == 0) {
    iVar1 = __copy_from_user(__s,param_2,param_3);
    if (iVar1 != 0) goto LAB_000103e8;
  }
  else if (param_3 != 0) {
    __memzero(__s,param_3,uVar3);
LAB_000103e8:
    kfree(__s);
    return 0xfffffff2;
  }
  __s[param_3] = '\0';
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  local_28 = (int)&local_1c + 2;
  local_24 = (int)&local_1c + 3;
  local_1c = 0;
  iVar1 = sscanf(__s,"%hhu.%hhu.%hhu.%hhu",&local_1c,(int)&local_1c + 1);
  if (iVar1 == 4) {
    local_28 = local_1c >> 0x18;
    g_wlan_debug_trp_dstip =
         (local_1c >> 8 & 0xff) * 0x10000 + local_1c * 0x1000000 + (local_1c >> 0x10 & 0xff) * 0x100
         + local_28;
    printk("set dstip = [%u.%u.%u.%u]\n");
  }
  else {
    printk("Invalid IP Address [%s]\n",__s);
  }
  kfree(__s);
  return param_3;
}

