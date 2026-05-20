// module: mt7915.ko
// function: mt_serv_set_bss_info @ 0x252b84
// size: 40 bytes
//

void mt_serv_set_bss_info(undefined4 *param_1,undefined4 param_2)

{
  net_ad_set_bss_info(*param_1,param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138,
                      (uint)*(byte *)(param_1 + 0x133),param_2);
  return;
}

