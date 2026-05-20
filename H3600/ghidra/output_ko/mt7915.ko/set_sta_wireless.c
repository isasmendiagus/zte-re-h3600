// module: mt7915.ko
// function: set_sta_wireless @ 0xcf9d4
// size: 248 bytes
//

undefined4 set_sta_wireless(undefined4 param_1,char *param_2)

{
  char *__s2;
  int iVar1;
  undefined1 *puVar2;
  char *local_24 [2];
  ushort local_1a;
  
  local_24[0] = param_2;
  __s2 = strsep(local_24,"-");
  if (0 < DebugLevel) {
    printk("func:%s, capi: %s, arg: %s \n","set_sta_wireless",__s2,local_24[0]);
  }
  if ((__s2 != (char *)0x0) && (*__s2 != '\0')) {
    puVar2 = sta_set_wireless_capi;
    do {
      iVar1 = strcmp(*(char **)puVar2,__s2);
      if (iVar1 == 0) {
        local_1a = os_str_tol(local_24[0],0,10);
        if (0 < DebugLevel) {
          printk("func:%s, [capi match], arg: %d\n","set_sta_wireless",local_1a);
        }
        (**(code **)((int)puVar2 + 4))(param_1,&local_1a);
        return 0;
      }
      puVar2 = (undefined1 *)((int)puVar2 + 8);
    } while (puVar2 != sta_set_rfeature_capi);
  }
  return 0;
}

