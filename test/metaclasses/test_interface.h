#ifndef TEST_ENUMS_H
#define TEST_ENUMS_H

#include <meta/metaclass.h>

#include <string>
#include <utility>

// 'Interface' metaclass declaration
METACLASS_DECL(Interface)
{
    static void GenerateDecl()
    {
        compiler.message("Hello world from metaprogrammer!");
        compiler.require($Interface.variables().empty(), "Interface may not contain data members");

        for (auto& f : $Interface.functions())
        {
            compiler.require(f.is_public(), "Inteface function must be public");
            f.make_pure_virtual();
        }
    }
};

METACLASS_INST(Interface, TestIface)
{
public:
    void TestMethod1();
    std::string TestMethod2(int param) const;
};

#if 0
METACLASS_INST(Interface, BadTestIface)
{
public:
    void TestMethod1();
    std::string TestMethod2(int param) const;

protected:
    void TestMethod3();

private:
    int m_val;
};
#endif

#endif // TEST_ENUMS_H
