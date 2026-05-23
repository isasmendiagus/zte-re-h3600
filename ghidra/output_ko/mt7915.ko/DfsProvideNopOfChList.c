// module: mt7915.ko
// function: DfsProvideNopOfChList @ 0x237558
// size: 392 bytes
//

void DfsProvideNopOfChList(int param_1,undefined1 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 *__dest;
  undefined1 *puVar6;
  uint uVar7;
  int iVar8;
  undefined1 *puVar9;
  undefined1 local_a0 [2];
  undefined2 local_9e [61];
  
  __dest = param_2 + 4;
  uVar5 = 0;
  puVar6 = param_2;
  do {
    os_zero_mem(local_a0,0x78);
    iVar2 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),
                                (int)puVar6 - (int)param_2 & 0xff);
    if (*(char *)(iVar2 + 0x49c) != '\0') {
      iVar8 = (uint)(byte)(*(char *)(iVar2 + 0x49c) - 1) * 0x14 + iVar2 + 0x20;
      iVar3 = iVar2 + 0xc;
      do {
        while( true ) {
          iVar1 = uVar5 * 4;
          if (*(short *)(iVar2 + 0xc) == 0) break;
          uVar5 = uVar5 + 1 & 0xff;
          local_a0[iVar1] = *(undefined1 *)(iVar3 + -0xc);
          local_a0[iVar1 + 1] = *(undefined1 *)(iVar3 + -3);
          *(undefined2 *)(local_a0 + iVar1 + 2) = *(undefined2 *)(iVar2 + 0xc);
LAB_002375ec:
          iVar3 = iVar3 + 0x14;
          iVar2 = iVar2 + 0x14;
          if (iVar3 == iVar8) goto LAB_00237658;
        }
        iVar1 = uVar5 * 4;
        if (*(short *)(iVar3 + -2) == 0) goto LAB_002375ec;
        iVar4 = iVar3 + 0x14;
        uVar5 = uVar5 + 1 & 0xff;
        iVar2 = iVar2 + 0x14;
        local_a0[iVar1] = *(undefined1 *)(iVar3 + -0xc);
        local_a0[iVar1 + 1] = *(undefined1 *)(iVar3 + -3);
        *(undefined2 *)(local_a0 + iVar1 + 2) = *(undefined2 *)(iVar3 + -2);
        iVar3 = iVar4;
      } while (iVar4 != iVar8);
    }
LAB_00237658:
    if (uVar5 != 0) {
      puVar9 = local_a0;
      uVar7 = 0;
      do {
        if (2 < DebugLevel) {
          printk("Local NopReportChList[%d].Channel = %d, Bw = %d, NOP = %d\n",uVar7,
                 local_a0[uVar7 * 4],puVar9[1],*(undefined2 *)(puVar9 + 2));
        }
        uVar7 = uVar7 + 1;
        puVar9 = puVar9 + 4;
      } while ((uVar7 & 0xff) < uVar5);
    }
    puVar6 = puVar6 + 1;
    *puVar6 = (char)uVar5;
    memcpy(__dest,local_a0,uVar5 << 2);
    __dest = __dest + 0x78;
    if (puVar6 == param_2 + 2) {
      return;
    }
  } while( true );
}

