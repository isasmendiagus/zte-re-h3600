// module: tm.ko
// function: sdet_info_show @ 0x6ec1c
// size: 188 bytes
//

undefined4 sdet_info_show(undefined4 param_1,undefined4 *param_2,char *param_3)

{
  int iVar1;
  char *__s1;
  undefined4 uVar2;
  undefined4 local_14;
  
  uVar2 = 0;
  local_14 = 0;
  __s1 = (char *)*param_2;
  sscanf(param_3,"%d",&local_14);
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = strcmp(__s1,"helpSdet");
    if (iVar1 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands[HEX]\n");
      printk("============================================================================\n");
      printk(" echo [port][mtu]        > sonumtu        - set onu mtu\n");
      uVar2 = 0;
    }
    else {
      printk("%s: illegal operation <%s>\n","sdet_info_show",*param_2);
    }
  }
  return uVar2;
}

