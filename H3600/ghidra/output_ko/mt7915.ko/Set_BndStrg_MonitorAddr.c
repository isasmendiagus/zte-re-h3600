// module: mt7915.ko
// function: Set_BndStrg_MonitorAddr @ 0x9c4f0
// size: 328 bytes
//

undefined4 Set_BndStrg_MonitorAddr(int *param_1,char *param_2)

{
  uint uVar1;
  size_t sVar2;
  byte *__s;
  undefined1 *puVar3;
  undefined1 auStack_1e [6];
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_MonitorAddr",uVar1);
  }
  if (uVar1 < 2) {
    sVar2 = strlen(param_2);
    if (sVar2 != 0x11) {
      return 0;
    }
    __s = (byte *)rstrtok(param_2,&_LC34);
    if (__s != (byte *)0x0) {
      puVar3 = auStack_1e;
      do {
        sVar2 = strlen((char *)__s);
        if (sVar2 != 2) {
          return 0;
        }
        if (((&_ctype)[*__s] & 0x44) == 0) {
          return 0;
        }
        if (((&_ctype)[__s[1]] & 0x44) == 0) {
          return 0;
        }
        AtoH(__s,puVar3);
        __s = (byte *)rstrtok(0,&_LC34);
        puVar3 = puVar3 + 1;
      } while (__s != (byte *)0x0);
    }
    if (param_1[uVar1 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar1 * 0x425 + 0xdb24f] + 0x4c))
                (param_1 + uVar1 * 0x425 + 0xdae49,auStack_1e);
    }
  }
  return 1;
}

