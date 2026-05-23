// module: mt7915.ko
// function: HW_WIFISYS_PEER_LINKDOWN @ 0xb1d50
// size: 12 bytes
//

undefined4 HW_WIFISYS_PEER_LINKDOWN(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  uint uStack_5c;
  uint uStack_58;
  uint uStack_54;
  uint uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  uint uStack_30;
  uint uStack_2c;
  uint uStack_28;
  uint uStack_24;
  
  uStack_5c = *(uint *)(((uint)&uStack_68 & 0xffffe000) + 4) & 0x1fff00;
  if (uStack_5c == 0) {
    uStack_3c = 2000;
    uStack_34 = 0x214;
    uStack_68 = 2000;
    uStack_60 = 0x214;
    uStack_44 = 0x2e;
    uStack_48 = 5;
    uStack_40 = CONCAT31(uStack_40._1_3_,1);
    uStack_64 = param_2;
    uStack_58 = uStack_5c;
    uStack_54 = uStack_5c;
    uStack_50 = uStack_5c;
    uStack_38 = param_2;
    uStack_30 = uStack_5c;
    uStack_2c = uStack_5c;
    uStack_28 = uStack_5c;
    uStack_24 = uStack_5c;
    uVar1 = HwCtrlEnqueueCmd(param_1,5,0x2e,uStack_40);
  }
  else {
    if (2 < DebugLevel) {
      printk("%s(): do not equeue wifi sys layer API to dispatch context!\n","wifi_sys_queue_work");
    }
    dump_stack();
    uVar1 = 0;
  }
  return uVar1;
}

