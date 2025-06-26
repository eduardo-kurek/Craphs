#pragma once
#include <cstdint>

struct Iteration {
	uint32_t w;
	uint32_t v;
	uint32_t d;
};

class Searcher {

public:
	virtual ~Searcher() = default;
	virtual void Start(uint32_t v) = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Iteration Current() const = 0;

	class It {

	};


};
