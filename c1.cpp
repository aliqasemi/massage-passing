#include "preproccesor.h"

using namespace std ;

int main(){

    sleep(1) ;


    //we go to open queue
    mqd_t c1 = mq_open(NAME_1, O_RDWR);

    //check for do not make queue
    if(c1 == -1){
        cout<<"Queue failed ; error number: "<<errno<<endl;
    }

    //define one queue for  consumer1
    struct my_message_c1 queue_c1 ;

    //make boolean attribute for show number of c2
    bool firstCycle = true;

    //go to get number from producer and sent accept massage
    for (int i = 0; i < NUM_1 ; i++) {

        //make boolean attribute for check  the massage reach or no reach
        bool b = true ;
        mq_receive(c1, (char *) &queue_c1, sizeof(my_message_c1), NULL);

        while (b) {

            if (i == 0 && firstCycle) {
                cout << "Consumer c1 has :" << queue_c1.number_of_number << " number" << endl;
                firstCycle = false;
            }

            if(queue_c1.flag[i] == 0) {
                cout << "Consumer c1 get number : " << queue_c1.number[i] << " from producer." << endl;
            }

            queue_c1.flag[i] = 1;

            mq_send(c1, (char *) &queue_c1, sizeof(queue_c1), 0);

            //sleep(3) ;

            mq_receive(c1, (char *) &queue_c1, sizeof(my_message_c1), NULL);

            if (queue_c1.flag[i] == 1){
                b = true ;
            } else{
                b = false ;
            }
        }

    }

    mq_close(c1);

    return 0 ;
}