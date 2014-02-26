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

TEST(TestSplit, shouldTriggerMemberObserverEvents) {
  // given
  SplitPtr split(new Split());
  TransactionPtr transaction(new Transaction());
  AccountPtr account(new Account());
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
  SplitPtr split(new Split());
  TransactionPtr transaction(new Transaction());

  // when
  split->setTransaction(transaction);

  // then
  ASSERT_EQ(1, transaction->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromTransactionWhenChagingToNull) {
  // given
  SplitPtr split(new Split());
  TransactionPtr transaction(new Transaction());
  split->setTransaction(transaction);

  // when
  split->setTransaction(TransactionWeakPtr());

  // then
  ASSERT_EQ(0, transaction->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromTransactionAndInsertIntoAnotherTransaction) {
  // given
  SplitPtr split(new Split());
  TransactionPtr tx1(new Transaction());
  TransactionPtr tx2(new Transaction());
  split->setTransaction(tx1);

  // when
  split->setTransaction(tx2);

  // then
  ASSERT_EQ(0, tx1->getSplits().size());
  ASSERT_EQ(1, tx2->getSplits().size());
}

TEST(TestSplit, shouldAddSplitIntoAccount) {
  // given
  SplitPtr split(new Split());
  AccountPtr account(new Account());

  // when
  split->setAccount(account);

  // then
  ASSERT_EQ(1, account->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromAccountWhenChagingToNull) {
  // given
  SplitPtr split(new Split());
  AccountPtr account(new Account());
  split->setAccount(account);

  // when
  split->setAccount(AccountWeakPtr());

  // then
  ASSERT_EQ(0, account->getSplits().size());
}

TEST(TestSplit, shouldRemoveSplitFromAccountAndInsertIntoAnotherAccount) {
  // given
  SplitPtr split(new Split());
  AccountPtr acc1(new Account());
  AccountPtr acc2(new Account());
  split->setAccount(acc1);

  // when
  split->setAccount(acc2);

  // then
  ASSERT_EQ(0, acc1->getSplits().size());
  ASSERT_EQ(1, acc2->getSplits().size());
}
