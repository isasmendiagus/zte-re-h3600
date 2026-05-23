// module: mt7915.ko
// function: alloc_rx_buf_64k @ 0x1cedd8
// size: 48 bytes
//

undefined4 alloc_rx_buf_64k(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 extraout_r1;
  uint uVar1;
  int iVar2;
  
  uVar1 = (uint)*(ushort *)(param_1 + 0x40);
  iVar2 = *(int *)(param_1 + 0x48);
  __aeabi_idivmod(uVar1 + 1,*(undefined2 *)(param_1 + 0x44),param_3,uVar1 * 3,param_4);
  *(undefined2 *)(param_1 + 0x40) = extraout_r1;
  return *(undefined4 *)(iVar2 + uVar1 * 0xc + 4);
}

