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

#ifndef __included_cc_avltree_h
#   error "This file shouldn't be compiled directly."
#endif

namespace CrissCross
{
	namespace Data
	{
		template <class Key, class Data>
		AVLNode<Key,Data>::AVLNode()
			: BinaryNode<Key,Data>()
		{
			m_balance = BALANCED;
			left = NULL;
			right = NULL;
			parent = NULL;
		}

		template <class Key, class Data>
		AVLTree<Key,Data>::AVLTree()
		{
			m_root = NULL;
			m_size = 0;
		}

		template <class Key, class Data>
		AVLTree<Key,Data>::~AVLTree()
		{
			if ( m_root )
				Dealloc ( m_root->id );
			delete m_root;
			m_root = NULL;
		}

		template <class Key, class Data>
		bool AVLTree<Key,Data>::erase ( Key const &_key )
		{
			Result ret = erase ( &m_root, _key );
			return ( ret == OK || ret == BALANCE );
		}

		template <class Key, class Data>
		bool AVLTree<Key,Data>::erase ( Key const &_key, Data const &_data )
		{
			Result ret = erase ( &m_root, _key, _data );
			return ( ret == OK || ret == BALANCE );
		}

		template <class Key, class Data>
		typename AVLTree<Key,Data>::Result AVLTree<Key,Data>::erase( AVLNode<Key,Data> **_node, Key const &_key, Data const &_data )
		{
			if( !*_node )
				return INVALID;

			Result result = OK;

			if ( Compare ( _key, (*_node)->id ) != 0 || Compare ( _data, (*_node)->data ) != 0 )
			{
				if ( Compare ( _key, (*_node)->id ) < 0 )
				{
					if ( (*_node)->left )
					{
						if ( ( result = erase( &(*_node)->left, _key ) ) == BALANCE )
							return balanceLeftShrunk( _node );

						if ( result != INVALID )
							return result;
					}
				}
				else if ( (*_node)->right )
				{
					if ( ( result = erase( &(*_node)->right, _key ) ) == BALANCE )
						return balanceRightShrunk( _node );

					if ( result != INVALID )
						return result;
				}

				//Node not found
				return INVALID;
			}

			//Erase this node
			--m_size;
			Dealloc ( (*_node)->id );
			
			if( (*_node)->left )
			{
				if( replaceWithHighest( *_node, &(*_node)->left, &result ) )
				{
					if( result == BALANCE )
						result = balanceLeftShrunk ( _node );
					return result;
				}
			}
			
			if( (*_node)->right )
			{
				if( replaceWithLowest( *_node, &(*_node)->right, &result ) )
				{
					if( result == BALANCE )
						result = balanceRightShrunk ( _node );
					return result;
				}
			}
			
			(*_node)->left = NULL;
			(*_node)->right = NULL;

			//Leaf, delete and rebalance
			delete *_node, *_node = 0;
			
			return BALANCE;
		}

		template <class Key, class Data>
		typename AVLTree<Key,Data>::Result AVLTree<Key,Data>::erase( AVLNode<Key,Data> **_node, Key const &_key )
		{
			if( !*_node )
				return INVALID;

			Result result = OK;

			if( Compare ( _key, (*_node)->id ) != 0 )
			{
				if( Compare ( _key, (*_node)->id ) < 0 )
				{
					if( (*_node)->left )
					{
						if( ( result = erase( &(*_node)->left, _key ) ) == BALANCE )
							return balanceLeftShrunk( _node );

						if( result != INVALID )
							return result;
					}
				}
				else if( (*_node)->right )
				{
					if( ( result = erase( &(*_node)->right, _key ) ) == BALANCE )
						return balanceRightShrunk( _node );

					if( result != INVALID )
						return result;
				}

				//Node not found
				return INVALID;
			}

			//Erase this node
			--m_size;
			Dealloc ( (*_node)->id );
			
			if( (*_node)->left )
			{
				if( replaceWithHighest( *_node, &(*_node)->left, &result ) )
				{
					if( result == BALANCE )
						result = balanceLeftShrunk ( _node );
					return result;
				}
			}
			
			if( (*_node)->right )
			{
				if( replaceWithLowest( *_node, &(*_node)->right, &result ) )
				{
					if( result == BALANCE )
						result = balanceRightShrunk ( _node );
					return result;
				}
			}
			
			(*_node)->left = NULL;
			(*_node)->right = NULL;

			//Leaf, delete and rebalance
			delete *_node, *_node = 0;
			
			return BALANCE;
		}
		
		template <class Key, class Data>
		void AVLTree<Key,Data>::insert ( Key const &_key, Data const &_data )
		{
			insert ( NULL, &m_root, _key, _data );
			++m_size;
		}

