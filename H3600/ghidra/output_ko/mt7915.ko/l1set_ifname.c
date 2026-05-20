// module: mt7915.ko
// function: l1set_ifname @ 0x14efcc
// size: 232 bytes
//

undefined4 l1set_ifname(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char *__s1;
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  
  __s1 = (char *)get_dev_name_prefix();
  pcVar1 = strchr(param_3,0x3b);
  if (pcVar1 != (char *)0x0) {
    if (2 < DebugLevel) {
      printk("DBDC format of ifname!\n");
    }
    *pcVar1 = '\0';
    pcVar2 = strchr(pcVar1 + 1,0x3b);
    if (pcVar2 != (char *)0x0) {
      *pcVar2 = '\0';
    }
    update_mtb_value(param_1,3,param_2,pcVar1 + 1);
  }
  iVar3 = strcmp(__s1,param_3);
  if (iVar3 == 0) {
    if (2 < DebugLevel) {
      printk("ifname remain %s\n",__s1);
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("ifname update from %s to %s\n",__s1,param_3);
    }
    strcpy(__s1,param_3);
  }
  return 0;
}

