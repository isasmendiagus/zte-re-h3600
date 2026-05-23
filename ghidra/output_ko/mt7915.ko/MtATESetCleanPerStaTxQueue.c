// module: mt7915.ko
// function: MtATESetCleanPerStaTxQueue @ 0x280dd8
// size: 228 bytes
//

undefined4 MtATESetCleanPerStaTxQueue(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_60;
  undefined1 local_5f;
  byte local_5e;
  undefined1 local_5d;
  
  iVar2 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar2 + 0x4cc);
  iVar2 = net_ad_wrap_service(param_1);
  os_zero_mem(&local_64,0x4c);
  local_5f = 0;
  local_60 = (undefined1)param_2;
  local_64 = 1;
  local_63 = 0x1c;
  local_5e = bVar1;
  uVar3 = HcGetOmacIdx(param_1,*(undefined4 *)((uint)bVar1 * 0xd18 + iVar2 + 0x79c));
  local_5d = (undefined1)uVar3;
  if (0 < DebugLevel) {
    printk("%s: StaPauseEnable:%d, StaID:%d, Band:%d, Reserved[0]:%d\n","MtATESetCleanPerStaTxQueue"
           ,local_60,local_5f,local_5e,uVar3);
  }
  uVar3 = MtCmdATETest(param_1,&local_64);
  if (0 < DebugLevel) {
    printk("%s: sta_pause_enable:%x\n","MtATESetCleanPerStaTxQueue",param_2);
  }
  return uVar3;
}

