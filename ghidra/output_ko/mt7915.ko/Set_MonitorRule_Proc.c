// module: mt7915.ko
// function: Set_MonitorRule_Proc @ 0x33ae4
// size: 400 bytes
//

undefined4 Set_MonitorRule_Proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  int iVar2;
  char *__s;
  size_t sVar3;
  undefined4 uVar4;
  byte *__s_00;
  undefined1 *puVar5;
  char *local_2c [2];
  undefined1 auStack_23 [7];
  
  local_2c[0] = param_2;
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (0 < DebugLevel) {
    printk("--> %s()\n","Set_MonitorRule_Proc");
  }
  do {
    do {
      while( true ) {
        while( true ) {
          __s = strsep(local_2c,";");
          if (__s == (char *)0x0) {
            if (iVar2 == 0) {
              uVar4 = 0;
              if (-1 < DebugLevel) {
                printk("wdev is NULL\n");
              }
            }
            else {
              uVar4 = HcGetBandByWdev(iVar2);
              uVar4 = asic_set_air_mon_rule(param_1,auStack_23,uVar4);
            }
            return uVar4;
          }
          if (*__s != '\0') break;
          if (1 < DebugLevel) {
            printk("An unnecessary delimiter entered!\n");
          }
        }
        sVar3 = strlen(__s);
        if (sVar3 == 5) break;
        if (-1 < DebugLevel) {
          printk("illegal length! (acceptable format 0:1:1 length 5)\n");
        }
      }
      __s_00 = (byte *)rstrtok(__s,&_LC162);
    } while (__s_00 == (byte *)0x0);
    puVar5 = auStack_23;
    do {
      sVar3 = strlen((char *)__s_00);
      if ((sVar3 != 1) || (((&_ctype)[*__s_00] & 0x44) == 0)) {
        if (-1 < DebugLevel) {
          printk("illegal format!\n");
        }
        break;
      }
      uVar1 = os_str_tol(__s_00,0,10);
      *puVar5 = uVar1;
      __s_00 = (byte *)rstrtok(0,&_LC162);
      puVar5 = puVar5 + 1;
    } while (__s_00 != (byte *)0x0);
  } while( true );
}