		template <class Key, class Data>
		AVLNode<Key,Data> *AVLTree<Key,Data>::findNode ( Key const &_key ) const
		{
			AVLNode<Key,Data> *p_current = m_root;
			while ( p_current )
			{
				if ( Compare ( _key, p_current->id ) < 0 )
					p_current = p_current->left;
				else if ( Compare ( _key, p_current->id ) > 0 )
					p_current = p_current->right;
				else if ( Compare ( _key, p_current->id ) == 0 )
				{
					return p_current;
				}
			}
			return NULL;
		}

		template <class Key, class Data>
		bool AVLTree<Key,Data>::find ( Key const &_key, Data &_data ) const
		{
			AVLNode<Key,Data> *p_current = findNode ( _key );
			if ( !p_current ) return false;
			_data = p_current->data;
			return true;
		}

		template <class Key, class Data>
		DArray<Data> *AVLTree<Key,Data>::findAll ( Key const &_key ) const
		{
			AVLNode<Key,Data> *p_current = findNode ( _key );
			DArray<Data> *data = new DArray<Data>();
			findRecursive ( data, _key, p_current );
			return data;
		}

		template<class Key, class Data>
		void AVLTree<Key,Data>::findRecursive ( DArray<Data> *_array, Key const &_key, AVLNode<Key,Data> *_node ) const
		{
			CoreAssert ( _array );
			if ( !_node ) return;
			findRecursive ( _array, _key, _node->left );
			if ( Compare(_node->id, _key) == 0 ) _array->insert ( _node->data );
			findRecursive ( _array, _key, _node->right );
		}

		template <class Key, class Data>
		Data AVLTree<Key,Data>::find ( Key const &_key ) const
		{
			AVLNode<Key,Data> *p_current = findNode ( _key );
			if ( !p_current ) return Data(0);
			return p_current->data;
		}

		template <class Key, class Data>
		bool AVLTree<Key,Data>::exists ( Key const &_key ) const
		{
			AVLNode<Key,Data> *p_current = findNode ( _key );
			if ( !p_current ) return false;
			else              return true;
		}

		template <class Key, class Data>
		void AVLTree<Key,Data>::rotateLeft ( AVLNode<Key,Data> **_node )
		{
			AVLNode<Key,Data> *p_tmp = *_node;
			*_node = p_tmp->right;
			p_tmp->right = (*_node)->left;
			(*_node)->left = p_tmp;
			(*_node)->parent = p_tmp->parent;
			p_tmp->parent = *_node;
			if( p_tmp->right )
				p_tmp->right->parent = (*_node)->left;
		}

		template <class Key, class Data>
		void AVLTree<Key,Data>::rotateRight ( AVLNode<Key,Data> **_node )
		{
			AVLNode<Key,Data> *p_tmp = *_node;
			*_node = p_tmp->left;
			p_tmp->left = (*_node)->right;
			(*_node)->right = p_tmp;
			
			(*_node)->parent = p_tmp->parent;
			p_tmp->parent = *_node;
			if( p_tmp->left )
				p_tmp->left->parent = (*_node)->right;
		}

		template <class Key, class Data>
		typename AVLTree<Key,Data>::Result AVLTree<Key,Data>::balanceLeftGrown ( AVLNode<Key,Data> **_node )
		{
			switch( (*_node)->m_balance )
			{
				case LEFTHEAVY:
				{
					if( (*_node)->left->m_balance == LEFTHEAVY )
					{
						(*_node)->m_balance = (*_node)->left->m_balance = BALANCED;
						rotateRight( _node );
					}
					else
					{
						switch( (*_node)->left->right->m_balance )
						{
							case LEFTHEAVY:
							{
								(*_node)->m_balance          = RIGHTHEAVY;
								(*_node)->left->m_balance = BALANCED;
								break;
							}

							case BALANCED:
							{
								(*_node)->m_balance          = BALANCED;
								(*_node)->left->m_balance = BALANCED;
								break;
							}

							case RIGHTHEAVY:
							{
								(*_node)->m_balance          = BALANCED;
								(*_node)->left->m_balance = LEFTHEAVY;
								break;
							}
						}

						(*_node)->left->right->m_balance = BALANCED;

						rotateLeft( &(*_node)->left );
						rotateRight( _node );
					}

					return OK;
				}

				case BALANCED:
				{
					(*_node)->m_balance = LEFTHEAVY;
					return BALANCE;
				}

				case RIGHTHEAVY:
				{
					(*_node)->m_balance = BALANCED;
					return OK;
				}
			}

			return INVALID;
		}

