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
#   error "This file shouldn't be compiled directly."
#endif

namespace CrissCross
{
	namespace Data
	{
		template <class Key, class Data>
		BPlusTree<Key,Data>::BPlusTree ( int _t )
			: m_height(0)
		{
			if ( _t < 2 ) _t = 2;
			m_TL = m_TI = _t;
			m_TL_1 = m_TI_1 = _t - 1;
			m_M = m_N = (2 * _t) - 1;
			m_height = 0;
			root = new BinaryNode<Key,Data>();
		}

		template <class Key, class Data>
		BPlusTree<Key,Data>::BPlusTree ( int _tleaf, int _tinner )
			: m_height(0)
		{
			if ( _tleaf < 2 ) _tleaf = 2;
			if ( _tinner < 2 ) _tinner = 2;
			m_TL = _tleaf;
			m_TI = _tinner;
			m_TL_1 = _tleaf - 1;
			m_TI_1 = _tinner - 1;
			m_M = 2 * _tleaf - 1;
			m_N = 2 * _tinner - 1;
			m_height = 0;
			root = new BinaryNode<Key,Data>();
		}

		template <class Key, class Data>
		void BPlusTree<Key,Data>::insert ( Key const &_key, Data const &_data )
		{
			bool split;
			InsertResult result;
			if ( m_height == 0 ) {
				split = insertLeaf ( (LeafNode<Key,Data> *)root, _key, _data, result );
			} else {
				split = insertInner ( (InnerNode<Key,Data> *)root, _key, _data, result );
			}
			if ( split )
			{
				m_height++;
				m_root = new InnerNode<Key,Data>();
				InnerNode<Key,Data> *node = (InnerNode<Key,Data> *)m_root;
				node->num = 1;
				node->keys[0] = result.key;
				node->children[0] = result.left;
				node->children[1] = result.right;

			}
		}

	}
}
