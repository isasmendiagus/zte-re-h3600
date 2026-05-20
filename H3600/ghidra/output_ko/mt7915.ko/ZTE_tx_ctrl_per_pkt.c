// module: mt7915.ko
// function: ZTE_tx_ctrl_per_pkt @ 0x15bb58
// size: 384 bytes
//

void ZTE_tx_ctrl_per_pkt(int param_1,int param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = (uint)*(byte *)(param_2 + 0xc);
  iVar4 = uVar5 * 0x5834 + param_1;
  if ("Query::OID_802_11_GET_COUNTRY_CODE\n"[iVar4 + 0x21] != '\0') {
    *(char *)(param_3 + 0x95) = "Query::OID_802_11_GET_COUNTRY_CODE\n"[iVar4 + 0x21];
    *(char *)(param_3 + 0x96) =
         (char)*(undefined4 *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 4);
  }
  iVar4 = uVar5 * 0x5834 + param_1;
  if ("Query::OID_802_11_GET_COUNTRY_CODE\n"[iVar4 + 0x22] != '\0') {
    *(char *)(param_3 + 0x97) = "Query::OID_802_11_GET_COUNTRY_CODE\n"[iVar4 + 0x22];
    *(char *)(param_3 + 0x98) =
         (char)*(undefined4 *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 8);
    *(char *)(param_3 + 0x99) =
         (char)*(undefined4 *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 0xc);
  }
  iVar4 = uVar5 * 0x5834 + param_1;
  if ("Query::OID_802_11_GET_COUNTRY_CODE\n"[iVar4 + 0x23] != '\0') {
    *(char *)(param_3 + 0x9a) = "Query::OID_802_11_GET_COUNTRY_CODE\n"[iVar4 + 0x23];
    bVar1 = *(byte *)(param_3 + 0x9d);
    bVar2 = (byte)((*(uint *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 0x10) & 0xf) <<
                  4);
    *(byte *)(param_3 + 0x9d) = bVar1 & 0xf | bVar2;
    bVar3 = (byte)((*(uint *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 0x14) & 1) << 3)
    ;
    *(byte *)(param_3 + 0x9d) = bVar1 & 7 | bVar2 | bVar3;
    *(byte *)(param_3 + 0x9d) =
         bVar1 & 1 | bVar2 | bVar3 |
         (byte)((*(uint *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 0x18) & 3) << 1);
    *(ushort *)(param_3 + 0x9c) =
         *(ushort *)(param_3 + 0x9c) & 0xfe7f |
         (ushort)((*(uint *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 0x1c) & 3) << 7);
    bVar1 = *(byte *)(param_3 + 0x9c);
    bVar2 = (byte)((*(uint *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 0x20) & 1) << 6)
    ;
    *(byte *)(param_3 + 0x9c) = bVar1 & 0xbf | bVar2;
    bVar3 = (byte)((*(uint *)("Query::unknown IOCTL\'s subcmd = 0x%08x\n" + iVar4 + 0x24) & 3) << 4)
    ;
    *(byte *)(param_3 + 0x9c) = bVar1 & 0x8f | bVar2 | bVar3;
    *(byte *)(param_3 + 0x9c) =
         bVar1 & 0x80 | bVar2 | bVar3 |
         (byte)*(undefined4 *)("%s: Allocate memory fail!!!\n" + iVar4) & 0xf;
  }
  iVar4 = uVar5 * 0x5834 + param_1;
  if ("Query::unknown IOCTL\'s subcmd = 0x%08x\n"[iVar4] != '\0') {
    *(char *)(param_3 + 0x9e) = "Query::unknown IOCTL\'s subcmd = 0x%08x\n"[iVar4];
    *(char *)(param_3 + 0xa1) = "%s: Allocate memory fail!!!\n"[iVar4 + 4];
  }
  iVar4 = uVar5 * 0x5834 + param_1;
  if ("Query::unknown IOCTL\'s subcmd = 0x%08x\n"[iVar4 + 1] != '\0') {
    *(char *)(param_3 + 0x9f) = "Query::unknown IOCTL\'s subcmd = 0x%08x\n"[iVar4 + 1];
    *(char *)(param_3 + 0xa2) = (char)*(undefined4 *)("%s: Allocate memory fail!!!\n" + iVar4 + 8);
  }
  if ("Query::unknown IOCTL\'s subcmd = 0x%08x\n"[uVar5 * 0x5834 + param_1 + 2] != '\0') {
    *(char *)(param_3 + 0xa0) =
         "Query::unknown IOCTL\'s subcmd = 0x%08x\n"[uVar5 * 0x5834 + param_1 + 2];
    *(undefined1 *)(param_3 + 0x87) = 1;
    *(undefined1 *)(param_3 + 0x86) = 0x22;
  }
  return;
}

