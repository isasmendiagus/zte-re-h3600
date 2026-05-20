// module: mt7915.ko
// function: check_copy_pkt_needed @ 0xc59f8
// size: 196 bytes
//

bool check_copy_pkt_needed(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_3 + 0xcc);
  if (iVar2 == 0) {
    printk(&_LC10,0xe7,param_3,param_4,param_4);
    dump_stack();
  }
  uVar1 = (*(ushort *)(iVar2 + 0xe) & 0xff) << 8;
  if (CONCAT11(*(undefined1 *)(iVar2 + 0xc),*(undefined1 *)(iVar2 + 0xd)) != -0x7f00) {
    if (*(char *)(param_2 + 0x8f8) != '\0') {
      return *(short *)(param_2 + 0x8fe) != 4;
    }
    return false;
  }
  if (*(char *)(param_2 + 0x8f8) == '\0') {
    return true;
  }
  if ((uVar1 & 0xfff | (uint)(*(ushort *)(iVar2 + 0xe) >> 8)) == (uint)*(ushort *)(param_2 + 0x8fa)
      && *(ushort *)(param_2 + 0x8fa) != 0) {
    return (uint)*(ushort *)(param_2 + 0x8fc) != uVar1 >> 0xd;
  }
  return false;
}

