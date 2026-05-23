// module: mt7915.ko
// function: hqa_get_tx_info @ 0x24731c
// size: 136 bytes
//

undefined4 hqa_get_tx_info(int *param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint local_18;
  uint local_14;
  
  local_18 = 0;
  local_14 = 0;
  uVar1 = mt_serv_get_tx_info();
  uVar2 = param_1[0x447];
  local_18 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18;
  if (*(char *)(*param_1 + 0x34) != '\0') {
    uVar2 = param_1[0x78d];
    local_14 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
               uVar2 >> 0x18;
  }
  sys_ad_move_mem((void *)(param_2 + 0xe),&local_18,4);
  sys_ad_move_mem((void *)(param_2 + 0x12),&local_14,4);
  FUN_00246b90(param_2,10,uVar1);
  return uVar1;
}

