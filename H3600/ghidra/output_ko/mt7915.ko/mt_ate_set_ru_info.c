// module: mt7915.ko
// function: mt_ate_set_ru_info @ 0x28c868
// size: 700 bytes
//

undefined4 mt_ate_set_ru_info(undefined4 param_1,int param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint local_24;
  
  uVar8 = 0;
  local_24 = 0;
  iVar2 = net_ad_wrap_service();
  iVar3 = net_ad_wrap_service(param_1);
  if (*param_3 != '\0') {
    iVar2 = iVar2 + param_2 * 0xd18;
    iVar3 = iVar3 + param_2 * 0xd18 + 0xa1c;
    __memzero(iVar3,0x6c0);
    pcVar4 = (char *)rstrtok(param_3,&_LC310);
    if (pcVar4 == (char *)0x0) {
LAB_0028ca14:
      pcVar4 = (char *)(iVar2 + 0x10dc);
      do {
        pcVar4 = pcVar4 + 1;
        if (*pcVar4 == -1) {
          *pcVar4 = 'q';
        }
      } while (pcVar4 != (char *)(iVar2 + 0x10e4));
      iVar3 = 0;
      do {
        if (0 < DebugLevel) {
          printk("%s: allocation[%d] = 0x%x\n","mt_ate_set_ru_info",iVar3,
                 *(undefined1 *)(iVar2 + 0x10dd + iVar3));
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 != 8);
      return 0;
    }
    cVar1 = *pcVar4;
    while (cVar1 != '\0') {
      iVar7 = iVar3 + (uVar8 & 0xff) * 0x6c;
      sscanf(pcVar4,"%4x-%u-%u-%u-%u-%u-%u-%u-%d-%u",&local_24,iVar7 + 8,iVar7 + 0xc,iVar7 + 0x10,
             iVar7 + 0x14,iVar7 + 0x18,iVar7 + 0x1c,iVar7 + 0x20,iVar7 + 0x24,iVar7 + 0x28);
      *(undefined1 *)(iVar3 + (uVar8 & 0xff) * 0x6c) = 1;
      if (*(int *)(iVar7 + 0x20) == 0) {
        iVar5 = net_ad_wrap_service(param_1);
        iVar6 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar7 + 0x20) =
             *(undefined4 *)((uint)*(byte *)(iVar6 + 0x4cc) * 0xd18 + iVar5 + 0x6dc);
      }
      mt_ate_add_allocation(iVar2 + 0x10dd,local_24 & 0xff,*(uint *)(iVar7 + 0xc) & 1);
      if (0 < DebugLevel) {
        printk("%s: ru_segment[%d]: allocation:%04x, ru_idx:%d, mpdu length:%d, alpha:%d\n\t\t\trate:0x%x, ldpc:%d, nss:%d, ru_mu_nss:%d\n"
               ,"mt_ate_set_ru_info",*(uint *)(iVar7 + 0xc) & 1,local_24,*(uint *)(iVar7 + 0xc) >> 1
               ,*(undefined4 *)(iVar7 + 0x20),*(undefined4 *)(iVar7 + 0x24),
               *(undefined4 *)(iVar7 + 0x10),*(undefined4 *)(iVar7 + 0x14),
               *(undefined4 *)(iVar7 + 0x18),*(undefined4 *)(iVar7 + 0x28));
      }
      uVar8 = uVar8 + 1;
      pcVar4 = (char *)rstrtok(0,&_LC310);
      if (pcVar4 == (char *)0x0) goto LAB_0028ca14;
      cVar1 = *pcVar4;
    }
    if (DebugLevel < 0) {
      return 1;
    }
    printk("Invalid format, %s ignored\n",pcVar4);
    if (DebugLevel < 0) {
      return 1;
    }
    printk(
          "<1.allocation>-<2.aid>-<3.ru_index>-<4.rate>-<5.lepc>-<6.nss>-<7.start_sp_st>-<8.mpdu_length>-<9.alpha>-<10.ru_mu_nss>\n"
          );
  }
  if (-1 < DebugLevel) {
    printk("Invalid input string\n");
  }
  return 1;
}

