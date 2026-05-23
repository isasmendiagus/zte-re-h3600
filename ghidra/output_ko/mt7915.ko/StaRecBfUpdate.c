// module: mt7915.ko
// function: StaRecBfUpdate @ 0x882ec
// size: 376 bytes
//

void StaRecBfUpdate(int param_1,undefined2 *param_2)

{
  *param_2 = 4;
  param_2[1] = 0x30;
  param_2[2] = *(undefined2 *)(param_1 + 0xc3a);
  *(undefined1 *)(param_2 + 3) = *(undefined1 *)(param_1 + 0xc3c);
  *(undefined1 *)((int)param_2 + 7) = *(undefined1 *)(param_1 + 0xc3d);
  *(undefined1 *)(param_2 + 4) = *(undefined1 *)(param_1 + 0xc3e);
  *(undefined1 *)((int)param_2 + 9) = *(undefined1 *)(param_1 + 0xc3f);
  *(undefined1 *)(param_2 + 5) = *(undefined1 *)(param_1 + 0xc40);
  *(undefined1 *)((int)param_2 + 0xb) = *(undefined1 *)(param_1 + 0xc41);
  *(undefined1 *)(param_2 + 6) = *(undefined1 *)(param_1 + 0xc42);
  *(undefined1 *)((int)param_2 + 0xd) = *(undefined1 *)(param_1 + 0xc43);
  *(undefined1 *)(param_2 + 7) = *(undefined1 *)(param_1 + 0xc44);
  *(undefined1 *)((int)param_2 + 0xf) = *(undefined1 *)(param_1 + 0xc45);
  *(undefined1 *)(param_2 + 8) = *(undefined1 *)(param_1 + 0xc46);
  *(undefined1 *)((int)param_2 + 0x11) = *(undefined1 *)(param_1 + 0xc47);
  *(undefined1 *)(param_2 + 9) = *(undefined1 *)(param_1 + 0xc48);
  *(byte *)((int)param_2 + 0x13) =
       *(byte *)((int)param_2 + 0x13) & 0xc0 | *(byte *)(param_1 + 0xc49) & 0x3f;
  *(undefined1 *)(param_2 + 10) = *(undefined1 *)(param_1 + 0xc4a);
  *(byte *)((int)param_2 + 0x15) =
       *(byte *)((int)param_2 + 0x15) & 0xc0 | *(byte *)(param_1 + 0xc4b) & 0x3f;
  *(undefined1 *)(param_2 + 0xb) = *(undefined1 *)(param_1 + 0xc4c);
  *(byte *)((int)param_2 + 0x17) =
       *(byte *)((int)param_2 + 0x17) & 0xc0 | *(byte *)(param_1 + 0xc4d) & 0x3f;
  *(undefined1 *)(param_2 + 0xc) = *(undefined1 *)(param_1 + 0xc4e);
  *(byte *)((int)param_2 + 0x19) =
       *(byte *)((int)param_2 + 0x19) & 0xc0 | *(byte *)(param_1 + 0xc4f) & 0x3f;
  param_2[0xd] = *(undefined2 *)(param_1 + 0xc50);
  *(undefined1 *)(param_2 + 0xe) = *(undefined1 *)(param_1 + 0xc52);
  *(undefined1 *)((int)param_2 + 0x1d) = *(undefined1 *)(param_1 + 0xc53);
  *(undefined1 *)(param_2 + 0xf) = *(undefined1 *)(param_1 + 0xc54);
  *(undefined1 *)((int)param_2 + 0x1f) = *(undefined1 *)(param_1 + 0xc55);
  *(undefined1 *)(param_2 + 0x10) = *(undefined1 *)(param_1 + 0xc56);
  *(undefined1 *)((int)param_2 + 0x21) = *(undefined1 *)(param_1 + 0xc57);
  *(undefined1 *)(param_2 + 0x11) = *(undefined1 *)(param_1 + 0xc58);
  *(undefined1 *)((int)param_2 + 0x23) = *(undefined1 *)(param_1 + 0xc59);
  *(undefined1 *)(param_2 + 0x12) = *(undefined1 *)(param_1 + 0xc5a);
  *(undefined1 *)((int)param_2 + 0x25) = *(undefined1 *)(param_1 + 0xc5b);
  *(undefined1 *)(param_2 + 0x13) = *(undefined1 *)(param_1 + 0xc5c);
  *(undefined1 *)((int)param_2 + 0x27) = *(undefined1 *)(param_1 + 0xc5d);
  *(undefined1 *)(param_2 + 0x14) = *(undefined1 *)(param_1 + 0xc5e);
  *(undefined1 *)((int)param_2 + 0x29) = *(undefined1 *)(param_1 + 0xc5f);
  *(undefined1 *)(param_2 + 0x15) = *(undefined1 *)(param_1 + 0xc60);
  *(undefined1 *)((int)param_2 + 0x2b) = *(undefined1 *)(param_1 + 0xc61);
  *(undefined1 *)(param_2 + 0x16) = *(undefined1 *)(param_1 + 0xc62);
  return;
}

