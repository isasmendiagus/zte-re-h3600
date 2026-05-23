// module: mt7915.ko
// function: bssUpdateBmcMngRate @ 0x1c2620
// size: 164 bytes
//

void bssUpdateBmcMngRate(int param_1,int param_2,undefined4 param_3)

{
  undefined2 local_18;
  undefined2 local_16;
  undefined4 local_14;
  uint local_10;
  undefined4 local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  if (1 < *(uint *)(param_2 + 4)) {
    local_14 = *(uint *)(param_2 + 0x54);
    local_10 = (uint)(*(int *)(param_1 + 0x795124) << 0x1b) >> 0x1f;
  }
  local_18 = 8;
  local_16 = 0x10;
  if (0 < DebugLevel) {
    printk("%s (BSS_INFO_BROADCAST_INFO), CmdBssInfoBmcRate.u2BcTransmit= %d, CmdBssInfoBmcRate.u2McTransmit = %d\n"
           ,"bssUpdateBmcMngRate",local_14 & 0xffff,local_14._2_2_);
  }
  AndesAppendCmdMsg(param_3,&local_18,0x10);
  return;
}

