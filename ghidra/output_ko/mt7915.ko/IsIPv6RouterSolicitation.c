// module: mt7915.ko
// function: IsIPv6RouterSolicitation @ 0x225994
// size: 348 bytes
//

undefined4 IsIPv6RouterSolicitation(undefined4 param_1,ushort *param_2)

{
  uint uVar1;
  int iVar2;
  ushort *puVar3;
  ushort *puVar4;
  byte bVar5;
  uint local_14;
  
  if ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x86dd) {
    bVar5 = (byte)param_2[4];
    puVar4 = param_2 + 0x15;
    local_14 = (uint)param_2[3];
    local_14 = (local_14 & 0xff) << 8 | (uint)(param_2[3] >> 8);
    if ((bVar5 == 0 || (bVar5 == 0x2b || bVar5 == 0x2c)) || (bVar5 == 0x33 || bVar5 == 0x3c)) {
      do {
        printk("IsIPv6RouterSolicitation: nextheader=0x%x, %d, %d\n",bVar5,local_14,1);
        if (bVar5 == 0x2c) {
          local_14 = local_14 - 8;
          puVar3 = puVar4 + 4;
          bVar5 = (byte)*puVar4;
        }
        else {
          if (bVar5 < 0x2d) {
            if ((bVar5 != 0) && (bVar5 != 0x2b)) {
LAB_00225abc:
              if ((int)local_14 < 1) {
                return 0;
              }
              goto LAB_00225a10;
            }
          }
          else {
            if (bVar5 == 0x33) {
              uVar1 = (uint)*(byte *)((int)puVar4 + 1) * 4 + 8 & 0xff;
              local_14 = local_14 - uVar1;
              puVar3 = (ushort *)((int)puVar4 + uVar1);
              bVar5 = (byte)*puVar4;
              goto LAB_00225a70;
            }
            if (bVar5 != 0x3c) goto LAB_00225abc;
          }
          bVar5 = (byte)*puVar4;
          iVar2 = *(byte *)((int)puVar4 + 1) + 1;
          local_14 = local_14 + iVar2 * -8;
          puVar3 = puVar4 + iVar2 * 4;
        }
LAB_00225a70:
        puVar4 = puVar3;
      } while (0 < (int)local_14);
    }
    else {
LAB_00225a10:
      if ((char)*puVar4 == -0x7b) {
        if (DebugLevel < 1) {
          return 1;
        }
        printk("The Packet is IPv6 Router Solicitation\n");
        return 1;
      }
    }
  }
  return 0;
}

