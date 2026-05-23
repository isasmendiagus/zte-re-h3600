// module: mt7915.ko
// function: SrDisSrBfrConnected @ 0x16bb0c
// size: 756 bytes
//

undefined4 SrDisSrBfrConnected(int param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_2c [2];
  undefined1 local_2a;
  uint local_24;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: wdev == NULL \n","SrDisSrBfrConnected");
    return 1;
  }
  iVar2 = HcGetBandByWdev(param_2);
  iVar5 = param_1 + iVar2;
  if (*(char *)(iVar5 + 0x795b16) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s: SREnable[%d] = %d Return SUCCESS\n","SrDisSrBfrConnected",iVar2,0);
      return 0;
    }
  }
  else {
    uVar4 = (uint)*(byte *)(iVar5 + 0x795b1c);
    if (uVar4 == param_3) {
      if (-1 < DebugLevel) {
        printk("%s: DisSrBfrConnected[%d] = %d == fgSrEnable = %d Return SUCCESS\n",
               "SrDisSrBfrConnected",iVar2,uVar4,uVar4);
      }
    }
    else {
      if (-1 < DebugLevel) {
        printk("%s: u1DbdcIdx = %d, fgSrEnable = %d \n","SrDisSrBfrConnected",iVar2,param_3);
      }
      uVar1 = (undefined1)iVar2;
      local_2a = uVar1;
      if (param_3 == 0) {
        os_zero_mem(local_2c);
        local_2c[0] = 0x10;
        local_24 = param_3;
        iVar3 = SrCmd(param_1,local_2c);
        if (iVar3 == 1) {
          if (-1 < DebugLevel) {
            printk("%s: Set SRSDEnable[%d]=%d Fail!\n","SrDisSrBfrConnected",iVar2,0);
            return 1;
          }
          return 1;
        }
        os_zero_mem(local_2c,0xc);
        local_2c[0] = 0xf;
        local_2a = uVar1;
        local_24 = param_3;
        iVar3 = SrCmd(param_1,local_2c);
        if (iVar3 != 1) {
          *(undefined1 *)(iVar5 + 0x795b1c) = 0;
          return 0;
        }
        if (-1 < DebugLevel) {
          printk("%s: Set SREnable[%d]=%d Fail!\n","SrDisSrBfrConnected",iVar2,0);
          return 1;
        }
        return 1;
      }
      os_zero_mem(local_2c,0xc);
      local_24 = (uint)*(byte *)(iVar5 + 0x795b16);
      local_2c[0] = 0xf;
      iVar3 = SrCmd(param_1,local_2c);
      if (iVar3 == 1) {
        if (-1 < DebugLevel) {
          printk("%s: Set SREnable[%d]=%d Fail!\n","SrDisSrBfrConnected",iVar2,
                 *(undefined1 *)(iVar5 + 0x795b16));
          return 1;
        }
        return 1;
      }
      *(undefined1 *)(iVar5 + 0x795b1c) = *(undefined1 *)(iVar5 + 0x795b16);
      os_zero_mem(local_2c,0xc);
      local_24 = (uint)*(byte *)(iVar5 + 0x795b1a);
      local_2c[0] = 0x10;
      local_2a = uVar1;
      iVar3 = SrCmd(param_1,local_2c);
      if (iVar3 == 1) {
        if (-1 < DebugLevel) {
          printk("%s: Set SRSDEnable[%d]=%d Fail!\n","SrDisSrBfrConnected",iVar2,
                 *(undefined1 *)(iVar5 + 0x795b1a));
          return 1;
        }
        return 1;
      }
    }
  }
  return 0;
}

