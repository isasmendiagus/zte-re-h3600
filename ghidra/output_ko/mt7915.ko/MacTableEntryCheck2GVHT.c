// module: mt7915.ko
// function: MacTableEntryCheck2GVHT @ 0x148d60
// size: 172 bytes
//

void MacTableEntryCheck2GVHT(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined8 uVar2;
  
  if (param_2 == (int *)0x0) {
    return;
  }
  if (*param_2 == 0) {
    return;
  }
  if (*(char *)((int)param_2 + 0xbfd) != '\0') {
    return;
  }
  uVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = param_2[2];
  if (iVar1 == 0) {
    return;
  }
  if (*(char *)(param_1 + 0x79505f) == '\0') {
    return;
  }
  if (*(char *)((int)uVar2 + 0x6c) == '\0') {
    return;
  }
  if ((*(ushort *)(iVar1 + 0x18) & 8) == 0) {
    return;
  }
  if (0xd < *(byte *)(iVar1 + 0x1a)) {
    return;
  }
  *(undefined1 *)((int)param_2 + 0xbfd) = 1;
  if (DebugLevel < 4) {
    return;
  }
  printk("Peer has 256QAM CAP support for 2.4G!\n",(int)((ulonglong)uVar2 >> 0x20),1,param_4);
  return;
}

