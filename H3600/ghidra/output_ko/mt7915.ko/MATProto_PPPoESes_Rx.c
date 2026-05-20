// module: mt7915.ko
// function: MATProto_PPPoESes_Rx @ 0x7b190
// size: 316 bytes
//

ushort * MATProto_PPPoESes_Rx(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  ushort *puVar3;
  
  iVar2 = *(int *)(param_2 + 0xcc);
  uVar1 = (uint)(*(ushort *)(param_3 + 2) >> 8);
  if (**(char **)(param_1 + 0x10) == '\0') {
    return (ushort *)0x0;
  }
  puVar3 = *(ushort **)(*(char **)(param_1 + 0x10) + (uVar1 & 0x3f) * 4 + 4);
  while( true ) {
    if (puVar3 == (ushort *)0x0) {
      return (ushort *)0x0;
    }
    if (((uint)*puVar3 == ((*(ushort *)(param_3 + 2) & 0xff) << 8 | uVar1)) &&
       (((((*(char *)(iVar2 + 7) == *(char *)((int)puVar3 + 3) &&
           (char)puVar3[1] == *(char *)(iVar2 + 6)) && (char)puVar3[2] == *(char *)(iVar2 + 8)) &&
         *(char *)(iVar2 + 9) == *(char *)((int)puVar3 + 5)) &&
        *(char *)(iVar2 + 10) == (char)puVar3[3]) &&
        *(char *)(iVar2 + 0xb) == *(char *)((int)puVar3 + 7))) break;
    puVar3 = *(ushort **)(puVar3 + 10);
  }
  if (2 < DebugLevel) {
    printk("%s(): find it! dstMac=%02x:%02x:%02x:%02x:%02x:%02x\n","getInMacByOutMacFromSesMacTb",
           (char)puVar3[4],*(undefined1 *)((int)puVar3 + 9),(char)puVar3[5],
           *(undefined1 *)((int)puVar3 + 0xb),(char)puVar3[6],*(undefined1 *)((int)puVar3 + 0xd));
  }
  *(undefined4 *)(puVar3 + 8) = jiffies;
  return puVar3 + 4;
}

