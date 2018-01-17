/// \file  tmcpar_tree.h
/// \brief trees classes for parsed data
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
// Syntax tree definition for parser
// File contains type definition and constructors

//TODO:
// I. create class that contains only debugging output.
// Must separate the class info:
// 1. Parser tree
// 2. Debug results
// 3. Rtl results
// II. create null-parser the only creates the tree
// 

#ifndef _tmcpar_tree_h_
#define _tmcpar_tree_h_

#include <string>

//! \enum indexing_types
//! Boolean operations
enum indexing_types
{
	indexing_matrix=0, //!< like ()
	indexing_cell=1,    //!< like {}
	indexing_field=2 //!< like a.f
};
//! \enum operation_types
//! Binary (two-operands) operations
enum operation_types
{
		operation_unknown=-1,
			operation_add=0,//!< +
			operation_sub,//!< -
			operation_mul,//!< *
			operation_el_mul,//!<  .*
			operation_el_or,//!< |
			operation_el_and,//!< &
			operation_div,//!< divide (/)
			operation_el_div,//!< scalar divide (./)
			operation_pow,//!<   power  ^
			operation_el_pow,//!< scalar power .^
			operation_ldiv,//!< left division '\'
			operation_el_ldiv,//!< sclar left division '.\'
			operation_le,//!< <=
			operation_lt,//!< <
			operation_ge,//!< >=
			operation_gt,//!< >
		    operation_ne,//!< not equal ~= 
		    operation_eq,//!< ==
};
//! \enum unary_operation_types
//! Short-curcuit boolean logical operations
enum bool_operation_types
{
			bool_operation_unknown=-1,
			bool_operation_and=0, //!< Short-circuit and (&&)
			bool_operation_or     //!< Short-circuit or  (||)
};
//! \enum unary_operation_types
//! Unary operations
enum unary_operation_types
{
			unary_operation_unknown=-1,
			unary_operation_uplus=0,//! +
			unary_operation_not,//! ~
			unary_operation_uminus,//! -
			unary_operation_transpose,//!< complex conjugate  transpose (')
			unary_operation_hermitian //!< scalar transpose (.')
};

#ifdef BLD_RTL_FEATURE
class CInstr;
class CInstrList;
#define tmclsp_list tmcpar_list
#include "tmc_rtl.h"

#endif

// for  tree_debug
extern int nTabsLevel;

#include "tmcpar_env.h"

#include "tmcpar_list.h"
#include "tmclsp_matrix.h"
#include "tmc_sym_table.h"




void printtabs(void);

//! Generic tree node information
class generic_tree
{
public:
	int const m_line;//!< source line
	int const m_column;//!< source column
	generic_tree *m_parent;//!< pointer to parent node. List elements store pointer to list node.
#ifdef BLD_RTL_FEATURE
public:
	CInstr *res_rtl; //!< stores result instructions (RTL) of the node at code generation.
#endif

public:
	generic_tree(int l=-1,int c=-1):m_line(l), m_column(c),m_parent(NULL)
#ifdef BLD_RTL_FEATURE
	,res_rtl(NULL)
#endif
	{
	};
	virtual ~generic_tree();
	int line() {return m_line;}
	int column() {return m_column;}

	generic_tree *parent() {return m_parent;};
  void	print_gen_tree();
  virtual void print_node()=0;
#ifdef BLD_RTL_FEATURE
	virtual bool is_constant() const {return false;}
	virtual bool is_while_command() {return false;};
	virtual CILabel end_ilabel(){ return 0;};
	virtual CILabel exit_ilabel(){ return 0;};
	virtual bool is_expr_colession() {return false;}
	virtual bool is_identifier() {return false;}
	virtual	bool is_expr_gen(void) const {return false;}
	//char* NoteType2string() { return "<>";}
  virtual void generate_rtl_node(CInstrList *list);// generic_tree
  void generate_rtl(CInstrList *list,bool bIsCellArray=false);
#endif
} ;

