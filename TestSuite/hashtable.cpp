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
#include "hashtable.h"

#include <crisscross/hashtable.h>

using namespace CrissCross::Data;

int TestHashTable_Int()
{
	HashTable<int>      ht;

	char                buffer[32];
	const unsigned long max = 1000;
	unsigned long       i;
	for (i = 0; i < max; i++) {
		sprintf(buffer, "%lu", i);
		ht.insert(buffer, max - i);
	}

	//ht.print_statistics();

	for (i = 0; i < max; i += 2) {
		sprintf(buffer, "%lu", i);
		if (!ht.erase(buffer))
			return i + 1;
	}

	//ht.print_statistics();

	for (i = 0; i < max; i += 2) {
		sprintf(buffer, "%lu", i);
		if (ht.find(buffer) != 0)
			return i + 1;
	}

	//ht.print_statistics();

	for (i = 1; i < max; i += 2) {
		sprintf(buffer, "%lu", i);
		if (ht.find(buffer) != (int)(max - i))
			return i + 1;
	}

	//ht.print_statistics();

	return 0;
}

int TestHashTable_CString()
{
	HashTable<const char *> ht;

	char                buffer1[32];
	char                buffer2[32];
	const unsigned long max = 1000;
	unsigned long       i;

	for (i = 0; i < max; i++) {
		sprintf(buffer1, "%lu", i);
		sprintf(buffer2, "%lu", max - i);
		ht.insert(buffer1, (const char *)cc_strdup(buffer2));
	}

	//ht.print_statistics();

	for (i = 0; i < max; i += 2) {
		sprintf(buffer1, "%lu", i);
		free((void *)ht.find(buffer1));
		if (!ht.erase(buffer1))
			return i + 1;
	}

	//ht.print_statistics();

	for (i = 0; i < max; i += 2) {
		sprintf(buffer1, "%lu", i);
		if (ht.find(buffer1) != 0)
			return i + 1;
	}

	//ht.print_statistics();

	for (i = 1; i < max; i += 2) {
		sprintf(buffer1, "%lu", i);
		sprintf(buffer2, "%lu", max - i);
		if (strcmp(ht.find(buffer1),buffer2) != 0)
			return i + 1;
	}

	//ht.print_statistics();

	/* Rest of the cleanup */
	for (i = 1; i < max; i += 2) {
		sprintf(buffer1, "%lu", i);
		free((void *)ht.find(buffer1));
		if (!ht.erase(buffer1))
			return i + 1;
	}

	return 0;
}

int TestHashTable_String()
{
	HashTable<std::string> ht;

	char                buffer1[32];
	char                buffer2[32];
	const unsigned long max = 1000;
	unsigned long       i;

	for (i = 0; i < max; i++) {
		sprintf(buffer1, "%lu", i);
		sprintf(buffer2, "%lu", max - i);
		ht.insert(buffer1, std::string(buffer2));
	}

	//ht.print_statistics();

	for (i = 0; i < max; i += 2) {
		sprintf(buffer1, "%lu", i);
		if (!ht.erase(buffer1))
			return i + 1;
	}

	//ht.print_statistics();

	for (i = 0; i < max; i += 2) {
		sprintf(buffer1, "%lu", i);
		if (ht.exists(buffer1))
			return i + 1;
	}

	//ht.print_statistics();

	std::string rec;
	for (i = 1; i < max; i += 2) {

		sprintf(buffer1, "%lu", i);
		sprintf(buffer2, "%lu", max - i);
		ht.find(buffer1, rec);
		if (rec != std::string(buffer2))
			return i + 1;
	}

	//ht.print_statistics();

	/* Rest of the cleanup */
	for (i = 1; i < max; i += 2) {
		sprintf(buffer1, "%lu", i);
		if (!ht.erase(buffer1))
			return i + 1;
	}

	return 0;
}
