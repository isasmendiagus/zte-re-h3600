// module: mt7915.ko
// function: HQA_GetTxPower @ 0x26f0e4
// size: 276 bytes
//

bool HQA_GetTxPower(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  int iVar5;
  bool bVar6;
  uint local_1c;
  
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  local_1c = 0;
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_GetTxPower");
  }
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x14);
  uVar3 = *(uint *)(param_3 + 0x18);
  *(char *)(param_1 + 0xa3ae36) = (char)((uint)*(undefined4 *)(param_3 + 0x10) >> 0x18);
  pcVar4 = *(code **)(iVar5 + 0xf4);
  bVar6 = pcVar4 == (code *)0x0;
  if (!bVar6) {
    (*pcVar4)(param_1,uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                      uVar1 >> 0x18,
              uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
              uVar2 >> 0x18,
              uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
              uVar3 >> 0x18,&local_1c);
    local_1c = local_1c << 0x18 | (local_1c >> 8 & 0xff) << 0x10 | (local_1c >> 0x10 & 0xff) << 8 |
               local_1c >> 0x18;
    *(uint *)(param_3 + 0x12) = local_1c;
  }
  FUN_0026cdd0(param_3,param_2,10,bVar6);
  return bVar6;
}

