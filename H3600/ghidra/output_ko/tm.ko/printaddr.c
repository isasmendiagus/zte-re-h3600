// module: tm.ko
// function: printaddr @ 0x5eb48
// size: 44 bytes
//

void printaddr(void)

{
  printk("0x%x   0x%x   0x%x\n",&TM_OPC_DEBUG,&TM_ACL_DEBUG,&TM_CLA_DEBUG);
  return;
}