///////////////////// EXPRESSIONS ///////////////////
//! Basic class for expression node (identifier,constant,binary,unary,range,matrix,index,assigments,function handle(@@))
class T_expr_gen: public generic_tree
{
protected:
public:
  T_expr_gen(int l = -1, int c = -1) :generic_tree(l,c)
	{
	};
	virtual ~T_expr_gen();
	virtual bool is_expr_col(void) {return false;};
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents


public:
	// assignment by pointer
  T_expr_gen (const T_expr_gen&);
  T_expr_gen& operator = (const T_expr_gen&);
public:
  void print_node();
#ifdef BLD_RTL_FEATURE
	virtual	bool is_constant(void) const {return false;}
	virtual	bool is_expr_gen(void) const {return true;}
	virtual bool is_expr_bool(void) {return false;}
	virtual bool is_expr_unar (void) const { return false; }
	virtual bool is_expr_matrix(void) const {return false;}
	virtual bool is_expr_assign (void) const { return false; }
	int paren_count() {return 1;}
	virtual bool is_expr_bin (void) const { return false; }
	virtual	bool is_expr_index (void) const { return false; }
	T_expr_gen* baseexpr(void); // reduce trivial colon_expression
	void mark_expr_as_lhs_of_assignment();// to distinguish between a(n)=.. and ..=a(n).
	void mark_var_in_lhs_of_assignment();// utility to mark assigned variable.
	void	mark_mag_end(struct CIRegEx r,int dim,int ndims);
	virtual void generate_rtl_node(CInstrList *list);//T_expr_gen

#endif
};
//! Identifier node. May be variable or function.
class T_ident : public T_expr_gen
{
private:
	std::string m_ident_name;//!< Identifier name
public:
	std::string name() {return m_ident_name;};
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return true;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
private:
	int m_num_out_pars;// if the identifier is a function. By default is 1 and restored by multy-assignment or statement.
	bool m_is_func_call;
	bool m_is_lhs_in_assignment;
	struct 
	{
		bool m_is_mag_end;
		int dim;
		int ndims;
		bool is_byname;// use mat_name or mat_reg
			std::string mat_name;
			CIReg mat_reg;
	} mag_end_info;
public:
	void put_mag_end_info(struct CIRegEx _mat_name,int _dim,int _ndims)
	{
		mag_end_info.is_byname=_mat_name.is_mat_name;
		if (_mat_name.is_mat_name==true)
		{
			mag_end_info.mat_name=_mat_name.r.varname;
		}
		else
		{
			mag_end_info.mat_reg=_mat_name.r.reg;
		}
		mag_end_info.dim= _dim;mag_end_info.ndims=_ndims;
	};

	void put_mag_end_info_r(CIReg _mat_reg,int _dim,int _ndims)
	{mag_end_info.is_byname=false;mag_end_info.mat_reg=_mat_reg;mag_end_info.dim= _dim;mag_end_info.ndims=_ndims;};

	bool is_mag_end(void) {return mag_end_info.m_is_mag_end;};
	void mark_as_lhs_in_assignment() {m_is_lhs_in_assignment=true;};
	bool is_lhs_in_assignment() {return m_is_lhs_in_assignment;};
	bool virtual is_identifier() {return true;};

	void store_num_out_pars(int n) {m_num_out_pars=n;};// identifier
	void mark_as_func_call() {m_is_func_call=true;}; // identifier
	void mark_as_formal_parameter (void)
	{
		TmcSymbolTable.mark_formal(name());
	}
	void mark_as_global (void)
	{
		TmcSymbolTable.mark_global(name());
	}
	//bool IsFormalPar()
	//{
	//	return TmcSymbolTable.is_formal_par(name(),Compiler.indFunc_RTL);
	//}
	virtual void generate_rtl_node(CInstrList *ilist);// identifier
#endif
	T_ident(std::string _ident_name,int l,int c): T_expr_gen(l,c),m_ident_name(_ident_name)
#ifdef BLD_RTL_FEATURE
	,m_num_out_pars(1),//Changed  15.11.2012	m_num_out_pars(1) to 0 - not good:
	// by default must asssume that there is some return value.
		m_is_func_call(false),
		m_is_lhs_in_assignment(false) 
#endif
	{
#ifdef BLD_RTL_FEATURE
		//mag_end_info.dim=0;mag_end_info.ndims=0;mag_end_info.mat_name="x";
		mag_end_info.m_is_mag_end=false;
		if (m_ident_name.compare("__end__")==0)
		{
			CIRegEx r;
			r.is_mat_name=1;
			r.r.varname="xx?";
			put_mag_end_info(r,1,1);// marks not-constant "end"
			mag_end_info.m_is_mag_end=true;
		}
#endif
	}

};

// class for constant values

//////////////////
//! Constant node.
class T_const : public T_expr_gen
{
private:
  // assignment by pointer
  T_const (const T_const&);
  T_const& operator = (const T_const&);
public:
	// The actual value
    struct tag_tmsMatrix  * const val ; 

public:
    T_const(CONST_VAL_TYPES type,struct tree_const_val* v,int l,int c);
	~T_const();
virtual void print_node();
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
#ifdef BLD_RTL_FEATURE
public:
 	bool is_constant (void) const { return true; }
	virtual void generate_rtl_node(CInstrList *ilist);// constant
#endif
};
//! Binary and boolean expression node (\link binary_op_type \endlink, \link bool_op_type \endlink)
class T_expr_bin: public T_expr_gen
{
protected:
  // The operands for the expression.
  T_expr_gen * const op_lhs;
  T_expr_gen * const op_rhs;
protected:
	union U_bin_op
	{
		enum operation_types		binary_op_type;// The type of the expression.
		enum bool_operation_types	bool_op_type;// The type of the expression.
	}  /* const */ m_op_type;

public:
	virtual ~T_expr_bin();
    T_expr_gen *oplhs (void) { return op_lhs; }
    T_expr_gen *oprhs (void) { return op_rhs; }
	T_expr_bin (enum operation_types etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c);
	T_expr_bin (enum bool_operation_types etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c);

