#include <QtTest>

#include "BinarySearchTree.h"

using BST = typename Custom::BinarySearchTree<int>;

class TestBST : public QObject
{
    Q_OBJECT

public:
    TestBST();
    ~TestBST();

private slots:
    void testInsert();
};

TestBST::TestBST()
{
}

TestBST::~TestBST()
{
}

void TestBST::testInsert()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);


}

QTEST_APPLESS_MAIN(TestBST)

#include "tst_bst.moc"
