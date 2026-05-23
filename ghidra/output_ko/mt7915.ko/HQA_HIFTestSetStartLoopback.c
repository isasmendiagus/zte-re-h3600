// module: mt7915.ko
// function: HQA_HIFTestSetStartLoopback @ 0x274484
// size: 484 bytes
//

undefined4 HQA_HIFTestSetStartLoopback(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  uint *puVar8;
  uint *puVar9;
  uint local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  uint local_54 [10];
  undefined4 local_2c;
  
  uVar1 = *(ushort *)(param_3 + 8);
  puVar6 = (uint *)(param_3 + 0xc);
  puVar7 = local_54;
  do {
    puVar9 = puVar7;
    puVar8 = puVar6;
    puVar6 = puVar8 + 4;
    uVar2 = puVar8[1];
    uVar3 = puVar8[2];
    puVar5 = (uint *)puVar8[3];
    *puVar9 = *puVar8;
    puVar9[1] = uVar2;
    puVar9[2] = uVar3;
    puVar9[3] = (uint)puVar5;
    puVar7 = puVar9 + 4;
  } while (puVar6 != (uint *)(param_3 + 0x2c));
  uVar3 = puVar8[5];
  uVar2 = ((uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8)) >> 2;
  if (uVar2 != 0) {
    puVar5 = local_54;
  }
  uVar4 = puVar8[6];
  puVar9[4] = *puVar6;
  puVar9[5] = uVar3;
  puVar9[6] = uVar4;
  if (uVar2 != 0) {
    puVar6 = puVar5;
    do {
      uVar3 = *puVar6;
      puVar7 = puVar6 + 1;
      *puVar6 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                uVar3 >> 0x18;
      puVar6 = puVar7;
    } while (puVar7 != puVar5 + uVar2);
  }
  *(undefined4 *)(param_1 + 0xa39fdc) = 1;
  local_80 = local_54[0];
  local_7c = local_54[1];
  local_78 = local_54[2];
  local_74 = local_54[3];
  local_70 = local_54[4];
  local_6c = local_54[5];
  local_68 = local_54[6];
  local_64 = local_54[7];
  local_60 = local_54[8];
  local_5c = local_54[9];
  local_58 = local_2c;
  if (*(char *)(param_1 + 0xa3baf9) == '\0') {
    LoopBack_Start(param_1,&local_80);
  }
  else if (1 < DebugLevel) {
    printk("%s: LB is running\n","HQA_HIFTestSetStartLoopback");
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  if (0 < DebugLevel) {
    printk("%s: start_len:%u, stop_len:%u, repeat:%u, is_default:%u, bulkout_num:%u, bulkin_num:%u, txagg_num:%u, rxagg_limit:%u, rxagg_lm:%u, rxagg_to:%u, enable_rxagg:%u\n"
           ,"HQA_HIFTestSetStartLoopback",local_54[0],local_54[1],local_54[2],local_54[3],
           local_54[4],local_54[5],local_54[6],local_54[7],local_54[8],local_54[9],local_2c);
  }
  return 0;
}

