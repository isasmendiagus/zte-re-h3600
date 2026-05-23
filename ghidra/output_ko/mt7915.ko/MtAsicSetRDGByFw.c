// module: mt7915.ko
// function: MtAsicSetRDGByFw @ 0x1995d4
// size: 88 bytes
//

undefined4 MtAsicSetRDGByFw(undefined4 param_1,ushort *param_2)

{
  undefined4 local_1c;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  byte local_13;
  
  local_1c = *(undefined4 *)(param_2 + 4);
  local_18 = *(undefined1 *)((int)param_2 + 5);
  local_17 = *(undefined1 *)((int)param_2 + 3);
  local_16 = (undefined1)param_2[2];
  local_14 = (undefined1)param_2[1];
  local_15 = (undefined1)*param_2;
  local_13 = (byte)(((uint)*param_2 << 0x16) >> 0x1e);
  MtCmdSetRdg(param_1,&local_1c);
  return 1;
}

