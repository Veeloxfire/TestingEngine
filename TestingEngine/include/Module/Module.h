#pragma once
#include "..\Test\Tests.h"

namespace Testing
{
	class ModuleBase {};

	template<typename T>
	concept IsModule = IsBaseOf<ModuleBase, T>::value;
}

#define ModuleName(Name) Module_ ## Name
#define Module(Name) ModuleName(Name)()

#define StartModule(Name)\
	class ModuleName(Name) : public ::Testing::ModuleBase\
	{\
	public:\
		constexpr ModuleName(Name) () {}\
		constexpr static char Module_Name[sizeof(#Name)/sizeof(char)]{#Name}

#define EndModule(...)\
		;\
		constexpr static ::Testing::Tests m_Tests{__VA_ARGS__};\
		constexpr const decltype(m_Tests)& GetTests() const { return m_Tests; }\
		constexpr const char* GetName() const { return Module_Name; }\
	};


#define TestName(Name) Name ## _Name
#define	TestLambda(Name) Name ## _Test

#define Test(Name) ::Testing::Test{TestName(Name), TestLambda(Name)}

#define ModuleTest(Name)\
	;\
	constexpr static char TestName(Name)[sizeof(#Name)/sizeof(char)]{#Name};\
	constexpr static auto TestLambda(Name) = []<typename RValueReferenceType, typename ForwardingReferenceType>\
([[maybe_unused]] RValueReferenceType&& RValueReference, [[maybe_unused]] ForwardingReferenceType&& ForwardingReference)