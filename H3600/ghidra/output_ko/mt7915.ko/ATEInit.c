// module: mt7915.ko
// function: ATEInit @ 0x26936c
// size: 532 bytes
//

void ATEInit(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  iVar1 = net_ad_wrap_service();
  uVar2 = *(undefined4 *)(iVar1 + 0x504);
  iVar1 = net_ad_wrap_service(param_1);
  uVar3 = *(undefined4 *)(iVar1 + 0x508);
  iVar1 = net_ad_wrap_service(param_1);
  uVar4 = *(undefined4 *)(iVar1 + 0x121c);
  iVar1 = net_ad_wrap_service(param_1);
  uVar5 = *(undefined4 *)(iVar1 + 0x1220);
  __memzero(param_1 + 0xa39fd0,0x1b28);
  __memzero(param_1 + 0xa3a098,0xb30);
  *(undefined4 *)(param_1 + 0xa3ac28) = uVar2;
  *(undefined4 *)(param_1 + 0xa3a114) = uVar4;
  *(undefined4 *)(param_1 + 0xa3ac14) = 0x100;
  *(undefined4 *)(param_1 + 0xa3ad7c) = 0xffffffff;
  *(undefined1 *)(param_1 + 0xa3af77) = 0xaa;
  *(undefined4 *)(param_1 + 0xa3ad78) = 0x422;
  *(undefined1 *)(param_1 + 0xa3ad6c) = 7;
  *(undefined4 *)(param_1 + 0xa3ad74) = 1;
  *(undefined1 *)(param_1 + 0xa3ad68) = 1;
  *(undefined1 *)(param_1 + 0xa3ad65) = 0;
  *(undefined1 *)(param_1 + 0xa3ad6b) = 0;
  *(undefined4 *)(param_1 + 0xa3a118) = uVar5;
  *(undefined4 *)(param_1 + 0xa3ac2c) = uVar3;
  if (("rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] - 0x1eU & 0xfb) == 0) {
    *(undefined1 *)(param_1 + 0xa3ad5c) = 0x24;
  }
  else {
    *(undefined1 *)(param_1 + 0xa3ad5c) = 1;
  }
  *(undefined4 *)(param_1 + 0xa3ac20) = 1;
  *(undefined4 *)(param_1 + 0xa3ac24) = 0;
  *(undefined2 *)(param_1 + 0xa3ad5a) = 1;
  *(undefined1 *)(param_1 + 0xa3ae57) = 0;
  *(undefined1 *)(param_1 + 0xa3ae58) = 0x11;
  *(undefined1 *)(param_1 + 0xa3ae59) = 0x22;
  *(undefined1 *)(param_1 + 0xa3ae5a) = 0xaa;
  *(undefined1 *)(param_1 + 0xa3ae5b) = 0xbb;
  *(undefined1 *)(param_1 + 0xa3ae5c) = 0xcc;
  *(undefined4 *)(param_1 + 0xa3aeb7) = *(undefined4 *)(param_1 + 0xa3ae57);
  *(undefined2 *)(param_1 + 0xa3aebb) = *(undefined2 *)(param_1 + 0xa3ae5b);
  *(undefined4 *)(param_1 + 0xa3af17) = *(undefined4 *)(param_1 + 0xa3ae57);
  *(undefined2 *)(param_1 + 0xa3af1b) = *(undefined2 *)(param_1 + 0xa3ae5b);
  *(undefined1 *)(param_1 + 0xa3b8b6) = 0;
  *(undefined1 *)(param_1 + 0xa3b8b7) = 0;
  *(undefined1 *)(param_1 + 0xa3b8b8) = 0;
  *(undefined1 *)(param_1 + 0xa3adf8) = 6;
  *(undefined4 *)(param_1 + 0xa3ad90) = 0;
  *(undefined1 *)(param_1 + 0xa3add8) = 0;
  *(undefined4 *)(param_1 + 0xa3addc) = 0;
  *(undefined4 *)(param_1 + 0xa3adf4) = 0;
  *(undefined2 *)(param_1 + 0xa3adfa) = 9;
  *(undefined2 *)(param_1 + 0xa3adfc) = 10;
  *(undefined1 *)(param_1 + 0xa3adfe) = 1;
  *(undefined1 *)(param_1 + 0xa3adff) = 1;
  *(undefined2 *)(param_1 + 0xa3ae00) = 0;
  *(undefined2 *)(param_1 + 0xa3ae02) = 0;
  *(undefined1 *)(param_1 + 0xa3ae36) = 0;
  *(undefined1 *)(param_1 + 0xa3ad58) = 0;
  *(undefined1 *)(param_1 + 0xa3ad59) = 0;
  *(undefined4 *)(param_1 + 0xa3a104) = 0x100;
  if (*(int *)(param_1 + 0xa3ac18) == 0) {
    *(undefined1 *)(param_1 + 0xa3a244) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0xa3a244) = 3;
  }
  *(undefined1 *)(param_1 + 0xa3a245) = 1;
  *(undefined1 *)(param_1 + 0xa3ae07) = 0;
  *(undefined1 *)(param_1 + 0xa3ae08) = 0;
  os_move_mem((void *)(param_1 + 0xa3ae37),TemplateFrame,0x20);
  MtTestModeInit(param_1);
  *(undefined1 *)(param_1 + 0xa3b8ba) = 0;
  return;
}

