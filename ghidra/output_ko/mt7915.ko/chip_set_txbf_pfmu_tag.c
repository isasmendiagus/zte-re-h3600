// module: mt7915.ko
// function: chip_set_txbf_pfmu_tag @ 0x17c5e4
// size: 676 bytes
//

undefined4 chip_set_txbf_pfmu_tag(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  
  iVar3 = hc_get_hdev_privdata();
  uVar1 = (undefined1)param_3;
  uVar2 = (undefined2)param_3;
  switch(param_2) {
  case 0:
    *(undefined2 *)(iVar3 + 0xa786fc) = uVar2;
    break;
  case 1:
    *(undefined1 *)(iVar3 + 0xa786fe) = uVar1;
    break;
  case 2:
    *(undefined1 *)(iVar3 + 0xa786ff) = uVar1;
    break;
  case 3:
    *(undefined1 *)(iVar3 + 0xa78701) = uVar1;
    break;
  case 4:
    *(undefined1 *)(iVar3 + 0xa78706) = uVar1;
    break;
  case 5:
    *(undefined2 *)(iVar3 + 0xa78708) = uVar2;
    break;
  case 6:
    *(undefined2 *)(iVar3 + 0xa7870a) = uVar2;
    break;
  case 7:
    *(undefined2 *)(iVar3 + 0xa7870c) = uVar2;
    break;
  case 8:
    *(undefined2 *)(iVar3 + 0xa7870e) = uVar2;
    break;
  case 9:
    *(undefined1 *)(iVar3 + 0xa78710) = uVar1;
    break;
  case 10:
    *(undefined1 *)(iVar3 + 0xa78711) = uVar1;
    break;
  case 0xb:
    *(undefined1 *)(iVar3 + 0xa78712) = uVar1;
    break;
  case 0xc:
    *(undefined1 *)(iVar3 + 0xa78713) = uVar1;
    break;
  case 0xd:
    *(undefined1 *)(iVar3 + 0xa78707) = uVar1;
    break;
  case 0xe:
    *(undefined1 *)(iVar3 + 0xa78702) = uVar1;
    break;
  case 0xf:
    *(undefined1 *)(iVar3 + 0xa78703) = uVar1;
    break;
  case 0x10:
    *(undefined1 *)(iVar3 + 0xa78705) = uVar1;
    break;
  case 0x11:
    *(undefined1 *)(iVar3 + 0xa78700) = uVar1;
    break;
  case 0x12:
    *(undefined1 *)(iVar3 + 0xa78704) = uVar1;
    break;
  case 0x13:
    *(undefined1 *)(iVar3 + 0xa78714) = uVar1;
    break;
  case 0x14:
    *(undefined1 *)(iVar3 + 0xa78715) = uVar1;
    break;
  case 0x15:
    *(undefined1 *)(iVar3 + 0xa78716) = uVar1;
    break;
  case 0x16:
    *(undefined1 *)(iVar3 + 0xa78717) = uVar1;
    break;
  case 0x17:
    *(undefined1 *)(iVar3 + 0xa78718) = uVar1;
    break;
  case 0x18:
    *(undefined1 *)(iVar3 + 0xa78719) = uVar1;
    break;
  case 0x19:
    *(undefined1 *)(iVar3 + 0xa7871a) = uVar1;
    break;
  case 0x1a:
    *(undefined1 *)(iVar3 + 0xa7871b) = uVar1;
    break;
  case 0x1b:
    *(undefined1 *)(iVar3 + 0xa7871c) = uVar1;
    break;
  case 0x1c:
    *(undefined1 *)(iVar3 + 0xa7871d) = uVar1;
    break;
  case 0x1d:
    *(undefined1 *)(iVar3 + 0xa7871e) = uVar1;
    break;
  case 0x1e:
    *(undefined1 *)(iVar3 + 0xa7871f) = uVar1;
    break;
  case 0x1f:
    *(undefined4 *)(iVar3 + 0xa78720) = param_3;
    break;
  case 0x20:
    *(undefined1 *)(iVar3 + 0xa78724) = uVar1;
    break;
  case 0x21:
    *(undefined1 *)(iVar3 + 0xa78725) = uVar1;
    break;
  case 0x22:
    *(undefined1 *)(iVar3 + 0xa78726) = uVar1;
    break;
  case 0x23:
    *(undefined1 *)(iVar3 + 0xa78727) = uVar1;
    break;
  case 0x24:
    *(undefined1 *)(iVar3 + 0xa78728) = uVar1;
    break;
  case 0x25:
    *(undefined1 *)(iVar3 + 0xa78729) = uVar1;
    break;
  case 0x26:
    *(undefined1 *)(iVar3 + 0xa7872a) = uVar1;
  }
  return 1;
}

