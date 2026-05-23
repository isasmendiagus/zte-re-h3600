// module: mt7915.ko
// function: MtAsicRemoveRepeaterEntryByFw @ 0x199d18
// size: 292 bytes
//

void MtAsicRemoveRepeaterEntryByFw(int param_1,int param_2)

{
  byte bVar1;
  void *__dest;
  void *local_38;
  undefined4 local_33;
  undefined2 local_2f;
  char local_2d [2];
  undefined4 local_2b;
  undefined2 local_27;
  undefined1 local_25 [10];
  byte local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  bVar1 = 0;
  local_38 = (void *)0x0;
  local_33 = 0;
  local_2f = 0;
  __memzero(local_25);
  __memzero(local_2d,8);
  local_25[0] = 1;
  local_1a = 1;
  local_1b = 2;
  local_19 = HcGetBandByWdev(param_2 * 0x42f4 + *(int *)(&DAT_003687a8 + param_1) + 0xe0);
  os_alloc_mem(param_1,&local_38,(uint)local_1b * 8 + 0xd);
  if (local_38 != (void *)0x0) {
    memmove(local_38,local_25,0xd);
    __dest = (void *)((int)local_38 + 0xd);
    if (local_1b != 0) {
      do {
        local_2d[0] = ReptGetMuarIdxByCliIdx(param_1,param_2);
        local_27 = local_2f;
        local_2d[0] = local_2d[0] + bVar1;
        local_2b = local_33;
        memmove(__dest,local_2d,8);
        bVar1 = bVar1 + 1;
        __dest = (void *)((int)__dest + 8);
      } while (bVar1 < local_1b);
    }
    MtCmdMuarConfigSet(param_1,local_38);
    os_free_mem(local_38);
  }
  return;
}