		template <class Key, class Data>
		typename AVLTree<Key,Data>::Result AVLTree<Key,Data>::balanceRightGrown ( AVLNode<Key,Data> **_node )
		{
			switch( (*_node)->m_balance )
			{
				case LEFTHEAVY:
				{
					(*_node)->m_balance = BALANCED;
					return OK;
				}

				case BALANCED:
				{
					(*_node)->m_balance = RIGHTHEAVY;
					return BALANCE;
				}

				case RIGHTHEAVY:
				{
					if( (*_node)->right->m_balance == RIGHTHEAVY )
					{
						(*_node)->m_balance = (*_node)->right->m_balance = BALANCED;
						rotateLeft( _node );
					}
					else
					{
						switch( (*_node)->right->left->m_balance )
						{
							case LEFTHEAVY:
							{
								(*_node)->m_balance           = BALANCED;
								(*_node)->right->m_balance = RIGHTHEAVY;
								break;
							}

							case BALANCED:
							{
								(*_node)->m_balance           = BALANCED;
								(*_node)->right->m_balance = BALANCED;
								break;
							}

							case RIGHTHEAVY:
							{
								(*_node)->m_balance           = LEFTHEAVY;
								(*_node)->right->m_balance = BALANCED;
								break;
							}
						}

						(*_node)->right->left->m_balance = BALANCED;

						rotateRight( &(*_node)->right );
						rotateLeft( _node );
					}

					return OK;
				}
			}

			return INVALID;
		}

		template <class Key, class Data>
		typename AVLTree<Key,Data>::Result AVLTree<Key,Data>::balanceLeftShrunk ( AVLNode<Key,Data> **_node )
		{
			switch( (*_node)->m_balance )
			{
				case LEFTHEAVY:
				{
					(*_node)->m_balance = BALANCED;
					return BALANCE;
				}

				case BALANCED:
				{
					(*_node)->m_balance = RIGHTHEAVY;
					return OK;
				}

				case RIGHTHEAVY:
				{
					switch( (*_node)->right->m_balance )
					{
						case LEFTHEAVY:
						{
							switch( (*_node)->right->left->m_balance )
							{
								case LEFTHEAVY:
								{
									(*_node)->m_balance           = BALANCED;
									(*_node)->right->m_balance = RIGHTHEAVY;
									break;
								}

								case BALANCED:
								{
									(*_node)->m_balance           = BALANCED;
									(*_node)->right->m_balance = BALANCED;
									break;
								}

								case RIGHTHEAVY:
								{
									(*_node)->m_balance           = LEFTHEAVY;
									(*_node)->right->m_balance = BALANCED;
									break;
								}
							}

							(*_node)->right->left->m_balance = BALANCED;

							rotateRight( &(*_node)->right );
							rotateLeft( _node );

							return BALANCE;
						}

						case BALANCED:
						{
							(*_node)->m_balance           = RIGHTHEAVY;
							(*_node)->right->m_balance = LEFTHEAVY;
							rotateLeft( _node );
							return OK;
						}

						case RIGHTHEAVY:
						{
							(*_node)->m_balance = (*_node)->right->m_balance = BALANCED;
							rotateLeft( _node );
							return BALANCE;
						}
					}

					break;
				}
			}

			return INVALID;
		}

		template <class Key, class Data>
		typename AVLTree<Key,Data>::Result AVLTree<Key,Data>::balanceRightShrunk ( AVLNode<Key,Data>** _node )
		{
			switch( (*_node)->m_balance )
			{
				case LEFTHEAVY:
				{
					switch( (*_node)->left->m_balance )
					{
						case LEFTHEAVY:
						{
							(*_node)->m_balance = (*_node)->left->m_balance = BALANCED;
							rotateRight( _node );
							return BALANCE;
						}

						case BALANCED:
						{
							(*_node)->m_balance          = LEFTHEAVY;
							(*_node)->left->m_balance = RIGHTHEAVY;
							rotateRight( _node );
							return OK;
						}

						case RIGHTHEAVY:
						{
							switch( (*_node)->left->right->m_balance )
							{
								case LEFTHEAVY:
								{
									(*_node)->m_balance          = RIGHTHEAVY;
									(*_node)->left->m_balance = BALANCED;
									break;
								}

								case BALANCED:
								{
									(*_node)->m_balance          = BALANCED;
									(*_node)->left->m_balance = BALANCED;
									break;
								}

								case RIGHTHEAVY:
								{
									(*_node)->m_balance          = BALANCED;
									(*_node)->left->m_balance = LEFTHEAVY;
									break;
								}
							}

							(*_node)->left->right->m_balance = BALANCED;

							rotateLeft( &(*_node)->left );
							rotateRight( _node );

							return BALANCE;
						}
					}

					break;
				}

				case BALANCED:
				{
					(*_node)->m_balance = LEFTHEAVY;
					return OK;
				}

				case RIGHTHEAVY:
				{
					(*_node)->m_balance = BALANCED;
					return BALANCE;
				}
			}

			return INVALID;
		}