	static enum operation_types get_op_type(const char *op);
	enum operation_types op_type() const { return m_op_type.binary_op_type; };
private:

  // assignment by pointer
  T_expr_bin (const T_expr_bin&);
  T_expr_bin& operator = (const T_expr_bin&);
public:
virtual void print_node();
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents

#ifdef BLD_RTL_FEATURE
	bool is_expr_bin (void) const { return true; }
	virtual void generate_rtl_node(CInstrList *ilist);// binary operation
#endif
};
//! Boolean expression node ( \link bool_op_type \endlink)
class T_expr_bool : public T_expr_bin
{
public:
	T_expr_bool (enum bool_operation_types  etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c);
	static enum bool_operation_types get_op_type(const char *op);
	enum bool_operation_types op_type() const { return m_op_type.bool_op_type; };
  // assignment by pointer
  T_expr_bool (const T_expr_bool&);
  T_expr_bool& operator = (const T_expr_bool&);
public:
virtual void print_node();
#ifdef BLD_RTL_FEATURE
	virtual bool is_expr_bool(void) {return true;}
	virtual void generate_rtl_node(CInstrList *ilist);// boolean operation
#endif
};
//! Unary expression node ( \link unary_operation_types \endlink)
class T_expr_unar:public T_expr_gen
{
private:
  // The operand for the expression.
  T_expr_gen * const op;
  enum unary_operation_types  const op_type;// The type of the expression.
public:
  T_expr_unar (enum unary_operation_types etype,T_expr_gen* te,int l,int c);
  ~T_expr_unar();
  static enum unary_operation_types get_op_type(const char *op);
private:
  // assignment by pointer
  T_expr_unar (const T_expr_unar&);
  T_expr_unar& operator = (const T_expr_unar&);
public:
	T_expr_gen *get_operand() {return op;} 
	unary_operation_types get_operation() { return  op_type;}
virtual void print_node();
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
#ifdef BLD_RTL_FEATURE
	bool is_expr_unar (void) const { return true; }
	virtual void generate_rtl_node(CInstrList *ilist);// unary operation
#endif
};
//! Range expression node (like [start:increment:limit])
class T_expr_col: public T_expr_gen
{
private:
	// The components of the expression.
    T_expr_gen * const op_base;
    T_expr_gen * const op_limit;
    T_expr_gen * const op_increment;
	bool keep_childern ;
private:
  // assignment by pointer
  T_expr_col (const T_expr_col&);
  T_expr_col& operator = (const T_expr_col&);
public:
	T_expr_col(T_expr_gen* base,T_expr_gen* lim,T_expr_gen* inc,int l,int c);
	~T_expr_col();
	void mark_keep_childern()
	{
		keep_childern=true;
	}
	T_expr_gen *base()
	{
		return op_base;
	}
	T_expr_gen *limit()
	{
		return op_limit;
	}
	T_expr_gen *increment()
	{
		return op_increment;
	}
	void append_expr(T_expr_gen *e);
virtual void print_node();
	virtual bool is_expr_col(void) {return true;}
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
#ifdef BLD_RTL_FEATURE
	virtual bool is_expr_colession() {return true;};
	virtual void generate_rtl_node(CInstrList *ilist); // colon
#endif
};
//! List of expressions node  
//! Used as multi-assignment left-hand side, index expression, matrix row (\sa \link tree_matrix \endlink, \link T_expr_index \endlink, \link  T_expr_assign_many \endlink).
class L_args : public tmcpar_list<T_expr_gen *>,public generic_tree
{
private:
  // assignment by pointer
  L_args (const L_args&);
  L_args& operator = (const L_args&);
public:
	L_args(T_expr_gen *x);
	~L_args()
	{
		erase_list();
	}
void print_node(void);// { print_list();     };//new - TEMPORARY
void print_node_for_index_expression() { print_list(); } ; // new - TEMPORARY
#ifdef BLD_RTL_FEATURE
private:
	bool simple_assign_lhs;
public:
	void mark_list_as_lhs_of_assignment();
	virtual void generate_rtl(CInstrList *ilist,bool bIsCellArrayRow=false);// add columns
#endif
};
//! Matrix node. If an expression and a list of rows.
class tree_matrix : public T_expr_gen,public tmcpar_list<L_args *>
{
protected:
	bool m_is_cell;
public:
	bool is_cell_matrix() {return m_is_cell;};
	void mark_cell_matrix(bool b) {m_is_cell=b;  };
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return true;}//for legacy colon only
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return true;} // for assigmnents,  mark multi-assignment
	bool IsEmptyMatrix()
	{
		if (this->length()==0)
			return true;
		else
			return false;
	}
	tree_matrix() {m_is_cell=false;};
	~tree_matrix()
	{
		erase_list();
	}
public:
virtual void print_node();
#ifdef BLD_RTL_FEATURE
	bool is_expr_matrix(void) const {return true;}
virtual void generate_rtl_node(CInstrList *ilist);// matrix
#endif
};

