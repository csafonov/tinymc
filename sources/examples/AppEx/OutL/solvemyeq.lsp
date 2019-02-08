 (
  tree=statement l=53 c=0
  stmnt=
   (
    tree=fnc_def l=53 c=0 name="solvemyeq"
    func=
     (
      tree=usr_func l=53 c=0 name="solvemyeq"
      params=
      (list=par
       (
        tree=ident l=1 c=0 name="a"
       )
       (
        tree=ident l=1 c=0 name="b"
       )
       (
        tree=ident l=1 c=0 name="ep1"
       )
      )
      results=
      (list=par
       (
        tree=ident l=1 c=0 name="S"
       )
      )
      statements=
      (list=statement
       (
        tree=statement l=3 c=0
        stmnt=
         (
          tree=decl_cmd l=3 c=0 decl="global"
          declars=
           (list=decl
            (
             tree=ident l=3 c=0 name="ite"
            )
           )
         )
       )
       (
        tree=statement l=4 c=0
        stmnt=
         (
          tree=s_assign l=4 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=4 c=0 name="ite"
          )
          rhs=
          (
           tree=const l=4 c=0 type="R8" val=0.000000000000000e+000
          )
         )
       )
       (
        tree=statement l=8 c=0
        stmnt=
         (
          tree=if l=8 c=0
          if_cmds=
           (list=if_clause
            (
             tree=if_clause l=8 c=0
             if_exp=
             (
              tree=bin_expr l=7 c=0 type=0 op="<"
              lhs=
              (
               tree=ident l=6 c=0 name="ep1"
              )
              rhs=
              (
               tree=bin_expr l=7 c=0 type=0 op="*"
               lhs=
               (
                tree=ident l=6 c=0 name="eps"
               )
               rhs=
               (
                tree=const l=6 c=0 type="R8" val=5.000000000000000e+000
               )
              )
             )
             statements=
             (list=statement
              (
               tree=statement l=7 c=0
               stmnt=
                (
                 tree=s_assign l=7 c=0 type=0 op="="
                 lhs=
                 (
                  tree=ident l=7 c=0 name="ep1"
                 )
                 rhs=
                 (
                  tree=bin_expr l=7 c=0 type=0 op="*"
                  lhs=
                  (
                   tree=ident l=7 c=0 name="eps"
                  )
                  rhs=
                  (
                   tree=const l=7 c=0 type="R8" val=5.000000000000000e+000
                  )
                 )
                )
              )
             )            )
           )
         )
       )
       (
        tree=statement l=10 c=0
        stmnt=
         (
          tree=s_assign l=10 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=10 c=0 name="y1"
          )
          rhs=
          (
           tree=indx_expr l=10 c=0 type="matr"
           args=(list=argument
            (
             tree=ident l=10 c=0 name="a"
            )
           )
           e=
           (
            tree=ident l=10 c=0 name="myeq"
           )
          )
         )
       )
       (
        tree=statement l=11 c=0
        stmnt=
         (
          tree=s_assign l=11 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=11 c=0 name="y2"
          )
          rhs=
          (
           tree=indx_expr l=11 c=0 type="matr"
           args=(list=argument
            (
             tree=ident l=11 c=0 name="b"
            )
           )
           e=
           (
            tree=ident l=11 c=0 name="myeq"
           )
          )
         )
       )
       (
        tree=statement l=15 c=0
        stmnt=
         (
          tree=if l=15 c=0
          if_cmds=
           (list=if_clause
            (
             tree=if_clause l=15 c=0
             if_exp=
             (
              tree=bin_expr l=13 c=0 type=0 op="=="
              lhs=
              (
               tree=indx_expr l=12 c=0 type="matr"
               args=(list=argument
                (
                 tree=ident l=12 c=0 name="y1"
                )
               )
               e=
               (
                tree=ident l=12 c=0 name="sign"
               )
              )
              rhs=
              (
               tree=indx_expr l=12 c=0 type="matr"
               args=(list=argument
                (
                 tree=ident l=12 c=0 name="y2"
                )
               )
               e=
               (
                tree=ident l=12 c=0 name="sign"
               )
              )
             )
             statements=
             (list=statement
              (
               tree=statement l=13 c=0
               stmnt=
                (
                 tree=s_assign l=13 c=0 type=0 op="="
                 lhs=
                 (
                  tree=ident l=13 c=0 name="S"
                 )
                 rhs=
                 (
                  tree=const l=-1 c=-1 type="MN" val=(nil)
                 )
                )
              )
              (
               tree=statement l=14 c=0
               stmnt=
                (
                 tree=return l=14 c=0
                )
              )
             )            )
           )
         )
       )
       (
        tree=statement l=17 c=0
        stmnt=
         (
          tree=s_assign l=17 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=17 c=0 name="x1"
          )
          rhs=
          (
           tree=ident l=17 c=0 name="a"
          )
         )
       )
       (
        tree=statement l=18 c=0
        stmnt=
         (
          tree=s_assign l=18 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=18 c=0 name="x2"
          )
          rhs=
          (
           tree=ident l=18 c=0 name="b"
          )
         )
       )
       (
        tree=statement l=31 c=0
        stmnt=
         (
          tree=while l=31 c=0
          w_exp=
          (
           tree=bin_expr l=21 c=0 type=0 op=">"
           lhs=
           (
            tree=indx_expr l=20 c=0 type="matr"
            args=(list=argument
             (
              tree=bin_expr l=20 c=0 type=0 op="-"
              lhs=
              (
               tree=ident l=20 c=0 name="x1"
              )
              rhs=
              (
               tree=ident l=20 c=0 name="x2"
              )
             )
            )
            e=
            (
             tree=ident l=20 c=0 name="abs"
            )
           )
           rhs=
           (
            tree=ident l=21 c=0 name="ep1"
           )
          )
          statements=
          (list=statement            (
            tree=statement l=21 c=0
            stmnt=
             (
              tree=s_assign l=21 c=0 type=0 op="="
              lhs=
              (
               tree=ident l=21 c=0 name="x0"
              )
              rhs=
              (
               tree=bin_expr l=21 c=0 type=0 op="*"
               lhs=
               (
                tree=const l=21 c=0 type="R8" val=5.000000000000000e-001
               )
               rhs=
               (
                tree=bin_expr l=21 c=0 type=0 op="+"
                lhs=
                (
                 tree=ident l=21 c=0 name="x1"
                )
                rhs=
                (
                 tree=ident l=21 c=0 name="x2"
                )
               )
              )
             )
           )
           (
            tree=statement l=22 c=0
            stmnt=
             (
              tree=s_assign l=22 c=0 type=0 op="="
              lhs=
              (
               tree=ident l=22 c=0 name="y0"
              )
              rhs=
              (
               tree=indx_expr l=22 c=0 type="matr"
               args=(list=argument
                (
                 tree=ident l=22 c=0 name="x0"
                )
               )
               e=
               (
                tree=ident l=22 c=0 name="myeq"
               )
              )
             )
           )
           (
            tree=statement l=25 c=0
            stmnt=
             (
              tree=if l=25 c=0
              if_cmds=
               (list=if_clause
                (
                 tree=if_clause l=25 c=0
                 if_exp=
                 (
                  tree=bin_expr l=24 c=0 type=0 op="<="
                  lhs=
                  (
                   tree=indx_expr l=23 c=0 type="matr"
                   args=(list=argument
                    (
                     tree=ident l=23 c=0 name="y0"
                    )
                   )
                   e=
                   (
                    tree=ident l=23 c=0 name="abs"
                   )
                  )
                  rhs=
                  (
                   tree=ident l=24 c=0 name="eps"
                  )
                 )
                 statements=
                 (list=statement
                  (
                   tree=statement l=24 c=0
                   stmnt=
                    (
                     tree=break l=24 c=0
                    )
                  )
                 )                )
               )
             )
           )
           (
            tree=statement l=30 c=0
            stmnt=
             (
              tree=if l=30 c=0
              if_cmds=
               (list=if_clause
                (
                 tree=if_clause l=30 c=0
                 if_exp=
                 (
                  tree=bin_expr l=27 c=0 type=0 op="!="
                  lhs=
                  (
                   tree=indx_expr l=26 c=0 type="matr"
                   args=(list=argument
                    (
                     tree=ident l=26 c=0 name="y0"
                    )
                   )
                   e=
                   (
                    tree=ident l=26 c=0 name="sign"
                   )
                  )
                  rhs=
                  (
                   tree=indx_expr l=26 c=0 type="matr"
                   args=(list=argument
                    (
                     tree=ident l=26 c=0 name="x0"
                    )
                   )
                   e=
                   (
                    tree=ident l=26 c=0 name="sign"
                   )
                  )
                 )
                 statements=
                 (list=statement
                  (
                   tree=statement l=27 c=0
                   stmnt=
                    (
                     tree=s_assign l=27 c=0 type=0 op="="
                     lhs=
                     (
                      tree=ident l=27 c=0 name="x2"
                     )
                     rhs=
                     (
                      tree=ident l=27 c=0 name="x0"
                     )
                    )
                  )
                 )                )
                (
                 tree=if_clause l=30 c=0
                 if_exp=
                 (nil)
                 statements=
                 (list=statement
                  (
                   tree=statement l=29 c=0
                   stmnt=
                    (
                     tree=s_assign l=29 c=0 type=0 op="="
                     lhs=
                     (
                      tree=ident l=29 c=0 name="x1"
                     )
                     rhs=
                     (
                      tree=ident l=29 c=0 name="x0"
                     )
                    )
                  )
                 )                )
               )
             )
           )
          )         )
       )
       (
        tree=statement l=33 c=0
        stmnt=
         (
          tree=s_assign l=33 c=0 type=0 op="="
          lhs=
          (
           tree=fn_expr l=33 c=0 type="fn" field="x0"
           e=
           (
            tree=ident l=33 c=0 name="S"
           )
          )
          rhs=
          (
           tree=ident l=33 c=0 name="x0"
          )
         )
       )
       (
        tree=statement l=34 c=0
        stmnt=
         (
          tree=s_assign l=34 c=0 type=0 op="="
          lhs=
          (
           tree=fn_expr l=34 c=0 type="fn" field="y0"
           e=
           (
            tree=ident l=34 c=0 name="S"
           )
          )
          rhs=
          (
           tree=ident l=34 c=0 name="y0"
          )
         )
       )
       (
        tree=statement l=36 c=0
        stmnt=
         (
          tree=s_assign l=36 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=36 c=0 name="xx"
          )
          rhs=
          (
           tree=matrix l=-1 c=-1
           rows=
           (list=argument_list
            (tree=argument_list
            arguments=
             (list=argument
               (
                tree=const l=36 c=0 type="R8" val=1.000000000000000e+000
               )
               (
                tree=const l=36 c=0 type="R8" val=3.000000000000000e+000
               )
               (
                tree=const l=36 c=0 type="R8" val=4.000000000000000e+000
               )
               (
                tree=const l=36 c=0 type="R8" val=5.000000000000000e+000
               )
               (
                tree=const l=36 c=0 type="R8" val=6.000000000000000e+000
               )
               (
                tree=const l=36 c=0 type="R8" val=1.000000000000000e+004
               )
             )
            )
           )          )
         )
       )
       (
        tree=statement l=37 c=0
        stmnt=
         (
          tree=s_assign l=37 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=37 c=0 name="rr"
          )
          rhs=
          (
           tree=indx_expr l=37 c=0 type="matr"
           args=(list=argument
            (
             tree=ident l=37 c=0 name="xx"
            )
           )
           e=
           (
            tree=ident l=37 c=0 name="roots"
           )
          )
         )
       )
       (
        tree=statement l=38 c=0
        stmnt=
         (
          tree=indx_expr l=38 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=38 c=0 name="rr"
           )
          )
          e=
          (
           tree=ident l=38 c=0 name="disp"
          )
         )
       )
       (
        tree=statement l=39 c=0
        stmnt=
         (
          tree=s_assign l=39 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=39 c=0 name="yy"
          )
          rhs=
          (
           tree=indx_expr l=39 c=0 type="matr"
           args=(list=argument
            (
             tree=ident l=39 c=0 name="xx"
            )
            (
             tree=ident l=39 c=0 name="rr"
            )
           )
           e=
           (
            tree=ident l=39 c=0 name="polyval"
           )
          )
         )
       )
       (
        tree=statement l=40 c=0
        stmnt=
         (
          tree=indx_expr l=40 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=40 c=0 name="yy"
           )
          )
          e=
          (
           tree=ident l=40 c=0 name="disp"
          )
         )
       )
       (
        tree=statement l=42 c=0
        stmnt=
         (
          tree=s_assign l=42 c=0 type=0 op="="
          lhs=
          (
           tree=fn_expr l=42 c=0 type="fn" field="rr"
           e=
           (
            tree=ident l=42 c=0 name="S"
           )
          )
          rhs=
          (
           tree=ident l=42 c=0 name="rr"
          )
         )
       )
       (
        tree=statement l=43 c=0
        stmnt=
         (
          tree=s_assign l=43 c=0 type=0 op="="
          lhs=
          (
           tree=fn_expr l=43 c=0 type="fn" field="yy"
           e=
           (
            tree=ident l=43 c=0 name="S"
           )
          )
          rhs=
          (
           tree=ident l=43 c=0 name="yy"
          )
         )
       )
       (
        tree=statement l=51 c=0
        stmnt=
         (
          tree=indx_expr l=51 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=51 c=0 name="S"
           )
          )
          e=
          (
           tree=ident l=51 c=0 name="disp"
          )
         )
       )
      )
     )
   )
 )
 (
  tree=statement l=60 c=0
  stmnt=
   (
    tree=fnc_def l=60 c=0 name="myeq"
    func=
     (
      tree=usr_func l=60 c=0 name="myeq"
      params=
      (list=par
       (
        tree=ident l=53 c=0 name="x"
       )
      )
      results=
      (list=par
       (
        tree=ident l=53 c=0 name="y"
       )
      )
      statements=
      (list=statement
       (
        tree=statement l=55 c=0
        stmnt=
         (
          tree=decl_cmd l=55 c=0 decl="global"
          declars=
           (list=decl
            (
             tree=ident l=54 c=0 name="ite"
            )
           )
         )
       )
       (
        tree=statement l=55 c=0
        stmnt=
         (
          tree=s_assign l=55 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=55 c=0 name="y"
          )
          rhs=
          (
           tree=bin_expr l=55 c=0 type=0 op="+"
           lhs=
           (
            tree=bin_expr l=55 c=0 type=0 op="-"
            lhs=
            (
             tree=bin_expr l=55 c=0 type=0 op=".*"
             lhs=
             (
              tree=bin_expr l=55 c=0 type=0 op=".^"
              lhs=
              (
               tree=ident l=55 c=0 name="x"
              )
              rhs=
              (
               tree=const l=55 c=0 type="R8" val=2.000000000000000e+000
              )
             )
             rhs=
             (
              tree=indx_expr l=55 c=0 type="matr"
              args=(list=argument
               (
                tree=ident l=55 c=0 name="x"
               )
              )
              e=
              (
               tree=ident l=55 c=0 name="sin"
              )
             )
            )
            rhs=
            (
             tree=bin_expr l=55 c=0 type=0 op=".*"
             lhs=
             (
              tree=bin_expr l=55 c=0 type=0 op=".^"
              lhs=
              (
               tree=ident l=55 c=0 name="x"
              )
              rhs=
              (
               tree=const l=55 c=0 type="R8" val=3.000000000000000e+000
              )
             )
             rhs=
             (
              tree=indx_expr l=55 c=0 type="matr"
              args=(list=argument
               (
                tree=ident l=55 c=0 name="x"
               )
              )
              e=
              (
               tree=ident l=55 c=0 name="cos"
              )
             )
            )
           )
           rhs=
           (
            tree=ident l=55 c=0 name="x"
           )
          )
         )
       )
       (
        tree=statement l=57 c=0
        stmnt=
         (
          tree=s_assign l=57 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=57 c=0 name="y"
          )
          rhs=
          (
           tree=indx_expr l=57 c=0 type="matr"
           args=(list=argument
            (
             tree=ident l=57 c=0 name="y"
            )
            (
             tree=ident l=57 c=0 name="y"
            )
           )
           e=
           (
            tree=ident l=57 c=0 name="ExMex1"
           )
          )
         )
       )
       (
        tree=statement l=58 c=0
        stmnt=
         (
          tree=s_assign l=58 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=58 c=0 name="ite"
          )
          rhs=
          (
           tree=bin_expr l=58 c=0 type=0 op="+"
           lhs=
           (
            tree=ident l=58 c=0 name="ite"
           )
           rhs=
           (
            tree=const l=58 c=0 type="R8" val=1.000000000000000e+000
           )
          )
         )
       )
      )
     )
   )
 )
