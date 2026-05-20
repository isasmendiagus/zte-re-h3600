// module: mt7915.ko
// function: UAPSD_QueueStatusGet @ 0x1de778
// size: 196 bytes
//

/* WARNING: Removing unreachable block (ram,0x001de828) */
/* WARNING: Removing unreachable block (ram,0x001de834) */

void UAPSD_QueueStatusGet
               (undefined4 param_1,int param_2,undefined1 *param_3,undefined1 *param_4,
               undefined1 *param_5,undefined1 *param_6)

{
  *param_3 = 0;
  *param_4 = 0;
  *param_5 = 0;
  *param_6 = 0;
  if (param_2 != 0) {
    _raw_spin_lock_bh();
    if (*(int *)(param_2 + 0xb18) != 0) {
      *param_3 = 1;
    }
    if (*(int *)(param_2 + 0xb28) != 0) {
      *param_4 = 1;
    }
    if (*(int *)(param_2 + 0xb38) != 0) {
      *param_5 = 1;
    }
    if (*(int *)(param_2 + 0xb48) != 0) {
      *param_6 = 1;
    }
    _raw_spin_unlock_bh();
    return;
  }
  return;
}

