// module: mt7915.ko
// function: MtAsicInsertRepeaterRootEntryByFw @ 0x199e3c
// size: 304 bytes
//

void MtAsicInsertRepeaterRootEntryByFw
               (int param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  void *local_34;
  char local_2d;
  undefined1 uStack_2c;
  undefined2 uStack_2b;
  undefined2 uStack_29;
  undefined2 uStack_27;
  undefined1 local_25 [10];
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_34 = (void *)0x0;
  __memzero(local_25,0xd);
  __memzero(&local_2d,8);
  os_alloc_mem(param_1,&local_34,0x15);
  if (local_34 != (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("\n%s %02x:%02x:%02x:%02x:%02x:%02x-CliIdx(%d)\n","MtAsicInsertRepeaterRootEntryByFw",
             *(undefined1 *)param_3,*(undefined1 *)((int)param_3 + 1),
             *(undefined1 *)((int)param_3 + 2),*(undefined1 *)((int)param_3 + 3),
             *(undefined1 *)(param_3 + 1),*(undefined1 *)((int)param_3 + 5),param_4);
    }
    local_25[0] = 1;
    local_1b = 1;
    local_1a = 1;
    local_19 = HcGetBandByWdev(param_4 * 0x42f4 + *(int *)(&DAT_003687a8 + param_1) + 0xe0);
    local_2d = ReptGetMuarIdxByCliIdx(param_1,param_4);
    uStack_27 = *(undefined2 *)(param_3 + 1);
    local_2d = local_2d + '\x01';
    uStack_2b = (undefined2)*param_3;
    uStack_29 = (undefined2)((uint)*param_3 >> 0x10);
    memmove(local_34,local_25,0xd);
    *(uint *)((int)local_34 + 0xd) = CONCAT22(uStack_2b,CONCAT11(uStack_2c,local_2d));
    *(uint *)((int)local_34 + 0x11) = CONCAT22(uStack_27,uStack_29);
    MtCmdMuarConfigSet(param_1,local_34);
    os_free_mem(local_34);
  }
  return;
}