//! Index expression node
class T_expr_index: public T_expr_gen
{
private:
	T_expr_gen    * const m_e; //! indexed expression 
	L_args * const m_arg_list; //! index itself
	std::string const m_fn;
	bool const m_is_fn;
	enum indexing_types const b_type;
public:
	T_expr_gen  * e() {return m_e;};
  bool is_cell_index() const {return (b_type==indexing_cell)? true:false;};
  L_args *arg_list() {return m_arg_list;};
  T_expr_index (const char*type,char* fn,T_expr_gen *e,int l , int c );
  T_expr_index (const char*type,L_args *lst,T_expr_gen *e,int l , int c );
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return true;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
virtual void print_node();
private:
  // assignment by pointer
  T_expr_index (const T_expr_index&);
  T_expr_index& operator = (const T_expr_index&);
#ifdef BLD_RTL_FEATURE
private:
	int  m_num_out_pars;//defaut=0, in mutly-ass=n,in statement=0;
	bool  m_is_lhs_in_assignment;
public:
	void mark_as_lhs_in_assignment();
	bool is_lhs_in_assignment() {return m_is_lhs_in_assignment;};
	void store_num_out_pars(int n) {m_num_out_pars=n;};
	bool mark_function__call();
	void	mark_mag_end();
	bool is_expr_index (void) const { return true; }
	virtual void generate_rtl_node(CInstrList *ilist);//index or field name

#endif
};
//! Single assignment node
class T_expr_assign_one : public T_expr_gen
{
private:
  //! The left hand side of the assignment.
  T_expr_gen * const lhs;
  //! The right hand side of the assignment.
  T_expr_gen * const rhs;
public:
	T_expr_assign_one(T_expr_gen *_lhs,T_expr_gen *_rhs,int l,int c);
	~T_expr_assign_one();
private:
	// assignment by pointer
  T_expr_assign_one (const T_expr_assign_one&);
  T_expr_assign_one& operator = (const T_expr_assign_one&);

public:
virtual void print_node();
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
#ifdef BLD_RTL_FEATURE
    bool is_expr_assign (void) const { return true; }
virtual void generate_rtl_node(CInstrList *ilist);// assignement
#endif
};

//! Multi-assignment node. Left side of function call.
class T_expr_assign_many : public T_expr_gen
{
private:
  L_args * const lhs;//! List of left-side expressions
  T_expr_gen * const rhs;//! Right-side expression
public:
  T_expr_assign_many(L_args *lst,T_expr_gen *r,int l,int c);
	~T_expr_assign_many();
  bool is_expr_assign (void) const { return true; }
  std::string get_rhs_name() //!< get identifier name of rhs for error message
  {
	  std::string ret = "";
	  if (rhs->is_expr_index())
	  {
			 T_expr_index* tei = (T_expr_index*)rhs;
			 if (tei->e()->is_ident())
			 {
				T_ident *ti = (T_ident*)tei->e();
				ret = ti->name();
			 }
	  }
	  return ret;
  }
private:
  // assignment by pointer
  T_expr_assign_many (const T_expr_assign_many&);
  T_expr_assign_many& operator = (const T_expr_assign_many&);
public:
virtual void print_node();
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return false;}
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
#ifdef BLD_RTL_FEATURE
	virtual void generate_rtl_node(CInstrList *ilist);//multi_assign
#endif
};

//! Function handle expression node (like @@foo)
class T_expr_func: public T_expr_gen
{
private:
  // assignment by pointer
  T_expr_func (const T_expr_func&);
  T_expr_func& operator = (const T_expr_func&);
private:
  std::string const fnc_name;//! function handle name
public:
	T_expr_func(const std::string f,int l, int c):T_expr_gen(l,c), fnc_name(f)
	{
	};
virtual void print_node();
	virtual bool is_expr_col(void) {return false;}
	virtual bool is_reference(void) {return true;}//for legacy colon only
	virtual bool is_ident(void) {return false;}
	virtual bool is_matrix(void) {return false;} // for assigmnents
#ifdef BLD_RTL_FEATURE
	virtual void generate_rtl_node(CInstrList *ilist);//fcn_handle
#endif
};

//! General statement node
class T_stmnt_gen: public generic_tree
{
private:
  generic_tree * const m_statement;
private:
	// assignment by pointer
  T_stmnt_gen (const T_stmnt_gen&);
  T_stmnt_gen& operator = (const T_stmnt_gen&);

public:
	~T_stmnt_gen();
	generic_tree *parent() {return m_parent;};
	T_stmnt_gen(generic_tree *x,int l,int c);
virtual void print_node();
#ifdef BLD_RTL_FEATURE
public:
	bool mark_procedure_call();// call of function without arguments.
	bool is_null_statement()
	{
		return false; // HSKOST
	};
virtual void generate_rtl_node(CInstrList *ilist);//statement
#endif
};
//! List of statements node
class L_stmnt_gen : public tmcpar_list<T_stmnt_gen *>,public generic_tree
{
private:
	  // assignment by pointer
  L_stmnt_gen (const L_stmnt_gen&);
  L_stmnt_gen& operator = (const L_stmnt_gen&);

public:
	~L_stmnt_gen();

