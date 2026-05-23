// module: mt7915.ko
// function: IsIpv6DuplicateAddrDetect @ 0x225458
// size: 468 bytes
//

undefined4 IsIpv6DuplicateAddrDetect(undefined4 param_1,ushort *param_2,char *param_3)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  ushort *puVar4;
  ushort *puVar5;
  uint local_2c;
  undefined4 local_25;
  undefined4 local_21;
  undefined4 local_1d;
  undefined1 local_19;
  
  local_25 = 0x2ff;
  local_21 = 0;
  local_1d = 0x1000000;
  local_19 = 0xff;
  if ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x86dd) {
    local_2c = (uint)param_2[3];
    local_2c = (local_2c & 0xff) << 8 | (uint)(param_2[3] >> 8);
    bVar3 = (byte)param_2[4];
    if ((((*(int *)(param_2 + 7) == 0 && *(int *)(param_2 + 5) == 0) && *(int *)(param_2 + 9) == 0)
         && *(int *)(param_2 + 0xb) == 0) &&
       (iVar1 = memcmp(param_2 + 0xd,&local_25,0xd), iVar1 == 0)) {
      puVar4 = param_2 + 0x15;
      if ((bVar3 == 0x2b || (bVar3 == 0 || bVar3 == 0x2c)) || ((bVar3 == 0x33 || (bVar3 == 0x3c))))
      {
        do {
          printk("IsIpv6DuplicateAddrDetect: nextheader=0x%x, %d, %d\n",bVar3,local_2c,1);
          if (bVar3 == 0x2c) {
            local_2c = local_2c - 8;
            puVar5 = puVar4 + 4;
            bVar3 = (byte)*puVar4;
          }
          else if (bVar3 < 0x2d) {
            if ((bVar3 != 0) && (bVar3 != 0x2b)) goto LAB_002255e0;
LAB_002255fc:
            bVar3 = (byte)*puVar4;
            iVar1 = *(byte *)((int)puVar4 + 1) + 1;
            local_2c = local_2c + iVar1 * -8;
            puVar5 = puVar4 + iVar1 * 4;
          }
          else {
            if (bVar3 != 0x33) {
              if (bVar3 == 0x3c) goto LAB_002255fc;
LAB_002255e0:
              if ((int)local_2c < 1) {
                return 0;
              }
              goto LAB_0022553c;
            }
            uVar2 = (uint)*(byte *)((int)puVar4 + 1) * 4 + 8 & 0xff;
            local_2c = local_2c - uVar2;
            puVar5 = (ushort *)((int)puVar4 + uVar2);
            bVar3 = (byte)*puVar4;
          }
          puVar4 = puVar5;
        } while (0 < (int)local_2c);
      }
      else {
LAB_0022553c:
        if ((char)*puVar4 == -0x79) {
          if (0 < DebugLevel) {
            printk("THe Packet is for Ipv6DuplicateAddrDetect\n");
          }
          *param_3 = ((char)puVar4 - (char)param_2) + '\b';
          return 1;
        }
      }
    }
  }
  return 0;
}

