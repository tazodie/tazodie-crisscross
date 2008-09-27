/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include "header.h"

#include "avltree.h"

using namespace CrissCross::Data;

int ProfileAVLTree()
{
	AVLTree<size_t, item_t> *tree = new AVLTree<size_t, item_t>();
	g_stdout->SetColour(g_stdout->FG_WHITE | g_stdout->FG_INTENSITY);
	g_stdout->WriteLine("AVLTree Statistics");
	g_stdout->SetColour();

	size_t                   usage = 0, i;
	for (i = 0; i <= MAX_NODES; i += (i) ? i : 1) {
		while (tree->size() < i)
		{
			size_t random = rand() * rand();
			if (!tree->exists(random))
				CoreAssert(tree->insert(random, 0));
		}
		usage = tree->mem_usage();
		g_stdout->WriteLine("%3d items: %4d bytes (%4.2lf KB)", tree->size(), usage, (double)usage / 1024.0);
	}

	g_stdout->WriteLine();

	delete tree;

	return 0;
}
