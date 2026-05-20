// module: mt7915.ko
// function: int_bn_mod_inverse @ 0x213ea8
// size: 2508 bytes
//

BIGNUM * int_bn_mod_inverse(BIGNUM *param_1,BIGNUM *param_2,BIGNUM *param_3,BN_CTX *param_4,
                           undefined4 *param_5)

{
  BIGNUM *pBVar1;
  BIGNUM *pBVar2;
  BIGNUM *pBVar3;
  BIGNUM *pBVar4;
  BIGNUM *pBVar5;
  BIGNUM *pBVar6;
  BIGNUM *pBVar7;
  int iVar8;
  int iVar9;
  BIGNUM *pBVar10;
  int iVar11;
  BIGNUM *a;
  BIGNUM *local_50;
  BIGNUM local_3c;
  
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = 0;
  }
  local_50 = param_1;
  if (((param_2 != (BIGNUM *)0x0) && ((param_2->flags & 4U) != 0)) ||
     ((param_3 != (BIGNUM *)0x0 && ((param_3->flags & 4U) != 0)))) {
    BN_CTX_start(param_4);
    pBVar1 = BN_CTX_get(param_4);
    pBVar2 = BN_CTX_get(param_4);
    pBVar3 = BN_CTX_get(param_4);
    pBVar4 = BN_CTX_get(param_4);
    pBVar5 = BN_CTX_get(param_4);
    pBVar6 = BN_CTX_get(param_4);
    pBVar7 = BN_CTX_get(param_4);
    if (pBVar7 == (BIGNUM *)0x0) {
      local_50 = (BIGNUM *)0x0;
    }
    else {
      if ((param_1 == (BIGNUM *)0x0) && (local_50 = BN_new(), local_50 == (BIGNUM *)0x0))
      goto LAB_002143f4;
      BN_set_word(pBVar3,1);
      if (pBVar6 != (BIGNUM *)0x0) {
        pBVar6->top = 0;
        pBVar6->neg = 0;
      }
      pBVar7 = BN_copy(pBVar2,param_2);
      if ((pBVar7 != (BIGNUM *)0x0) && (pBVar7 = BN_copy(pBVar1,param_3), pBVar7 != (BIGNUM *)0x0))
      {
        if (pBVar1 != (BIGNUM *)0x0) {
          pBVar1->neg = 0;
        }
        if ((pBVar2 != (BIGNUM *)0x0) &&
           (((pBVar2->neg != 0 || (pBVar1 == (BIGNUM *)0x0)) ||
            (iVar8 = FUN_0020cef8(pBVar2,pBVar1), -1 < iVar8)))) {
          local_3c.d = DAT_005f4ac8;
          local_3c.top = DAT_005f4acc;
          local_3c.dmax = DAT_005f4ad0;
          local_3c.neg = DAT_005f4ad4;
          local_3c.flags = DAT_005f4ad8;
          FUN_0020cfb8(&local_3c,pBVar2,4);
          iVar8 = BN_nnmod(pBVar2,&local_3c,pBVar1,param_4);
          if (iVar8 == 0) goto LAB_002140e0;
        }
        iVar8 = -1;
        while ((pBVar7 = pBVar6, pBVar6 = pBVar3, pBVar3 = pBVar1, pBVar2 == (BIGNUM *)0x0 ||
               (pBVar2->top != 0))) {
          local_3c.d = DAT_005f4ac8;
          local_3c.top = DAT_005f4acc;
          local_3c.dmax = DAT_005f4ad0;
          local_3c.neg = DAT_005f4ad4;
          iVar8 = -iVar8;
          local_3c.flags = DAT_005f4ad8;
          if (pBVar3 != (BIGNUM *)0x0) {
            FUN_0020cfb8(&local_3c,pBVar3,4);
          }
          iVar9 = BN_div(pBVar4,pBVar5,&local_3c,pBVar2,param_4);
          if (((iVar9 == 0) || (pBVar4 == (BIGNUM *)0x0 || pBVar6 == (BIGNUM *)0x0)) ||
             ((iVar9 = FUN_00212078(pBVar3,pBVar4,pBVar6,param_4), iVar9 == 0 ||
              (iVar9 = BN_add(pBVar3,pBVar3,pBVar7), pBVar1 = pBVar2, pBVar2 = pBVar5,
              pBVar5 = pBVar7, iVar9 == 0)))) goto LAB_002140e0;
        }
        if (((iVar8 != -1) || (iVar8 = BN_sub(pBVar7,param_3,pBVar7), iVar8 != 0)) &&
           (iVar8 = BN_is_one(pBVar3), iVar8 != 0)) {
          if (((pBVar7->neg != 0) || (param_3 == (BIGNUM *)0x0 || pBVar7 == (BIGNUM *)0x0)) ||
             (iVar8 = FUN_0020cef8(pBVar7,param_3), -1 < iVar8)) goto LAB_00214440;
          pBVar1 = BN_copy(local_50,pBVar7);
          goto joined_r0x00214480;
        }
      }
    }
    goto LAB_002140e0;
  }
  BN_CTX_start(param_4);
  pBVar6 = BN_CTX_get(param_4);
  pBVar1 = BN_CTX_get(param_4);
  pBVar2 = BN_CTX_get(param_4);
  pBVar5 = BN_CTX_get(param_4);
  pBVar3 = BN_CTX_get(param_4);
  pBVar7 = BN_CTX_get(param_4);
  pBVar4 = BN_CTX_get(param_4);
  if (pBVar4 == (BIGNUM *)0x0) {
    local_50 = (BIGNUM *)0x0;
    goto LAB_002140e0;
  }
  if ((param_1 != (BIGNUM *)0x0) || (local_50 = BN_new(), local_50 != (BIGNUM *)0x0)) {
    BN_set_word(pBVar2,1);
    if (pBVar7 != (BIGNUM *)0x0) {
      pBVar7->top = 0;
      pBVar7->neg = 0;
    }
    if ((((pBVar1 != (BIGNUM *)0x0) && (pBVar10 = BN_copy(pBVar1,param_2), pBVar10 != (BIGNUM *)0x0)
         ) && (pBVar10 = BN_copy(pBVar6,param_3), pBVar10 != (BIGNUM *)0x0)) &&
       ((((pBVar6 != (BIGNUM *)0x0 && (pBVar6->neg = 0, pBVar1->neg == 0)) &&
         (iVar8 = FUN_0020cef8(pBVar1,pBVar6), iVar8 < 0)) ||
        (iVar8 = BN_nnmod(pBVar1,pBVar1,pBVar6,param_4), iVar8 != 0)))) {
      if (((param_3 == (BIGNUM *)0x0) || (param_3->top < 1)) ||
         (((*param_3->d & 1) == 0 || (iVar8 = BN_num_bits(param_3), 0x800 < iVar8)))) {
        iVar8 = -1;
        pBVar10 = pBVar6;
        a = pBVar7;
        do {
          pBVar7 = a;
          a = pBVar2;
          pBVar6 = pBVar10;
          pBVar10 = pBVar1;
          if ((pBVar10 != (BIGNUM *)0x0) && (pBVar10->top == 0)) {
            if (iVar8 != -1) goto LAB_002147ac;
            goto LAB_00214840;
          }
          iVar9 = BN_num_bits(pBVar6);
          iVar11 = BN_num_bits(pBVar10);
          if (iVar9 == iVar11) {
LAB_00214518:
            iVar9 = BN_set_word(pBVar5,1);
            if (iVar9 == 0) goto LAB_002140e0;
            iVar9 = BN_sub(pBVar3,pBVar6,pBVar10);
          }
          else if (iVar9 == iVar11 + 1) {
            if ((pBVar10 == (BIGNUM *)0x0) || (iVar9 = FUN_0020d528(pBVar4,pBVar10), iVar9 == 0))
            goto LAB_002140e0;
            if ((pBVar6 != (BIGNUM *)0x0) && (iVar9 = FUN_0020cef8(pBVar6,pBVar4), iVar9 < 0))
            goto LAB_00214518;
            iVar9 = BN_sub(pBVar3,pBVar6,pBVar4);
            if ((iVar9 == 0) || (iVar9 = BN_add(pBVar5,pBVar4,pBVar10), iVar9 == 0))
            goto LAB_002140e0;
            if ((pBVar5 == (BIGNUM *)0x0 || pBVar6 == (BIGNUM *)0x0) ||
               (iVar9 = FUN_0020cef8(pBVar6,pBVar5), -1 < iVar9)) {
              iVar9 = BN_set_word(pBVar5,3);
              if (iVar9 == 0) goto LAB_002140e0;
              iVar9 = BN_sub(pBVar3,pBVar3,pBVar10);
            }
            else {
              iVar9 = BN_set_word(pBVar5,2);
            }
          }
          else {
            iVar9 = BN_div(pBVar5,pBVar3,pBVar6,pBVar10,param_4);
          }
          if (iVar9 == 0) goto LAB_002140e0;
          iVar9 = BN_is_one(pBVar5);
          if (iVar9 == 0) {
            iVar9 = BN_is_word(pBVar5,2);
            if (iVar9 == 0) {
              iVar9 = BN_is_word(pBVar5,4);
              if (iVar9 == 0) {
                if (pBVar5 == (BIGNUM *)0x0) goto LAB_002140e0;
                if (pBVar5->top == 1) {
                  pBVar1 = BN_copy(pBVar6,a);
                  if (pBVar1 == (BIGNUM *)0x0) goto LAB_002140e0;
                  iVar9 = BN_mul_word(pBVar6,*pBVar5->d);
                }
                else {
                  if (a == (BIGNUM *)0x0) goto LAB_002140e0;
                  iVar9 = FUN_00212078(pBVar6,pBVar5,a,param_4);
                }
              }
              else {
                iVar9 = BN_lshift(pBVar6,a,2);
              }
            }
            else {
              if (pBVar6 == (BIGNUM *)0x0 || a == (BIGNUM *)0x0) goto LAB_002140e0;
              iVar9 = FUN_0020d528(pBVar6,a);
            }
            if (iVar9 == 0) goto LAB_002140e0;
            iVar9 = BN_add(pBVar6,pBVar6,pBVar7);
          }
          else {
            iVar9 = BN_add(pBVar6,a,pBVar7);
          }
          if (iVar9 == 0) goto LAB_002140e0;
          iVar8 = -iVar8;
          pBVar1 = pBVar3;
          pBVar2 = pBVar6;
          pBVar3 = pBVar7;
        } while( true );
      }
      while( true ) {
        if (pBVar1->top == 0) goto LAB_00214840;
        iVar8 = 0;
        while ((iVar8 < 0 || (iVar9 = FUN_0020cf74(pBVar1,iVar8), iVar9 == 0))) {
          iVar8 = iVar8 + 1;
          if ((((pBVar2 != (BIGNUM *)0x0) && ((0 < pBVar2->top && ((*pBVar2->d & 1) != 0)))) &&
              (iVar9 = BN_uadd(pBVar2,pBVar2,param_3), iVar9 == 0)) ||
             (iVar9 = BN_rshift1(pBVar2,pBVar2), iVar9 == 0)) goto LAB_002140e0;
        }
        if ((iVar8 != 0) && (iVar8 = BN_rshift(pBVar1,pBVar1,iVar8), iVar8 == 0)) break;
        iVar8 = 0;
        while ((pBVar6 == (BIGNUM *)0x0 || iVar8 < 0 ||
               (iVar9 = FUN_0020cf74(pBVar6,iVar8), iVar9 == 0))) {
          iVar8 = iVar8 + 1;
          if (((pBVar7 != (BIGNUM *)0x0) &&
              (((0 < pBVar7->top && ((*pBVar7->d & 1) != 0)) &&
               (iVar9 = BN_uadd(pBVar7,pBVar7,param_3), iVar9 == 0)))) ||
             (iVar9 = BN_rshift1(pBVar7,pBVar7), iVar9 == 0)) goto LAB_002140e0;
        }
        if ((iVar8 != 0) && (iVar8 = BN_rshift(pBVar6,pBVar6,iVar8), iVar8 == 0)) break;
        iVar8 = FUN_0020cef8(pBVar1,pBVar6);
        if (iVar8 < 0) {
          iVar8 = BN_uadd(pBVar7,pBVar7,pBVar2);
          if (iVar8 == 0) break;
          iVar8 = BN_usub(pBVar6,pBVar6,pBVar1);
        }
        else {
          iVar8 = BN_uadd(pBVar2,pBVar2,pBVar7);
          if (iVar8 == 0) break;
          iVar8 = BN_usub(pBVar1,pBVar1,pBVar6);
        }
        if (iVar8 == 0) break;
      }
    }
    goto LAB_002140e0;
  }
