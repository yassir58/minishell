
RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

function exec_test ()
{
    BASH_TEST=$(./echo $@ > BASH_FILE)
    MINS_TEST=$(echo $@ > MINS_FILE)
    RES=$(diff BASH_FILE MINS_FILE)
    if [ "$RES" == "" ]; then
        printf "$RESET test [$@] $GREEN\t\tpassed\n"
    else
        printf "$RESET test [$@] $REED\t\tfailed\n"
    fi
}

function test_pwd ()
{
    $($@)
    MINS_TEST=$(./pwd > MINS_FILE)
    BASH_TEST=$(pwd > BASH_FILE)
    RES=$(diff BASH_FILE MINS_FILE)
    cat MINS_FILE BASH_FILE
    if [ "$RES" == "" ]; then
        printf "$RESET test $GREEN\t\tpassed\n"
    else
        printf "$RESET test $REED\t\tfailed\n"
    fi
}

printf "$YELLOW testing [echo] ....\n"
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'
printf "$YELLOW testing [pwd] ...\n$RESET"
test_pwd
