// module: mt7915.ko
// function: HQA_DBDCTXTone @ 0x26ed74
// size: 444 bytes
//

bool HQA_DBDCTXTone(int param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  code *pcVar12;
  code *pcVar13;
  
  iVar11 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_DBDCTXTone");
  }
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar3 = *(uint *)(param_3 + 0x14);
  uVar4 = *(uint *)(param_3 + 0x18);
  uVar10 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18
  ;
  uVar3 = *(uint *)(param_3 + 0x1c);
  uVar5 = *(uint *)(param_3 + 0x20);
  uVar6 = *(uint *)(param_3 + 0x24);
  uVar7 = *(uint *)(param_3 + 0x28);
  uVar8 = *(uint *)(param_3 + 0x2c);
  uVar9 = *(uint *)(param_3 + 0x30);
  *(char *)(param_1 + 0xa3ae36) = (char)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  pcVar12 = *(code **)(iVar11 + 0xf0);
  if (pcVar12 != (code *)0x0) {
    (*pcVar12)(param_1,uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                       uVar2 >> 0x18,uVar10,
               uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
               uVar4 >> 0x18,
               uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
               uVar3 >> 0x18,
               uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
               uVar5 >> 0x18,
               uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
               uVar6 >> 0x18,
               uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 |
               uVar7 >> 0x18);
  }
  pcVar13 = *(code **)(iVar11 + 0x90);
  if (pcVar13 != (code *)0x0) {
    (*pcVar13)(param_1,uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
                       uVar8 >> 0x18,
               uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
               uVar9 >> 0x18,uVar10);
  }
  bVar1 = pcVar13 == (code *)0x0 || pcVar12 == (code *)0x0;
  FUN_0026cdd0(param_3,param_2,2,bVar1);
  return bVar1;
}

