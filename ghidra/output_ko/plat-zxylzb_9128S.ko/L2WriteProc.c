// module: plat-zxylzb_9128S.ko
// function: L2WriteProc @ 0x170c8
// size: 1076 bytes
//

uint L2WriteProc(undefined4 param_1,uint param_2,uint param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  short sVar5;
  undefined2 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *puVar13;
  uint uVar14;
  undefined6 *puVar15;
  undefined6 *puVar16;
  char *__s1;
  undefined1 *puVar17;
  char *pcVar18;
  undefined1 *local_48;
  undefined1 *local_44;
  undefined1 *local_40;
  undefined1 *local_3c;
  undefined4 uStack_38;
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [4];
  undefined1 auStack_28 [4];
  undefined1 auStack_24 [4];
  
  uVar9 = param_3;
  if (0x7e < param_3) {
    uVar9 = 0x7f;
  }
  uVar14 = *(uint *)(((uint)&local_48 & 0xffffe000) + 8);
  uVar11 = param_2 + uVar9;
  uVar12 = uVar11;
  if (!CARRY4(param_2,uVar9)) {
    uVar12 = uVar11 - (uVar14 + 1);
  }
  if (!CARRY4(param_2,uVar9) && uVar11 <= uVar14) {
    uVar14 = 0;
  }
  if (uVar14 == 0) {
    iVar8 = __copy_from_user(l2_cmd_line,param_2,uVar9);
    if (iVar8 != 0) {
      return 0xfffffff2;
    }
  }
  else if (uVar9 != 0) {
    __memzero(l2_cmd_line,uVar9,uVar12);
    return 0xfffffff2;
  }
  l2_cmd_line[uVar9] = 0;
  proc_get_cmd(l2_cmd_line);
  iVar8 = proc_argc;
  if (proc_argc < 2) {
LAB_000171b0:
    printk(&_LC16,
           "Usage: echo [OPTIONS] add/del/show/hash/cls > /proc/xxx/l2 \nexample -m xx:xx:xx:xx:xx:xx -v 1 -p 0 add \n        show \nOptions:\n  -m,         set mac address\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -h,         help\n"
          );
    return param_3;
  }
  l2_port = 0;
  l2_has_mac = '\0';
  l2_vlan = 1;
  __memzero(&l2_mac,6);
  optind = 1;
  optreset = 1;
  while (iVar7 = getopt(iVar8,(char **)proc_argv,"m:v:p:h?"), iVar7 != -1) {
    if (iVar7 == 0x70) {
      bVar4 = simple_strtoul(optarg,0,10);
      l2_port = bVar4 & 7;
    }
    else if (iVar7 == 0x76) {
      sVar5 = simple_strtoul(optarg,0,10);
      l2_vlan = sVar5 * 0xfff;
    }
    else {
      if (iVar7 != 0x6d) goto LAB_000171b0;
      local_48 = auStack_30;
      local_44 = auStack_2c;
      local_3c = auStack_24;
      local_40 = auStack_28;
      iVar7 = sscanf(optarg,"%x:%x:%x:%x:%x:%x",&uStack_38,auStack_34);
      if (iVar7 != 6) {
        printk("invalid mac %s\n",optarg);
        return param_3;
      }
      puVar13 = &uStack_38;
      puVar15 = &l2_mac;
      do {
        puVar16 = (undefined6 *)((int)puVar15 + 1);
        *(char *)puVar15 = (char)*puVar13;
        puVar13 = puVar13 + 1;
        puVar15 = puVar16;
      } while (puVar16 != (undefined6 *)0x2e772);
      l2_has_mac = '\x01';
    }
  }
  if (iVar8 <= optind) {
    printk("error: no rule,%d/%d\n",optind,iVar8);
    return param_3;
  }
  pcVar18 = *(char **)(proc_argv + optind * 4);
  l2_cmd = pcVar18;
  if (optind < iVar8 + -1) {
    __s1 = *(char **)(proc_argv + optind * 4 + 4);
    l2_param = __s1;
    iVar8 = strcmp(pcVar18,"show");
    if (iVar8 != 0) goto LAB_00017308;
    if (__s1 != (char *)0x0) {
      iVar8 = strcmp(__s1,"cnt");
      if (iVar8 != 0) {
        uVar6 = simple_strtoul(__s1,0,10);
        pon_pp_dump_hash_mac(uVar6);
        return param_3;
      }
      uVar10 = pon_pp_learned_mac();
      printk("mac learned %d\n",uVar10);
      return param_3;
    }
  }
  else {
    l2_param = (char *)0x0;
    iVar8 = strcmp(pcVar18,"show");
    if (iVar8 != 0) {
LAB_00017308:
      iVar8 = strcmp(pcVar18,"cls");
      if ((iVar8 == 0) && ((*(uint *)(pp_base + 0x8004) & 0x10000) == 0)) {
        *(uint *)(pp_base + 0x8004) =
             *(uint *)(pp_base + 0x8004) | (1 << l2_port & 0xffU) << 8 | 0x10000;
      }
      pcVar18 = l2_cmd;
      if (l2_has_mac == '\0') {
        printk("need input mac\n");
        return param_3;
      }
      iVar8 = strcmp(l2_cmd,"add");
      if (iVar8 == 0) {
        pon_pp_add_mac(&l2_mac,l2_vlan,l2_port);
        return param_3;
      }
      iVar8 = strcmp(pcVar18,"del");
      if (iVar8 != 0) {
        iVar8 = strcmp(pcVar18,"hash");
        uVar3 = l2_mac._2_1_;
        uVar2 = l2_mac._1_1_;
        uVar1 = (undefined1)l2_mac;
        if (iVar8 != 0) {
          return param_3;
        }
        puVar17 = (undefined1 *)(uint)l2_mac._3_1_;
        uVar11 = (uint)l2_mac._4_1_;
        uVar12 = (uint)l2_mac._5_1_;
        uVar9 = crc_16(&l2_mac,6,0);
        local_3c = (undefined1 *)(uVar9 & 0x3ff);
        local_48 = puVar17;
        local_44 = (undefined1 *)uVar11;
        local_40 = (undefined1 *)uVar12;
        printk("mac %.2x %.2x %.2x %.2x %.2x %.2x hash is %d\n",uVar1,uVar2,uVar3);
        return param_3;
      }
      pon_pp_del_mac(&l2_mac,l2_vlan);
      return param_3;
    }
  }
  pon_pp_dump_mac();
  return param_3;
}

