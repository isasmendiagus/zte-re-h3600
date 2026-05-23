// module: mt7915.ko
// function: scan_extra_probe_req @ 0x143548
// size: 144 bytes
//

void scan_extra_probe_req
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               void *param_5,byte param_6)

{
  byte bVar1;
  int iVar2;
  void *__src;
  undefined1 auStack_48 [36];
  
  iVar2 = get_scan_ctrl_by_wdev(param_1,param_4);
  __memzero(auStack_48,0x20);
  bVar1 = *(byte *)(iVar2 + 3);
  __src = (void *)(iVar2 + 4);
  memcpy(auStack_48,__src,(uint)bVar1);
  *(byte *)(iVar2 + 3) = param_6;
  memcpy(__src,param_5,(uint)param_6);
  FUN_00142a84(param_1,param_2,param_3,param_4);
  *(byte *)(iVar2 + 3) = bVar1;
  memcpy(__src,auStack_48,(uint)bVar1);
  return;
}

