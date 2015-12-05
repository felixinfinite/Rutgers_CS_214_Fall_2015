#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <pthread.h>
#define NAME_MAX_LENGTH 101
#define REQUEST_MES_LENGTH 101
#define RESPONSE_MES_LENGTH 300
#define AMOUNT_SIZE 100
#define MAX_ACCOUNT 20
enum response_error_code_t{
        SUCCESS,
        CANNOT_OPEN,
        CANNOT_START,
        CLIENT_NOT_IN_SESSION,
        ACCOUNT_UNFOUND,
        BALANCE_REACH_ZERO,
        CONNECTION_TIME_OUT,
        ACCOUNT_EXIT
};
typedef struct response_t{
    int code;
    char message[RESPONSE_MES_LENGTH];
} response_t;

// Read and write request code as character!
enum client_request_code_t{
        OPEN ,
        START ,
        CREDIT,
        DEBIT,
        BALANCE ,
        FINISH ,
        EXIT
};
typedef struct request_t{
    int code;  
    union {
        char name[NAME_MAX_LENGTH];
        char amount[AMOUNT_SIZE];
    } message;
} request_t;
/* An account structure to be stored online */
typedef struct account_t{
    char name[NAME_MAX_LENGTH];
    float balance;
    // Session mutex lock
    pthread_mutex_t account_session_mutex;
    enum {NOT_IN_SESSION=0,IN_SESSION} in_session;
} account_t;

void account_open( account_t* account,char* name);
int account_debit(account_t* account, float credit_amount);
void account_credit(account_t* account, float debit_amount);
float account_balance( account_t* account);
int account_is_in_session(account_t* account);
// listen_request reads incoming request from the socket fd
int listen_request(request_t* request, int socket_fd);
void form_response(response_t* response, int code, char* message);


#endif
