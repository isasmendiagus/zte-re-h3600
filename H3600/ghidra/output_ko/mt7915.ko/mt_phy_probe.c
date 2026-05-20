// module: mt7915.ko
// function: mt_phy_probe @ 0x1c8540
// size: 140 bytes
//

undefined4 mt_phy_probe(int param_1)

{
  os_zero_mem(&_LANCHOR1,0x4c);
  *(undefined **)("Get_RBIST_IQ_Data_Proc" + param_1) = &_LANCHOR1;
  DAT_005f48b8 = 0;
  DAT_005f48d0 = MTBbpInit;
  DAT_005f48d4 = MTShowPartialBBP;
  DAT_005f48d8 = MTShowAllBBP;
  DAT_005f48dc = MTShowPartialRF;
  DAT_005f48e0 = MTShowAllRF;
  DAT_005f48e4 = MTAPAutoSelectChannel;
  DAT_005f48e8 = MTSmartCarrierSense;
  return 1;
}

