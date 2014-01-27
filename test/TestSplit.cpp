#include "opencash/model/Split.h"
#include "opencash/model/Transaction.h"
#include "opencash/model/Account.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

IMPORT_ALIAS(Split);
IMPORT_ALIAS(Transaction);
IMPORT_ALIAS(Account);

using namespace testing;

const std::string UUID1 = "uuid 1";
const std::string UUID2 = "uuid 2";
const std::string UUID3 = "uuid 3";

TEST(TestSplit, shouldTriggerMemberObserverEvents) {
  // given
  SplitPtr split(new Split(UUID1));
  TransactionPtr transaction(new Transaction(UUID2));
  AccountPtr account(new Account(UUID3));
  MockModelObserver obs(*split);

  {
    InSequence dummy;

    EXPECT_CALL(obs, willChange("transaction"));
    EXPECT_CALL(obs, didChange("transaction"));

    EXPECT_CALL(obs, willChange("account"));
    EXPECT_CALL(obs, didChange("account"));

    EXPECT_CALL(obs, willChange("memo"));
    EXPECT_CALL(obs, didChange("memo"));

    EXPECT_CALL(obs, willChange("action"));
    EXPECT_CALL(obs, didChange("action"));

    EXPECT_CALL(obs, willChange("value"));
    EXPECT_CALL(obs, didChange("value"));
  }

  // when
  split->setTransaction(transaction);
  split->setAccount(account);
  split->setMemo("memo");
  split->setAction("action");
  split->setValue(1234);

  // then
  // mock expectations implicitly verified
}

TEST(TestSplit, shouldAddSplitIntoTransaction) {
  // given
  SplitPtr split(new Split(UUID1));
  TransactionPtr transaction(new Transaction(UUID2));

  // when
  split->setTransaction(transaction);

  // then
  ASSERT_EQ(1, transaction->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromTransactionWhenChagingToNull) {
  // given
  SplitPtr split(new Split(UUID1));
  TransactionPtr transaction(new Transaction(UUID2));
  split->setTransaction(transaction);

  // when
  split->setTransaction(TransactionWeakPtr());

  // then
  ASSERT_EQ(0, transaction->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromTransactionAndInsertIntoAnotherTransaction) {
  // given
  SplitPtr split(new Split(UUID1));
  TransactionPtr tx1(new Transaction(UUID2));
  TransactionPtr tx2(new Transaction(UUID3));
  split->setTransaction(tx1);

  // when
  split->setTransaction(tx2);

  // then
  ASSERT_EQ(0, tx1->getSplits().size());
  ASSERT_EQ(1, tx2->getSplits().size());
}

TEST(TestSplit, shouldAddSplitIntoAccount) {
  // given
  SplitPtr split(new Split(UUID1));
  AccountPtr account(new Account(UUID2));

  // when
  split->setAccount(account);

  // then
  ASSERT_EQ(1, account->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromAccountWhenChagingToNull) {
  // given
  SplitPtr split(new Split(UUID1));
  AccountPtr account(new Account(UUID2));
  split->setAccount(account);

  // when
  split->setAccount(AccountWeakPtr());

  // then
  ASSERT_EQ(0, account->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromAccountAndInsertIntoAnotherAccount) {
  // given
  SplitPtr split(new Split(UUID1));
  AccountPtr acc1(new Account(UUID2));
  AccountPtr acc2(new Account(UUID3));
  split->setAccount(acc1);

  // when
  split->setAccount(acc2);

  // then
  ASSERT_EQ(0, acc1->getSplits().size());
  ASSERT_EQ(1, acc2->getSplits().size());
}
