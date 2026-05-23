// module: plat-zxylzb_9128S.ko
// function: VlanWriteProc @ 0x17218
// size: 556 bytes
//

uint VlanWriteProc(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *__s1;
  undefined4 uStack_28;
  
  uVar6 = param_3;
  if (0x7e < param_3) {
    uVar6 = 0x7f;
  }
  uVar5 = *(uint *)(((uint)&uStack_28 & 0xffffe000) + 8);
  uVar3 = param_2 + uVar6;
  uVar4 = uVar3;
  if (!CARRY4(param_2,uVar6)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(param_2,uVar6) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  uStack_28 = param_4;
  if (uVar5 == 0) {
    iVar2 = __copy_from_user(vlan_cmd_line,param_2,uVar6);
    if (iVar2 != 0) {
      return 0xfffffff2;
    }
  }
  else if (uVar6 != 0) {
    __memzero(vlan_cmd_line,uVar6,uVar4);
    return 0xfffffff2;
  }
  vlan_cmd_line[uVar6] = 0;
  proc_get_cmd(vlan_cmd_line);
  iVar2 = proc_argc;
  if (proc_argc < 2) {
LAB_000172fc:
    printk(&_LC16,
           "Usage: echo [OPTIONS] add/del/show/hash/cls > /proc/xxx/l2 \nexample -m xx:xx:xx:xx:xx:xx -v 1 -p 0 add \n        show \nOptions:\n  -m,         set mac address\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -h,         help\n"
          );
  }
  else {
    vlan_port = 0;
    optreset = 1;
    optind = 1;
    vlan_vlan = 1;
    vlan_tag = 3;
    while (iVar1 = getopt(iVar2,(char **)proc_argv,"t:v:p:h?"), iVar1 != -1) {
      if (iVar1 == 0x74) {
        vlan_tag = simple_strtoul(optarg,0,10);
      }
      else if (iVar1 == 0x76) {
        vlan_vlan = simple_strtoul(optarg,0,10);
      }
      else {
        if (iVar1 != 0x70) goto LAB_000172fc;
        vlan_port = simple_strtoul(optarg,0,10);
      }
    }
    if (optind < iVar2) {
      __s1 = *(char **)(proc_argv + optind * 4);
      vlan_cmd = __s1;
      iVar2 = strcmp(__s1,"show");
      if (iVar2 == 0) {
        dump_vlan_info(vlan_vlan);
        return param_3;
      }
      iVar2 = strcmp(__s1,"add");
      if (iVar2 == 0) {
        pon_pp_add_port_to_vlan(vlan_vlan,vlan_port,vlan_tag);
        return param_3;
      }
      iVar2 = strcmp(__s1,"del");
      if (iVar2 == 0) {
        pon_pp_add_port_to_vlan(vlan_vlan,vlan_port);
        return param_3;
      }
    }
    else {
      printk("error: no rule,%d/%d\n",optind,iVar2);
    }
  }
  return param_3;
}

