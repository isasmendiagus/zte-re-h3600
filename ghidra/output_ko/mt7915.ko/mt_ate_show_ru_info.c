// module: mt7915.ko
// function: mt_ate_show_ru_info @ 0x27bcbc
// size: 212 bytes
//

undefined4 mt_ate_show_ru_info(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  undefined2 uVar5;
  
  iVar1 = net_ad_wrap_service();
  uVar5 = 0;
  iVar1 = iVar1 + param_2 * 0xd18;
  iVar2 = net_ad_wrap_service(param_1);
  pcVar3 = (char *)(iVar1 + 0xa1c);
  piVar4 = (int *)(iVar2 + param_2 * 0xd18 + 0x758);
  do {
    piVar4 = piVar4 + 1;
    if (*pcVar3 != '\0') {
      if (*piVar4 != 0) {
        uVar5 = *(undefined2 *)(*piVar4 + 0xe0);
      }
      if (0 < DebugLevel) {
        printk("(%s) RU index[%d] in Segment[%d]: WCID[%d](0: N/A) TX mcs[%d],nss[%d], ldpc[%d], mpdu length:%d, RU MU Nss:%d\n"
               ,"mt_ate_show_ru_info",*(uint *)(pcVar3 + 0xc) >> 1,*(uint *)(pcVar3 + 0xc) & 1,uVar5
               ,*(undefined4 *)(pcVar3 + 0x10),*(undefined4 *)(pcVar3 + 0x18),
               *(undefined4 *)(pcVar3 + 0x14),*(undefined4 *)(pcVar3 + 0x20),
               *(undefined4 *)(pcVar3 + 0x28));
      }
    }
    pcVar3 = pcVar3 + 0x6c;
  } while (pcVar3 != (char *)(iVar1 + 0x10dc));
  return 0;
}

