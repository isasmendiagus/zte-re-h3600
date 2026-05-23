// module: mt7915.ko
// function: hqa_set_tx_power_ext @ 0x24bc8c
// size: 256 bytes
//

undefined4 hqa_set_tx_power_ext(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_38;
  undefined4 local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  
  local_38 = param_2 + 0xc;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  FUN_002474f4(1,4,&local_38,&local_34);
  FUN_002474f4(1,4,&local_38,&local_30);
  FUN_002474f4(1,4,&local_38,&local_2c);
  FUN_002474f4(1,4,&local_38,&local_28);
  FUN_002474f4(1,4,&local_38,local_24);
  iVar2 = local_30 * 0xd18 + param_1;
  *(char *)(param_1 + 0x4cc) = (char)local_30;
  *(undefined4 *)(iVar2 + 0x1164) = local_24[0];
  *(undefined4 *)(iVar2 + 0x1168) = local_34;
  *(int *)(iVar2 + 0x1170) = local_30;
  *(undefined4 *)(iVar2 + 0x116c) = local_2c;
  *(undefined4 *)(iVar2 + 0x1174) = local_28;
  uVar1 = mt_serv_tx_power_operation(param_1,0);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

