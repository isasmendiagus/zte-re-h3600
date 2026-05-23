// module: tm.ko
// function: tm_acl_showhashCount @ 0x5fea8
// size: 148 bytes
//

undefined4
tm_acl_showhashCount(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  if ((param_1 & 0x8000) == 0) {
    uVar1 = (param_1 & 0x7fff) % 0x4400;
    printk(" hash addr 0x%x cnt %d\n",param_1,s_aclHashUsedCnt[uVar1],uVar1 + 0xc6de4,param_4);
    return 1;
  }
  uVar1 = ((param_1 & 0x7fff) + 0x208) % 0x4400;
  printk(" hash addr 0x%x cnt %d\n",param_1,s_aclHashUsedCnt[uVar1],uVar1 + 0xc6de4,param_4);
  return 1;
}

