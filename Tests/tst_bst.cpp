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

    void testIsEqualIfSame();
    void testIsEqualIfSizeNotSame();
    void testIsEqualIfNodesNotSame();
    void testIsEqualIfEqual();

    void testFindIfExist();
    void testFindIfNotExit();

    void testEraseIfRoot();
    void testEraseIfNotRoot();

    void testCopyConstructor();
    void testCopyAssigment();
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

    QVERIFY(bst.size() == 7u);
}

void TestBST::testIsEqualIfSame()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);

    QVERIFY(bst == bst);
}

void TestBST::testIsEqualIfSizeNotSame()
{
    BST bst0;

    bst0.insert(4);
    bst0.insert(2);
    bst0.insert(1);
    bst0.insert(3);
    bst0.insert(10);
    bst0.insert(6);
    bst0.insert(7);

    BST bst1;

    bst1.insert(4);

    QVERIFY(bst0.size() != bst1.size());
    QVERIFY(bst0 != bst1);
}

void TestBST::testIsEqualIfNodesNotSame()
{
    BST bst0;

    bst0.insert(4);
    bst0.insert(2);
    bst0.insert(1);
    bst0.insert(3);
    bst0.insert(10);
    bst0.insert(6);
    bst0.insert(7);

    BST bst1;

    bst1.insert(4);
    bst1.insert(2);
    bst1.insert(1);
    bst1.insert(3);
    bst1.insert(10);
    bst1.insert(6);
    bst1.insert(8);

    QVERIFY(bst0.size() == bst1.size());
    QVERIFY(bst0 != bst1);
}

void TestBST::testIsEqualIfEqual()
{
    BST bst0;

    bst0.insert(4);
    bst0.insert(2);
    bst0.insert(1);
    bst0.insert(3);
    bst0.insert(10);
    bst0.insert(6);
    bst0.insert(7);

    BST bst1;

    bst1.insert(4);
    bst1.insert(2);
    bst1.insert(1);
    bst1.insert(3);
    bst1.insert(10);
    bst1.insert(6);
    bst1.insert(7);

    QVERIFY(bst0.size() == bst1.size());
    QVERIFY(bst0 == bst1);
}

void TestBST::testFindIfExist()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);

    QVERIFY(bst.find(7));
}

void TestBST::testFindIfNotExit()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);

    QVERIFY(!bst.find(99));
}

void TestBST::testEraseIfRoot()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);

    bst.erase(4);

    BST reference;
    reference.insert(6);
    reference.insert(2);
    reference.insert(1);
    reference.insert(3);
    reference.insert(10);
    reference.insert(7);

    QVERIFY(bst.size() == reference.size());
    QVERIFY(bst == reference);
}

void TestBST::testEraseIfNotRoot()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);

    bst.erase(6);

    BST reference;
    reference.insert(4);
    reference.insert(2);
    reference.insert(1);
    reference.insert(3);
    reference.insert(10);
    reference.insert(7);

    QVERIFY(bst.size() == reference.size());
    QVERIFY(bst == reference);
}

void TestBST::testCopyConstructor()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);

    BST result(bst);

    QVERIFY(bst.size() == result.size());
    QVERIFY(bst == result);
}

void TestBST::testCopyAssigment()
{
    BST actual;
    actual.insert(10);

    BST expected;

    expected.insert(4);
    expected.insert(2);
    expected.insert(1);
    expected.insert(3);
    expected.insert(10);
    expected.insert(6);
    expected.insert(7);

    actual = expected;

    QCOMPARE(actual.size(), expected.size());
    QVERIFY(actual == expected);
}


QTEST_APPLESS_MAIN(TestBST)

#include "tst_bst.moc"
