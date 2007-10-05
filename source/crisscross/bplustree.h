/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_bplustree_h
#define __included_cc_bplustree_h

#include <crisscross/compare.h>

namespace CrissCross
{
	namespace Data
	{
		template <class Key, class Data>
		class BPlusTree
		{
		private:
			BinaryNode<Key,Data> *m_root;
			
			int m_height;		//B+ Tree height,  A tree of height/depth 0 only has a leaf node.
			int m_TL;			//the minimum degree of B Tree Leaf Node, TL> 2
			int m_TI;			//the minimun degree of B Tree Inner Node, TI > 2
			int m_TL_1;			//the minimum degree of B Tree Leaft Node, TL> 2
			int m_TI_1;			//the minimun degree of B Tree Inner Node, TI > 2
			int m_M;			//the maximum number of keys in the leaf node, M must be > 0
			int m_N;			//the maximum number of keys in inner node, the number of pointer is N+1, N must be > 2

		public:
			BPlusTree ( int _t );
			BPlusTree ( int _tleaf, int _tinner );
			~BPlusTree ();

			void insert ( Key const &_key, Data const &_data );
			bool erase ( Key const &_key );
		};
	}
}

#include <crisscross/bplustree.cpp>

#endif
