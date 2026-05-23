// module: mt7915.ko
// function: GroupChListUpdate @ 0x22d8fc
// size: 228 bytes
//

void GroupChListUpdate(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = param_2 * 0x10;
  if ((*(char *)(param_1 + iVar1 + 0xa79240) == '\0') && (*(char *)(param_3 + 5) == '\x01')) {
    *(undefined1 *)(param_1 + iVar1 + 0xa79240) = 1;
  }
  iVar2 = param_1 + param_2 * 0x10;
  uVar4 = *(uint *)(param_3 + 0x10);
  uVar3 = *(uint *)(iVar2 + 0xa79238);
  if (uVar3 < uVar4) {
    *(uint *)(iVar2 + 0xa79238) = uVar4;
  }
  if (uVar3 < uVar4) {
    uVar4 = *(uint *)(param_3 + 0x10);
  }
  if (uVar4 < *(uint *)(param_1 + iVar1 + 0xa7923c)) {
    *(uint *)(param_1 + iVar1 + 0xa7923c) = uVar4;
    *(undefined1 *)(iVar2 + 0xa79234) = *(undefined1 *)(param_3 + 1);
  }
  if (2 < DebugLevel) {
    printk("%s Update group channel list index=%d CenChannel=%d BestCtrlChannel=%d ipi_noisy=%x SkipGroup=%d\n"
           ,"GroupChListUpdate",*(undefined1 *)(param_1 + 0xa795e4),
           *(undefined1 *)(iVar2 + 0xa79235),*(undefined1 *)(iVar2 + 0xa79234),
           *(undefined4 *)(iVar2 + 0xa79238),*(undefined1 *)(param_1 + iVar1 + 0xa79240));
  }
  return;
}

