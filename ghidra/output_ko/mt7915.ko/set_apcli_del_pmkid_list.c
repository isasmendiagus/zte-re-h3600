// module: mt7915.ko
// function: set_apcli_del_pmkid_list @ 0x6c104
// size: 148 bytes
//

undefined4 set_apcli_del_pmkid_list(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  if (*param_2 == '\0') {
    return 0;
  }
  iVar2 = *param_1;
  if (*(int *)(iVar2 + 0x38) != 0x400) {
    return 0;
  }
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\x01') {
    sta_delete_pmkid_cache_all(param_1,*(undefined1 *)(iVar2 + 0x3c));
    if (-1 < DebugLevel) {
      printk("%s:: Delete PMKID list (%d)  \n","set_apcli_del_pmkid_list",1);
      return 1;
    }
  }
  return 1;
}