		template <class Key, class Data>
		bool AVLTree<Key,Data>::replaceWithHighest ( AVLNode<Key,Data>* _target, AVLNode<Key,Data>** _subtree, Result* _result )
		{
			AVLNode<Key,Data> *p_tmp;

			*_result = BALANCE;

			if( !*_subtree )
				return false;

			if( (*_subtree)->right )
			{
				if( !replaceWithHighest( _target, &(*_subtree)->right, _result ) )
					return false;

				if( *_result == BALANCE )
					*_result = balanceRightShrunk( _subtree );

				return true;
			}

			_target->data = (*_subtree)->data;
			_target->id = Duplicate ( (*_subtree)->id );

			p_tmp       = *_subtree;
			*_subtree = p_tmp->left;
			if( *_subtree )
				(*_subtree)->parent = p_tmp->parent;

			if ( p_tmp )
				Dealloc ( p_tmp->id );
			delete p_tmp;

			return true;
		}

		template <class Key, class Data>
		bool AVLTree<Key,Data>::replaceWithLowest ( AVLNode<Key,Data>* _target, AVLNode<Key,Data>** _subtree, Result* _result )
		{
			AVLNode<Key,Data> *p_tmp;

			*_result = BALANCE;

			if( !*_subtree )
				return false;

			if( (*_subtree)->left )
			{
				if( !replaceWithLowest( _target, &(*_subtree)->left, _result ) )
					return false;

				if( *_result == BALANCE )
					*_result = balanceLeftShrunk( _subtree );

				return true;
			}

			_target->data = (*_subtree)->data;
			_target->id =	Duplicate ( (*_subtree)->id );

			p_tmp       = *_subtree;
			*_subtree = p_tmp->right;
			if( *_subtree )
				(*_subtree)->parent = p_tmp->parent;

			if ( p_tmp )
				Dealloc ( p_tmp->id );
			delete p_tmp;

			return true;
		}

		template <class Key, class Data>
		typename AVLTree<Key,Data>::Result AVLTree<Key,Data>::insert ( AVLNode<Key,Data>** pp_parent, AVLNode<Key,Data>** _node, Key const &_key, Data const &_data )
		{
			Result result = OK;

			CoreAssert ( _node );

			if( !*_node )
			{
				*_node = new AVLNode<Key,Data>();
				(*_node)->parent = pp_parent ? *pp_parent : NULL;
				(*_node)->id = Duplicate(_key);
				(*_node)->data = _data;
				return BALANCE;
			}

			if( Compare( _key, (*_node)->id ) < 0 )
			{
				if( ( result = insert( _node, &(*_node)->left, _key, _data ) ) == BALANCE )
					result = balanceLeftGrown( _node );
			}
			else //obj >= nodeobj
			{
				if( ( result = insert( _node, &(*_node)->right, _key, _data ) ) == BALANCE )
					result = balanceRightGrown( _node );
			}

			return result;
		}

		template <class Key, class Data>
			DArray<Data> *AVLTree<Key,Data>::ConvertToDArray () const
		{
			DArray<Data> *darray = new DArray<Data> ( m_size );
			RecursiveConvertToDArray ( darray, m_root );
			return darray;
		}

		template <class Key, class Data>
			DArray<Key> *AVLTree<Key,Data>::ConvertIndexToDArray () const
		{
			DArray<Key> *darray = new DArray<Key> ( m_size );
			RecursiveConvertIndexToDArray ( darray, m_root );
			return darray;
		}

		template <class Key, class Data>
			void AVLTree<Key,Data>::RecursiveConvertToDArray ( DArray<Data> *darray, AVLNode<Key,Data> *btree ) const
		{
			if ( !btree ) return;
			RecursiveConvertToDArray ( darray, btree->left );
			darray->insert ( btree->data );
			RecursiveConvertToDArray ( darray, btree->right );
		}

		template <class Key, class Data>
			void AVLTree<Key,Data>::RecursiveConvertIndexToDArray ( DArray<Key> *darray, AVLNode<Key,Data> *btree ) const
		{
			if ( !btree ) return;
			RecursiveConvertIndexToDArray ( darray, btree->left );
			darray->insert ( btree->id );
			RecursiveConvertIndexToDArray ( darray, btree->right );
		}
	}
}