// module: mt7915.ko
// function: ShowMsgTrace @ 0x19336c
// size: 556 bytes
//

void ShowMsgTrace(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  int local_3c;
  int local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c [2];
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  os_alloc_mem(0,&local_3c,0x700);
  if (local_3c == 0) {
    if (-1 < DebugLevel) {
      printk("%s : msg_trace Allocate memory fail!!!\n","ShowMsgTrace");
    }
  }
  else {
    __memzero(local_3c,0x700);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f054,&local_38);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f05c,&local_34);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f058,local_2c);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),local_34,&local_30);
    iVar1 = local_3c;
    local_30 = local_30 & 0xff;
    local_2c[0] = local_2c[0] & 0xff;
    if (local_30 < local_2c[0]) {
      bVar7 = 0x3f < local_2c[0];
      bVar6 = local_2c[0] == 0x40;
      if (local_2c[0] < 0x41) {
        bVar7 = 0x3e < local_30;
        bVar6 = local_30 == 0x3f;
      }
      if (!bVar7 || bVar6) {
        uVar4 = local_2c[0] * 0x1c;
        iVar5 = local_38 - local_3c;
        iVar3 = local_3c;
        do {
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar3 + iVar5,iVar3);
          uVar2 = (iVar3 + 4) - iVar1;
          iVar3 = iVar3 + 4;
        } while (uVar2 <= uVar4 && uVar4 - uVar2 != 0);
        if (((0 < DebugLevel) && (printk(&_LC12), 0 < DebugLevel)) &&
           (printk("       msg trace:\n"), 0 < DebugLevel)) {
          printk("       format: t_id=task_id/task_prempt_cnt/msg_read_idx\n");
        }
        uVar4 = 0;
        do {
          uVar4 = uVar4 + 1;
          if (0 < DebugLevel) {
            iVar3 = local_3c + local_30 * 0x1c;
            iVar1 = *(int *)(iVar3 + 0x14);
            printk("       (m_%d)t_id=%x/%d/%d, m_id=%d, ts_en=%u, ts_de = %u, ts_fin=%u, wait=%d, exe=%d\n"
                   ,local_30,*(undefined4 *)(local_3c + local_30 * 0x1c),*(undefined4 *)(iVar3 + 8),
                   *(undefined4 *)(iVar3 + 0xc),*(undefined1 *)(iVar3 + 4),*(int *)(iVar3 + 0x10),
                   iVar1,*(int *)(iVar3 + 0x18),iVar1 - *(int *)(iVar3 + 0x10),
                   *(int *)(iVar3 + 0x18) - iVar1);
          }
          local_30 = local_30 + 1;
          if (local_2c[0] <= local_30) {
            local_30 = 0;
          }
        } while (uVar4 < local_2c[0]);
      }
    }
    os_free_mem(local_3c);
  }
  return;
}

