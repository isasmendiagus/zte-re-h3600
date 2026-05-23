// module: mt7915.ko
// function: hqa_get_rx_statistics_leg @ 0x246ea0
// size: 124 bytes
//

undefined4 hqa_get_rx_statistics_leg(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  void *__dest;
  void *pvVar3;
  uint *puVar4;
  uint local_40c;
  uint auStack_408 [126];
  undefined1 auStack_210 [504];
  
  uVar1 = mt_serv_get_rx_stat_leg(param_1,auStack_210);
  sys_ad_move_mem(auStack_408,auStack_210,0x1f8);
  __dest = (void *)(param_2 + 0xe);
  puVar4 = auStack_408;
  do {
    uVar2 = *puVar4;
    pvVar3 = (void *)((int)__dest + 4);
    local_40c = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
    sys_ad_move_mem(__dest,&local_40c,4);
    __dest = pvVar3;
    puVar4 = puVar4 + 1;
  } while (pvVar3 != (void *)(param_2 + 0x206));
  FUN_00246b90(param_2,0x1fa,uVar1);
  return uVar1;
}

