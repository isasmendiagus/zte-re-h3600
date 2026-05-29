/* ===== FUN FUN_40e50c40 @ 40e50c40 =====
 * callers: 40e50440:FUN_40e50440
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e4010c:FUN_40e4010c, 40e40204:FUN_40e40204, 40e45ac0:FUN_40e45ac0, 40e4fdcc:FUN_40e4fdcc, 40e50bd4:FUN_40e50bd4, 40e50c20:FUN_40e50c20
 */


void FUN_40e50c40(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined4 local_1c;
  
  iVar1 = DAT_40e50e60/*=0x47f4af94*/;
  uVar6 = 0;
  local_1c = 0;
  if (param_1 < 5) {
    FUN_40e4010c(*(undefined1 *)(DAT_40e50e60/*=0x47f4af94*/ + param_1),0x1e,(int)&local_1c + 2,param_4,param_1);
    FUN_40e40204(*(undefined1 *)(iVar1 + param_1),0x1e,0);
    FUN_40e4010c(*(undefined1 *)(iVar1 + param_1),0x1a,&local_1c);
    FUN_40e45ac0(10);
    FUN_40e4010c(*(undefined1 *)(iVar1 + param_1),0x1a,&local_1c);
    FUN_40e40204(*(undefined1 *)(iVar1 + param_1),0x1e,local_1c._2_2_);
    iVar1 = DAT_40e50e64/*=0x47f5969c*/;
    if ((local_1c & 0x40) != 0) {
      uVar5 = local_1c & 0x380;
      local_1c = CONCAT22(local_1c._2_2_,(short)uVar5);
      if (uVar5 == *(uint *)(DAT_40e50e64/*=0x47f5969c*/ + param_1 * 4)) {
        FUN_40e50c20(param_1);
      }
      else {
        uVar5 = uVar5 >> 7;
        if ((1 < uVar5) && (uVar6 = (uint)(uVar5 - 2 < 2), 1 < uVar5 - 2)) {
          if (uVar5 - 4 < 2) {
            uVar6 = 2;
          }
          else {
            uVar6 = 0;
          }
        }
        if (uVar5 == 4 || (uVar5 & 5) == 0) {
          iVar8 = 0;
        }
        else if (uVar5 == 5 || (uVar5 & 5) == 1) {
          iVar8 = 1;
        }
        else {
          iVar8 = 0;
        }
        FUN_40e2a1b4(DAT_40e50e6c/*=0x47f3ed7d*/,param_1,*(undefined4 *)(DAT_40e50e68/*=0x47f35958*/ + uVar6 * 4),
                     *(undefined4 *)(DAT_40e50e68/*=0x47f35958*/ + iVar8 * 4 + 0x10));
        FUN_40e4fdcc(1 << (param_1 + 6 & 0xff));
        uVar2 = DAT_40e50e74/*=0x47f3ed9f*/;
        iVar7 = param_1 * 0x40000;
        *(undefined4 *)(iVar7 + -0x6de00000) = DAT_40e50e70/*=0x00bbe003*/;
        *(undefined4 *)(iVar7 + -0x6ddffff8) = 0x80000001;
        iVar3 = DAT_40e50e7c/*=0x922000e0[MAC0]*/;
        *(undefined4 *)(DAT_40e50e7c/*=0x922000e0[MAC0]*/ + param_1 * 0x40000) = DAT_40e50e78/*=0x00011200*/;
        *(undefined4 *)(iVar3 + 0xc20 + param_1 * 0x40000) = 0x32;
        *(undefined4 *)(iVar3 + 0xc50 + param_1 * 0x40000) = 0xa8;
        uVar4 = DAT_40e50e80/*=0x00300002*/;
        *(undefined4 *)(iVar7 + -0x6ddffffc) = 0xfffe;
        iVar7 = DAT_40e50e84/*=0x92200070[MAC0]*/;
        *(undefined4 *)(DAT_40e50e84/*=0x92200070[MAC0]*/ + param_1 * 0x40000) = uVar4;
        *(undefined4 *)(iVar7 + 0x44 + param_1 * 0x40000) = 0x4000;
        *(undefined4 *)(iVar7 + 0xa90 + param_1 * 0x40000) = DAT_40e50e88/*=0x0010ff11*/;
        FUN_40e2a1b4(uVar2);
        FUN_40e50bd4(param_1,uVar6,iVar8);
        iVar8 = DAT_40e50e8c/*=0x921d9000*/;
        iVar7 = 5;
        do {
          FUN_40e45ac0(1);
          if ((1 << (param_1 + 5 & 0xff) & *(uint *)(iVar8 + 0x68)) != 0) {
            *(uint *)(DAT_40e50e8c/*=0x921d9000*/ + 0x68) = *(uint *)(iVar8 + 0x68) | 1 << (param_1 & 0xff);
            break;
          }
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
        FUN_40e50c20(param_1);
        *(uint *)(iVar1 + param_1 * 4) = local_1c & 0xffff;
      }
    }
  }
  return;
}
