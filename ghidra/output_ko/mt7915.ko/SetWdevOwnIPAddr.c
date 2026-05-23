// module: mt7915.ko
// function: SetWdevOwnIPAddr @ 0x113a44
// size: 96 bytes
//

undefined4 SetWdevOwnIPAddr(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  iVar2 = rtinet_aton(param_2,local_14);
  iVar1 = DebugLevel;
  if (iVar2 != 0) {
    *(undefined4 *)(param_1 + 0x4b0) = local_14[0];
    if (2 < iVar1) {
      printk("own_ip_addr=%s(%x)\n",param_2);
    }
  }
  return 1;
}

