// module: mt7915.ko
// function: mt_serv_set_txbf_sa @ 0x252b4c
// size: 56 bytes
//

void mt_serv_set_txbf_sa(undefined4 *param_1,undefined4 param_2)

{
  net_ad_set_device_info
            (*param_1,param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138,param_2,
             (uint)*(byte *)(param_1 + 0x133),1);
  return;
}

