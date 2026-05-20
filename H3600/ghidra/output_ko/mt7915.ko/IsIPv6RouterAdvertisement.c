// module: mt7915.ko
// function: IsIPv6RouterAdvertisement @ 0x225af0
// size: 396 bytes
//

undefined4 IsIPv6RouterAdvertisement(undefined4 param_1,ushort *param_2,char *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  ushort *puVar5;
  ushort *puVar6;
  uint local_24;
  
  if ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x86dd) {
    bVar4 = (byte)param_2[4];
    local_24 = (uint)param_2[3];
    uVar3 = (local_24 & 0xff) << 8 | (uint)(param_2[3] >> 8);
    if ((bVar4 == 0 || (bVar4 == 0x2b || bVar4 == 0x2c)) || (bVar4 == 0x33 || bVar4 == 0x3c)) {
      puVar5 = param_2 + 0x15;
      do {
        if (2 < DebugLevel) {
          printk("IsIPv6RouterAdvertisement: nextheader=0x%x, %d, %d\n",bVar4,uVar3,1);
        }
        if (bVar4 == 0x2c) {
          uVar3 = uVar3 - 8;
          puVar6 = puVar5 + 4;
          bVar4 = (byte)*puVar5;
        }
        else {
          if (bVar4 < 0x2d) {
            if ((bVar4 != 0) && (bVar4 != 0x2b)) {
LAB_00225c0c:
              if (uVar3 == 0) {
                return 0;
              }
              goto LAB_00225b74;
            }
          }
          else {
            if (bVar4 == 0x33) {
              uVar1 = (uint)*(byte *)((int)puVar5 + 1) * 4 + 8 & 0xff;
              uVar3 = uVar3 - uVar1;
              puVar6 = (ushort *)((int)puVar5 + uVar1);
              bVar4 = (byte)*puVar5;
              goto LAB_00225bf0;
            }
            if (bVar4 != 0x3c) goto LAB_00225c0c;
          }
          bVar4 = (byte)*puVar5;
          iVar2 = *(byte *)((int)puVar5 + 1) + 1;
          uVar3 = uVar3 + iVar2 * -8;
          puVar6 = puVar5 + iVar2 * 4;
        }
LAB_00225bf0:
        puVar5 = puVar6;
      } while (0 < (int)uVar3);
    }
    else {
      puVar5 = param_2 + 0x15;
LAB_00225b74:
      if ((char)*puVar5 == -0x7a) {
        if (2 < DebugLevel) {
          printk("The Packet is IPv6 Router Advertisement\n");
        }
        *param_3 = (char)puVar5 - ((char)param_2 + '*');
        return 1;
      }
    }
  }
  return 0;
}