LAB_002143f4:
  pBVar1 = local_50;
  local_50 = (BIGNUM *)0x0;
  BN_free(pBVar1);
LAB_002140f4:
  BN_CTX_end(param_4);
  return local_50;
LAB_00214840:
  iVar8 = BN_sub(pBVar7,param_3,pBVar7);
  if (iVar8 != 0) {
LAB_002147ac:
    iVar8 = BN_is_one(pBVar6);
    if (iVar8 == 0) {
      if (param_5 != (undefined4 *)0x0) {
        *param_5 = 1;
      }
    }
    else {
      if (((pBVar7->neg == 0) && (param_3 != (BIGNUM *)0x0 && pBVar7 != (BIGNUM *)0x0)) &&
         (iVar8 = FUN_0020cef8(pBVar7,param_3), iVar8 < 0)) {
        pBVar1 = BN_copy(local_50,pBVar7);
      }
      else {
LAB_00214440:
        pBVar1 = (BIGNUM *)BN_nnmod(local_50,pBVar7,param_3,param_4);
      }
joined_r0x00214480:
      if (pBVar1 != (BIGNUM *)0x0) goto LAB_002140f4;
    }
  }
LAB_002140e0:
  if (param_1 != (BIGNUM *)0x0) {
    local_50 = (BIGNUM *)0x0;
    goto LAB_002140f4;
  }
  goto LAB_002143f4;
}

