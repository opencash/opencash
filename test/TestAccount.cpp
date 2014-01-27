#include "opencash/model/Account.h"
#include "opencash/model/Split.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

IMPORT_ALIAS(Account);
IMPORT_ALIAS(Split);

using InSequence = ::testing::InSequence;

const std::string A_UUID = "a_uuid";
const std::string ANOTHER_UUID = "another_uuid";
const std::string YET_ANOTHER_UUID = "yet_another_uuid";

TEST(TestAccount, shouldAllowOneParent) {
  // given
  AccountPtr parentAcc(new Account(A_UUID));
  parentAcc->setName("parent");

  AccountPtr childAcc(new Account(ANOTHER_UUID));
  childAcc->setName("child");

  // when
  childAcc->setParent(parentAcc);

  // then
  ASSERT_EQ(parentAcc, childAcc->getParent());
}

TEST(TestAccount, shouldAllowMultipleChildren) {
  // given
  AccountPtr parentAcc(new Account(A_UUID));
  parentAcc->setName("parent");

  AccountPtr childAcc1(new Account(ANOTHER_UUID));
  childAcc1->setName("child1");

  AccountPtr childAcc2(new Account(YET_ANOTHER_UUID));
  childAcc2->setName("child2");

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);

  // then
  ASSERT_EQ(childAcc1, parentAcc->getChildren().at(0).lock());
  ASSERT_EQ(childAcc2, parentAcc->getChildren().at(1).lock());
  ASSERT_EQ(2, parentAcc->getChildren().size());
}

TEST(TestAccount, shouldRemoveChildWhenSettingParentToNull) {
  // given
  AccountPtr parentAcc(new Account(A_UUID));
  parentAcc->setName("parent");

  AccountPtr childAcc1(new Account(ANOTHER_UUID));
  childAcc1->setName("child1");

  AccountPtr childAcc2(new Account(YET_ANOTHER_UUID));
  childAcc2->setName("child2");

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);
  childAcc1->setParent(NULL);

  // then
  ASSERT_EQ(childAcc2, parentAcc->getChildren().at(0).lock());
  ASSERT_EQ(1, parentAcc->getChildren().size());
}

TEST(TestAccount, shouldCompareEqualityBasedOnlyOnUuid) {
  // given
  Account a1(A_UUID);
  a1.setName("a1");

  Account a2(A_UUID);
  a2.setName("a2");

  Account another1(ANOTHER_UUID);
  another1.setName("another1");

  Account another2(ANOTHER_UUID);
  another2.setName("another2");

  Account a1DiffUuid(ANOTHER_UUID);
  a1DiffUuid.setName("a1");

  // when

  // then
  ASSERT_TRUE(a1 == a1);
  ASSERT_TRUE(a1 == a2);
  ASSERT_FALSE(a1 == another1);
  ASSERT_FALSE(a1 == another2);
  ASSERT_TRUE(another1 == another2);
  ASSERT_FALSE(a1 == a1DiffUuid);
}

TEST(TestTransaction, shouldAddSplitIntoAccount) {
  //given
  AccountPtr account(new Account(A_UUID));
  SplitPtr split1(new Split(ANOTHER_UUID));
  SplitPtr split2(new Split(YET_ANOTHER_UUID));

  //when
  account->addSplit(split1);
  account->addSplit(split2);

  //then
  const Splits& splits = account->getSplits();
  ASSERT_EQ(2, splits.size());
  ASSERT_EQ(split1, splits[0]);
  ASSERT_EQ(split2, splits[1]);
}

TEST(TestAccount, shouldNotTriggerParentChangedWhenSettingToSameParent) {
  // given
  AccountPtr parentAcc(new Account(A_UUID));
  AccountPtr parentAccRef(parentAcc);

  AccountPtr childAcc1(new Account(ANOTHER_UUID));
  MockModelObserver childObs1(*childAcc1);

  {
    InSequence dummy;

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(childObs1, didChange("parent"));
  }

  // when
  childAcc1->setParent(parentAcc);
  childAcc1->setParent(parentAccRef);

  // then
  // mock expectations implicitly verified
}

TEST(TestAccount, shouldTriggerMemberObserverEvents) {
  // given
  Account acc(A_UUID);
  MockModelObserver obs(acc);

  {
    InSequence dummy;

    EXPECT_CALL(obs, willChange("name"));
    EXPECT_CALL(obs, didChange("name"));

    EXPECT_CALL(obs, willChange("descr"));
    EXPECT_CALL(obs, didChange("descr"));

    EXPECT_CALL(obs, willChange("type"));
    EXPECT_CALL(obs, didChange("type"));
  }

  // when
  acc.setName("A name");
  acc.setDescr("A descr");
  acc.setType(Account::AccountType::Asset);

  // then
  // mock expectations implicitly verified
}

TEST(TestAccount, shouldTriggerParentChildrenObserverEvents) {
  // given
  AccountPtr parentAcc(new Account(A_UUID));
  MockModelObserver parentObs(*parentAcc);

  AccountPtr childAcc1(new Account(ANOTHER_UUID));
  MockModelObserver childObs1(*childAcc1);

  AccountPtr childAcc2(new Account(YET_ANOTHER_UUID));
  MockModelObserver childObs2(*childAcc2);

  {
    using opencash::model::ObservableModel::ChangeType::Insertion;
    using opencash::model::ObservableModel::ChangeType::Removal;

    InSequence dummy;

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 0, Insertion));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 0, Insertion));
    EXPECT_CALL(childObs1, didChange("parent"));

    EXPECT_CALL(childObs2, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 1, Insertion));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 1, Insertion));
    EXPECT_CALL(childObs2, didChange("parent"));

    EXPECT_CALL(childObs2, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 1, Removal));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 1, Removal));
    EXPECT_CALL(childObs2, didChange("parent"));

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 0, Removal));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 0, Removal));
    EXPECT_CALL(childObs1, didChange("parent"));
  }

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);
  childAcc2->setParent(NULL);
  childAcc1->setParent(NULL);

  // then
  // mock expectations implicitly verified
}
