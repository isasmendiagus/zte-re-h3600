// module: mt7915.ko
// function: IgmpGroupDelMembers @ 0x241360
// size: 268 bytes
//

void IgmpGroupDelMembers(int param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0xa77bc4);
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar1 & 0x400) == 0) {
    iVar3 = iVar4 + 0x21c;
    do {
      while (*(char *)(iVar3 + -0x18) == '\x01') {
        if (param_2 != 0) {
          _raw_spin_lock_bh(iVar4 + 0xc04);
          FUN_002400ac(iVar4,iVar3,param_2);
          _raw_spin_unlock_bh(iVar4 + 0xc04);
        }
        if (*(int *)(iVar3 + -0x14) != 1) break;
        if (iVar3 == 0) {
          if (-1 < DebugLevel) {
            printk("%s: membert list doesn\'t exist.\n","IgmpMemberCnt");
          }
        }
        else if (*(char *)(iVar3 + 8) != '\0') break;
        iVar2 = iVar3 + -8;
        iVar3 = iVar3 + 0x28;
        AsicMcastEntryDelete
                  (param_1,iVar2,*(undefined1 *)((int)param_3 + 0x999),param_2,*param_3,param_4);
        if (iVar3 == iVar4 + 0xc1c) {
          return;
        }
      }
      iVar3 = iVar3 + 0x28;
    } while (iVar3 != iVar4 + 0xc1c);
  }
  return;
}

