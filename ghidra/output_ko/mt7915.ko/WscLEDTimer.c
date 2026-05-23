// module: mt7915.ko
// function: WscLEDTimer @ 0x1ed084
// size: 80 bytes
//

void WscLEDTimer(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0x29e8);
  if (2 < DebugLevel) {
    printk("%s: Turn off the WPS successful LED pattern.\n","WscLEDTimer");
  }
  uVar1 = HcGetBandByWdev(*(undefined4 *)(param_2 + 0x29ec));
  RTMPSetLED(uVar2,0xc,uVar1,param_4);
  return;
}

