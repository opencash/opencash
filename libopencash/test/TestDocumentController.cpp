#include "opencash/controller/DocumentController.h"
#include "opencash/model/Account.h"
#include "opencash/model/Split.h"
#include "opencash/model/Transaction.h"
#include "opencash/model/AccountsMeta.h"
#include "opencash/model/TransactionsMeta.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using DocumentController = opencash::controller::DocumentController;
using AccountsMeta = opencash::model::AccountsMeta;

IMPORT_ALIAS(Account);
IMPORT_ALIAS(Split);
IMPORT_ALIAS(Transaction);

using InSequence = ::testing::InSequence;

const std::string DBFILENAME = ":memory:";
// const std::string DBFILENAME = "Test.db";

class TestDocumentController : public ::testing::Test {
  protected:
    std::unique_ptr<DocumentController> _doc;

    TestDocumentController()
      : _doc(new DocumentController(DBFILENAME, true))
    {}

    AccountPtr createAnAssetAccount()
    {
      AccountPtr ret = _doc->newAccount();
      ret->setName("test account");
      ret->setDescr("This is my first asset account");
      ret->setType(Account::AccountType::Asset);
      return ret;
    }

    SplitPtr createSplit() {
      return _doc->newSplit();
    }

    TransactionPtr createTransaction() {
      return _doc->newTransaction();
    }
};

TEST_F(TestDocumentController, shouldInitializeWithRootAccount) {
  ASSERT_EQ(1, _doc->getAccountsMeta()->getCount());
  ASSERT_EQ(Account::AccountType::Root, _doc->retrieveAccounts().at(0)->getType());
}

TEST_F(TestDocumentController, shouldPersistOneAccount) {
  // given
  AccountPtr acc = createAnAssetAccount();

  // when
  _doc->persistAccount(*acc);

  // then
  ASSERT_EQ(2, _doc->getAccountsMeta()->getCount());
}

TEST_F(TestDocumentController, shouldPersistTwoAccounts) {
  // given
  AccountPtr acc = createAnAssetAccount();
  AccountPtr acc2 = createAnAssetAccount();

  // when
  _doc->persistAccount(*acc);
  _doc->persistAccount(*acc2);

  // then
  ASSERT_EQ(3, _doc->getAccountsMeta()->getCount());
}

TEST_F(TestDocumentController, shouldRetrieveAccounts) {
  // given
  AccountPtr acc = createAnAssetAccount();
  AccountPtr acc2 = createAnAssetAccount();
  _doc->persistAccount(*acc);
  _doc->persistAccount(*acc2);

  // when
  Accounts accounts = _doc->retrieveAccounts();

  // then
  ASSERT_EQ(3, accounts.size());
  ASSERT_EQ(*acc, *(accounts.at(1)));
  ASSERT_EQ(*acc2, *(accounts.at(2)));
}

TEST_F(TestDocumentController, shouldUpdateAccountsMetaAndFireEvents) {
  // given
  AccountsMeta *accMeta = _doc->getAccountsMeta();
  MockModelObserver obs(*accMeta);
  {
    InSequence dummy;
    EXPECT_CALL(obs, willChange("count"));
    EXPECT_CALL(obs, didChange("count"));
  }
  AccountPtr acc = createAnAssetAccount();

  // when
  _doc->persistAccount(*acc);

  // then (mock expectations implicitly verified)
}

TEST_F(TestDocumentController, shouldLoadSplitsFromAPersistedAccount) {
  {
    AccountPtr account = createAnAssetAccount();
    TransactionPtr transaction = createTransaction();
    SplitPtr split1 = createSplit();
    SplitPtr split2 = createSplit();

    transaction->setDescription("transaction");

    split1->setValue(1234.0);
    split1->setMemo("memo: my split 1");
    split1->setAction("action: my split 1");

    split2->setValue(4321.0);
    split2->setMemo("memo: my split 2");
    split2->setAction("action: my split 2");

    account->addSplit(split1);
    transaction->addSplit(split1);

    account->addSplit(split2);
    transaction->addSplit(split2);

    ASSERT_EQ(2, transaction->getSplits().size());
    ASSERT_EQ(2, account->getSplits().size());

    _doc->persistAccount(*account);
    _doc->persistTransaction(*transaction);
    _doc->persistSplit(*split1);
    _doc->persistSplit(*split2);
  }

  {
    Accounts accounts = _doc->retrieveAccounts();
    ASSERT_EQ(2, accounts.size());

    Splits splits = accounts[1]->getSplits();
    ASSERT_EQ(2, splits.size());
    ASSERT_EQ(splits[0]->getAccount().lock(), splits[1]->getAccount().lock());
  }
}

TEST_F(TestDocumentController, shouldLoadSplitsFromAPersistedTransaction) {
  {
    AccountPtr account = createAnAssetAccount();
    TransactionPtr transaction = createTransaction();
    SplitPtr split1 = createSplit();
    SplitPtr split2 = createSplit();

    transaction->setDescription("transaction");

    split1->setValue(1234.0);
    split1->setMemo("memo: my split 1");
    split1->setAction("action: my split 1");

    split2->setValue(4321.0);
    split2->setMemo("memo: my split 2");
    split2->setAction("action: my split 2");

    account->addSplit(split1);
    transaction->addSplit(split1);

    account->addSplit(split2);
    transaction->addSplit(split2);

    ASSERT_EQ(2, transaction->getSplits().size());
    ASSERT_EQ(2, account->getSplits().size());

    _doc->persistAccount(*account);
    _doc->persistTransaction(*transaction);
    _doc->persistSplit(*split1);
    _doc->persistSplit(*split2);
  }

  {
    Transactions transactions = _doc->retrieveTransactions();
    ASSERT_EQ(1, transactions.size());

    Splits splits = transactions[0]->getSplits();
    ASSERT_EQ(2, splits.size());
    ASSERT_EQ(splits[0]->getTransaction().lock(), splits[1]->getTransaction().lock());
  }
}
