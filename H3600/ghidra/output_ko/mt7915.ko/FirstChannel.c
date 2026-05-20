// module: mt7915.ko
// function: FirstChannel @ 0x103078
// size: 44 bytes
//

undefined1 FirstChannel(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  uVar1 = HcGetBandByWdev(param_2);
  puVar2 = (undefined1 *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar1);
  return *puVar2;
}

