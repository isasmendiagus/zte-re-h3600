// module: mt7915.ko
// function: bar_process @ 0xa74c0
// size: 828 bytes
//

undefined4 bar_process(int param_1,uint param_2,uint param_3,int param_4)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  ushort uVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  
  uVar4 = (uint)(*(byte *)(param_4 + 0x11) >> 4);
  if (2 < DebugLevel) {
    printk("%s(): BAR-Wcid(%d), Tid (%d)\n","bar_process",param_2,uVar4);
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 0x140) == 0) {
    if (param_3 < 0x901) {
      if (param_3 == 0x14) {
        uVar2 = HcGetMaxStaNum(param_1);
        bVar11 = 6 < uVar4;
        if (uVar4 < 8) {
          bVar11 = uVar2 <= param_2;
        }
        if (!bVar11) {
          iVar8 = param_1 + 0x1c0;
          uVar2 = (uint)*(ushort *)(param_1 + (param_2 * 0xa60 + uVar4 + 0x514f8) * 2 + 4);
          iVar9 = iVar8 + uVar2 * 0x60;
          if (2 < DebugLevel) {
            printk("BAR(%d) : Tid (%d) - %04x:%04x\n",param_2,uVar4,
                   (uint)*(byte *)(param_4 + 0x13) << 4 | (uint)(*(byte *)(param_4 + 0x12) >> 4),
                   *(undefined2 *)(uVar2 * 0x60 + iVar8 + 0xc));
          }
          uVar1 = jiffies;
          FUN_000a4968(param_1,(uint)*(byte *)(param_4 + 0x13) << 4 |
                               (uint)(*(byte *)(param_4 + 0x12) >> 4),3,iVar9,jiffies);
          *(int *)(param_1 + 0x9dd08) = *(int *)(param_1 + 0x9dd08) + 1;
          uVar4 = *(uint *)(param_1 + 0x2f68c);
          if ((((uVar4 & 1) != 0) && (iVar3 = *(int *)(param_1 + uVar2 * 0x60 + 0x208), iVar3 != 0))
             && ((uVar4 & 2) != 0)) {
            iVar10 = *(int *)(param_1 + uVar2 * 0x60 + 0x20c) * 0x14;
            iVar5 = iVar3 + iVar10;
            *(short *)(iVar5 + 6) = (short)param_2;
            *(ushort *)(iVar3 + iVar10) =
                 (ushort)*(byte *)(param_4 + 0x13) << 4 | (ushort)(*(byte *)(param_4 + 0x12) >> 4);
            *(undefined1 *)(iVar5 + 2) = 0;
            *(undefined1 *)(iVar5 + 3) = 1;
            *(undefined2 *)(iVar5 + 4) = *(undefined2 *)(iVar8 + uVar2 * 0x60 + 0xc);
            if ((*(uint *)(param_1 + 0x2f68c) & 4) != 0) {
              *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(param_4 + 10);
              *(undefined2 *)(iVar5 + 0xc) = *(undefined2 *)(param_4 + 0xe);
              *(undefined4 *)(iVar5 + 0xe) = *(undefined4 *)(param_4 + 4);
              *(undefined2 *)(iVar5 + 0x12) = *(undefined2 *)(param_4 + 8);
            }
            iVar3 = uVar2 * 0x60 + param_1;
            *(uint *)(iVar3 + 0x20c) = *(int *)(iVar3 + 0x20c) + 1U & 0xff;
            uVar4 = *(uint *)(param_1 + 0x2f68c);
          }
          if ((uVar4 & 0x100) != 0) {
            ba_resource_dump_all(param_1,1);
          }
          if ((*(short *)(iVar8 + uVar2 * 0x60 + 0xc) -
               ((ushort)*(byte *)(param_4 + 0x13) << 4 | (ushort)(*(byte *)(param_4 + 0x12) >> 4)) &
              0x800) != 0) {
            *(int *)(param_1 + 0x9dd0c) = *(int *)(param_1 + 0x9dd0c) + 1;
            uVar6 = (ushort)*(byte *)(param_4 + 0x13) << 4 |
                    (ushort)(*(byte *)(param_4 + 0x12) >> 4);
            if (uVar6 == 0) {
              sVar7 = 0xfff;
            }
            else {
              sVar7 = uVar6 - 1;
            }
            FUN_000a46ac(param_1,iVar8,iVar9,sVar7);
            iVar3 = iVar8 + uVar2 * 0x60;
            *(short *)(iVar3 + 0xc) = sVar7;
            *(undefined4 *)(param_1 + uVar2 * 0x60 + 0x1d8) = uVar1;
            iVar8 = FUN_000a4804(param_1,iVar8,iVar9,*(undefined2 *)(iVar3 + 0xc));
            if (iVar8 != 0xffff) {
              *(short *)(iVar3 + 0xc) = (short)iVar8;
              return 1;
            }
          }
          return 1;
        }
      }
      else if (-1 < DebugLevel) {
        printk("BlockAck Request frame length size = %ld incorrect\n",param_3);
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("frame too large, size = %ld\n",param_3);
      return 0;
    }
  }
  return 0;
}

