// module: mt7915.ko
// function: vie_oper_proc @ 0x145e2c
// size: 1320 bytes
//

undefined4 vie_oper_proc(int *param_1,char *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  size_t sVar4;
  char *pcVar5;
  int *piVar6;
  uint uVar7;
  uint local_338;
  uint local_334;
  uint local_330;
  undefined4 local_32c;
  char local_325 [6];
  undefined4 local_31f;
  char acStack_220 [516];
  
  piVar6 = (int *)0x0;
  local_325[2] = 0;
  local_338 = 0;
  local_325[3] = 0;
  local_334 = 0;
  local_325[4] = 0;
  local_330 = 0;
  local_325[5] = 0;
  local_32c = 0;
  local_325[0] = '\0';
  local_325[1] = 0;
  memset(acStack_220,0,0x200);
  memset(&local_31f,0,0xff);
  if (*(char *)((int)param_1 + 0x286285) == '\0') {
    piVar6 = param_1 + *(int *)(*param_1 + 0x3c) * 0x84dec + 0xdb6d6;
  }
  else if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    piVar6 = param_1 + *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92;
  }
  if (param_2 == (char *)0x0) {
    return 1;
  }
  iVar3 = sscanf(param_2,"%u-frm_map:%x-oui:%6s-length:%u-ctnt:%s",&local_338,&local_330,local_325,
                 &local_334,acStack_220);
  uVar2 = local_330;
  uVar1 = local_334;
  uVar7 = local_338;
  if (local_338 < 5) {
    if ((iVar3 != 5 && local_338 != 4) || (local_338 == 4 && iVar3 != 2)) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("oper:%d, input_argument:%d\n",local_338,iVar3);
    }
    else if (local_330 < 0x80) {
      if (local_338 == 4) {
LAB_00145f34:
        if (-1 < DebugLevel) {
          printk("%s(): oper:%d, frm_map:0x%x, oui:%s, length:%d, ctnt:%s\n","vie_oper_proc",uVar7,
                 uVar2,local_325,uVar1,acStack_220);
          uVar7 = local_338;
        }
        if (uVar7 - 1 < 3) {
          AtoH(local_325,&local_31f,3);
          if (3 < local_334) {
            AtoH(acStack_220,(int)&local_31f + 3,local_334 - 3);
          }
          local_32c = local_31f;
          if (local_338 == 3) {
            iVar3 = remove_vie(param_1,piVar6,local_330,local_31f,local_334,&local_31f);
            if (iVar3 == 1) {
              if (DebugLevel < 0) {
                return 0;
              }
              printk("%s(): remove failed.\n","vie_oper_proc");
              return 0;
            }
          }
          else {
            iVar3 = add_vie();
            if (iVar3 == 1) {
              if (-1 < DebugLevel) {
                pcVar5 = "add";
                if (local_338 != 1) {
                  pcVar5 = "update";
                }
                printk("%s(): %s failed.\n","vie_oper_proc",pcVar5);
                return 0;
              }
              return 0;
            }
          }
        }
        else if (piVar6 != (int *)0x0 && uVar7 == 4) {
          print_vie(piVar6,local_330);
        }
        return 1;
      }
      sVar4 = strlen(local_325);
      if (sVar4 == 6) {
        sVar4 = strlen(acStack_220);
        if (sVar4 == uVar1 * 2 - 6) goto LAB_00145f34;
        if (DebugLevel < 0) {
          return 0;
        }
        printk("oui len + ctnt length:%d != input length:%d!\n",sVar4 >> 1,uVar1);
      }
      else {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("oui format error:%s, should be xxxxxx!\n",local_325);
      }
    }
    else {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("frm_map error:0x%x\n",local_330,iVar3);
    }
  }
  else {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("oper error:%d\n",local_338,iVar3);
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk(
        "\nCommand Format: \'op\'-frm_map:\'bitmap\'-oui:\'xxxxxx\'-length:\'len\'-ctnt:\'xxxxxx\'\n"
        );
  if (DebugLevel < 0) {
LAB_001460a4:
    if (-1 < DebugLevel) {
      printk("\nlength: the total length of oui and content\n");
      if (DebugLevel < 0) {
        return 0;
      }
      printk("\nctnt: in hex format, such as aabbcc\n");
      goto LAB_001460dc;
    }
  }
  else {
    printk("op: 1: ADD, 2: UPDATE, 3: REMOVE, 4: SHOW\n");
    if (DebugLevel < 0) {
      return 0;
    }
    printk("\nbitmap: 0x1: BEACON, 0x2: PROBE_REQ, 0x4: PROBE_RESP, 0x8: ASSOC_REQ\n");
    if (-1 < DebugLevel) {
      printk("\t 0x10: ASSOC_RESP, 0x20: AUTH_REQ, 0x40: AUTH_RESP\n");
      if (DebugLevel < 0) {
        return 0;
      }
      printk("\noui: in hex format, such as 000c43\n");
      goto LAB_001460a4;
    }
LAB_001460dc:
    if (DebugLevel < 0) goto LAB_0014614c;
    printk("\nCase 1: Add or Update\n");
    if (DebugLevel < 0) {
      return 0;
    }
    printk("\tiwpriv ra0 set vie_op=1-frm_map:1-oui:00aabb-length:4-ctnt:cc\n");
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("\nCase 2: Remove\n");
  if (DebugLevel < 0) {
    return 0;
  }
  printk("\tiwpriv ra0 set vie_op=3-frm_map:1-oui:00aabb-length:4-ctnt:cc\n");
LAB_0014614c:
  if ((-1 < DebugLevel) && (printk("\nCase 3: Show\n"), -1 < DebugLevel)) {
    printk("\tiwpriv ra0 set vie_op=4-frm_map:1\n");
    return 0;
  }
  return 0;
}

