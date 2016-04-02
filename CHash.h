#pragma once

#define INVALID_HASH 0xffffffff
#define HASH_INIT	0x811c9dc5
#define HASH_PRIME	0x01000193

class CHash
{
public:
	CHash();
	CHash(unsigned int hashValue);
	CHash(const char *pString);
	CHash(const CHash &rhs);
	CHash &operator=(const CHash &rhs);

	void Set(const unsigned int hash);

	bool IsValid() const;
	operator unsigned int()			{ return mHashValue; }

	const bool operator<(const CHash &rhs) const;
	const bool operator>(const CHash &rhs) const;
	const bool operator<=(const CHash &rhs) const;
	const bool operator>=(const CHash &rhs) const;
	const bool operator==(const CHash &rhs) const;
	const bool operator!=(const CHash &rhs) const;
private:
	unsigned int MakeHash(const char *pString);

	unsigned int mHashValue;
};