// module: mt7915.ko
// function: IsIPv6ProxyARPCandidate @ 0x225630
// size: 420 bytes
//

undefined4 IsIPv6ProxyARPCandidate(undefined4 param_1,ushort *param_2)

{
  int iVar1;
  uint uVar2;
  ushort *puVar3;
  byte bVar4;
  uint local_24;
  undefined4 local_1d;
  undefined4 local_19;
  undefined4 local_15;
  undefined1 local_11;
  
  local_1d = 0x2ff;
  local_19 = 0;
  local_15 = 0x1000000;
  local_11 = 0xff;
  if ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x86dd) {
    local_24 = (uint)param_2[3];
    bVar4 = (byte)param_2[4];
    local_24 = (local_24 & 0xff) << 8 | (uint)(param_2[3] >> 8);
    iVar1 = memcmp(param_2 + 0xd,&local_1d,0xd);
    if (iVar1 == 0) {
      param_2 = param_2 + 0x15;
      if (((bVar4 == 0x2b || (bVar4 == 0 || bVar4 == 0x2c)) || (bVar4 == 0x33)) || (bVar4 == 0x3c))
      {
        do {
          printk("IsIPv6ProxyARPCandidate: nextheader=0x%x, %d, %d\n",bVar4,local_24,1);
          if (bVar4 == 0x2c) {
            local_24 = local_24 - 8;
            puVar3 = param_2 + 4;
            bVar4 = (byte)*param_2;
          }
          else if (bVar4 < 0x2d) {
            if ((bVar4 != 0) && (bVar4 != 0x2b)) goto LAB_00225798;
LAB_002257b4:
            bVar4 = (byte)*param_2;
            iVar1 = *(byte *)((int)param_2 + 1) + 1;
            local_24 = local_24 + iVar1 * -8;
            puVar3 = param_2 + iVar1 * 4;
          }
          else {
            if (bVar4 != 0x33) {
              if (bVar4 == 0x3c) goto LAB_002257b4;
LAB_00225798:
              if ((int)local_24 < 1) {
                return 0;
              }
              goto LAB_002256f0;
            }
            uVar2 = (uint)*(byte *)((int)param_2 + 1) * 4 + 8 & 0xff;
            local_24 = local_24 - uVar2;
            puVar3 = (ushort *)((int)param_2 + uVar2);
            bVar4 = (byte)*param_2;
          }
          param_2 = puVar3;
        } while (0 < (int)local_24);
      }
      else {
LAB_002256f0:
        if ((char)*param_2 == -0x79) {
          if (DebugLevel < 3) {
            return 1;
          }
          printk("The Packet is IPv6ProxyARPCandidate\n");
          return 1;
        }
      }
    }
  }
  return 0;
}

