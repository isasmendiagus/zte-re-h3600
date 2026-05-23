// module: mt7915.ko
// function: mt_serv_get_rxv_content_len @ 0x251ccc
// size: 100 bytes
//

undefined4
mt_serv_get_rxv_content_len(undefined4 *param_1,uint param_2,undefined4 param_3,short *param_4)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(param_1[0x7c4] + 0xa4))
                    (*param_1,1 << (param_2 & 0xff) & 0xff,param_3,param_4,param_4);
  switch(param_2) {
  case 0:
  case 3:
    *param_4 = *param_4 * 2 + 6;
    return uVar1;
  case 1:
  case 2:
    *param_4 = *param_4 * 0x11 + 0x24;
    return uVar1;
  default:
    return 0x105;
  }
}

