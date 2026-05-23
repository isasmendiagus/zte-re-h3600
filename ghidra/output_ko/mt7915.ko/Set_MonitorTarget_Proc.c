// module: mt7915.ko
// function: Set_MonitorTarget_Proc @ 0x2c77c
// size: 460 bytes
//

undefined4 Set_MonitorTarget_Proc(int param_1,char *param_2)

{
  char *__s;
  size_t sVar1;
  byte *__s_00;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  char *local_24 [2];
  
  local_24[0] = param_2;
  if (2 < DebugLevel) {
    printk("--> %s()\n","Set_MonitorTarget_Proc");
  }
  puVar3 = (undefined1 *)(param_1 + 0xa37695);
  do {
    do {
      while( true ) {
        while( true ) {
          __s = strsep(local_24,";");
          if (__s == (char *)0x0) {
            iVar2 = DebugLevel;
            do {
              if (0 < iVar2) {
                printk("%02X ",*puVar3);
                iVar2 = DebugLevel;
              }
              puVar3 = puVar3 + 1;
            } while (puVar3 != (undefined1 *)(param_1 + 0xa3769b));
            if ((0 < iVar2) && (printk(&_LC220), 0 < DebugLevel)) {
              printk("<-- %s()\n","Set_MonitorTarget_Proc");
            }
            return 1;
          }
          if (*__s != '\0') break;
          if (1 < DebugLevel) {
            printk("An unnecessary delimiter entered!\n");
          }
        }
        sVar1 = strlen(__s);
        if (sVar1 == 0x11) break;
        if (-1 < DebugLevel) {
          printk("illegal MAC address length! (acceptable format 01:02:03:04:05:06 length 17)\n");
        }
      }
      __s_00 = (byte *)rstrtok(__s,&_LC162);
      puVar4 = puVar3;
    } while (__s_00 == (byte *)0x0);
    do {
      sVar1 = strlen((char *)__s_00);
      if (((sVar1 != 2) || (((&_ctype)[*__s_00] & 0x44) == 0)) ||
         (((&_ctype)[__s_00[1]] & 0x44) == 0)) {
        if (-1 < DebugLevel) {
          printk("illegal MAC address format or octet!\n");
        }
        break;
      }
      AtoH(__s_00,puVar4);
      __s_00 = (byte *)rstrtok(0,&_LC162);
      puVar4 = puVar4 + 1;
    } while (__s_00 != (byte *)0x0);
  } while( true );
}

