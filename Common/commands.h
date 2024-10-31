
DEF_CMD(PUSH, 101, {double* arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip)); 
                    StackPush (stk, *(arg)); 
                    spu->reg[0] = 0; })

DEF_CMD(POP, 107, {double a = 0; 
                   StackPop (stk, &a); 
                   double *arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip)); 
                   *arg = a; })

DEF_CMD(OUTC, 120, {double a = 0; 
                    StackPop (stk, &a);
                    printf ("%c\n", (int) a); })

DEF_CMD(IN, 117, {double a = 0;
                  scanf ("%lf", &a);
                  StackPush (stk, a); })

DEF_CMD(SQRT, 118, {double a = 0;
                    StackPop (stk, &a);
                    a = sqrt (a);
                    StackPush (stk, a); })

DEF_CMD(SUB, 102, {double a = 0; 
                   StackPop (stk, &a);
                   double b = 0; 
                   StackPop (stk, &b);
                   StackPush (stk, b - a); })

DEF_CMD(ADD, 103, {double a = 0; 
                   StackPop (stk, &a);
                   double b = 0; 
                   StackPop (stk, &b);
                   StackPush (stk, a + b); })

DEF_CMD(DIV, 104, {double a = 0; 
                   StackPop (stk, &a);
                   double b = 0; 
                   StackPop (stk, &b);
                   if (CompareDouble (a, 0)) 
                   {
                       printf ("DIV ON ZERO\n"); 
                       return DIV_ZERO;
                   } 
                   else StackPush (stk, b / a); })

DEF_CMD(OUT, 105, {double a = 0; 
                   StackPop (stk, &a);
                   printf ("%.*lf\n", PRECISION, a); })

DEF_CMD(MUL, 106, {double a = 0;
                   StackPop (stk, &a);
                   double b = 0;
                   StackPop (stk, &b);
                   StackPush (stk, (int) b * a); })

DEF_CMD(JB, 108, {double a = 0; 
                  StackPop (stk, &a);
                  double b = 0;
                  StackPop (stk, &b);
                  if (b < a) 
                      (spu->ip) = spu->code[(spu->ip)];
                  else 
                      (spu->ip)++; })

DEF_CMD(JA, 109, {double a = 0; 
                  StackPop (stk, &a);
                  double b = 0; 
                  StackPop (stk, &b);
                  if (b > a) 
                      (spu->ip) = spu->code[(spu->ip)];
                  else 
                      (spu->ip)++; })

DEF_CMD(JAE, 110, {double a = 0; 
                  StackPop (stk, &a);
                  double b = 0; 
                  StackPop (stk, &b);
                  if (b >= a) 
                      (spu->ip) = spu->code[(spu->ip)];
                  else 
                      (spu->ip)++; })

DEF_CMD(JBE, 111, {double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (b <= a) 
                    (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; })

DEF_CMD(JE, 112, {double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (CompareDouble (a, b)) 
                     (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; })

DEF_CMD(JNE, 113, {double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (!CompareDouble (a, b)) 
                    (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; })

DEF_CMD(JMP, 114, {int new_pointer = spu->code[(spu->ip)];
                (spu->ip) = new_pointer; })

DEF_CMD(CALL, 115, {StackPush (stk_func, spu->ip + 1);
                spu->ip = spu->code[spu->ip]; })

DEF_CMD(RET, 116, {double a = 0;
                StackPop (stk_func, &a);
                spu->ip = (int) a; })

DEF_CMD(DRAW, 119, {Paint (spu->RAM, SQUARE, SQUARE); })

DEF_CMD(HLT, -1, {isEnd = false; })
