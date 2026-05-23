// module: mt7915.ko
// function: mt_agent_set_ru_cli @ 0x24cc70
// size: 428 bytes
//

undefined4 mt_agent_set_ru_cli(int param_1,char *param_2)

{
  char *__s;
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  if (*param_2 == '\0') {
    return 0x104;
  }
  iVar3 = (uint)*(byte *)(param_1 + 0x4cc) * 0xd18;
  iVar6 = param_1 + iVar3 + 0xa1c;
  sys_ad_zero_mem(iVar6,0x6c0);
  __s = (char *)agent_trtok(param_2,&_LC90);
  if (__s != (char *)0x0) {
    uVar5 = 0;
    do {
      uVar2 = uVar5 & 0xff;
      uVar5 = uVar5 + 1;
      iVar4 = iVar6 + uVar2 * 0x6c;
      uVar1 = sscanf(__s,"%4x-%u-%u-%u-%u-%u-%u-%u-%d",iVar4 + 8,iVar4 + 4,iVar4 + 0xc,iVar4 + 0x10,
                     iVar4 + 0x14,iVar4 + 0x18,iVar4 + 0x1c,iVar4 + 0x20,iVar4 + 0x24);
      if ((uVar1 & 0xff) != 9 || *__s == '\0') {
        printk("Invalid format, %s ignored!\n",param_2);
        return 0x104;
      }
      *(undefined1 *)(iVar6 + uVar2 * 0x6c) = 1;
      if (*(int *)(iVar4 + 0x20) == 0) {
        *(undefined4 *)(iVar4 + 0x20) = *(undefined4 *)(param_1 + iVar3 + 0x6dc);
      }
      printk("%s: segment[%d]: alloc:%04x\n","mt_agent_set_ru_cli",*(uint *)(iVar4 + 0xc) & 1,
             *(undefined4 *)(iVar4 + 8));
      printk("%s:\t\t\tru_idx:%d, length:%d,\n","mt_agent_set_ru_cli",*(uint *)(iVar4 + 0xc) >> 1,
             *(undefined4 *)(iVar4 + 0x20));
      printk("%s:\t\t\talpha:%d, rate:0x%x,\n","mt_agent_set_ru_cli",*(undefined4 *)(iVar4 + 0x24),
             *(undefined4 *)(iVar4 + 0x10));
      printk("%s: \t\t\tldpc:%d, nss:%d\n","mt_agent_set_ru_cli",*(undefined4 *)(iVar4 + 0x14),
             *(undefined4 *)(iVar4 + 0x18));
      __s = (char *)agent_trtok(0,&_LC90);
    } while (__s != (char *)0x0);
  }
  return 0;
}

