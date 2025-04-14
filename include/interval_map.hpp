#include <map>
#include <iostream>
 
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	template<typename V_forward>
	interval_map(V_forward&& val)
	: m_valBegin(std::forward<V_forward>(val))
	{}
	void print() 
	{
		for(auto it=m_map.begin(); it != m_map.end(); it++)
			std::cout << it->first << " : " << it->second << '\t'; 
		std::cout << std::endl << "----------" << std::endl;
	}
	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	template<typename V_forward>
	void assign( K const& keyBegin, K const& keyEnd, V_forward&& val )
		requires (std::is_same<std::remove_cvref_t<V_forward>, V>::value)
	{
		// no interval , return
		if(keyEnd <  keyBegin)
			return; 
		
		bool isEmpty = m_map.empty();

		// m_map is empty & val = m_valBegin , not legal
		if(isEmpty && (val == m_valBegin))
			return;

		if(isEmpty) 
		{
            m_map.insert_or_assign(keyBegin, std::move(val));
			m_map.insert_or_assign(keyEnd, m_valBegin);
			return ;
		}
        // mark iterators for keyBegin & keyEnd
		auto itBegin = m_map.lower_bound(keyBegin);
		auto itEnd = m_map.lower_bound(keyEnd);

        // extract prev. (for keyBegin entry)
        // and next values (for keyEnd entry) 
        
        V prevVal = m_valBegin;
        V nextVal = m_valBegin;
		if (itBegin != m_map.begin()) 
            prevVal = (std::prev(itBegin))->second;

		if (itEnd != m_map.end())
            nextVal = itEnd->second;
            
		// mark the keyEnd calculated value
		V endVal = (m_map.contains(keyEnd))? nextVal : std::prev(itEnd)->second;
        std::cout << "prev " << prevVal << ", next " << nextVal << ", end " << endVal << std::endl; 
        // check if val is legal in range [keyBegin, keyEnd)
		if (!(prevVal == val) && !(val == nextVal))
		{   
            m_map.erase(itBegin, itEnd);
			// update new entries with val. and endVal
            m_map.insert_or_assign(keyBegin, std::move(val));
			m_map.insert_or_assign(keyEnd, endVal);
		} 
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};
