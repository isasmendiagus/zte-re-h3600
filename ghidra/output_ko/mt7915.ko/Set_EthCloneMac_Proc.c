// module: mt7915.ko
// function: Set_EthCloneMac_Proc @ 0xdfce0
// size: 608 bytes
//

undefined4 Set_EthCloneMac_Proc(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *__s1;
  
  *(undefined1 *)(param_1 + 0xa77bf2) = 0;
  if (*param_2 == '\0') {
    __memzero(param_1 + 0xa77bc9,6);
  }
  else {
    iVar2 = rtstrmactohex(param_2,(undefined4 *)(param_1 + 0xa77bc9));
    if (iVar2 == 0) {
      if (-1 < DebugLevel) {
        printk("Set_EthCloneMac_Proc: wrong Mac Address format or length!\n");
      }
      *(undefined4 *)(param_1 + 0xa77bc9) = *(undefined4 *)(param_1 + 0x794b5b);
      *(undefined2 *)(param_1 + 0xa77bcd) = *(undefined2 *)(param_1 + 0x794b5f);
      return 0;
    }
  }
  iVar2 = DebugLevel;
  __s1 = (undefined4 *)(param_1 + 0xa77bc9);
  if (DebugLevel < 3) {
    iVar1 = memcmp(__s1,&ZERO_MAC_ADDR,6);
    if (iVar1 != 0) {
      iVar1 = memcmp(__s1,&BROADCAST_ADDR,6);
      if (iVar1 != 0) {
LAB_000dfeb8:
        *(undefined1 *)(param_1 + 0xa77bd0) = 1;
        goto LAB_000dfd78;
      }
LAB_000dfe04:
      *__s1 = *(undefined4 *)(param_1 + 0x794b5b);
      iVar2 = DebugLevel;
      *(undefined2 *)(param_1 + 0xa77bcd) = *(undefined2 *)(param_1 + 0x794b5f);
      *(undefined1 *)(param_1 + 0xa77bd0) = 0;
      *(undefined1 *)(param_1 + 0xa77bf2) = 1;
      goto LAB_000dfd78;
    }
  }
  else {
    printk("Set_EthCloneMac_Proc(): CloneMac = %02x:%02x:%02x:%02x:%02x:%02x\n",
           *(undefined1 *)(param_1 + 0xa77bc9),*(undefined1 *)(param_1 + 0xa77bca),
           *(undefined1 *)(param_1 + 0xa77bcb),*(undefined1 *)(param_1 + 0xa77bcc),
           *(undefined1 *)(param_1 + 0xa77bcd),*(undefined1 *)(param_1 + 0xa77bce));
    iVar2 = memcmp(__s1,&ZERO_MAC_ADDR,6);
    if (iVar2 != 0) {
      iVar2 = memcmp(__s1,&BROADCAST_ADDR,6);
      if (iVar2 != 0) {
        iVar2 = DebugLevel;
        if (2 < DebugLevel) {
          printk("Use user assigned spcific Mac address for cloned MAC!\n");
          iVar2 = DebugLevel;
        }
        goto LAB_000dfeb8;
      }
      if (2 < DebugLevel) {
        printk("Use first frowarded Packet\'s source Mac for cloned MAC!\n");
      }
      goto LAB_000dfe04;
    }
    if (2 < DebugLevel) {
      printk("Use our default Mac address for cloned MAC!\n");
    }
  }
  *__s1 = *(undefined4 *)(param_1 + 0x794b5b);
  iVar2 = DebugLevel;
  *(undefined2 *)(param_1 + 0xa77bcd) = *(undefined2 *)(param_1 + 0x794b5f);
  *(undefined1 *)(param_1 + 0xa77bd0) = 1;
LAB_000dfd78:
  if (2 < iVar2) {
    printk("Set_EthCloneMac_Proc(): After ajust, CloneMac = %02x:%02x:%02x:%02x:%02x:%02x\n",
           *(undefined1 *)(param_1 + 0xa77bc9),*(undefined1 *)(param_1 + 0xa77bca),
           *(undefined1 *)(param_1 + 0xa77bcb),*(undefined1 *)(param_1 + 0xa77bcc),
           *(undefined1 *)(param_1 + 0xa77bcd),*(undefined1 *)(param_1 + 0xa77bce));
  }
  return 1;
}

