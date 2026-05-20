// module: mt7915.ko
// function: RepeaterSyncWdevWithMainSta @ 0x81530
// size: 508 bytes
//

void RepeaterSyncWdevWithMainSta(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  *(undefined4 *)(param_1 + 0x904) = *(undefined4 *)(param_2 + 0x904);
  *(undefined4 *)(param_1 + 0xb10) = *(undefined4 *)(param_2 + 0xb10);
  *(undefined4 *)(param_1 + 0xb14) = *(undefined4 *)(param_2 + 0xb14);
  *(undefined4 *)(param_1 + 0xabc) = *(undefined4 *)(param_2 + 0xabc);
  memcpy((void *)(param_1 + 0x2c),(void *)(param_2 + 0x2c),0x85c);
  *(undefined4 *)(param_1 + 0x21) = *(undefined4 *)(param_2 + 0x21);
  *(undefined2 *)(param_1 + 0x25) = *(undefined2 *)(param_2 + 0x25);
  *(undefined1 *)(param_1 + 0x28) = *(undefined1 *)(param_2 + 0x28);
  uVar6 = *(undefined4 *)(param_2 + 0xaa4);
  uVar1 = *(undefined4 *)(param_2 + 0xaa8);
  uVar5 = *(undefined4 *)(param_2 + 0xaac);
  *(undefined4 *)(param_1 + 0xaa0) = *(undefined4 *)(param_2 + 0xaa0);
  *(undefined4 *)(param_1 + 0xaa4) = uVar6;
  *(undefined4 *)(param_1 + 0xaa8) = uVar1;
  *(undefined4 *)(param_1 + 0xaac) = uVar5;
  uVar5 = *(undefined4 *)(param_2 + 0xab4);
  uVar1 = *(undefined4 *)(param_2 + 0xab8);
  *(undefined4 *)(param_1 + 0xab0) = *(undefined4 *)(param_2 + 0xab0);
  *(undefined4 *)(param_1 + 0xab4) = uVar5;
  *(undefined4 *)(param_1 + 0xab8) = uVar1;
  *(undefined4 *)(param_1 + 0xbcc) = *(undefined4 *)(param_2 + 0xbcc);
  *(undefined4 *)(param_1 + 0xc98) = *(undefined4 *)(param_2 + 0xc98);
  *(undefined4 *)(param_1 + 0xedc) = *(undefined4 *)(param_2 + 0xedc);
  *(undefined4 *)(param_1 + 0xe20) = *(undefined4 *)(param_2 + 0xe20);
  *(undefined4 *)(param_1 + 0x3fe4) = *(undefined4 *)(param_2 + 0x3fe4);
  *(undefined2 *)(param_1 + 0x18) = *(undefined2 *)(param_2 + 0x18);
  *(undefined1 *)(param_1 + 0x1a) = *(undefined1 *)(param_2 + 0x1a);
  puVar2 = (undefined4 *)(param_1 + 0xade);
  puVar3 = (undefined4 *)(param_2 + 0xade);
  do {
    puVar4 = puVar3 + 4;
    uVar6 = puVar3[1];
    uVar1 = puVar3[2];
    uVar5 = puVar3[3];
    *puVar2 = *puVar3;
    puVar2[1] = uVar6;
    puVar2[2] = uVar1;
    puVar2[3] = uVar5;
    puVar2 = puVar2 + 4;
    puVar3 = puVar4;
  } while (puVar4 != (undefined4 *)(param_2 + 0xb0e));
  memcpy((void *)(param_1 + 0x98c),(void *)(param_2 + 0x98c),0x114);
  uVar6 = *(undefined4 *)(param_2 + 0x895);
  uVar1 = *(undefined4 *)(param_2 + 0x899);
  uVar5 = *(undefined4 *)(param_2 + 0x89d);
  *(undefined4 *)(param_1 + 0x891) = *(undefined4 *)(param_2 + 0x891);
  *(undefined4 *)(param_1 + 0x895) = uVar6;
  *(undefined4 *)(param_1 + 0x899) = uVar1;
  *(undefined4 *)(param_1 + 0x89d) = uVar5;
  uVar5 = *(undefined4 *)(param_2 + 0x8a5);
  uVar1 = *(undefined4 *)(param_2 + 0x8a9);
  *(undefined4 *)(param_1 + 0x8a1) = *(undefined4 *)(param_2 + 0x8a1);
  *(undefined4 *)(param_1 + 0x8a5) = uVar5;
  *(undefined4 *)(param_1 + 0x8a9) = uVar1;
  *(undefined2 *)(param_1 + 0x8ae) = *(undefined2 *)(param_2 + 0x8ae);
  *(undefined1 *)(param_1 + 0x8b0) = *(undefined1 *)(param_2 + 0x8b0);
  *(undefined1 *)(param_1 + 0x8f8) = *(undefined1 *)(param_2 + 0x8f8);
  *(undefined2 *)(param_1 + 0x8fe) = *(undefined2 *)(param_2 + 0x8fe);
  *(undefined2 *)(param_1 + 0x900) = *(undefined2 *)(param_2 + 0x900);
  *(undefined2 *)(param_1 + 0x8fc) = *(undefined2 *)(param_2 + 0x8fc);
  *(undefined2 *)(param_1 + 0x8fa) = *(undefined2 *)(param_2 + 0x8fa);
  *(undefined1 *)(param_1 + 0xd) = *(undefined1 *)(param_2 + 0xd);
  *(undefined1 *)(param_1 + 0x27) = *(undefined1 *)(param_2 + 0x27);
  *(undefined2 *)(param_1 + 0x10) = *(undefined2 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 0xb18) = *(undefined4 *)(param_2 + 0xb18);
  *(undefined4 *)(param_1 + 0x88c) = *(undefined4 *)(param_2 + 0x88c);
  return;
}

