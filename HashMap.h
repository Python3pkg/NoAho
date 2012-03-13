//
// HashMap.h
//
// $Id: //poco/1.4/Foundation/include/Poco/HashMap.h#1 $
//
// Library: Foundation
// Package: Hashing
// Module:  HashMap
//
// Definition of the HashMap class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_HashMap_INCLUDED
#define Foundation_HashMap_INCLUDED

#include "LinearHashTable.h"
#include <utility>


namespace PocoJgd {


template <class Key, class Value>
struct HashMapEntry
	/// This class template is used internally by HashMap.
{
	Key   first;
	Value second;

	HashMapEntry():
		first(),
		second()
	{
	}

	HashMapEntry(const Key& key):
		first(key),
		second()
	{
	}

	HashMapEntry(const Key& key, const Value& value):
		first(key),
		second(value)
	{
	}

	bool operator == (const HashMapEntry& entry) const
	{
		return first == entry.first;
	}

	bool operator != (const HashMapEntry& entry) const
	{
		return first != entry.first;
	}
};


/*
template <class HME, class KeyHashFunc>
struct HashMapEntryHash
	/// This class template is used internally by HashMap.
{
	std::size_t operator () (const HME& entry) const
	{
		return func_(entry.first);
	}

private:
	KeyHashFunc func_;
};
*/

template <class Key, class Mapped /*, class HashFunc = Hash<Key>*/ >
class HashMap
/// This class implements a map using a LinearHashTable.
///
/// A HashMap can be used just like a std::map.
{
public:
	typedef Key                 KeyType;
	typedef Mapped              MappedType;
	typedef Mapped&             Reference;
	typedef const Mapped&       ConstReference;
	typedef Mapped*             Pointer;
	typedef const Mapped*       ConstPointer;

	typedef HashMapEntry<Key, Mapped>      ValueType;
	typedef std::pair<KeyType, MappedType> PairType;

//	typedef HashMapEntryHash<ValueType, HashFunc> HashType;
        typedef LinearHashTable<ValueType /*, HashType*/ >  HashTable;

	typedef typename HashTable::Iterator      iterator;
	typedef typename HashTable::ConstIterator const_iterator;

	HashMap()
		/// Creates an empty HashMap.
	{
	}

	HashMap(std::size_t initialReserve):
		table_(initialReserve)
		/// Creates the HashMap with room for initialReserve entries.
	{
	}

	HashMap& operator = (const HashMap& map)
		/// Assigns another HashMap.
	{
		HashMap tmp(map);
		swap(tmp);
		return *this;
	}

	void swap(HashMap& map)
		/// Swaps the HashMap with another one.
	{
		table_.swap(map.table_);
	}

	const_iterator begin() const
	{
		return table_.begin();
	}

	const_iterator end() const
	{
		return table_.end();
	}

	iterator begin()
	{
		return table_.begin();
	}

	iterator end()
	{
		return table_.end();
	}

	const_iterator find(const KeyType& key) const
	{
		ValueType value(key);
		return table_.find(value);
	}

	iterator find(const KeyType& key)
	{
		ValueType value(key);
		return table_.find(value);
	}

	std::pair<iterator, bool> insert(const PairType& pair)
	{
		ValueType value(pair.first, pair.second);
		return table_.insert(value);
	}

	std::pair<iterator, bool> insert(const ValueType& value)
	{
		return table_.insert(value);
	}

	void erase(iterator it)
	{
		table_.erase(it);
	}

	void erase(const KeyType& key)
	{
		iterator it = find(key);
		table_.erase(it);
	}

	void clear()
	{
		table_.clear();
	}

	std::size_t size() const
	{
		return table_.size();
	}

	bool empty() const
	{
		return table_.empty();
	}

	// ConstReference operator [] (const KeyType& key) const
	// {
	// 	const_iterator it = table_.find(key);
	// 	if (it != table_.end())
	// 		return it->second;
	// 	else
	// 		throw NotFoundException();
	// }

	Reference operator [] (const KeyType& key)
	{
		ValueType value(key);
		std::pair<iterator, bool> res = table_.insert(value);
		return res.first->second;
	}

private:
	HashTable table_;
};

} // namespace PocoJgd

#endif // Foundation_HashMap_INCLUDED