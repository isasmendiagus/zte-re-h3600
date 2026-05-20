// module: idmfdb.ko
// function: print_idm_multicast_cnt @ 0x11020
// size: 260 bytes
//

int print_idm_multicast_cnt(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = &g_mtrans_dbg_cnt;
  iVar3 = 0;
  do {
    if (*pcVar2 != '\0') {
      if (0 < param_3) {
        iVar1 = snprintf((char *)(param_2 + iVar3),param_3 - iVar3,
                         "%10s: mcast %02x:%02x:%02x:%02x:%02x:%02x to %02x:%02x:%02x:%02x:%02x:%02x\n\t  %10lld pkt, %10lld bytes\n"
                         ,*(undefined4 *)(*(int *)(pcVar2 + 0x18) + 0x14),(uint)(byte)pcVar2[0xe],
                         (uint)(byte)pcVar2[0xf],(uint)(byte)pcVar2[0x10],(uint)(byte)pcVar2[0x11],
                         (uint)(byte)pcVar2[0x12],(uint)(byte)pcVar2[0x13],(uint)(byte)pcVar2[8],
                         (uint)(byte)pcVar2[9],(uint)(byte)pcVar2[10],(uint)(byte)pcVar2[0xb],
                         (uint)(byte)pcVar2[0xc],(uint)(byte)pcVar2[0xd],
                         *(undefined4 *)(pcVar2 + 0x20),*(undefined4 *)(pcVar2 + 0x24),
                         *(undefined4 *)(pcVar2 + 0x28),*(undefined4 *)(pcVar2 + 0x2c));
        iVar3 = iVar3 + iVar1;
      }
    }
    pcVar2 = pcVar2 + 0x30;
  } while (pcVar2 != g_PortMacInfo);
  if (0 < param_3) {
    iVar1 = snprintf((char *)(param_2 + iVar3),param_3 - iVar3,"\n");
    iVar3 = iVar3 + iVar1;
  }
  return iVar3;
}

