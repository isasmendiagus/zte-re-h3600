// module: mt7915.ko
// function: Set_TxBfProfileTag_Mem @ 0xe7230
// size: 436 bytes
//

undefined4 Set_TxBfProfileTag_Mem(int param_1,char *param_2)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  size_t sVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint uVar11;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar6 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_30 = 0;
  local_2c = 0;
  sVar7 = strlen(param_2);
  if (sVar7 == 0x17) {
    pbVar8 = (byte *)rstrtok(param_2,&_LC232);
    if (pbVar8 == (byte *)0x0) {
LAB_000e730c:
      uVar11 = local_30 & 0xff;
      uVar2 = local_30._2_1_;
      uVar3 = local_30._3_1_;
      uVar10 = local_2c & 0xff;
      uVar4 = local_2c._1_1_;
      uVar1 = local_2c >> 0x10;
      uVar5 = local_2c._3_1_;
      if (*(code **)(iVar6 + 0x158) != (code *)0x0) {
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),5,local_30._1_1_);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),6,uVar3);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),7,uVar4);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),8,uVar5);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),9,uVar11);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),10,uVar2);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0xb,uVar10);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0xc,uVar1 & 0xff);
        return 1;
      }
    }
    else if ((((&_ctype)[*pbVar8] & 0x44) != 0) && (((&_ctype)[pbVar8[1]] & 0x44) != 0)) {
      puVar9 = &local_30;
      do {
        AtoH(pbVar8,puVar9);
        pbVar8 = (byte *)rstrtok(0,&_LC232);
        if (pbVar8 == (byte *)0x0) goto LAB_000e730c;
      } while ((((&_ctype)[*pbVar8] & 0x44) != 0) &&
              (puVar9 = (undefined4 *)((int)puVar9 + 1), ((&_ctype)[pbVar8[1]] & 0x44) != 0));
    }
  }
  return 0;
}

