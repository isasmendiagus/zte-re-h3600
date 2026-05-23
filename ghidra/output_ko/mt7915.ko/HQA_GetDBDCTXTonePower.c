// module: mt7915.ko
// function: HQA_GetDBDCTXTonePower @ 0x26e914
// size: 212 bytes
//

undefined4 HQA_GetDBDCTXTonePower(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  code *pcVar2;
  int iVar3;
  uint local_1c [2];
  
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  local_1c[0] = 0;
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_GetDBDCTXTonePower",param_3,0,0);
  }
  uVar1 = *(uint *)(param_3 + 0xc);
  pcVar2 = *(code **)(iVar3 + 0x94);
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(param_1,local_1c);
    local_1c[0] = local_1c[0] << 0x18 | (local_1c[0] >> 8 & 0xff) << 0x10 |
                  (local_1c[0] >> 0x10 & 0xff) << 8 | local_1c[0] >> 0x18;
    *(uint *)(param_3 + 0xe) = local_1c[0];
    FUN_0026cdd0(param_3,param_2,6,0,uVar1);
    return 0;
  }
  FUN_0026cdd0(param_3,param_2,2,1,uVar1);
  return 1;
}

