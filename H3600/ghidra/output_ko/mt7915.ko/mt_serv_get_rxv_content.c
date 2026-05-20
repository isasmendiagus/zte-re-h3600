// module: mt7915.ko
// function: mt_serv_get_rxv_content @ 0x251a00
// size: 60 bytes
//

void mt_serv_get_rxv_content(undefined4 *param_1)

{
  if (*(char *)(param_1 + 0x7d1) != '\0') {
                    /* WARNING: Could not recover jumptable at 0x00251a28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1[0x7c4] + 0x120))(*param_1);
    return;
  }
  net_ad_get_rxv_content(*param_1,*(undefined1 *)(param_1 + 0x133));
  return;
}

