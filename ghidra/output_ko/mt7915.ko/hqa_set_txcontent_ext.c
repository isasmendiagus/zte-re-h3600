// module: mt7915.ko
// function: hqa_set_txcontent_ext @ 0x27700c
// size: 1220 bytes
//

undefined4 hqa_set_txcontent_ext(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int local_64;
  undefined4 local_5e;
  undefined1 auStack_5a [4];
  int local_56;
  undefined4 local_52;
  undefined4 local_4e;
  uint local_4a;
  undefined4 local_46;
  int local_42;
  uint local_3e;
  undefined1 auStack_3a [6];
  undefined1 auStack_34 [6];
  undefined1 auStack_2e [10];
  
  local_64 = param_3 + 0xc;
  FUN_00276034(1,4,&local_64,&local_5e);
  FUN_00276034(1,4,&local_64,auStack_5a);
  FUN_00276034(1,4,&local_64,&local_56);
  FUN_00276034(1,4,&local_64,&local_52);
  FUN_00276034(1,4,&local_64,&local_4e);
  FUN_00276034(1,4,&local_64,&local_4a);
  FUN_00276034(1,4,&local_64,&local_46);
  FUN_00276034(1,4,&local_64,&local_42);
  FUN_00276034(1,4,&local_64,&local_3e);
  FUN_00276034(0,6,&local_64,auStack_3a);
  FUN_00276034(0,6,&local_64,auStack_34);
  FUN_00276034(0,6,&local_64,auStack_2e);
  iVar7 = local_56 * 0xd18;
  if (0x80 < local_3e) {
    local_3e = 0x80;
  }
  *(char *)(param_1 + 0xa3ae36) = (char)local_56;
  iVar6 = 0;
  do {
    iVar1 = net_ad_wrap_service(param_1);
    iVar8 = iVar6 + 1;
    iVar6 = iVar7 + iVar6 * 6;
    iVar1 = iVar1 + iVar6;
    iVar2 = net_ad_wrap_service(param_1);
    iVar2 = iVar2 + iVar6;
    iVar3 = net_ad_wrap_service(param_1);
    iVar3 = iVar3 + iVar6;
    memmove((undefined1 *)(iVar1 + 0x531),auStack_3a,6);
    memmove((undefined1 *)(iVar2 + 0x591),auStack_34,6);
    memmove((undefined1 *)(iVar3 + 0x5f1),auStack_2e,6);
    iVar6 = iVar8;
  } while (iVar8 != 0x10);
  iVar6 = net_ad_wrap_service(param_1);
  iVar6 = iVar6 + iVar7;
  iVar8 = net_ad_wrap_service(param_1);
  uVar5 = *(undefined4 *)(iVar8 + iVar7 + 0x6d8);
  iVar8 = net_ad_wrap_service(param_1);
  memmove((void *)(iVar6 + 0x511),&local_52,2);
  *(short *)(iVar6 + 0x513) = (short)local_4e;
  *(char *)(iVar6 + 0x528) = (char)((local_4a << 0x14) >> 0x18);
  *(byte *)(iVar6 + 0x527) = *(byte *)(iVar6 + 0x527) & 0xf | (byte)((local_4a & 0xf) << 4);
  iVar6 = net_ad_wrap_service(param_1);
  *(undefined4 *)(iVar6 + iVar7 + 0x6e0) = local_46;
  iVar6 = net_ad_wrap_service(param_1);
  *(int *)(iVar6 + iVar7 + 0x6dc) = local_42;
  iVar6 = net_ad_wrap_service(param_1);
  *(uint *)(iVar6 + iVar7 + 0x6d8) = local_3e;
  if (local_3e != 0 && local_42 != 0) {
    iVar4 = net_ad_wrap_service(param_1);
    iVar6 = DebugLevel;
    iVar4 = iVar4 + iVar7 + 0x10e8;
    if (*(char *)(iVar4 + 4) == '\x01') {
      *(int *)(iVar4 + 8) = local_42;
      if (0 < iVar6) {
        printk("%s: FC:%04x, dur:%u, seq:%u, plen:%u, pkt_tx_time:%u, GENPKT:%u\n",
               "hqa_set_txcontent_ext",local_52,local_4e,local_4a,local_3e,local_42,local_46);
      }
    }
    else if (0 < DebugLevel) {
      printk("%s: FC:%04x, dur:%u, seq:%u, plen:%u, txlen:%u, GENPKT:%u\n","hqa_set_txcontent_ext",
             local_52,local_4e,local_4a,local_3e,local_42,local_46);
    }
    FUN_00276034(0,local_3e,&local_64,local_56 * 0xd18 + iVar8 + 0x651);
    *(undefined4 *)(param_3 + 0xe) = local_5e;
    FUN_0026cdd0(param_3,param_2,6,0);
    if (((0 < DebugLevel) &&
        (printk("%s: addr1:%02x:%02x:%02x:%02x:%02x:%02x\n","hqa_set_txcontent_ext",
                *(undefined1 *)(iVar1 + 0x531),*(undefined1 *)(iVar1 + 0x532),
                *(undefined1 *)(iVar1 + 0x533),*(undefined1 *)(iVar1 + 0x534),
                *(undefined1 *)(iVar1 + 0x535),*(undefined1 *)(iVar1 + 0x536)), 0 < DebugLevel)) &&
       (printk("%s: addr2:%02x:%02x:%02x:%02x:%02x:%02x\n","hqa_set_txcontent_ext",
               *(undefined1 *)(iVar2 + 0x591),*(undefined1 *)(iVar2 + 0x592),
               *(undefined1 *)(iVar2 + 0x593),*(undefined1 *)(iVar2 + 0x594),
               *(undefined1 *)(iVar2 + 0x595),*(undefined1 *)(iVar2 + 0x596)), 0 < DebugLevel)) {
      uVar9 = (uint)*(byte *)(iVar3 + 0x5f4);
      uVar10 = (uint)*(byte *)(iVar3 + 0x5f5);
      uVar11 = (uint)*(byte *)(iVar3 + 0x5f6);
      printk("%s: addr3:%02x:%02x:%02x:%02x:%02x:%02x\n","hqa_set_txcontent_ext",
             *(undefined1 *)(iVar3 + 0x5f1),*(undefined1 *)(iVar3 + 0x5f2),
             *(undefined1 *)(iVar3 + 0x5f3),uVar9,uVar10,uVar11);
      if (0 < DebugLevel) {
        printk("%s: ret:%u, len:%u, param_len:%u\n","hqa_set_txcontent_ext",0,local_3e,uVar5,uVar9,
               uVar10,uVar11);
      }
    }
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s: txlen/payload_len=%d/%d can\'t be 0!!\n","hqa_set_txcontent_ext");
  }
  return 1;
}

