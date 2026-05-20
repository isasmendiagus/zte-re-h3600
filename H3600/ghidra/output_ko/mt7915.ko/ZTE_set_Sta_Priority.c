// module: mt7915.ko
// function: ZTE_set_Sta_Priority @ 0x15d76c
// size: 628 bytes
//

undefined4 ZTE_set_Sta_Priority(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  byte *__s;
  int iVar2;
  byte *pbVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined4 uVar8;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  
  if (2 < DebugLevel) {
    printk("%s %s\n","ZTE_set_Sta_Priority",param_2);
  }
  sVar1 = strlen(param_2);
  if (sVar1 - 0x16 < 2) {
    __s = (byte *)rstrtok(param_2,&_LC11);
    puVar6 = &local_26;
    if (__s == (byte *)0x0) {
LAB_0015d9a8:
      __s = (byte *)0x0;
    }
    else {
      do {
        sVar1 = strlen((char *)__s);
        puVar7 = puVar6 + 1;
        if (sVar1 != 2) {
          return 0;
        }
        if (((&_ctype)[*__s] & 0x44) == 0) {
          return 0;
        }
        if (((&_ctype)[__s[1]] & 0x44) == 0) {
          return 0;
        }
        AtoH(__s,puVar6);
        __s = (byte *)rstrtok(0,&_LC11);
        if (__s == (byte *)0x0) goto LAB_0015d9a8;
        puVar6 = puVar7;
      } while (puVar7 != &stack0xffffffe0);
    }
    iVar2 = memcmp(&local_26,&BROADCAST_ADDR,6);
    if ((iVar2 == 0) || (iVar2 = memcmp(&local_26,&ZERO_MAC_ADDR,6), iVar2 == 0)) {
      return 1;
    }
    if (__s != (byte *)0x0) {
      iVar2 = strcmp((char *)__s,"BE");
      if (iVar2 == 0) {
        uVar8 = 0;
      }
      else {
        iVar2 = strcmp((char *)__s,"BK");
        if (iVar2 == 0) {
          uVar8 = 1;
        }
        else {
          iVar2 = strcmp((char *)__s,"VI");
          if (iVar2 == 0) {
            uVar8 = 5;
          }
          else {
            iVar2 = strcmp((char *)__s,"VO");
            if (iVar2 == 0) {
              uVar8 = 7;
            }
            else {
              iVar2 = strcmp((char *)__s,"DF");
              if (iVar2 != 0) {
                return 0;
              }
              uVar8 = 0xffffffff;
            }
          }
        }
      }
      pbVar3 = (byte *)rstrtok(0,&_LC11);
      if ((pbVar3 != (byte *)0x0) && (((&_ctype)[*pbVar3] & 4) != 0)) {
        uVar4 = simple_strtol(pbVar3,0,10);
        iVar5 = MacTableLookup(param_1,&local_26);
        iVar2 = DebugLevel;
        if (iVar5 != 0) {
          *(undefined4 *)(iVar5 + 0xccc) = uVar8;
          *(undefined4 *)(iVar5 + 0xcd0) = uVar4;
        }
        if (iVar2 < 3) {
          return 1;
        }
        printk("set %02x:%02x:%02x:%02x:%02x:%02x protocol[%d] to %s\n",local_26,local_25,local_24,
               local_23,local_22,local_21,uVar4,__s);
        return 1;
      }
    }
  }
  return 0;
}