	void store_parent(generic_tree *p) {m_parent=p;};
	L_stmnt_gen()
	{
		m_parent=NULL;
	};
	void append (T_stmnt_gen *s)
	{ 
	  tmcpar_list<T_stmnt_gen *>::append(s);
	  s->m_parent = this;
	}
	L_stmnt_gen(T_stmnt_gen *stmt):generic_tree(stmt->m_line,stmt->m_column) {
		//m_parent=NULL;
		append (stmt);
		//tmcpar_list<T_stmnt_gen *>::m_line=stmt->m_line;
		//tmcpar_list<T_stmnt_gen *>::m_column=stmt->m_column;
	};
public: 
	void print_node(void) {print_list();};//new - TEMPORARY
};

// commands
//! General command node
class T_cmd_gen : public generic_tree
{
public:
	T_cmd_gen(int l,int c):generic_tree(l,c) {};
	virtual ~T_cmd_gen();
private:
  // assignment by pointer
  T_cmd_gen (const T_cmd_gen&);
  T_cmd_gen& operator = (const T_cmd_gen&);
public:
    T_cmd_gen* get_parent_while(T_cmd_gen *t);
};
/////////////////////////////////////
class T_vardecl  : public generic_tree
{
private:
  // An initializer expression (may be zero); - not supported
  //T_expr_gen *expr;
	bool m_bIsStoredInputPar;
public:
 // An identifier to tag with the declared property.
    T_ident * const id;
  bool IsStoredInputPar(void) {return m_bIsStoredInputPar;};
  void IsStoredInputPar(bool b) {m_bIsStoredInputPar=b;};

  T_vardecl(T_ident *x) : id(x) //,expr(NULL)
	{
	};
 	~T_vardecl();
private:
  // assignment by pointer
  T_vardecl (const T_vardecl&);
  T_vardecl& operator = (const T_vardecl&);
public:
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
public:
	void mark_as_formal_parameter (void)
    {
      if (id)
        id->mark_as_formal_parameter ();
    }
	void mark_as_global (void)
    {
      if (id)
        id->mark_as_global ();
    }
	virtual void generate_rtl_node(CInstrList *list);
#endif
};

class L_vardecl : public tmcpar_list<T_vardecl *>
{
public:
	L_vardecl(void) {};
	L_vardecl(T_vardecl *t) { append (t); };
	~L_vardecl()
	{
		erase_list();
	}
public:
	void print_node(void) { print_list();     };//new - TEMPORARY
};

/////////////////////////  root : function definition ////////////////
class L_funcpar : public tmcpar_list<T_vardecl *>
{
public:
  enum in_or_out
    {
      in = 1,
      out = 2
    };
	L_funcpar(T_vardecl *t) { append (t);};
	L_funcpar() {};
	~L_funcpar();
  // assignment by pointer
  L_funcpar (const L_funcpar&);
  L_funcpar& operator = (const L_funcpar&);
public:
void print_node(void) { print_list();     };//new - TEMPORARY
#ifdef BLD_RTL_FEATURE
public:
	bool validate (in_or_out type) {return true;};
	void mark_as_formal_parameters(void)
	{
	  for (iterator p = begin (); p != end (); p++)
		{
		  T_vardecl *elt = *p;
		  elt->mark_as_formal_parameter ();
		}
	};
	bool is_in_arg(std::string par_name)
    {// return true if the argument name is found in param_list
	for ( L_funcpar::iterator p=this->begin(); p != this->end(); p++)
	{
		T_vardecl* elt = *p;
		if (elt->id->name().compare(par_name)==0)
			return true;
	}
	return false;
  }
	void generate_rtl_list(CInstrList *list,bool bIsCellRow=false);

#endif
};

/// Function definition information (member of in \link T_func_hdr \endlink )
class T_func_block :public generic_tree
{
private:
	std::string const m_fnc_name;//!< function name
	L_funcpar * const ret_list;//!< list of left-hand parameters 
    L_funcpar * const param_list;//!< list of right-hand parameters
    L_stmnt_gen * const stmt_list;//!< list of statements
public:
	std::string name() {return m_fnc_name;};//!< get function name
	int num_pars() { //! get number of right-hand parameters
		if (param_list)
			return (int)param_list->length();
		else
			return 0;
	};
  T_func_block (std::string  _fnc_name,//!< constructor 
			L_funcpar *pl,
			L_funcpar *rl,
			L_stmnt_gen *cl,int l=-1, int c=-1) : m_fnc_name(_fnc_name),ret_list(rl),
			param_list(pl),stmt_list(cl),generic_tree(l,c)
  {   
  };
  ~T_func_block();
public:
virtual void print_node();//! generate lsp-presentation
private:
  // assignment by pointer
  T_func_block (const T_func_block& f);
  T_func_block& operator = (const T_func_block& f);
#ifdef BLD_RTL_FEATURE
public:
virtual void generate_rtl_node(CInstrList *ilist);//!< Generated code for function (T_func_block)
#endif
};

