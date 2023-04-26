#include <assert.h>

#include "../Headers/SortedMap.h"
#include "../Headers/SMIterator.h"
#include "../Headers/ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());
}

void testJumpForward()
{
    SortedMap sm(relatie1);

    sm.add(1, 1);
    sm.add(2, 2);
    sm.add(3, 3);
    sm.add(4, 4);

    SMIterator it = sm.iterator();

    it.jumpForward(1);
    TElem e = it.getCurrent();

    assert(e.first == 2);
    assert(e.second == 2);

    it.jumpForward(2);
    e = it.getCurrent();

    assert(e.first == 4);
    assert(e.second == 4);

    try
    {
        it.jumpForward(-1);
        assert(false);
    }
    catch(const std::exception&)
    {
        // Do nothing.
    }
    
}
