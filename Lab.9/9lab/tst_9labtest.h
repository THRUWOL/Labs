#ifndef TST_9LABTEST_H
#define TST_9LABTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lockcontroller.h>
#include <IKeypad.h>
#include <ILatch.h>

using namespace testing;

class MockIKeypad : public IKeypad
{
public:
    MOCK_METHOD(bool, isActive,(),(override));
    MOCK_METHOD(void, wait,(),(override));
    MOCK_METHOD(PasswordResponse, requestPassword,(),(override));
};
class MockILatch : public ILatch
{
public:
    MOCK_METHOD(bool, isActive,(),(override));
    MOCK_METHOD(DoorStatus, open,(),(override));
    MOCK_METHOD(DoorStatus, close,(),(override));
    MOCK_METHOD(DoorStatus, getDoorStatus,(),(override));
};

// ТЕСТ 1
TEST(LockController, WAIT)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    EXPECT_CALL(keypad, wait()).Times(1).WillOnce(Return());
    lock->wait();
    delete lock;
}

// ТЕСТ 2
TEST(LockController, DOORCLOSED)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    EXPECT_CALL(latch, getDoorStatus()).Times(1).WillOnce(Return(DoorStatus::CLOSE));


    bool result = lock->isDoorOpen();
    ASSERT_FALSE(result);
    delete lock;
}

// ТЕСТ 3
TEST(LockController, DOOROPEN)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    EXPECT_CALL(latch, getDoorStatus()).Times(1).WillOnce(Return(DoorStatus::OPEN));
    bool result = lock->isDoorOpen();
    ASSERT_TRUE(result);
    delete lock;
}

// ТЕСТ 4
TEST(LockController, UNLOCKDOOR)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    EXPECT_CALL(latch, open()).Times(1).WillOnce(Return(DoorStatus::OPEN));
    DoorStatus res = lock->unlockDoor();
    ASSERT_EQ(res, DoorStatus::OPEN);
    delete lock;

}

// ТЕСТ 5
TEST(LockController, LOCKDOOR)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    EXPECT_CALL(latch, close()).Times(1).WillOnce(Return(DoorStatus::CLOSE));
    DoorStatus res = lock->lockDoor();
    ASSERT_EQ(res, DoorStatus::CLOSE);
    delete lock;
}

// ТЕСТ 6
TEST(LockController, CHECKHARDWARE_OK)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    EXPECT_CALL(keypad, isActive()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(latch, isActive()).Times(1).WillOnce(Return(true));
    HardWareStatus res = lock->hardWareCheck();
    ASSERT_EQ(res, HardWareStatus::OK);
    delete lock;
}

// ТЕСТ 7
TEST(LockController, CHECKHARDWARE_KEYPAD_ERROR)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(nullptr, &latch);
    EXPECT_CALL(keypad, isActive()).Times(AtLeast(0)).WillOnce(Return(true));
    EXPECT_CALL(latch, isActive()).Times(AtLeast(0)).WillOnce(Return(true));
    HardWareStatus res = lock->hardWareCheck();
    ASSERT_EQ(res, HardWareStatus::ERROR);
    delete lock;
}

// ТЕСТ 8
TEST(LockController, CHECKHARDWARE_LATCH_ERROR)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    EXPECT_CALL(keypad, isActive()).Times(AtLeast(0)).WillOnce(Return(true));
    EXPECT_CALL(latch, isActive()).Times(AtLeast(0)).WillOnce(Return(false));
    HardWareStatus res = lock->hardWareCheck();
    ASSERT_EQ(res, HardWareStatus::ERROR);
    delete lock;
}

// ТЕСТ 9
TEST(LockController, PASSWORD_CHECK_OK)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    PasswordResponse pr;
    pr.status = PasswordResponse::Status::OK;
    pr.password = "0000";
    EXPECT_CALL(keypad, requestPassword()).Times(AtLeast(0)).WillOnce(Return(pr));
    bool res = lock->isCorrectPassword();
    ASSERT_TRUE(res);
    delete lock;
}

// ТЕСТ 10
TEST(LockController, PASSWORD_CHECK_WRONG)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController *lock = new LockController(&keypad, &latch);
    PasswordResponse pr;
    pr.status = PasswordResponse::Status::OK;
    pr.password = "1111";
    EXPECT_CALL(keypad, requestPassword()).Times(AtLeast(0)).WillOnce(Return(pr));
    bool res = lock->isCorrectPassword();
    ASSERT_FALSE(res);
    delete lock;
}

// ТЕСТ 11
TEST(LockController, PASSWORD_CHECK_RESET)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController controller(&keypad, &latch);
    PasswordResponse user_input_old;
    user_input_old.status = PasswordResponse::Status::OK;
    user_input_old.password = "0000";
    PasswordResponse user_input_new;
    user_input_new.status = PasswordResponse::Status::OK;
    user_input_new.password = "1111";
    EXPECT_CALL(keypad, requestPassword()).Times(3).WillOnce(Return(user_input_old)).WillOnce(Return(user_input_new)).WillOnce(Return(user_input_new));
    controller.resetPassword();
    bool correct_password = controller.isCorrectPassword();
    ASSERT_TRUE(correct_password);
}

// ТЕСТ 12
TEST(LockController, PASSWORD_CHECK_RESET_TWICE)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController controller(&keypad, &latch);
    PasswordResponse user_input_old;
    user_input_old.status = PasswordResponse::Status::OK;
    user_input_old.password = "0000";
    PasswordResponse user_input_new;
    user_input_new.status = PasswordResponse::Status::OK;
    user_input_new.password = "9876";
    EXPECT_CALL(keypad, requestPassword()).Times(4).WillOnce(Return(user_input_old)).WillOnce(Return(user_input_new)).WillOnce(Return(user_input_old)).WillOnce(Return(user_input_new)) ;
    controller.resetPassword();
    user_input_old.password = user_input_new.password;
    user_input_new.password = "1111";
    controller.resetPassword();
    bool correct_password = controller.isCorrectPassword();
    ASSERT_TRUE(correct_password);
}
#endif // TST_TESTDIVISIONBYZERO_H
