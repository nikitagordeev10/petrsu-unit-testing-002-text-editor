#include "load_tests.h"
#include "move_tests.h"
#include "mpweb_tests.h"
#include "rn_tests.h"
#include "save_tests.h"
#include "show_tests.h"
#include "showunderscores_tests.h"
#include "load_tests.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
