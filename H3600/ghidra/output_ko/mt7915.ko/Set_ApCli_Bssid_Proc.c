// module: mt7915.ko
// function: Set_ApCli_Bssid_Proc @ 0x301d4
// size: 556 bytes
//

undefined4 Set_ApCli_Bssid_Proc(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  byte *__s;
  uint uVar4;
  int iVar5;
  
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    uVar4 = (uint)*(byte *)(*param_1 + 0x3c);
    cVar1 = *(char *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e8d);
    sta_reset_owe_parameters(param_1,uVar4);
    if ((cVar1 == '\x01') && (iVar5 = strcmp(param_2,"00:00:00:00:00:00"), iVar5 != 0)) {
      *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e8d) = 0;
      ApCliIfDown(param_1);
    }
    __memzero(&DAT_00580e5b + (int)(param_1 + uVar4 * 0x84dec),6);
    sVar3 = strlen(param_2);
    if (sVar3 != 0x11) {
LAB_00030270:
      if (2 < DebugLevel) {
        printk("Set_ApCli_Bssid_Proc (%2X:%2X:%2X:%2X:%2X:%2X)\n",
               *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e5b),
               (char)param_1[uVar4 * 0x84dec + 0x160397],
               *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e5d),
               *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e5e),
               *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e5f),
               (char)param_1[uVar4 * 0x84dec + 0x160398]);
      }
      *(char *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e8d) = cVar1;
      return 1;
    }
    __s = (byte *)rstrtok(param_2,&_LC162);
    if (__s != (byte *)0x0) {
      iVar5 = 0;
      do {
        sVar3 = strlen((char *)__s);
        iVar2 = iVar5 + uVar4 * 0x2137b0;
        iVar5 = iVar5 + 1;
        if (sVar3 != 2) {
          return 0;
        }
        if (((&_ctype)[*__s] & 0x44) == 0) {
          return 0;
        }
        if (((&_ctype)[__s[1]] & 0x44) == 0) {
          return 0;
        }
        AtoH(__s,(undefined *)((int)param_1 + (int)(&DAT_00580e5b + iVar2)));
        __s = (byte *)rstrtok(0,&_LC162);
      } while (__s != (byte *)0x0);
      if (iVar5 == 6) goto LAB_00030270;
    }
  }
  return 0;
}

