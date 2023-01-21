// #include"lib/scopeTable.h"
// #include"lib/functionSymbolInfo.h"
#include <iostream>
// #include "lib/src/treeWalker.cpp"
#include "lib/ast.h"

using namespace std;

// int main(){
//     ScopeTable scp(10, 1);
//     auto s1 = new SymbolInfo("abc", "INT");
//     auto s2 = new SymbolInfo("abcd", "INT");
//     auto f1 = new FunctionSymbolInfo("abcde", "INT", {});

//     scp.insert(s1);
//     cout << scp << endl;

//     scp.insert(s2);
//     cout << scp << endl;

//     scp.insert(f1);
//     cout << scp << endl;

//     auto f2 = scp.lookup("abcde");
//     cout << f2 << endl;
//     cout << *f2 << endl;
//     auto f3 = dynamic_cast<FunctionSymbolInfo *> (f2);

//     cout << f3 << endl;
//     cout << *f3 << endl;
//     cout << f3->getReturnType() << endl;
// }

int main(){
   TokenAST *t1 = new TokenAST(NodeType::TOKEN, "nothing", 1);
   t1->addChild(new TokenAST(NodeType::TOKEN, "anything", 1));
   ExpressionAST *e1 = new ExpressionAST(t1, "int");

   t1->removeAllChild();
   delete t1;

   e1->print(cout);
   delete e1;

   float f = 3.2;
   f++;
   cout << f << endl;
}