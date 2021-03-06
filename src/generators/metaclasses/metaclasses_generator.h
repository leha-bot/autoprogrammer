#ifndef METACLASSES_GENERATOR_H
#define METACLASSES_GENERATOR_H

#include "generators/basic_generator.h"
#include "decls_reflection.h"

namespace codegen
{

class MetaclassesGenerator : public BasicGenerator
{
public:
    MetaclassesGenerator(const Options& opts);

    // GeneratorBase interface
    void SetupMatcher(clang::ast_matchers::MatchFinder& finder, clang::ast_matchers::MatchFinder::MatchCallback* defaultCallback) override;
    void HandleMatch(const clang::ast_matchers::MatchFinder::MatchResult& matchResult) override;
    bool Validate() override;

protected:
    struct MetaclassInfo
    {
        reflection::ClassInfoPtr metaclass;
        reflection::MethodInfoPtr declGenMethod;
        reflection::MethodInfoPtr defGenMethod;
    };

    struct MetaclassImplInfo
    {
        std::vector<reflection::MethodInfoPtr> metaclasses;
        reflection::ClassInfoPtr implDecl;
        reflection::ClassInfoPtr impl;
        reflection::NamespaceInfoPtr ns;
    };

    // BasicGenerator interface
    void WriteHeaderContent(CppSourceStream& hdrOs) override;

    void ProcessMetaclassDecl(reflection::ClassInfoPtr classInfo, const clang::ASTContext* astContext);
    void ProcessMetaclassImplDecl(reflection::ClassInfoPtr classInfo, const clang::ASTContext* astContext);

private:
    const clang::ASTContext* m_astContext = nullptr;
    std::vector<MetaclassImplInfo> m_implsInfo;
    std::unordered_map<std::string, MetaclassInfo> m_metaclasses;
    reflection::NamespacesTree m_namespaces;
    reflection::NamespacesTree m_implNamespaces;

};

} // codegen

#endif // METACLASSES_GENERATOR_H
