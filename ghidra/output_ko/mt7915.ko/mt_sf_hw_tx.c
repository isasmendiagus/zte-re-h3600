// module: mt7915.ko
// function: mt_sf_hw_tx @ 0x19b324
// size: 80 bytes
//

undefined4 mt_sf_hw_tx(undefined4 param_1,int param_2)

{
  undefined1 auStack_12 [6];
  
  if ((*(uint *)(param_2 + 0x18) & 0x1000000) == 0) {
    tx_bytes_calculate();
  }
  asic_write_tmac_info(param_1,*(undefined4 *)(param_2 + 0x58),param_2);
  asic_write_tx_resource(param_1,param_2,1,auStack_12);
  return 0;
}

