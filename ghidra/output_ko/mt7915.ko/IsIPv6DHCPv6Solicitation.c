// module: mt7915.ko
// function: IsIPv6DHCPv6Solicitation @ 0x2257d8
// size: 444 bytes
//

undefined4 IsIPv6DHCPv6Solicitation(undefined4 param_1,ushort *param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  ushort *puVar4;
  byte bVar5;
  uint local_14;
  
  if ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x86dd) {
    bVar5 = (byte)param_2[4];
    local_14 = (uint)param_2[3];
    local_14 = (local_14 & 0xff) << 8 | (uint)(param_2[3] >> 8);
    if ((bVar5 == 0 || (bVar5 == 0x2b || bVar5 == 0x2c)) || (bVar5 == 0x33 || bVar5 == 0x3c)) {
      param_2 = param_2 + 0x15;
      do {
        printk("IsIPv6DHCPv6Solicitation: nextheader=0x%x, %d, %d\n",bVar5,local_14,1);
        if (bVar5 == 0x2c) {
          local_14 = local_14 - 8;
          puVar4 = param_2 + 4;
          bVar5 = (byte)*param_2;
        }
        else {
          if (bVar5 < 0x2d) {
            if ((bVar5 != 0) && (bVar5 != 0x2b)) {
LAB_00225960:
              if ((int)local_14 < 1) {
                return 0;
              }
              goto LAB_0022585c;
            }
          }
          else {
            if (bVar5 == 0x33) {
              uVar2 = (uint)*(byte *)((int)param_2 + 1) * 4 + 8 & 0xff;
              local_14 = local_14 - uVar2;
              puVar4 = (ushort *)((int)param_2 + uVar2);
              bVar5 = (byte)*param_2;
              goto LAB_00225914;
            }
            if (bVar5 != 0x3c) goto LAB_00225960;
          }
          bVar5 = (byte)*param_2;
          iVar3 = *(byte *)((int)param_2 + 1) + 1;
          local_14 = local_14 + iVar3 * -8;
          puVar4 = param_2 + iVar3 * 4;
        }
LAB_00225914:
        param_2 = puVar4;
      } while (0 < (int)local_14);
    }
    else {
      if (bVar5 != 0x11) {
        return 0;
      }
      param_2 = param_2 + 0x15;
LAB_0022585c:
      cVar1 = (char)param_2[4];
      if ((cVar1 == '\x01' || cVar1 == '\x04') &&
         ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x222 &&
          (ushort)(param_2[1] << 8 | param_2[1] >> 8) == 0x223)) {
        if (DebugLevel < 1) {
          return 1;
        }
        printk("The Packet is DHCPv6 Solicitation,msg type=%d\n",cVar1);
        return 1;
      }
    }
  }
  return 0;
}

