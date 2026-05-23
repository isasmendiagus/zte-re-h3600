// module: mt7915.ko
// function: TxBfProfileDataWrite @ 0x86f8c
// size: 304 bytes
//

bool TxBfProfileDataWrite(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined1 local_3c;
  byte bStack_3b;
  undefined1 local_3a;
  byte bStack_39;
  undefined1 local_38;
  byte bStack_37;
  undefined1 local_36;
  byte bStack_35;
  undefined1 local_34;
  byte bStack_33;
  undefined1 local_32;
  byte bStack_31;
  byte local_30;
  byte local_2f;
  
  _local_3c = CONCAT11((byte)((*(ushort *)(param_2 + 4) & 0x1ff) >> 8) |
                       (byte)((*(ushort *)(param_2 + 6) & 0x7f) << 1),
                       (char)(*(ushort *)(param_2 + 4) & 0x1ff));
  _local_3a = CONCAT11((byte)((*(ushort *)(param_2 + 8) & 0x1ff) >> 8) |
                       (byte)((*(ushort *)(param_2 + 10) & 0x7f) << 1),
                       (char)(*(ushort *)(param_2 + 8) & 0x1ff));
  _local_38 = CONCAT11((byte)((*(ushort *)(param_2 + 0xc) & 0x1ff) >> 8) |
                       (byte)((*(ushort *)(param_2 + 0xe) & 0x7f) << 1),
                       (char)(*(ushort *)(param_2 + 0xc) & 0x1ff));
  _local_36 = CONCAT11((byte)((*(ushort *)(param_2 + 0x10) & 0x1ff) >> 8) |
                       (byte)((*(ushort *)(param_2 + 0x12) & 0x7f) << 1),
                       (char)(*(ushort *)(param_2 + 0x10) & 0x1ff));
  _local_34 = CONCAT11((byte)((*(ushort *)(param_2 + 0x14) & 0x1ff) >> 8) |
                       (byte)((*(ushort *)(param_2 + 0x16) & 0x7f) << 1),
                       (char)(*(ushort *)(param_2 + 0x14) & 0x1ff));
  local_30 = (byte)*(undefined2 *)(param_2 + 0x1c) & 0xf |
             (byte)((*(ushort *)(param_2 + 0x1e) & 0xf) << 4);
  _local_32 = CONCAT11((byte)((*(ushort *)(param_2 + 0x18) & 0x1ff) >> 8) |
                       (byte)((*(ushort *)(param_2 + 0x1a) & 0x7f) << 1),
                       (char)(*(ushort *)(param_2 + 0x18) & 0x1ff));
  local_2f = (byte)*(undefined2 *)(param_2 + 0x20) & 0xf |
             (byte)((*(ushort *)(param_2 + 0x22) & 0xf) << 4);
  iVar1 = CmdETxBfPfmuProfileDataWrite(param_1,*param_2,*(undefined2 *)(param_2 + 2),&local_3c);
  return iVar1 == 0;
}

