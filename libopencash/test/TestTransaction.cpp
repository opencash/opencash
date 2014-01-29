#include "opencash/model/Transaction.h"
#include "opencash/model/Split.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

IMPORT_ALIAS(Transaction);
IMPORT_ALIAS(Split);

using namespace testing;

const std::string UUID1 = "uuid 1";
const std::string UUID2 = "uuid 2";
const std::string UUID3 = "uuid 3";

TEST(TestTransaction, shouldCompareEqualityBasedOnlyOnUuid) {
  //given
  Transaction tx1(UUID1);
  tx1.setDescription("transaction one");

  Transaction tx2(UUID1);
  tx2.setDescription("transaction two");

  Transaction tx3(UUID2);
  tx3.setDescription("transaction three");

  //when

  //then
  ASSERT_EQ(tx1, tx2);
  ASSERT_NE(tx1, tx3);
  ASSERT_NE(tx2, tx3);
}

TEST(TestTransaction, shouldAddSplitIntoTransaction) {
  //given
  TransactionPtr transaction(new Transaction(UUID1));
  SplitPtr split1(new Split(UUID2));
  SplitPtr split2(new Split(UUID3));

  //when
  transaction->addSplit(split1);
  transaction->addSplit(split2);

  //then
  const Splits& splits = transaction->getSplits();
  ASSERT_EQ(2, splits.size());
  ASSERT_EQ(split1, splits[0]);
  ASSERT_EQ(split2, splits[1]);
}

TEST(TestTransaction, shouldRemoveSplitFromTransaction) {
  //given
  TransactionPtr transaction(new Transaction(UUID1));
  SplitPtr split1(new Split(UUID2));
  SplitPtr split2(new Split(UUID3));
  transaction->addSplit(split1);
  transaction->addSplit(split2);

  //when
  transaction->removeSplit(split2);

  //then
  const Splits& splits = transaction->getSplits();
  ASSERT_EQ(1, splits.size());
  ASSERT_EQ(split1, splits[0]);
  // ASSERT_EQ(split2, splits[1]);
}

TEST(TestTransaction, shouldSetTransactionInSplitWhenAddingSplit) {
  //given
  TransactionPtr transaction(new Transaction(UUID1));
  SplitPtr split1(new Split(UUID2));

  //when
  transaction->addSplit(split1);

  //then
  ASSERT_EQ(transaction, split1->getTransaction().lock());
}

TEST(TestTransaction, shouldTriggerMemberObserverEvents) {
  // given
  TransactionPtr transaction(new Transaction(UUID1));
  SplitPtr split1(new Split(UUID2));
  SplitPtr split2(new Split(UUID3));
  MockModelObserver obs(*transaction);

  {
    InSequence dummy;

    EXPECT_CALL(obs, willChangeAtIndex("splits", 0, ObservableModel::ChangeType::Insertion));
    EXPECT_CALL(obs, didChangeAtIndex("splits", 0, ObservableModel::ChangeType::Insertion));

    EXPECT_CALL(obs, willChange("description"));
    EXPECT_CALL(obs, didChange("description"));

    EXPECT_CALL(obs, willChangeAtIndex("splits", 1, ObservableModel::ChangeType::Insertion));
    EXPECT_CALL(obs, didChangeAtIndex("splits", 1, ObservableModel::ChangeType::Insertion));

    EXPECT_CALL(obs, willChangeAtIndex("splits", 0, ObservableModel::ChangeType::Removal));
    EXPECT_CALL(obs, didChangeAtIndex("splits", 0, ObservableModel::ChangeType::Removal));
  }

  // when
  transaction->addSplit(split1);
  transaction->setDescription("desc");
  transaction->addSplit(split2);
  transaction->removeSplit(split1);

  // then
  // mock expectations implicitly verified
}

