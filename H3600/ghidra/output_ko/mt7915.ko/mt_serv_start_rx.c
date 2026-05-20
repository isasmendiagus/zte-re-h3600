// module: mt7915.ko
// function: mt_serv_start_rx @ 0x250f48
// size: 304 bytes
//

int mt_serv_start_rx(int *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined2 uVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  
  uVar7 = (uint)*(byte *)(param_1 + 0x133);
  iVar8 = *param_1;
  piVar6 = param_1 + uVar7 * 0x346 + 0x138;
  if ((char)param_1[0x7d1] == '\0') {
    iVar3 = mt_engine_set_auto_resp(iVar8,param_1[0x7c4],piVar6,uVar7,1);
    if (iVar3 != 0) {
      return iVar3;
    }
    if (*(byte *)(iVar8 + 0x55) == 0) {
      uVar4 = 0;
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      uVar9 = 0;
      do {
        uVar1 = uVar9 & 0xff;
        uVar2 = uVar9 & 0xff;
        uVar9 = uVar9 + 1;
        if (((int)(uint)*(ushort *)((int)param_1 + uVar7 * 0xd18 + 0x112e) >> uVar2 & 1U) != 0) {
          uVar5 = uVar5 | 1 << uVar1 & 0xffU;
        }
        uVar4 = (undefined2)uVar5;
      } while (uVar9 != *(byte *)(iVar8 + 0x55));
    }
    *(undefined2 *)((int)param_1 + uVar7 * 0xd18 + 0x112e) = uVar4;
    *(char *)(param_1 + uVar7 * 0x346 + 0x450) = (char)uVar5;
    iVar8 = mt_engine_start_rx(*param_1,piVar6,param_1[0x7c4],uVar7);
  }
  else {
    iVar8 = (**(code **)(param_1[0x7c4] + 0x70))(iVar8,uVar7,piVar6);
  }
  if (iVar8 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_start_rx",iVar8);
  }
  return iVar8;
}

