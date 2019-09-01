#ifndef __JOE_PAIR__
#define __JOE_PAIR__


namespace Joe
{
template<typename T1, typename T2>
class Joe_pair
{
public:
    using  first_type  = T1;
    using  scoend_type = T2;

    first_type first;
    scoend_type scoend;

    Joe_pair():first(T1()), scoend(T2()) {	}
    Joe_pair(const first_type a,const scoend_type b):first(a), scoend(b) {		}

    template<typename _U1, typename _U2>
    Joe_pair(const Joe_pair<_U1, _U2>& _p):first(_p,first), scoend(_p.scoend) { } //copy construct
};

template <typename T1, typename T2>
inline bool operator==(const Joe_pair<T1, T2>& x1, const Joe_pair<T1, T2>& x2)
{
    return x1.first == x1.first && x1.scoend == x2.scoend;
}

template <typename T1, typename T2>
inline bool operator!=(const Joe_pair<T1, T2>& x1, const Joe_pair<T1, T2>& x2)
{
    return x1.first != x1.first && x1.scoend != x2.scoend;
}

template <typename T1, typename T2>
inline bool operator<(const Joe_pair<T1, T2>& x1, const Joe_pair<T1, T2>& x2)
{
    return (x1.first < x1.first) && x1.scoend < x2.scoend;
}

template <typename T1, typename T2>
inline bool operator<=(const Joe_pair<T1, T2>& x1, const Joe_pair<T1, T2>& x2)
{
    return (x1.first <= x1.first) && x1.scoend <= x2.scoend;
}

template <typename T1, typename T2>
inline bool operator>(const Joe_pair<T1, T2>& x1, const Joe_pair<T1, T2>& x2)
{
    return (x1.first > x1.first) && x1.scoend > x2.scoend;
}

template <typename T1, typename T2>
inline bool operator>=(const Joe_pair<T1, T2>& x1, const Joe_pair<T1, T2>& x2)
{
    return (x1.first >= x1.first) && x1.scoend >= x2.scoend;
}

template <typename T1, typename T2>
inline Joe_pair<T1, T2> make_pair(const T1& x1, const T2& x2)
{
    return Joe_pair<T1, T2>(x1, x2);
}
}


#endif //__JOE_PAIR__