/// Function definition node (cmd wrapper for \link T_func_block \endlink)
class T_func_hdr : public T_cmd_gen
{
private:
//	std::string m_func_def_name;
	T_func_block * const m_f;
public:
	T_func_hdr(T_func_block *f, int l = -1, int c = -1)
		: T_cmd_gen(l,c),m_f(f)
	{
		f->m_parent=this;
		Compiler.indFunc++;//! < increment local function enumeration. Here the function parsing is finished.
	}
	~T_func_hdr()
	{
			if (m_f) delete m_f;
	}
private:
  // assignment by pointer
  T_func_hdr (const T_func_hdr&);
  T_func_hdr& operator = (const T_func_hdr&);
public:
virtual void print_node();//! generate lsp-presentation for the function
#ifdef BLD_RTL_FEATURE
public:
virtual void generate_rtl_node(CInstrList *list);//!< generate code for the function (T_func_hdr)
#endif
};

/////////// CTRL CONSTRUCTIONS /////////////
//! return command node
class T_cmd_ctrl_return : public T_cmd_gen
{
public:
	T_cmd_ctrl_return(int l=-1, int c=-1): T_cmd_gen(l,c) {};
private:
	CILabel  get_fnc_exit_ilabel() //!< get label at function exit
	{ 
		return 1;/// \Note funtion exit label is const so far but we should reset label counter before each local function parsing
	};
  // assignment by pointer
  T_cmd_ctrl_return (const T_cmd_ctrl_return&);
  T_cmd_ctrl_return& operator = (const T_cmd_ctrl_return&);
public:
  	virtual void print_node();
#ifdef BLD_RTL_FEATURE
public:
	virtual void generate_rtl_node(CInstrList *ilist);
#endif
};

class T_cmd_decl_gen : public T_cmd_gen
{ // support for global VAR,... decalrations
  // no other declarations are supported. 
protected:
  std::string const cmd_name;
  L_vardecl * const init_list;
public:
	T_cmd_decl_gen(const std::string& n, L_vardecl *t,int l = -1, int c = -1)
		: T_cmd_gen (l, c), cmd_name (n), init_list (t)
	{
		// mark the declared variables as global
		// only 'global' declaration is supported
		//bool is_global = ((cmd_name.compare("global")==0) || (cmd_name.compare("GLOBAL")==0));
		//if (is_global==true)
		for (L_vardecl::iterator p=init_list->begin(); p !=init_list->end();p++)
		{
#ifdef BLD_RTL_FEATURE
			(*p)->mark_as_global();
#endif
		}
	};
	~T_cmd_decl_gen()
	{
		if (init_list) delete init_list;
	}
  L_vardecl *initializer_list (void) { return init_list; }
  std::string name (void) { return cmd_name; }// always 'global'
private:
  // assignment by pointer
  T_cmd_decl_gen (const T_cmd_decl_gen&);
  T_cmd_decl_gen& operator = (const T_cmd_decl_gen&);
public:
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
	virtual void generate_rtl_node(CInstrList *list);
#endif
};

class T_cmd_decl_global: public T_cmd_decl_gen
{
public:
	T_cmd_decl_global(L_vardecl *lst,int l, int c):
	T_cmd_decl_gen("global",lst,l,c)
	{};//HAZARD - implement global variables
  // assignment by pointer
  T_cmd_decl_global (const T_cmd_decl_global&);
  T_cmd_decl_global& operator = (const T_cmd_decl_global&);
};
class T_cmd_ctrl_label:  public T_cmd_gen
{
std::string m_type;
public:
	T_cmd_ctrl_label(const std::string& type, int l, int c) : T_cmd_gen(l,c)  {/* m_line=l;m_column=c;*/m_type=type;}
	virtual void print_node();
private:
  // assignment by pointer
  T_cmd_ctrl_label (const T_cmd_ctrl_label&);
  T_cmd_ctrl_label& operator = (const T_cmd_ctrl_label&);
#ifdef BLD_RTL_FEATURE
public:
	virtual void generate_rtl_node(CInstrList *list);
#endif
};
///////////////// SWITCH ////////////////////////////
//class L_stmnt_gen;
typedef struct Csw_case_val
{// structure for a value of an element of case label 
	std::string m_str;
	double      m_scalar;
	char		m_type; // 'd' or 's'
} sw_case_val;

class T_sw_case: public generic_tree
{
private:
	std::list<sw_case_val> label_value;
private:
  // The case label.
  T_expr_gen * const label;
  // The list of statements to evaluate if the label matches.
  L_stmnt_gen * const list;
public:
    // switch end label
    int ilabel_end;

	T_sw_case(L_stmnt_gen *sl,int l = -1, int c = -1)
	: generic_tree (l, c), label (0), list (sl) {list->store_parent(this);};

	T_sw_case(T_expr_gen *e,L_stmnt_gen *sl,int l,int c)
		: generic_tree (l, c), label (e), list (sl) {list->store_parent(this);};
	~T_sw_case()
	{
		if (label) delete label;
		if (list) delete	list;
	}
private:
  // assignment by pointer
  T_sw_case (const T_sw_case&);
  T_sw_case& operator = (const T_sw_case&);

