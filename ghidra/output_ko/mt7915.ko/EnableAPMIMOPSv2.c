// module: mt7915.ko
// function: EnableAPMIMOPSv2 @ 0x84b8c
// size: 68 bytes
//

void EnableAPMIMOPSv2(undefined4 param_1,int param_2)

{
  bbp_set_mmps(param_1,*(undefined1 *)(param_2 + 1));
  HcSetGreenAPActiveByBand(param_1,0,1);
  if (DebugLevel < 4) {
    return;
  }
  printk("EnableAPMIMOPSNew, 30xx changes the # of antenna to 1\n");
  return;
}

