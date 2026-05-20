// module: mt7915.ko
// function: SetRF @ 0xea0fc
// size: 504 bytes
//

undefined4 SetRF(int param_1,int param_2)

{
  int iVar1;
  char *__s;
  uint uVar2;
  uint uVar3;
  undefined4 local_24 [3];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar1 + 0x40) != 3) {
    return 0;
  }
  uVar3 = 0;
  local_24[0] = 0;
  local_24[1] = 0;
  local_24[2] = 0;
  if (param_2 == 0) {
    return 0;
  }
  __s = (char *)rstrtok(param_2,&_LC547);
  if (__s == (char *)0x0) {
    if (DebugLevel < 3) {
      return 0;
    }
    uVar3 = 0;
  }
  else {
    do {
      uVar2 = sscanf(__s,"%8x",local_24 + uVar3);
      if ((uVar2 & 0xff) == 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: invalid format(%s), ignored!\n","SetMTRF",__s);
        return 0;
      }
      __s = (char *)rstrtok(0,&_LC547);
      uVar3 = uVar3 + 1 & 0xff;
    } while (__s != (char *)0x0);
    if (DebugLevel < 3) goto LAB_000ea1e8;
  }
  printk("RfIdx = %d, Offset = 0x%08x, Value = 0x%08x\n",local_24[0],local_24[1],local_24[2]);
LAB_000ea1e8:
  if (uVar3 < 4) {
    if (uVar3 == 2) {
      MtCmdRFRegAccessRead(param_1,local_24[0],local_24[1],local_24 + 2);
      if (0 < DebugLevel) {
        printk("%s:%d read[0x%08x]=0x%08x\n","SetMTRF",local_24[0],local_24[1],local_24[2]);
      }
    }
    else if (uVar3 == 3) {
      MtCmdRFRegAccessWrite(param_1,local_24[0],local_24[1],local_24[2]);
      local_24[2] = 0;
      MtCmdRFRegAccessRead(param_1,local_24[0],local_24[1],local_24 + 2);
      if (0 < DebugLevel) {
        printk("%s:%d write[0x%08x]=0x%08x\n","SetMTRF",local_24[0],local_24[2],local_24[2]);
      }
    }
  }
  else if (0 < DebugLevel) {
    printk("%s(): incorrect format(%s)\n","SetMTRF",param_2);
  }
  return 0;
}

