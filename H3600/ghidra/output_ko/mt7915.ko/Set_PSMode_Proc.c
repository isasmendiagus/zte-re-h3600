// module: mt7915.ko
// function: Set_PSMode_Proc @ 0x5891c
// size: 1016 bytes
//

undefined4 Set_PSMode_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  if ((*(int *)(*param_1 + 0x38) == 0x400) && (0 < DebugLevel)) {
    printk("%s:wdev(type=%d,if=%s)\n","Set_PSMode_Proc",param_1[iVar3 * 0x84dec + 0xdb6db],
           param_1[iVar3 * 0x84dec + 0xdb6d6],param_4);
  }
  if ((char)param_1[iVar3 * 0x84dec + 0xdc6ee] != '\x01') {
    return 0;
  }
  iVar1 = strcmp(param_2,"Max_PSP");
  if (((iVar1 == 0) || (iVar1 = strcmp(param_2,"max_psp"), iVar1 == 0)) ||
     (iVar1 = strcmp(param_2,"MAX_PSP"), iVar1 == 0)) {
    if ((char)param_1[iVar3 * 0x84dec + 0x160003] == '\0') {
      param_1[iVar3 * 0x84dec + 0x160001] = 1;
    }
    piVar2 = param_1 + 0x1e5400;
    param_1[iVar3 * 0x84dec + 0x160002] = 1;
    param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
    *(undefined2 *)((int)param_1 + iVar3 * 0x2137b0 + 0x57fffe) = 5;
  }
  else {
    iVar1 = strcmp(param_2,"Fast_PSP");
    if (((iVar1 == 0) || (iVar1 = strcmp(param_2,"fast_psp"), iVar1 == 0)) ||
       (iVar1 = strcmp(param_2,"FAST_PSP"), iVar1 == 0)) {
      param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
      if ((char)param_1[iVar3 * 0x84dec + 0x160003] == '\0') {
        param_1[iVar3 * 0x84dec + 0x160001] = 2;
      }
      piVar2 = param_1 + iVar3 * 0x84dec + 0x15fffe;
      param_1[iVar3 * 0x84dec + 0x160002] = 2;
      *(undefined2 *)((int)param_1 + iVar3 * 0x2137b0 + 0x57fffe) = 3;
    }
    else {
      iVar1 = strcmp(param_2,"Legacy_PSP");
      puVar4 = (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar3 * 0x2137b0));
      if (((iVar1 == 0) || (iVar1 = strcmp(param_2,"legacy_psp"), iVar1 == 0)) ||
         (iVar1 = strcmp(param_2,"LEGACY_PSP"), iVar1 == 0)) {
        param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
        if ((char)param_1[iVar3 * 0x84dec + 0x160003] == '\0') {
          if (param_1[iVar3 * 0x84dec + 0x160001] == 0) {
            RTMP_SLEEP_FORCE_AUTO_WAKEUP(param_1,puVar4);
          }
          param_1[iVar3 * 0x84dec + 0x160001] = 3;
        }
        piVar2 = param_1 + iVar3 * 0x84dec + 0x15fffe;
        param_1[iVar3 * 0x84dec + 0x160002] = 3;
        *(undefined2 *)((int)param_1 + iVar3 * 0x2137b0 + 0x57fffe) = 3;
      }
      else {
        if (2 < DebugLevel) {
          printk("%s(line=%d): -->\n","Set_PSMode_Proc",0x64d);
        }
        MlmeSetPsmBit(param_1,puVar4,0);
        param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
        if (((char)param_1[iVar3 * 0x84dec + 0x160003] == '\0') &&
           (param_1[iVar3 * 0x84dec + 0x160001] != 0)) {
          RTMP_FORCE_WAKEUP(param_1,puVar4);
          param_1[iVar3 * 0x84dec + 0x160001] = 0;
        }
        piVar2 = (int *)0x0;
        param_1[iVar3 * 0x84dec + 0x160002] = 0;
      }
    }
  }
  if (2 < DebugLevel) {
    printk("Set_PSMode_Proc::(PSMode=%ld)\n",param_1[iVar3 * 0x84dec + 0x160001],piVar2,
           param_1 + iVar3 * 0x84dec + 0x160000,param_4);
    return 1;
  }
  return 1;
}

