// module: mt7915.ko
// function: Set_TxBfProfileTag_Matrix @ 0xe73e4
// size: 384 bytes
//

undefined4 Set_TxBfProfileTag_Matrix(int param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  size_t sVar7;
  byte *pbVar8;
  undefined2 *puVar9;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  
  iVar6 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_26 = 0;
  local_24 = 0;
  local_22 = 0;
  sVar7 = strlen(param_2);
  if (sVar7 == 0x11) {
    pbVar8 = (byte *)rstrtok(param_2,&_LC232);
    if (pbVar8 == (byte *)0x0) {
LAB_000e74c4:
      uVar1 = local_26._1_1_;
      uVar2 = (undefined1)local_24;
      uVar3 = local_24._1_1_;
      uVar4 = (undefined1)local_22;
      uVar5 = local_22._1_1_;
      if (*(code **)(iVar6 + 0x158) != (code *)0x0) {
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0xe,(undefined1)local_26);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0xf,uVar1);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x10,uVar2);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x11,uVar3);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x12,uVar4);
        (**(code **)(iVar6 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x13,uVar5);
        return 1;
      }
    }
    else if ((((&_ctype)[*pbVar8] & 0x44) != 0) && (((&_ctype)[pbVar8[1]] & 0x44) != 0)) {
      puVar9 = &local_26;
      do {
        AtoH(pbVar8,puVar9);
        pbVar8 = (byte *)rstrtok(0,&_LC232);
        if (pbVar8 == (byte *)0x0) goto LAB_000e74c4;
      } while ((((&_ctype)[*pbVar8] & 0x44) != 0) &&
              (puVar9 = (undefined2 *)((int)puVar9 + 1), ((&_ctype)[pbVar8[1]] & 0x44) != 0));
    }
  }
  return 0;
}

