#ifndef MAKE_ARRAY_1
#define MAKE_ARRAY_1(text,id) auto * a##id = (text##id*)args[id];
#define MAKE_ARRAY_2(text,id) ,text##id
#define MAKE_ARRAY_3(text,id) BEAR_IF_COMMA(id) text##id a##id
#define MAKE_ARRAY_4(text,id) stack[id]=&text##id;
#endif
#ifdef CALL_IN_MAKER
template<class P BEAR_IF_COMMA(BEARNUMBER) BEAR_ENUM_PARAMS(BEARNUMBER, class A)  >
void call_impl(P(*function)(BEAR_ENUM_PARAMS(BEARNUMBER, A)), void**args)
{
	BEAR_REPEAT(BEARNUMBER, MAKE_ARRAY_1, A);
	Impl::BearFunctionRefCaller<P>()(function, m_return BEAR_REPEAT(BEARNUMBER, MAKE_ARRAY_2, a));
}
#endif
#ifdef CALL_IN_REF
template<class R BEAR_IF_COMMA(BEARNUMBER) BEAR_ENUM_PARAMS(BEARNUMBER, class A)>
inline R Call(BEAR_REPEAT(BEARNUMBER, MAKE_ARRAY_3, A))
{
	void*stack[256];
	BEAR_REPEAT(BEARNUMBER, MAKE_ARRAY_4, a);
	return Impl::BearFunctionReturner<bear_remove_reference<R>::type>()(Call(stack));
}
#endif