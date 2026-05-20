// module: mt7915.ko
// function: MakePwrConstraintIe @ 0xb4430
// size: 388 bytes
//

void MakePwrConstraintIe(int param_1,int param_2,int *param_3,int param_4)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  byte local_39;
  int local_38;
  int local_34;
  undefined1 auStack_2d [9];
  
  local_38 = *param_3;
  uVar1 = *(ushort *)(param_2 + 0x18);
  local_34 = 0;
  if (((*(byte *)(param_2 + 0x1a) < 0xf) || (*(char *)(param_1 + 0x795074) != '\x01')) &&
     (*(char *)(param_2 + 0xb21) != '\x01')) {
    *param_3 = local_38;
    return;
  }
  local_3b = *(undefined1 *)(param_1 + 0x795043);
  local_3d = 0x20;
  local_3c = 1;
  MakeOutgoingFrame(param_4 + local_38,&local_34,1,&local_3d,1,&local_3c,1,&local_3b,0xffffffff);
  local_38 = local_34 + local_38;
  iVar3 = param_4 + local_38;
  uVar2 = GetMaxTxPwr(param_1);
  InsertTpcReportIE(param_1,iVar3,&local_38,uVar2,0);
  if ((uVar1 & 0x20) != 0) {
    local_34 = 0;
    local_3a = 0xc3;
    local_39 = build_vht_txpwr_envelope(param_1,param_2,auStack_2d);
    MakeOutgoingFrame(param_4 + local_38,&local_34,1,&local_3a,1,&local_39,local_39,auStack_2d,
                      0xffffffff);
    *param_3 = local_34 + local_38;
    return;
  }
  *param_3 = local_38;
  return;
}

