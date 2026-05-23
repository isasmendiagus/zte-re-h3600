// module: tm.ko
// function: tm_test_show @ 0x77d98
// size: 276 bytes
//

undefined4 tm_test_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  char *__s1;
  
  __s1 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = strcmp(__s1,"featureopen");
    if (iVar1 == 0) {
      printk("Open tmtst feature command success!\n");
      uVar2 = 0;
    }
    else {
      iVar1 = strcmp(__s1,"tmup");
      if (iVar1 == 0) {
        iVar1 = tm_up_statistics_get();
        if (iVar1 != 0) {
          printk("[tmtst]tm up fail, error code %d!\n");
          return 0;
        }
      }
      else {
        iVar1 = strcmp(__s1,"tmdn");
        if (iVar1 == 0) {
          iVar1 = tm_dn_statistics_get();
          if (iVar1 != 0) {
            printk("[tmtst]tm dn fail, error code %d!\n");
            return 0;
          }
        }
        else {
          iVar1 = strcmp(__s1,"tmerrormonitor");
          if (iVar1 != 0) {
            printk("%s: illegal operation <%s>\n","tm_test_show",*param_2);
            return 0;
          }
          iVar1 = tm_error_monitor();
          if (iVar1 != 0) {
            printk("[tmtst] tm error monitor failed,erro code!\n");
            return 0;
          }
        }
      }
      uVar2 = 0;
    }
  }
  return uVar2;
}

