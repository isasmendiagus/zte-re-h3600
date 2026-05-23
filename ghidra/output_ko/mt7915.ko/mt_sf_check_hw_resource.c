// module: mt7915.ko
// function: mt_sf_check_hw_resource @ 0x19b3ec
// size: 40 bytes
//

bool mt_sf_check_hw_resource(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hif_get_tx_resource_free_num
                    (*(undefined4 *)(param_1 + 0xa797a0),param_3,param_3,param_4,param_4);
  return iVar1 < 1;
}

