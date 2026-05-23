// module: mt7915.ko
// function: hqa_get_tx_power @ 0x24bb54
// size: 312 bytes
//

undefined4 hqa_get_tx_power(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_3c;
  uint local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  
  local_3c = param_2 + 0xc;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  FUN_002474f4(1,4,&local_3c,&local_30);
  FUN_002474f4(1,4,&local_3c,&local_34);
  FUN_002474f4(1,4,&local_3c,&local_2c);
  FUN_002474f4(1,4,&local_3c,&local_28);
  iVar2 = local_34 * 0xd18 + param_1;
  *(char *)(param_1 + 0x4cc) = (char)local_34;
  *(undefined4 *)(iVar2 + 0x1164) = local_28;
  *(int *)(iVar2 + 0x1170) = local_34;
  *(undefined4 *)(iVar2 + 0x116c) = local_30;
  *(undefined4 *)(iVar2 + 0x1174) = local_2c;
  uVar1 = mt_serv_tx_power_operation(param_1,1);
  local_24 = local_24 << 0x18 | (local_24 >> 8 & 0xff) << 0x10 | (local_24 >> 0x10 & 0xff) << 8 |
             local_24 >> 0x18;
  local_38 = *(uint *)(local_34 * 0xd18 + param_1 + 0x1168);
  sys_ad_move_mem((void *)(param_2 + 0xe),&local_24,4);
  local_38 = local_38 << 0x18 | (local_38 >> 8 & 0xff) << 0x10 | (local_38 >> 0x10 & 0xff) << 8 |
             local_38 >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0x12),&local_38,4);
  FUN_00246b90(param_2,10,uVar1);
  return uVar1;
}

