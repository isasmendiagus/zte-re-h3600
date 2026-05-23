// module: mt7915.ko
// function: raWrapperEntrySet @ 0x1d9918
// size: 600 bytes
//

void raWrapperEntrySet(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  byte bVar3;
  uint uVar4;
  
  *(undefined2 *)(param_3 + 2) = *(undefined2 *)(param_2 + 0xe0);
  *(undefined1 *)(param_3 + 4) = *(undefined1 *)(param_2 + 0xb7e);
  *(char *)(param_3 + 5) = (char)*(undefined2 *)(*(int *)(param_2 + 8) + 0x18);
  *(undefined1 *)(param_3 + 6) = *(undefined1 *)(*(int *)(param_2 + 8) + 0x1a);
  uVar2 = HcGetBw(param_1,*(undefined4 *)(param_2 + 8));
  *(undefined1 *)(param_3 + 8) = 0;
  *(undefined1 *)(param_3 + 7) = uVar2;
  *(byte *)(param_3 + 9) = *(byte *)(param_2 + 0xcab) & 1;
  *(byte *)(param_3 + 10) = (byte)(((uint)*(byte *)(param_2 + 0xca4) << 0x1b) >> 0x1f);
  *(undefined1 *)(param_3 + 0xb) = *(undefined1 *)(param_2 + 0xca7);
  *(undefined1 *)(param_3 + 0xc) = *(undefined1 *)(param_2 + 0xca8);
  *(undefined1 *)(param_3 + 0xd) = *(undefined1 *)(param_2 + 0xca9);
  *(undefined1 *)(param_3 + 0xe) = *(undefined1 *)(param_2 + 0xcaa);
  *(undefined1 *)(param_3 + 0xf) = *(undefined1 *)(param_2 + 0xd10);
  uVar2 = 1;
  if (*(char *)(param_2 + 0xbfd) != '\x01') {
    if (*(char *)(param_1 + 0x79505f) != '\x01') {
      *(undefined1 *)(param_3 + 0x15) = 0;
      goto LAB_001d99c8;
    }
    uVar2 = 2;
  }
  *(undefined1 *)(param_3 + 0x15) = uVar2;
LAB_001d99c8:
  *(undefined1 *)(param_3 + 0x16) = *(undefined1 *)(param_2 + 0xd05);
  *(undefined1 *)(param_3 + 0x17) = *(undefined1 *)(param_2 + 0xb7c);
  *(undefined1 *)(param_3 + 0x18) = *(undefined1 *)(param_2 + 0xbfe);
  *(undefined1 *)(param_3 + 0x19) = *(undefined1 *)(param_2 + 0xbff);
  *(undefined1 *)(param_3 + 0x1a) = *(undefined1 *)(param_2 + 0xc00);
  *(undefined4 *)(param_3 + 0x1c) = *(undefined4 *)(param_2 + 0xc04);
  *(undefined2 *)(param_3 + 0x20) = *(undefined2 *)(param_2 + 0xc08);
  *(undefined2 *)(param_3 + 0x22) = *(undefined2 *)(param_2 + 0xc0a);
  if (((uint)*(ushort *)(param_2 + 0xbe) << 0x17) >> 0x1e != 3) {
    *(undefined2 *)(param_3 + 0x24) = *(undefined2 *)(param_2 + 0xc0c);
    *(undefined2 *)(param_3 + 0x26) = *(undefined2 *)(param_2 + 0xc0e);
  }
  *(undefined1 *)(param_3 + 0x28) = *(undefined1 *)(param_2 + 0xd20);
  *(byte *)(param_3 + 0x29) = (byte)(((uint)*(byte *)(param_2 + 0xd21) << 0x1e) >> 0x1e);
  *(byte *)(param_3 + 0x2a) = (byte)(((uint)*(byte *)(param_2 + 0xd21) << 0x19) >> 0x1d);
  *(byte *)(param_3 + 0x2b) = *(byte *)(param_2 + 0xd21) >> 7;
  *(undefined1 *)(param_3 + 0x10) = *(undefined1 *)(param_2 + 0x10c);
  *(undefined1 *)(param_3 + 0x11) = *(undefined1 *)(param_2 + 0x10d);
  uVar2 = *(undefined1 *)(param_2 + 0x10e);
  *(undefined1 *)(param_3 + 0x42) = 0;
  *(undefined1 *)(param_3 + 0x12) = uVar2;
  *(undefined4 *)(param_3 + 0x2c) = *(undefined4 *)(param_2 + 0xb4);
  bVar3 = *(byte *)(param_2 + 0xbf);
  *(byte *)(param_3 + 0x30) = bVar3 >> 5;
  *(byte *)(param_3 + 0x32) = (byte)(((uint)*(byte *)(param_2 + 0xbf) << 0x1d) >> 0x1f);
  *(byte *)(param_3 + 0x33) = (byte)(((uint)*(byte *)(param_2 + 0xbf) << 0x1e) >> 0x1f);
  *(byte *)(param_3 + 0x34) = (byte)(((uint)*(ushort *)(param_2 + 0xbe) << 0x17) >> 0x1e);
  *(byte *)(param_3 + 0x35) = (byte)(((uint)*(byte *)(param_2 + 0xbe) << 0x19) >> 0x1f);
  bVar1 = *(byte *)(param_2 + 0xbe);
  if (((uint)bVar3 << 0x18) >> 0x1d < 4) {
    *(undefined1 *)(param_3 + 0x37) = 0;
    *(byte *)(param_3 + 0x36) = bVar1 & 0x3f;
  }
  else {
    *(byte *)(param_3 + 0x36) = bVar1 & 0xf;
    *(byte *)(param_3 + 0x37) = (byte)(((uint)*(byte *)(param_2 + 0xbe) << 0x1a) >> 0x1e) + 1;
  }
  uVar4 = ((uint)*(byte *)(param_2 + 0xbd) << 0x18) >> 0x1d;
  *(byte *)(param_3 + 0x39) = *(byte *)(param_2 + 0xbd) >> 5;
  bVar3 = *(byte *)(param_2 + 0xbd);
  *(byte *)(param_3 + 0x3b) = (byte)(((uint)bVar3 << 0x1d) >> 0x1f);
  if (uVar4 < 4) {
    bVar3 = 0;
  }
  *(byte *)(param_3 + 0x3c) = (byte)(((uint)*(byte *)(param_2 + 0xbd) << 0x1e) >> 0x1f);
  *(byte *)(param_3 + 0x3d) = (byte)(((uint)*(ushort *)(param_2 + 0xbc) << 0x17) >> 0x1e);
  *(byte *)(param_3 + 0x3e) = (byte)(((uint)*(byte *)(param_2 + 0xbc) << 0x19) >> 0x1f);
  bVar1 = *(byte *)(param_2 + 0xbc);
  if (uVar4 < 4) {
    *(byte *)(param_3 + 0x40) = bVar3;
    *(byte *)(param_3 + 0x3f) = bVar1 & 0x3f;
  }
  else {
    *(byte *)(param_3 + 0x3f) = bVar1 & 0xf;
    *(byte *)(param_3 + 0x40) = (byte)(((uint)*(byte *)(param_2 + 0xbc) << 0x1a) >> 0x1e) + 1;
  }
  return;
}