  T_expr_gen * get_switch_expression(); 

  void calc_label_value(void);
public:
  	virtual void print_node();
#ifdef BLD_RTL_FEATURE
private:
	  CIReg get_switch_expression_val(); 
public:
	virtual void generate_rtl_node(CInstrList *ilist);
#endif
};
class LT_sw_cases : public tmcpar_list<T_sw_case *>,public generic_tree
{
public:
  void append(T_sw_case *t)
  {
	  tmcpar_list<T_sw_case *>::append(t);
	  t->m_parent=this;
  }

  LT_sw_cases() {};
  LT_sw_cases (T_sw_case *t)
  {
	  append (t);
  }
  ~LT_sw_cases (void)
    {
		erase_list();
    }
private:
  // assignment by pointer
  LT_sw_cases (const LT_sw_cases&);
  LT_sw_cases& operator = (const LT_sw_cases&);
public: 
	void print_node(void) {print_list();};//new - TEMPORARY
};

class T_ctrl_cmd_switch : public T_cmd_gen
{
private:
  // Value on which to switch.
  T_expr_gen * const expr;
  // List of cases (case 1, case 2, ..., default)
  LT_sw_cases * const list;
private:
  // assignment by pointer
  T_ctrl_cmd_switch (const T_ctrl_cmd_switch&);
  T_ctrl_cmd_switch& operator = (const T_ctrl_cmd_switch&);
public:
	  T_ctrl_cmd_switch (T_expr_gen *e, LT_sw_cases *lst,
		        int l = -1, int c = -1)
    : T_cmd_gen (l, c), expr (e), list (lst)
       {list->m_parent = this; }
	~T_ctrl_cmd_switch()
	{
		if (expr) delete expr;
		if (list) delete list;
	}
public:
	T_expr_gen *get_expr()
	{
		return expr;
	};

	virtual void print_node();
#ifdef BLD_RTL_FEATURE
private:
  CIReg exp_val_reg;// register for exp value
public:
		CIReg get_exp_val_reg() {return exp_val_reg;}
		virtual void generate_rtl_node(CInstrList *ilist);
#endif
};

//////////// if ////////////////////////////////
//! Single block (if,elseif,else) in IF command (\link T_ctrl_cmd_if \endlink)
class T_if_block: public generic_tree
{
private:
  //!  IF condition to test.
  T_expr_gen * const expr;
  //!   The list of statements to evaluate if expr is true.
  L_stmnt_gen * const list;
public:
    //! if end label
    int ilabel_end;

	T_if_block(L_stmnt_gen *sl,int l=-1,int c=-1)
		:generic_tree(l,c), expr (0), list (sl)
	{list->store_parent(this);};
	T_if_block(T_expr_gen *e,L_stmnt_gen *sl,int l=-1,int c=-1)
		:	generic_tree(l,c), expr (e), list (sl)
	{list->store_parent(this);};
	~T_if_block();
private:
  // assignment by pointer
  T_if_block (const T_if_block&);
  T_if_block& operator = (const T_if_block&);
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
	virtual void generate_rtl_node(CInstrList *ilist);// if clauses
#endif
};

