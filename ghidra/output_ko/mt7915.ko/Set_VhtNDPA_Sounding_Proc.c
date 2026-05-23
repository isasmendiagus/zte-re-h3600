// module: mt7915.ko
// function: Set_VhtNDPA_Sounding_Proc @ 0xe6ec8
// size: 384 bytes
//

undefined4 Set_VhtNDPA_Sounding_Proc(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  char *__s;
  undefined4 uVar2;
  byte *__s_00;
  undefined1 *puVar3;
  int iVar4;
  undefined2 local_28;
  undefined1 local_26 [4];
  undefined1 local_22;
  undefined1 local_21;
  
  local_28 = 0x3a;
  if (2 < DebugLevel) {
    printk(&_LC743);
  }
  sVar1 = strlen(param_2);
  if (((0x12 < sVar1) && (__s = strchr(param_2,0x2d), __s != (char *)0x0)) &&
     (sVar1 = strlen(__s), 1 < sVar1)) {
    iVar4 = 0;
    uVar2 = os_str_tol(__s + 1,0,10);
    *__s = '\0';
    __s_00 = (byte *)rstrtok(param_2,&local_28);
    if (__s_00 != (byte *)0x0) {
      do {
        sVar1 = strlen((char *)__s_00);
        puVar3 = local_26 + iVar4;
        iVar4 = iVar4 + 1;
        if (sVar1 != 2) {
          return 0;
        }
        if (((&_ctype)[*__s_00] & 0x44) == 0) {
          return 0;
        }
        if (((&_ctype)[__s_00[1]] & 0x44) == 0) {
          return 0;
        }
        AtoH(__s_00,puVar3);
        __s_00 = (byte *)rstrtok(0,&local_28);
      } while (__s_00 != (byte *)0x0);
      if (iVar4 == 6) {
        if (0 < DebugLevel) {
          printk("\n%02x:%02x:%02x:%02x:%02x:%02x-%02x\n",local_26[0],local_26[1],local_26[2],
                 local_26[3],local_22,local_21,uVar2);
        }
        iVar4 = MacTableLookup(param_1,local_26);
        if (iVar4 == 0) {
          return 1;
        }
        trigger_vht_ndpa(param_1);
        return 1;
      }
    }
  }
  return 0;
}

