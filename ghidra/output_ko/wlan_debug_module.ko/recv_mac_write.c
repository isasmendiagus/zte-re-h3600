// module: wlan_debug_module.ko
// function: recv_mac_write @ 0x110dc
// size: 292 bytes
//

uint recv_mac_write(int param_1,uint param_2,uint param_3)

{
  char *__s;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int local_30;
  int iStack_2c;
  undefined2 *puStack_28;
  int local_24;
  undefined4 local_1e;
  undefined2 local_1a;
  
  __s = (char *)__kmalloc(param_3 + 1,0x80d0);
  if (__s == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar4 = *(uint *)(((uint)&local_30 & 0xffffe000) + 8);
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
    if (iVar1 != 0) goto LAB_000111d4;
  }
  else if (param_3 != 0) {
    __memzero(__s,param_3,uVar3);
LAB_000111d4:
    kfree(__s);
    return 0xfffffff2;
  }
  __s[param_3] = '\0';
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  local_30 = (int)&local_1e + 2;
  iStack_2c = (int)&local_1e + 3;
  puStack_28 = &local_1a;
  local_24 = (int)&local_1a + 1;
  local_1e = 0;
  local_1a = 0;
  iVar1 = sscanf(__s,"%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",&local_1e,(int)&local_1e + 1);
  if (iVar1 == 6) {
    g_wlan_debug_recv_mac = local_1e;
    DAT_0001746c = local_1a;
  }
  else {
    printk("Invalid MAC Address [%s]\n",__s);
  }
  kfree(__s);
  return param_3;
}

