 (
  tree=statement l=61 c=0
  stmnt=
   (
    tree=fnc_def l=61 c=0 name="TestO"
    func=
     (
      tree=usr_func l=61 c=0 name="TestO"
      params=
      (list=par
       (
        tree=ident l=1 c=0 name="x"
       )
      )
      results=
      (list=par
       (
        tree=ident l=1 c=0 name="y"
       )
      )
      statements=
      (list=statement
       (
        tree=statement l=4 c=0
        stmnt=
         (
          tree=decl_cmd l=4 c=0 decl="global"
          declars=
           (list=decl
            (
             tree=ident l=4 c=0 name="ite"
            )
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
           tree=ident l=10 c=0 name="MG"
          )
          rhs=
          (
           tree=const l=10 c=0 type="R8" val=1.000000000000000e+002
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
           tree=ident l=11 c=0 name="AL"
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
                tree=const l=11 c=0 type="R8" val=1.000000000000000e+001
               )
               (
                tree=const l=11 c=0 type="R8" val=1.000000000000000e+002
               )
               (
                tree=const l=11 c=0 type="R8" val=1.000000000000000e+002
               )
               (
                tree=const l=11 c=0 type="R8" val=2.000000000000000e+002
               )
               (
                tree=const l=11 c=0 type="R8" val=3.000000000000000e+002
               )
               (
                tree=const l=11 c=0 type="R8" val=4.000000000000000e+002
               )
             )
            )
           )          )
         )
       )
       (
        tree=statement l=12 c=0
        stmnt=
         (
          tree=s_assign l=12 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=12 c=0 name="Ib"
          )
          rhs=
          (
           tree=indx_expr l=12 c=0 type="matr"
           args=(list=argument
            (
             tree=bin_expr l=12 c=0 type=0 op="&"
             lhs=
             (
              tree=bin_expr l=12 c=0 type=0 op=">="
              lhs=
              (
               tree=indx_expr l=12 c=0 type="matr"
               args=(list=argument
                (
                 tree=colon_expr l=12 c=0
                 base=
                 (
                  tree=const l=12 c=0 type="R8" val=1.000000000000000e+000
                 )
                 lim=
                 (
                  tree=bin_expr l=12 c=0 type=0 op="-"
                  lhs=
                  (
                   tree=ident l=12 c=0 name="__end__"
                  )
                  rhs=
                  (
                   tree=const l=12 c=0 type="R8" val=1.000000000000000e+000
                  )
                 )
                 inc=
                 (nil)
                )
               )
               e=
               (
                tree=ident l=12 c=0 name="AL"
               )
              )
              rhs=
              (
               tree=ident l=12 c=0 name="MG"
              )
             )
             rhs=
             (
              tree=bin_expr l=12 c=0 type=0 op="<"
              lhs=
              (
               tree=indx_expr l=12 c=0 type="matr"
               args=(list=argument
                (
                 tree=colon_expr l=12 c=0
                 base=
                 (
                  tree=const l=12 c=0 type="R8" val=2.000000000000000e+000
                 )
                 lim=
                 (
                  tree=ident l=12 c=0 name="__end__"
                 )
                 inc=
                 (nil)
                )
               )
               e=
               (
                tree=ident l=12 c=0 name="AL"
               )
              )
              rhs=
              (
               tree=ident l=12 c=0 name="MG"
              )
             )
            )
           )
           e=
           (
            tree=ident l=12 c=0 name="find"
           )
          )
         )
       )
       (
        tree=statement l=13 c=0
        stmnt=
         (
          tree=indx_expr l=13 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=13 c=0 name="Ib"
           )
          )
          e=
          (
           tree=ident l=13 c=0 name="disp"
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
       (
        tree=statement l=16 c=0
        stmnt=
         (
          tree=s_assign l=16 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=16 c=0 name="x"
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
                tree=colon_expr l=16 c=0
                base=
                (
                 tree=const l=16 c=0 type="R8" val=1.000000000000000e+000
                )
                lim=
                (
                 tree=const l=16 c=0 type="R8" val=1.000000000000000e+002
                )
                inc=
                (nil)
               )
             )
            )
           )          )
         )
       )
       (
        tree=statement l=17 c=0
        stmnt=
         (
          tree=s_assign l=17 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=17 c=0 name="S"
          )
          rhs=
          (
           tree=indx_expr l=17 c=0 type="matr"
           args=(list=argument
            (
             tree=const l=17 c=0 type="R8" val=2.000000000000000e+000
            )
            (
             tree=const l=17 c=0 type="R8" val=1.000000000000000e+000
            )
           )
           e=
           (
            tree=ident l=17 c=0 name="cell"
           )
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
           tree=fn_expr l=18 c=0 type="fn" field="r"
           e=
           (
            tree=indx_expr l=18 c=0 type="cell"
            args=(list=argument
             (
              tree=const l=18 c=0 type="R8" val=1.000000000000000e+000
             )
            )
            e=
            (
             tree=ident l=18 c=0 name="S"
            )
           )
          )
          rhs=
          (
           tree=ident l=18 c=0 name="x"
          )
         )
       )
       (
        tree=statement l=19 c=0
        stmnt=
         (
          tree=s_assign l=19 c=0 type=0 op="="
          lhs=
          (
           tree=fn_expr l=19 c=0 type="fn" field="r"
           e=
           (
            tree=indx_expr l=19 c=0 type="cell"
            args=(list=argument
             (
              tree=const l=19 c=0 type="R8" val=2.000000000000000e+000
             )
            )
            e=
            (
             tree=ident l=19 c=0 name="S"
            )
           )
          )
          rhs=
          (
           tree=bin_expr l=19 c=0 type=0 op="*"
           lhs=
           (
            tree=ident l=19 c=0 name="x"
           )
           rhs=
           (
            tree=const l=19 c=0 type="R8" val=2.000000000000000e+000
           )
          )
         )
       )
       (
        tree=statement l=20 c=0
        stmnt=
         (
          tree=s_assign l=20 c=0 type=0 op="="
          lhs=
          (
           tree=indx_expr l=20 c=0 type="cell"
           args=(list=argument
            (
             tree=ident l=20 c=0 name="__end__"
            )
           )
           e=
           (
            tree=ident l=20 c=0 name="S"
           )
          )
          rhs=
          (
           tree=const l=20 c=0 type="R8" val=4.400000000000000e+001
          )
         )
       )
       (
        tree=statement l=21 c=0
        stmnt=
         (
          tree=indx_expr l=21 c=0 type="matr"
          args=(list=argument
           (
            tree=matrix l=-1 c=-1
            rows=
            (list=argument_list
             (tree=argument_list
             arguments=
              (list=argument
                (
                 tree=const l=21 c=0 type="STR" val='R='
                )
                (
                 tree=indx_expr l=21 c=0 type="matr"
                 args=(list=argument
                  (
                   tree=indx_expr l=21 c=0 type="matr"
                   args=(list=argument
                    (
                     tree=bin_expr l=21 c=0 type=0 op="-"
                     lhs=
                     (
                      tree=ident l=21 c=0 name="__end__"
                     )
                     rhs=
                     (
                      tree=const l=21 c=0 type="R8" val=1.000000000000000e+000
                     )
                    )
                   )
                   e=
                   (
                    tree=fn_expr l=21 c=0 type="fn" field="r"
                    e=
                    (
                     tree=indx_expr l=21 c=0 type="cell"
                     args=(list=argument
                      (
                       tree=bin_expr l=21 c=0 type=0 op="-"
                       lhs=
                       (
                        tree=ident l=21 c=0 name="__end__"
                       )
                       rhs=
                       (
                        tree=const l=21 c=0 type="R8" val=1.000000000000000e+000
                       )
                      )
                     )
                     e=
                     (
                      tree=ident l=21 c=0 name="S"
                     )
                    )
                   )
                  )
                 )
                 e=
                 (
                  tree=ident l=21 c=0 name="num2str"
                 )
                )
              )
             )
            )           )
          )
          e=
          (
           tree=ident l=21 c=0 name="disp"
          )
         )
       )
       (
        tree=statement l=22 c=0
        stmnt=
         (
          tree=indx_expr l=22 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=22 c=0 name="S"
           )
          )
          e=
          (
           tree=ident l=22 c=0 name="disp"
          )
         )
       )
       (
        tree=statement l=23 c=0
        stmnt=
         (
          tree=s_assign l=23 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=23 c=0 name="K"
          )
          rhs=
          (
           tree=ident l=23 c=0 name="struct"
          )
         )
       )
       (
        tree=statement l=24 c=0
        stmnt=
         (
          tree=s_assign l=24 c=0 type=0 op="="
          lhs=
          (
           tree=fn_expr l=24 c=0 type="fn" field="y"
           e=
           (
            tree=ident l=24 c=0 name="K"
           )
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
                tree=colon_expr l=24 c=0
                base=
                (
                 tree=const l=24 c=0 type="R8" val=1.000000000000000e+000
                )
                lim=
                (
                 tree=const l=24 c=0 type="R8" val=1.000000000000000e+002
                )
                inc=
                (nil)
               )
             )
            )
           )          )
         )
       )
       (
        tree=statement l=25 c=0
        stmnt=
         (
          tree=indx_expr l=25 c=0 type="matr"
          args=(list=argument
           (
            tree=indx_expr l=25 c=0 type="matr"
            args=(list=argument
             (
              tree=bin_expr l=25 c=0 type=0 op="-"
              lhs=
              (
               tree=ident l=25 c=0 name="__end__"
              )
              rhs=
              (
               tree=const l=25 c=0 type="R8" val=3.000000000000000e+000
              )
             )
            )
            e=
            (
             tree=fn_expr l=25 c=0 type="fn" field="y"
             e=
             (
              tree=indx_expr l=25 c=0 type="matr"
              args=(list=argument
               (
                tree=ident l=25 c=0 name="__end__"
               )
              )
              e=
              (
               tree=ident l=25 c=0 name="K"
              )
             )
            )
           )
          )
          e=
          (
           tree=ident l=25 c=0 name="disp"
          )
         )
       )
       (
        tree=statement l=29 c=0
        stmnt=
         (
          tree=s_assign l=29 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=29 c=0 name="a"
          )
          rhs=
          (
           tree=un_expr l=29 c=0  type=0 op="-"
           operand=
           (
            tree=const l=29 c=0 type="R8" val=5.000000000000000e+000
           )
          )
         )
       )
       (
        tree=statement l=30 c=0
        stmnt=
         (
          tree=s_assign l=30 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=30 c=0 name="b"
          )
          rhs=
          (
           tree=const l=30 c=0 type="R8" val=5.000000000000000e+001
          )
         )
       )
       (
        tree=statement l=31 c=0
        stmnt=
         (
          tree=s_assign l=31 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=31 c=0 name="Len"
          )
          rhs=
          (
           tree=ident l=31 c=0 name="x"
          )
         )
       )
       (
        tree=statement l=32 c=0
        stmnt=
         (
          tree=s_assign l=32 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=32 c=0 name="e"
          )
          rhs=
          (
           tree=indx_expr l=32 c=0 type="matr"
           args=(list=argument
            (
             tree=un_expr l=32 c=0  type=0 op="-"
             operand=
             (
              tree=const l=32 c=0 type="R8" val=5.000000000000000e+000
             )
            )
            (
             tree=un_expr l=32 c=0  type=0 op="-"
             operand=
             (
              tree=const l=32 c=0 type="R8" val=2.000000000000000e+000
             )
            )
            (
             tree=ident l=32 c=0 name="Len"
            )
           )
           e=
           (
            tree=ident l=32 c=0 name="logspace"
           )
          )
         )
       )
       (
        tree=statement l=33 c=0
        stmnt=
         (
          tree=s_assign l=33 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=33 c=0 name="e"
          )
          rhs=
          (
           tree=indx_expr l=33 c=0 type="matr"
           args=(list=argument
            (
             tree=ident l=33 c=0 name="e"
            )
           )
           e=
           (
            tree=ident l=33 c=0 name="fliplr"
           )
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
           tree=ident l=34 c=0 name="y"
          )
          rhs=
          (
           tree=indx_expr l=34 c=0 type="matr"
           args=(list=argument
            (
             tree=const l=34 c=0 type="R8" val=1.000000000000000e+000
            )
            (
             tree=ident l=34 c=0 name="Len"
            )
           )
           e=
           (
            tree=ident l=34 c=0 name="zeros"
           )
          )
         )
       )
       (
        tree=statement l=35 c=0
        stmnt=
         (
          tree=s_assign l=35 c=0 type=0 op="="
          lhs=
          (
           tree=ident l=35 c=0 name="x"
          )
          rhs=
          (
           tree=ident l=35 c=0 name="y"
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
           tree=ident l=36 c=0 name="z"
          )
          rhs=
          (
           tree=ident l=36 c=0 name="y"
          )
         )
       )
       (
        tree=statement l=44 c=0
        stmnt=
         (
          tree=for l=44 c=0
          lmodify_exp=
          (
           tree=ident l=37 c=0 name="k"
          )
          reval_exp=
          (
           tree=colon_expr l=38 c=0
           base=
           (
            tree=const l=37 c=0 type="R8" val=1.000000000000000e+000
           )
           lim=
           (
            tree=indx_expr l=37 c=0 type="matr"
            args=(list=argument
             (
              tree=ident l=37 c=0 name="e"
             )
            )
            e=
            (
             tree=ident l=37 c=0 name="length"
            )
           )
           inc=
           (nil)
          )
          statements=
          (list=statement
           (
            tree=statement l=38 c=0
            stmnt=
             (
              tree=s_assign l=38 c=0 type=0 op="="
              lhs=
              (
               tree=ident l=38 c=0 name="ep1"
              )
              rhs=
              (
               tree=indx_expr l=38 c=0 type="matr"
               args=(list=argument
                (
                 tree=ident l=38 c=0 name="k"
                )
               )
               e=
               (
                tree=ident l=38 c=0 name="e"
               )
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
               tree=ident l=39 c=0 name="S"
              )
              rhs=
              (
               tree=indx_expr l=39 c=0 type="matr"
               args=(list=argument
                (
                 tree=ident l=39 c=0 name="a"
                )
                (
                 tree=ident l=39 c=0 name="b"
                )
                (
                 tree=ident l=39 c=0 name="ep1"
                )
               )
               e=
               (
                tree=ident l=39 c=0 name="solvemyeq"
               )
              )
             )
           )
           (
            tree=statement l=43 c=0
            stmnt=
             (
              tree=if l=43 c=0
              if_cmds=
               (list=if_clause
                (
                 tree=if_clause l=43 c=0
                 if_exp=
                 (
                  tree=un_expr l=41 c=0  type=0 op="!"
                  operand=
                  (
                   tree=indx_expr l=40 c=0 type="matr"
                   args=(list=argument
                    (
                     tree=ident l=40 c=0 name="S"
                    )
                   )
                   e=
                   (
                    tree=ident l=40 c=0 name="isempty"
                   )
                  )
                 )
                 statements=
                 (list=statement
                  (
                   tree=statement l=41 c=0
                   stmnt=
                    (
                     tree=s_assign l=41 c=0 type=0 op="="
                     lhs=
                     (
                      tree=indx_expr l=41 c=0 type="matr"
                      args=(list=argument
                       (
                        tree=ident l=41 c=0 name="k"
                       )
                      )
                      e=
                      (
                       tree=ident l=41 c=0 name="y"
                      )
                     )
                     rhs=
                     (
                      tree=fn_expr l=41 c=0 type="fn" field="y0"
                      e=
                      (
                       tree=ident l=41 c=0 name="S"
                      )
                     )
                    )
                  )
                  (
                   tree=statement l=41 c=0
                   stmnt=
                    (
                     tree=s_assign l=41 c=0 type=0 op="="
                     lhs=
                     (
                      tree=indx_expr l=41 c=0 type="matr"
                      args=(list=argument
                       (
                        tree=ident l=41 c=0 name="k"
                       )
                      )
                      e=
                      (
                       tree=ident l=41 c=0 name="x"
                      )
                     )
                     rhs=
                     (
                      tree=fn_expr l=41 c=0 type="fn" field="x0"
                      e=
                      (
                       tree=ident l=41 c=0 name="S"
                      )
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
                      tree=indx_expr l=42 c=0 type="matr"
                      args=(list=argument
                       (
                        tree=ident l=42 c=0 name="k"
                       )
                      )
                      e=
                      (
                       tree=ident l=42 c=0 name="z"
                      )
                     )
                     rhs=
                     (
                      tree=ident l=42 c=0 name="ite"
                     )
                    )
                  )
                 )                )
               )
             )
           )
          )
         )
       )
       (
        tree=statement l=45 c=0
        stmnt=
         (
          tree=indx_expr l=45 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=45 c=0 type="STR" val='res.mat'
           )
           (
            tree=const l=45 c=0 type="STR" val='y'
           )
           (
            tree=const l=45 c=0 type="STR" val='x'
           )
           (
            tree=const l=45 c=0 type="STR" val='z'
           )
          )
          e=
          (
           tree=ident l=45 c=0 name="save"
          )
         )
       )
       (
        tree=statement l=49 c=0
        stmnt=
         (
          tree=return l=49 c=0
         )
       )
       (
        tree=statement l=51 c=0
        stmnt=
         (
          tree=indx_expr l=51 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=51 c=0 type="R8" val=1.000000000000000e+001
           )
          )
          e=
          (
           tree=ident l=51 c=0 name="figure"
          )
         )
       )
       (
        tree=statement l=52 c=0
        stmnt=
         (
          tree=indx_expr l=52 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=52 c=0 type="R8" val=3.000000000000000e+000
           )
           (
            tree=const l=52 c=0 type="R8" val=1.000000000000000e+000
           )
           (
            tree=const l=52 c=0 type="R8" val=1.000000000000000e+000
           )
          )
          e=
          (
           tree=ident l=52 c=0 name="subplot"
          )
         )
       )
       (
        tree=statement l=53 c=0
        stmnt=
         (
          tree=indx_expr l=53 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=53 c=0 name="e"
           )
           (
            tree=ident l=53 c=0 name="y"
           )
           (
            tree=const l=53 c=0 type="STR" val='b'
           )
          )
          e=
          (
           tree=ident l=53 c=0 name="plot"
          )
         )
       )
       (
        tree=statement l=53 c=0
        stmnt=
         (
          tree=indx_expr l=53 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=53 c=0 type="STR" val='on'
           )
          )
          e=
          (
           tree=ident l=53 c=0 name="grid"
          )
         )
       )
       (
        tree=statement l=54 c=0
        stmnt=
         (
          tree=indx_expr l=54 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=54 c=0 type="R8" val=3.000000000000000e+000
           )
           (
            tree=const l=54 c=0 type="R8" val=1.000000000000000e+000
           )
           (
            tree=const l=54 c=0 type="R8" val=2.000000000000000e+000
           )
          )
          e=
          (
           tree=ident l=54 c=0 name="subplot"
          )
         )
       )
       (
        tree=statement l=55 c=0
        stmnt=
         (
          tree=indx_expr l=55 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=55 c=0 name="e"
           )
           (
            tree=ident l=55 c=0 name="x"
           )
           (
            tree=const l=55 c=0 type="STR" val='r'
           )
          )
          e=
          (
           tree=ident l=55 c=0 name="plot"
          )
         )
       )
       (
        tree=statement l=55 c=0
        stmnt=
         (
          tree=indx_expr l=55 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=55 c=0 type="STR" val='on'
           )
          )
          e=
          (
           tree=ident l=55 c=0 name="grid"
          )
         )
       )
       (
        tree=statement l=56 c=0
        stmnt=
         (
          tree=indx_expr l=56 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=56 c=0 type="R8" val=3.000000000000000e+000
           )
           (
            tree=const l=56 c=0 type="R8" val=1.000000000000000e+000
           )
           (
            tree=const l=56 c=0 type="R8" val=3.000000000000000e+000
           )
          )
          e=
          (
           tree=ident l=56 c=0 name="subplot"
          )
         )
       )
       (
        tree=statement l=57 c=0
        stmnt=
         (
          tree=indx_expr l=57 c=0 type="matr"
          args=(list=argument
           (
            tree=ident l=57 c=0 name="e"
           )
           (
            tree=ident l=57 c=0 name="z"
           )
           (
            tree=const l=57 c=0 type="STR" val='g'
           )
          )
          e=
          (
           tree=ident l=57 c=0 name="plot"
          )
         )
       )
       (
        tree=statement l=57 c=0
        stmnt=
         (
          tree=indx_expr l=57 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=57 c=0 type="STR" val='on'
           )
          )
          e=
          (
           tree=ident l=57 c=0 name="grid"
          )
         )
       )
       (
        tree=statement l=59 c=0
        stmnt=
         (
          tree=indx_expr l=59 c=0 type="matr"
          args=(list=argument
           (
            tree=const l=59 c=0 type="STR" val='done'
           )
          )
          e=
          (
           tree=ident l=59 c=0 name="disp"
          )
         )
       )
      )
     )
   )
 )
