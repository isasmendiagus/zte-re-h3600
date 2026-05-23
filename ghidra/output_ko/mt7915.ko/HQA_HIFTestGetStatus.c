// module: mt7915.ko
// function: HQA_HIFTestGetStatus @ 0x27b148
// size: 164 bytes
//

undefined4 HQA_HIFTestGetStatus(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uStack_30;
  uint local_2c [8];
  
  puVar1 = &uStack_30;
  LoopBack_Status(param_1,local_2c);
  do {
    puVar1 = puVar1 + 1;
    uVar2 = *puVar1;
    *puVar1 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
              uVar2 >> 0x18;
  } while (puVar1 != local_2c + 6);
  *(uint *)(param_3 + 0xe) = local_2c[0];
  *(uint *)(param_3 + 0x12) = local_2c[1];
  *(uint *)(param_3 + 0x16) = local_2c[2];
  *(uint *)(param_3 + 0x1a) = local_2c[3];
  *(uint *)(param_3 + 0x1e) = local_2c[4];
  *(uint *)(param_3 + 0x22) = local_2c[5];
  *(uint *)(param_3 + 0x26) = local_2c[6];
  FUN_0026cdd0(param_3,param_2,0x1e,0);
  if (0 < DebugLevel) {
    printk(&_LC11,"HQA_HIFTestGetStatus");
  }
  return 0;
}

