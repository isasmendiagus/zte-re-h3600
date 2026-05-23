// module: mt7915.ko
// function: DisableAPMIMOPSv2 @ 0x84bd0
// size: 68 bytes
//

void DisableAPMIMOPSv2(undefined4 param_1)

{
  bbp_set_mmps(param_1,0);
  HcSetGreenAPActiveByBand(param_1,0,0);
  if (DebugLevel < 4) {
    return;
  }
  printk("DisableAPMIMOPSNew, 30xx reserve only one antenna\n");
  return;
}

