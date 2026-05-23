// module: mt7915.ko
// function: is_udp_packet @ 0xcdd34
// size: 200 bytes
//

bool is_udp_packet(undefined4 param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_2 + 0xcc);
  if (iVar2 == 0) {
    printk(&_LC10,0x1e2a);
    dump_stack();
  }
  uVar1 = CONCAT11(*(undefined1 *)(iVar2 + 0xc),*(undefined1 *)(iVar2 + 0xd));
  if (uVar1 < 0x5dd) {
    if (*(char *)(iVar2 + 0xe) != -0x56) {
      return false;
    }
    if (*(char *)(iVar2 + 0xf) != -0x56) {
      return false;
    }
    if (*(char *)(iVar2 + 0x10) != '\x03') {
      return false;
    }
    iVar3 = iVar2 + 0x16;
    uVar1 = (ushort)*(byte *)(iVar2 + 0x15) + (ushort)*(byte *)(iVar2 + 0x14) * 0x100;
  }
  else {
    iVar3 = iVar2 + 0xe;
  }
  if (uVar1 != 0x800) {
    return false;
  }
  if (*(uint *)(param_2 + 100) < 0x23) {
    printk(&_LC55,0x1e3e);
    dump_stack();
  }
  return *(char *)(iVar3 + 9) == '\x11';
}

