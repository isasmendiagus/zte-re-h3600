// module: mt7915.ko
// function: ShowRxPhyRate @ 0x1530e8
// size: 568 bytes
//

bool ShowRxPhyRate(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  undefined8 uVar5;
  undefined1 auStack_a4 [20];
  undefined1 auStack_90 [20];
  undefined1 auStack_7c [20];
  undefined1 auStack_68 [20];
  undefined1 auStack_54 [20];
  undefined1 auStack_40 [20];
  undefined1 auStack_2c [20];
  
  memcpy(auStack_90,&DAT_0029a44c,0x78);
  if ((uint)*(byte *)(*param_1 + 0x3c) < (uint)*(byte *)((int)param_1 + 0x2b7242)) {
    HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    uVar5 = HcGetBandByWdev(param_1 + 0xdb6d6);
    uVar3 = (uint)uVar5;
    if (uVar3 < 2) {
      if (0 < DebugLevel) {
        printk("(PHY STATE INFO)\n",(int)((ulonglong)uVar5 >> 0x20),uVar3);
      }
      if (param_3 == 0) {
        iVar1 = MtCmdPhyShowInfo(param_1,1,uVar3);
        bVar2 = iVar1 == 0;
      }
      else {
        bVar2 = false;
      }
      uVar3 = param_1[0xa1688];
      uVar4 = uVar3 & 0x7f;
      switch((uint)(param_1[0xa1689] << 0x18) >> 0x1c) {
      case 0:
        uVar4 = uVar3 & 3;
        os_move_mem(auStack_a4,auStack_90,0x14);
        break;
      case 1:
        uVar4 = uVar3 & 0xf;
        os_move_mem(auStack_a4,auStack_7c,0x14);
        if (uVar4 != 0xb) {
          if (uVar4 == 0xf) {
            uVar4 = 1;
          }
          else if (uVar4 == 10) {
            uVar4 = 2;
          }
          else if (uVar4 == 0xe) {
            uVar4 = 3;
          }
          else if (uVar4 == 9) {
            uVar4 = 4;
          }
          else if (uVar4 == 0xd) {
            uVar4 = 5;
          }
          else if (uVar4 == 8) {
            uVar4 = 6;
          }
          else if (uVar4 == 0xc) {
            uVar4 = 7;
          }
          else {
            uVar4 = 0;
          }
          break;
        }
      default:
        uVar4 = 0;
        break;
      case 2:
        os_move_mem(auStack_a4,auStack_68,0x14);
        break;
      case 3:
        os_move_mem(auStack_a4,auStack_54,0x14);
        break;
      case 4:
        uVar4 = uVar3 & 0xf;
        os_move_mem(auStack_a4,auStack_40,0x14);
        break;
      case 8:
      case 9:
      case 10:
      case 0xb:
        uVar4 = uVar3 & 0xf;
        os_move_mem(auStack_a4,auStack_2c,0x14);
      }
      if ((0 < DebugLevel) && (printk("contention-based:\n"), 0 < DebugLevel)) {
        printk("rx rate: %s(%dNss M%d)\n",auStack_a4,((uVar3 << 0x16) >> 0x1d) + 1,uVar4);
        return bVar2;
      }
      return bVar2;
    }
  }
  return false;
}

