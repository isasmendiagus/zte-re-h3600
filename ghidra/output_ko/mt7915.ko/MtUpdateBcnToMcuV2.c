// module: mt7915.ko
// function: MtUpdateBcnToMcuV2 @ 0x1a78f8
// size: 132 bytes
//

undefined4 MtUpdateBcnToMcuV2(undefined4 param_1,int param_2)

{
  undefined1 auStack_124 [12];
  undefined1 local_118;
  undefined1 local_117;
  undefined4 local_e8;
  undefined1 local_1e;
  
  memcpy(auStack_124,(void *)(param_2 + 0x98c),0x114);
  local_e8 = 0x8000;
  if (2 < DebugLevel) {
    printk("%s: wdev(%d) bssIdx %d, OM 0x%x, Band %d\n","MtUpdateBcnToMcuV2",
           *(undefined1 *)(param_2 + 0xc),local_117,local_118,local_1e);
  }
  AsicBssInfoUpdate(param_1,auStack_124);
  return 1;
}

