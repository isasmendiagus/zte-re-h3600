// module: mt7915.ko
// function: get_fw_cmd @ 0xbcdec
// size: 416 bytes
//

undefined4 get_fw_cmd(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  char *__s;
  undefined1 local_1d;
  int local_1c;
  
  iVar2 = rstrtok(param_2,&_LC156);
  if (iVar2 == 0) {
    return 0;
  }
  __s = (char *)(iVar2 + 3);
  AtoH(iVar2,&local_1d,1);
  sVar3 = strlen(__s);
  uVar1 = sVar3 >> 1;
  if (0 < DebugLevel) {
    printk("=======Get_FwCmd==========\n");
  }
  os_alloc_mem(param_1,&local_1c,uVar1);
  if (local_1c == 0) {
    return 0;
  }
  if (uVar1 == 0) {
    if (DebugLevel < 1) goto LAB_000bcec8;
    printk("EID= 0x%x, CMD[%d] = ",local_1d,0);
    iVar2 = DebugLevel;
  }
  else {
    uVar5 = 0;
    do {
      iVar2 = local_1c + uVar5;
      uVar5 = uVar5 + 1;
      AtoH(__s,iVar2,1);
      __s = __s + 2;
    } while (uVar1 != uVar5);
    if (0 < DebugLevel) {
      printk("EID= 0x%x, CMD[%d] = ",local_1d,uVar1);
    }
    iVar6 = 0;
    iVar2 = DebugLevel;
    do {
      if (0 < iVar2) {
        printk("0x%x ",*(undefined1 *)(local_1c + iVar6));
        iVar2 = DebugLevel;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < (int)uVar1);
  }
  if (0 < iVar2) {
    printk(&_LC242);
  }
LAB_000bcec8:
  uVar4 = MtCmdSendRaw(param_1,local_1d,local_1c,uVar1,0);
  os_free_mem(local_1c);
  return uVar4;
}