//! List of blocks (if,elseif,else) in IF command (\link T_ctrl_cmd_if \endlink) 
class LT_if_blocks : public tmcpar_list<T_if_block *>,public generic_tree
{
public:
  void append(T_if_block *t)
  {
	  tmcpar_list<T_if_block *>::append(t);
	  t->m_parent = this;
  }
  LT_if_blocks (T_if_block *t)
  {
		append (t);
  }
	LT_if_blocks()
	{
		// HSKOST_ADDED
	}
  ~LT_if_blocks (void);
private:
  // assignment by pointer
  LT_if_blocks (const LT_if_blocks&);
  LT_if_blocks& operator = (const LT_if_blocks&);
public: 
	void print_node(void) {print_list();};//new - TEMPORARY
};
//! Full IF flow-control command node (if, elseif, elseif, ... else, endif)
class T_ctrl_cmd_if : public T_cmd_gen
{
private:
  //! List of if blocks  (if, elseif, elseif, ... else, endif)
  LT_if_blocks * const list;
public:
	T_ctrl_cmd_if (LT_if_blocks *lst,
		   int l = -1, int c = -1)
    : T_cmd_gen (l, c), list (lst)
	{ list->m_parent = this;}
	~T_ctrl_cmd_if();
private:
  // assignment by pointer
  T_ctrl_cmd_if (const T_ctrl_cmd_if&);
  T_ctrl_cmd_if& operator = (const T_ctrl_cmd_if&);
public:
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
	virtual void generate_rtl_node(CInstrList *ilist);// if command
#endif
};
/////////// while //////////////////
//! WHILE command node
class T_ctrl_cmd_while : public T_cmd_gen
{
protected:
  //! WHILE Expression to test.
  T_expr_gen * const expr;
  //! List of commands to execute.
  L_stmnt_gen * const list;
public:
  T_ctrl_cmd_while (T_expr_gen *e, L_stmnt_gen *lst,
		      int l = -1, int c = -1)
    : T_cmd_gen (l, c), expr (e), list (lst)  { list->store_parent(this);}
	~T_ctrl_cmd_while()
	{
		if (expr) delete expr;
		if (list) delete list;
	}
private:
  // assignment by pointer
  T_ctrl_cmd_while (const T_ctrl_cmd_while&);
  T_ctrl_cmd_while& operator = (const T_ctrl_cmd_while&);

public:
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
private:
  // while command's end and exit labels
  CILabel m_end_ilabel;//!< end label (for CONTINUE)
  CILabel m_exit_ilabel;//!< exit label (for BREAK or finsih)

public:
	virtual bool is_while_command(){ return true;};
	virtual CILabel end_ilabel(){ return m_end_ilabel;};
	virtual CILabel exit_ilabel(){ return m_exit_ilabel;};
	virtual void generate_rtl_node(CInstrList *ilist);// while
#endif
};
/////////////
//! CONTINUE command node
class T_ctrl_cmd_continue : public T_cmd_gen
{
public:
	T_ctrl_cmd_continue(int l, int c)
		:T_cmd_gen(l,c) {};
public:
  	virtual void print_node();
private:
  // assignment by pointer
  T_ctrl_cmd_continue (const T_ctrl_cmd_continue&);
  T_ctrl_cmd_continue& operator = (const T_ctrl_cmd_continue&);
#ifdef BLD_RTL_FEATURE
	virtual void generate_rtl_node(CInstrList *ilist);// continue
#endif
};
//! BREAK command node
class T_ctrl_cmd_break : public T_cmd_gen
{
public:
	T_ctrl_cmd_break(int l, int c)
		: T_cmd_gen (l, c) {};
private:
  // assignment by pointer
  T_ctrl_cmd_break (const T_ctrl_cmd_break&);
  T_ctrl_cmd_break& operator = (const T_ctrl_cmd_break&);
public:
  	virtual void print_node();
#ifdef BLD_RTL_FEATURE
	virtual void generate_rtl_node(CInstrList *ilist);//break
#endif
};
////////////// FOR /////////////////
//! FOR command node
class T_ctrl_cmd_for : public T_cmd_gen
{
private:
  //! Expression to modify.
  T_expr_gen * const lhs;
  //! Expression to evaluate.
  T_expr_gen * const expr;
  //! List of commands to execute.
  L_stmnt_gen * const list;
  // assignment by pointer
  T_ctrl_cmd_for (const T_ctrl_cmd_for&);
  T_ctrl_cmd_for& operator = (const T_ctrl_cmd_for&);
public:
  T_ctrl_cmd_for (T_expr_gen *le, T_expr_gen *re,
			   L_stmnt_gen *lst,
			   int l = -1, int c = -1)
    : T_cmd_gen (l, c), lhs (le), expr (re), list (lst)
    
  { list->store_parent(this);
#ifdef BLD_RTL_FEATURE
  lhs->mark_expr_as_lhs_of_assignment();
  lhs->mark_var_in_lhs_of_assignment();
#endif
  }
  ~T_ctrl_cmd_for()
  {
		if (lhs) delete lhs;
		if (expr) delete expr;
		if (list) delete list;
  }
public:
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
private:
  // while command's end and exit labels
  CILabel m_end_ilabel;//!< end label (for CONTINUE)
  CILabel m_exit_ilabel;//!< exit label (for BREAK or finish)
public:
	virtual bool is_while_command(){ return true;};
	virtual CILabel end_ilabel(){ return m_end_ilabel;};
	virtual CILabel exit_ilabel(){ return m_exit_ilabel;};
public:
	virtual void generate_rtl_node(CInstrList *ilist);//for
#endif
};
/////////// try-catch ///////////////
//! TRY-CATCH node
class T_ctrl_cmd_try_catch : public T_cmd_gen
{
private:
  //! The first block of code to attempt to execute.
  L_stmnt_gen * const try_code;
  //! The code to execute if an error occurs in the first block.
  L_stmnt_gen *const catch_code;
public:
  T_ctrl_cmd_try_catch (L_stmnt_gen *tc, L_stmnt_gen *cc,
			  int l = -1, int c = -1)
    : T_cmd_gen (l, c), try_code (tc), catch_code (cc)      
  {
	  if (try_code)
	  try_code->store_parent(this);
	  if (catch_code)
	  catch_code->store_parent(this);
  }
  ~T_ctrl_cmd_try_catch()
  {
		if (try_code) delete try_code;
		if (catch_code) delete catch_code;
  }
private:
  // assignment by pointer
  T_ctrl_cmd_try_catch (const T_ctrl_cmd_try_catch&);
  T_ctrl_cmd_try_catch& operator = (const T_ctrl_cmd_try_catch&);
public:
	virtual void print_node();
#ifdef BLD_RTL_FEATURE
public:
	virtual void generate_rtl_node(CInstrList *ilist);//try-catch
#endif
};
#endif