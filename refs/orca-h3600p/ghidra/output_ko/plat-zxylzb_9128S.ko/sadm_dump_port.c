// module: plat-zxylzb_9128S.ko
// function: sadm_dump_port @ 0x17e68
// size: 404 bytes
//

void sadm_dump_port(uint param_1)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  uint local_20 [2];
  
  if (7 < param_1) {
    return;
  }
  iVar4 = *(int *)(pp_base + 0x4024);
  iVar2 = sadm_ram_get(param_1,local_20,0);
  if (-1 < iVar2) {
    printk("sadm bucket fill time 0x%x\n",iVar4);
    printk("port bucket:\n");
    pcVar5 = "enable";
    pcVar3 = pcVar5;
    if ((local_20[0] & 1) == 0) {
      pcVar3 = "disable";
    }
    printk("\tbucket %s\n",pcVar3);
    iVar2 = sadm_ram_get(param_1,local_20,2);
    uVar1 = local_20[0];
    if (-1 < iVar2) {
      iVar2 = __aeabi_uidiv(0x773594,iVar4 + 1);
      printk("\tbucket fill 0x%x(%u bps)\n",uVar1,uVar1 * iVar2);
      iVar4 = sadm_ram_get(param_1,local_20,4);
      if (-1 < iVar4) {
        printk("\tbucket max 0x%x\n",local_20[0]);
        iVar4 = sadm_ram_get(param_1,local_20,1);
        if (-1 < iVar4) {
          printk("cast bucket:\n");
          if ((local_20[0] & 1) == 0) {
            pcVar5 = "disable";
          }
          printk("\tbucket %s\n",pcVar5);
          iVar4 = sadm_ram_get(param_1,local_20,3);
          if (-1 < iVar4) {
            printk("\tbucket fill 0x%x(%u bps)\n",local_20[0],local_20[0] * iVar2);
            iVar2 = sadm_ram_get(param_1,local_20,5);
            if (-1 < iVar2) {
              printk("\tbucket max 0x%x\n",local_20[0]);
            }
          }
        }
      }
    }
  }
  return;
}

