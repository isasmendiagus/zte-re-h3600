// module: mt7915.ko
// function: Set_TxBfProfileTag_SNR @ 0xe76a8
// size: 444 bytes
//

undefined4 Set_TxBfProfileTag_SNR(int param_1,char *param_2)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  int iVar7;
  size_t sVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  uint uVar11;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar7 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_30 = 0;
  local_2c = 0;
  sVar8 = strlen(param_2);
  if (sVar8 == 0xb || sVar8 == 0x17) {
    pbVar9 = (byte *)rstrtok(param_2,&_LC232);
    if (pbVar9 == (byte *)0x0) {
LAB_000e7788:
      uVar2 = local_30._1_1_;
      uVar3 = local_30._2_1_;
      uVar4 = local_30._3_1_;
      uVar11 = local_2c & 0xff;
      uVar5 = local_2c._1_1_;
      uVar6 = local_2c._2_1_;
      uVar1 = local_2c >> 0x18;
      if (*(code **)(iVar7 + 0x158) != (code *)0x0) {
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x17,local_30 & 0xff);
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x18,uVar2);
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x19,uVar3);
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x1a,uVar4);
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x1b,uVar11);
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x1c,uVar5);
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x1d,uVar6);
        (**(code **)(iVar7 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x1e,uVar1);
        return 1;
      }
    }
    else if ((((&_ctype)[*pbVar9] & 0x44) != 0) && (((&_ctype)[pbVar9[1]] & 0x44) != 0)) {
      puVar10 = &local_30;
      do {
        AtoH(pbVar9,puVar10);
        pbVar9 = (byte *)rstrtok(0,&_LC232);
        if (pbVar9 == (byte *)0x0) goto LAB_000e7788;
      } while ((((&_ctype)[*pbVar9] & 0x44) != 0) &&
              (puVar10 = (undefined4 *)((int)puVar10 + 1), ((&_ctype)[pbVar9[1]] & 0x44) != 0));
    }
  }
  return 0;
}

