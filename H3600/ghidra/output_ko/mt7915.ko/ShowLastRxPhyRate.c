// module: mt7915.ko
// function: ShowLastRxPhyRate @ 0x152ddc
// size: 312 bytes
//

bool ShowLastRxPhyRate(undefined4 param_1,uint param_2,undefined4 param_3,uint *param_4)

{
  int iVar1;
  bool bVar2;
  undefined1 uStack_28;
  byte local_27;
  byte local_26;
  byte local_25;
  byte local_24;
  byte local_23;
  byte local_22;
  byte local_21;
  
  if (param_2 < 2) {
    if (3 < DebugLevel) {
      printk("(PHY STATE INFO)\n");
    }
    os_zero_mem(&uStack_28,8);
    iVar1 = MtCmdPhyGetRxRate(param_1,3,param_2,param_3,&uStack_28);
    *param_4 = (local_24 & 3) << 0xe | (local_26 & 0xf) << 0x10 | local_25 & 7 |
               (local_27 & 0x3f) << 8 | (local_21 & 7) << 5 | (local_22 & 1) << 4 |
               (local_23 & 1) << 3;
    bVar2 = iVar1 == 0;
    if ((3 < DebugLevel) && (printk("contention-based:\n"), 3 < DebugLevel)) {
      printk("%s: Wcid:%u Rate::%u Mode:%u Nsts:%u\n","ShowLastRxPhyRate",param_3,local_27,local_26,
             local_25);
    }
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}

