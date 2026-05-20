// module: mt7915.ko
// function: ba_resrc_ori_add @ 0xa5f08
// size: 640 bytes
//

undefined4
ba_resrc_ori_add(int param_1,int param_2,uint param_3,undefined2 param_4,undefined1 param_5,
                undefined2 param_6)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined1 auStack_29 [5];
  
  uVar7 = (uint)*(ushort *)(param_1 + (param_2 * 0xa60 + param_3 + 0x51500) * 2 + 4);
  iVar3 = HcGetBandByWdev(*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28));
  if (uVar7 == 0) {
    uVar4 = 0;
  }
  else {
    iVar5 = param_1 + uVar7 * 0x48;
    if (*(int *)(iVar5 + 0x1b1cc) == 2) {
      iVar8 = param_1 + 0x1c0;
      iVar6 = iVar8 + uVar7 * 0x48;
      *(undefined2 *)(iVar6 + 0x1b004) = param_4;
      *(undefined2 *)(iVar6 + 0x1b00a) = param_6;
      *(undefined1 *)(iVar5 + 0x1b1c7) = param_5;
      iVar6 = param_1 + uVar7 * 0x48;
      if ((*(uint *)(param_1 + iVar3 * 0x24 + 0xa7d18c) & 0x800) != 0) {
        *(undefined1 *)(iVar5 + 0x1b1c7) = 0;
      }
      iVar5 = param_2 * 0x14c0 + param_1;
      *(undefined4 *)(iVar6 + 0x1b1cc) = 3;
      *(int *)(param_1 + 0x2f688) = *(int *)(param_1 + 0x2f688) + 1;
      uVar2 = (ushort)(1 << (param_3 & 0xff));
      *(undefined2 *)(iVar8 + uVar7 * 0x48 + 0x1b008) =
           *(undefined2 *)
            (iVar8 + (param_3 + (uint)*(ushort *)(iVar5 + 0xa1e00) * 0x310 + 0x17a78) * 2 + 4);
      *(ushort *)(iVar5 + 0xa29e0) = uVar2 | *(ushort *)(iVar5 + 0xa29e0);
      uVar1 = ~uVar2 & *(ushort *)(iVar5 + 0xa29e2);
      *(ushort *)(iVar5 + 0xa29e6) = *(ushort *)(iVar5 + 0xa29e6) & ~uVar2;
      *(ushort *)(iVar5 + 0xa29e2) = uVar1;
      iVar3 = uVar7 * 0x48;
      if (*(char *)(iVar6 + 0x1b1c7) != '\0') {
        *(ushort *)(iVar5 + 0xa29e2) = uVar2 | uVar1;
      }
      iVar6 = iVar8 + iVar3 + 0x1b010;
      RTMPCancelTimer(iVar6,auStack_29);
      iVar5 = param_2 * 0x14c0 + param_1;
      *(undefined4 *)(param_1 + iVar3 + 0x1b1f0) = 0;
      HW_SET_BA_REC(param_1,*(undefined2 *)(iVar5 + 0xa1e00),param_3,
                    *(undefined2 *)(iVar8 + iVar3 + 0x1b008),
                    *(undefined2 *)(iVar8 + iVar3 + 0x1b004),1,1,
                    *(undefined1 *)(param_1 + iVar3 + 0x1b1c7));
      if (2 < DebugLevel) {
        iVar3 = param_1 + uVar7 * 0x48;
        printk("%s():TXBAbitmap=%x, AMSDUCap=%d, BAWinSize=%d, TimeOut=%ld\n","ba_resrc_ori_add",
               *(undefined2 *)(iVar5 + 0xa29e0),*(undefined1 *)(iVar3 + 0x1b1c7),
               *(undefined2 *)(iVar8 + uVar7 * 0x48 + 0x1b004),*(undefined4 *)(iVar3 + 0x1b1f0));
      }
      if (*(int *)(param_1 + uVar7 * 0x48 + 0x1b1f0) != 0) {
        RTMPSetTimer(iVar6);
      }
    }
    uVar4 = 1;
  }
  return uVar4;
}

