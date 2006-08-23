/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net> and Rudolf Olah <omouse@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of Uplink Laboratories nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without specific
 *       prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __included_rbtree_h
#    define __included_rbtree_h

#    include "core_deprecate.h"
#    include "darray.h"

typedef enum
{
	STATUS_OK,
	STATUS_NULL_POINTER,
	STATUS_MEM_EXHAUSTED,
	STATUS_DUPLICATE_KEY,
	STATUS_KEY_NOT_FOUND,
	STATUS_KEY_TOO_LARGE
} statusEnum;

template < class dataType, class keyType > class RedBlackTree
{

  public:

	typedef enum
	{ BLACK, RED } nodeColor;
	typedef enum
	{
		NODE_ITSELF_VISITED = 0,
		LEFT_CHILD_VISITED,
		ALL_CHILDS_VISITED
	} beenThereEnum;

	/*
	   This is what a node looks like in this tree.
	 */
	struct nodeType
	{
		struct nodeType *left;	// Left child.
		struct nodeType *right;	// Right child.
		struct nodeType *parent;	// Supernode.
		nodeColor color;		// Color of this node (Red/Black).

		keyType id;				// This node's key (doesn't have to be unique).
		dataType data;			// The actual record associated with this node.
		beenThereEnum beenThere;	// Used for iterators.
		struct nodeType *Left (  )
		{
			return left;
		}
		struct nodeType *Right (  )
		{
			return right;
		}
	};

	nodeType *rootNode;
	nodeType *NULL_NODE;

	RedBlackTree (  );
	~RedBlackTree (  );
	statusEnum insert ( keyType key, dataType rec );
	statusEnum deleteNode ( keyType key );
	statusEnum killNode ( nodeType * z );
	dataType find ( keyType key ) const;
	nodeType *findNode ( keyType key ) const;
	bool ValidNode ( nodeType * node ) const;

  protected:
	inline char *reallocKey ( char *pointer, char *a );
	inline int *reallocKey ( int *pointer, int *a );
	inline char *newKey ( char *a );
	inline int *newKey ( int *a );
	inline bool compLT ( const char *a, const char *b ) const;
	inline bool compLTEQU ( const char *a, const char *b ) const;
	inline bool compEQ ( const char *a, const char *b ) const;

	inline bool compLT ( const int *a, const int *b ) const;
	inline bool compLTEQU ( const int *a, const int *b ) const;
	inline bool compEQ ( const int *a, const int *b ) const;

	/*
	   these are automatically called. no need to use them externally at all.
	 */
	void killAll ( nodeType * rec );
	void killAll (  );

  public:
	size_t size (  );
	void getNext ( nodeType ** current );

	/*
	   other old backward-compatible functions
	 */
	_DS_DEPRECATE_FUNCTION ( find ) dataType GetData ( keyType key ) const;
	_DS_DEPRECATE_FUNCTION ( insert ) void PutData ( keyType key,
													 dataType rec );
	_DS_DEPRECATE_FUNCTION ( deleteNode ) void RemoveData ( keyType key );
	_DS_DEPRECATE_FUNCTION ( findNode ) nodeType *LookupTree ( keyType key );

  public:
	DArray < dataType > *ConvertToDArray (  );
	DArray < keyType > *ConvertIndexToDArray (  );

  protected:
	void RecursiveConvertIndexToDArray ( DArray < keyType > *darray,
										 nodeType * btree );
	void RecursiveConvertToDArray ( DArray < dataType > *darray,
									nodeType * btree );

  public:
	_DS_DEPRECATE_FUNCTION ( size ) int Size (  );
	_DS_DEPRECATE_FUNCTION_N void Empty (  );	// Ironically, an empty function, just here for straight compatibility.
	void Print (  );			// Not deprecated, but still down here because it is a backwards-compatibility function.

  protected:
	void rotateLeft ( nodeType * x );
	void rotateRight ( nodeType * x );
	void insertFixup ( nodeType * x );
	void deleteFixup ( nodeType * x );
};

#    include "rbtree.cpp"

#endif
