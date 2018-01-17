// File: tmcpar_list.h
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
// Customized list template
#ifndef _tmcpar_list_h_
#define _tmcpar_list_h_

template <typename elt_type> class tmcpar_list
{
public:
  typedef typename std::list<elt_type>::iterator iterator;
  typedef typename std::list<elt_type>::const_iterator const_iterator;

  bool empty (void) const { return lst.empty (); }

  size_t length (void) const { return lst.size (); }

  iterator erase (iterator pos) { return lst.erase (pos); }

  void clear (void) { lst.clear (); }

  iterator begin (void) { return iterator (lst.begin ()); }
  const_iterator begin (void) const { return const_iterator (lst.begin ()); }

  iterator end (void) { return iterator (lst.end ()); }
  const_iterator end (void) const { return const_iterator (lst.end ()); }

  elt_type& front (void) { return lst.front (); }
  elt_type& back (void) { return lst.back (); }

  const elt_type& front (void) const { return lst.front (); }
  const elt_type& back (void) const { return lst.back (); }

  void push_front (const elt_type& s) { lst.push_front (s); }
  void push_back (const elt_type& s) { lst.push_back (s); }

  void pop_front (void) { lst.pop_front (); }
  void pop_back (void) { lst.pop_back (); }
  void append (const elt_type& s) { lst.push_back (s); }
public:
	void erase_list()
	{
		while (! empty ())
		{
		  iterator p = begin ();
		  delete *p;
		  erase (p);
		}
	}
private:
  std::list<elt_type> lst;
//public: // HSKOST - for tracing
	//int m_line;
	//int m_column;
protected:
	void	print_list()
	{
	  nTabsLevel++;
	  for (iterator p = begin (); p != end (); p++)
		{
		  elt_type elt = *p;
		  elt->print_gen_tree(); 
		//  fprintf(dump_file,"\n");
		}
	  nTabsLevel--;
	};
#ifdef BLD_RTL_FEATURE
public:
	std::list<CInstr*> res_rtl_list; // list of pointers to rtl of the list elements
	void generate_rtl_list(CInstrList *list,bool bIsCellRow=false)
	{
	    for (iterator p = begin (); p != end (); p++)
		{
		  elt_type elt = *p;
		  if (bIsCellRow==true)
		  {
			elt->generate_rtl(list,bIsCellRow); 
		  }
		  else
		  {
			elt->generate_rtl(list);
		  }
		  res_rtl_list.push_back(elt->res_rtl);
		}
	};
#endif
};
#endif