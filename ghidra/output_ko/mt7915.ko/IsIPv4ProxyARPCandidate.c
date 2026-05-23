// module: mt7915.ko
// function: IsIPv4ProxyARPCandidate @ 0x2253bc
// size: 156 bytes
//

undefined4 IsIPv4ProxyARPCandidate(undefined4 param_1,ushort *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x806) &&
      ((ushort)(param_2[4] << 8 | param_2[4] >> 8) == 1)) &&
     (iVar2 = memcmp(param_2 + 8,param_2 + 0xd,4), iVar2 != 0)) {
    uVar1 = 1;
    if (2 < DebugLevel) {
      printk("IPv4ProxyARPCandidate\n");
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

