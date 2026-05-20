// module: mt7915.ko
// function: set_sta_rfeatures @ 0xcfad4
// size: 240 bytes
//

undefined4 set_sta_rfeatures(undefined4 param_1,char *param_2)

{
  char *__s2;
  int iVar1;
  undefined1 *puVar2;
  char *local_24 [2];
  byte local_19;
  
  local_24[0] = param_2;
  __s2 = strsep(local_24,"-");
  if (0 < DebugLevel) {
    printk("func:%s, capi: %s, arg: %s \n","set_sta_rfeatures",__s2,local_24[0]);
  }
  if ((__s2 != (char *)0x0) && (*__s2 != '\0')) {
    puVar2 = sta_set_rfeature_capi;
    do {
      iVar1 = strcmp(*(char **)puVar2,__s2);
      if (iVar1 == 0) {
        local_19 = os_str_tol(local_24[0],0,10);
        if (0 < DebugLevel) {
          printk("func:%s, [capi match], arg: %d\n","set_sta_rfeatures",local_19);
        }
        (**(code **)((int)puVar2 + 4))(param_1,&local_19);
        return 0;
      }
      puVar2 = (undefined1 *)((int)puVar2 + 8);
    } while ((undefined4 *)puVar2 != (undefined4 *)0x32f598);
  }
  return 0;
}

