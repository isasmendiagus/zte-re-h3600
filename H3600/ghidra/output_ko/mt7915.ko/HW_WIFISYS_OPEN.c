// module: mt7915.ko
// function: HW_WIFISYS_OPEN @ 0xb1d14
// size: 224 bytes
//

undefined4 HW_WIFISYS_OPEN(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  uint uStack_5c;
  uint local_58;
  uint uStack_54;
  uint uStack_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  
  uStack_5c = *(uint *)(((uint)&local_68 & 0xffffe000) + 4) & 0x1fff00;
  if (uStack_5c == 0) {
    local_3c = 2000;
    local_34 = 0x214;
    local_68 = 2000;
    uStack_60 = 0x214;
    local_44 = 0x2b;
    local_48 = 5;
    local_40 = CONCAT31(local_40._1_3_,1);
    uStack_64 = param_2;
    local_58 = uStack_5c;
    uStack_54 = uStack_5c;
    uStack_50 = uStack_5c;
    local_38 = param_2;
    local_30 = uStack_5c;
    local_2c = uStack_5c;
    local_28 = uStack_5c;
    local_24 = uStack_5c;
    uVar1 = HwCtrlEnqueueCmd(param_1,5,0x2b,local_40);
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

