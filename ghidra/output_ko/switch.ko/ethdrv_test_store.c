// module: switch.ko
// function: ethdrv_test_store @ 0x101e0
// size: 480 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4
ethdrv_test_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined6 *puVar3;
  undefined6 *puVar4;
  char *__s1;
  char local_44 [20];
  undefined4 local_30 [6];
  
  __s1 = (char *)*param_2;
  local_44[0] = '\0';
  local_44[1] = '\0';
  local_44[2] = '\0';
  local_44[3] = '\0';
  local_44[4] = '\0';
  local_44[5] = '\0';
  local_44[6] = '\0';
  local_44[7] = '\0';
  local_44[8] = '\0';
  local_44[9] = '\0';
  local_44[10] = '\0';
  local_44[0xb] = '\0';
  local_44[0xc] = '\0';
  local_44[0xd] = '\0';
  local_44[0xe] = '\0';
  local_44[0xf] = '\0';
  local_44[0x10] = '\0';
  local_44[0x11] = '\0';
  local_44[0x12] = '\0';
  local_44[0x13] = '\0';
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  local_30[4] = 0;
  local_30[5] = 0;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    disableIRQinterrupts();
    iVar1 = strcmp(__s1,"dbg");
    if (iVar1 == 0) {
      iVar1 = sscanf(param_3,"dbg %s",local_44);
      if (iVar1 == 1) {
        iVar1 = strncmp(local_44,"mac",3);
        if (iVar1 == 0) {
          g_debug_mode = 4;
        }
        else {
          iVar1 = strncmp(local_44,"recv",4);
          if (iVar1 == 0) {
            g_debug_mode = 2;
          }
          else {
            iVar1 = strncmp(local_44,"send",4);
            if (iVar1 == 0) {
              g_debug_mode = 3;
            }
            else {
              iVar1 = strncmp(local_44,"all",3);
              g_debug_mode = iVar1 == 0;
            }
          }
        }
      }
    }
    else {
      iVar1 = strcmp(__s1,"mac");
      if (iVar1 == 0) {
        iVar1 = sscanf(param_3,"mac %s",local_44);
        if (iVar1 == 1) {
          sscanf(param_3,"mac %x:%x:%x:%x:%x:%x",local_30,local_30 + 1,local_30 + 2,local_30 + 3,
                 local_30 + 4,local_30 + 5);
          puVar2 = local_30;
          puVar3 = &g_eth_debug_mac;
          do {
            puVar4 = (undefined6 *)((int)puVar3 + 1);
            *(char *)puVar3 = (char)*puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar4;
          } while (puVar4 != (undefined6 *)0x2b65a);
        }
      }
      else {
        printk("llegal operation <%s>\n",*param_2);
      }
    }
  }
  return param_4;
}

